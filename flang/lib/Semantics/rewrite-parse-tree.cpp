//===-- lib/Semantics/rewrite-parse-tree.cpp ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "rewrite-parse-tree.h"

#include "flang/Common/indirection.h"
#include "flang/Parser/parse-tree-visitor.h"
#include "flang/Parser/parse-tree.h"
#include "flang/Parser/tools.h"
#include "flang/Semantics/scope.h"
#include "flang/Semantics/semantics.h"
#include "flang/Semantics/symbol.h"
#include "flang/Semantics/tools.h"
#include <list>

namespace Fortran::semantics {

using namespace parser::literals;

/// Convert misidentified statement functions to array element assignments
/// or pointer-valued function result assignments.
/// Convert misidentified format expressions to namelist group names.
/// Convert misidentified character variables in I/O units to integer
/// unit number expressions.
/// Convert misidentified named constants in data statement values to
/// initial data targets
class RewriteMutator {
public:
  RewriteMutator(SemanticsContext &context)
      : context_{context}, errorOnUnresolvedName_{!context.AnyFatalError()},
        messages_{context.messages()} {}

  // Default action for a parse tree node is to visit children.
  template <typename T> bool Pre(T &) { return true; }
  template <typename T> void Post(T &) {}

  void Post(parser::Name &);
  bool Pre(parser::MainProgram &);
  bool Pre(parser::FunctionSubprogram &);
  bool Pre(parser::SubroutineSubprogram &);
  bool Pre(parser::SeparateModuleSubprogram &);
  bool Pre(parser::BlockConstruct &);
  bool Pre(parser::ActionStmt &);
  void Post(parser::ReadStmt &);
  void Post(parser::WriteStmt &);

  // Name resolution yet implemented:
  // TODO: Can some/all of these now be enabled?
  bool Pre(parser::EquivalenceStmt &) { return false; }
  bool Pre(parser::Keyword &) { return false; }
  bool Pre(parser::EntryStmt &) { return false; }
  bool Pre(parser::CompilerDirective &) { return false; }

  // Don't bother resolving names in end statements.
  bool Pre(parser::EndBlockDataStmt &) { return false; }
  bool Pre(parser::EndFunctionStmt &) { return false; }
  bool Pre(parser::EndInterfaceStmt &) { return false; }
  bool Pre(parser::EndModuleStmt &) { return false; }
  bool Pre(parser::EndMpSubprogramStmt &) { return false; }
  bool Pre(parser::EndProgramStmt &) { return false; }
  bool Pre(parser::EndSubmoduleStmt &) { return false; }
  bool Pre(parser::EndSubroutineStmt &) { return false; }
  bool Pre(parser::EndTypeStmt &) { return false; }

private:
  void FixMisparsedStmtFuncs(parser::SpecificationPart &, parser::Block &);

  SemanticsContext &context_;
  bool errorOnUnresolvedName_{true};
  parser::Messages &messages_;
};

// Check that name has been resolved to a symbol
void RewriteMutator::Post(parser::Name &name) {
  if (!name.symbol && errorOnUnresolvedName_) {
    messages_.Say(name.source, "Internal: no symbol found for '%s'"_err_en_US,
        name.source);
  }
}

static bool ReturnsDataPointer(const Symbol &symbol) {
  if (const Symbol * funcRes{FindFunctionResult(symbol)}) {
    return IsPointer(*funcRes) && !IsProcedure(*funcRes);
  } else if (const auto *generic{symbol.detailsIf<GenericDetails>()}) {
    for (auto ref : generic->specificProcs()) {
      if (ReturnsDataPointer(*ref)) {
        return true;
      }
    }
  }
  return false;
}

// Finds misparsed statement functions in a specification part, rewrites
// them into array element assignment statements, and moves them into the
// beginning of the corresponding (execution part's) block.
void RewriteMutator::FixMisparsedStmtFuncs(
    parser::SpecificationPart &specPart, parser::Block &block) {
  auto &list{std::get<std::list<parser::DeclarationConstruct>>(specPart.t)};
  auto origFirst{block.begin()}; // insert each elem before origFirst
  for (auto it{list.begin()}; it != list.end();) {
    bool convert{false};
    if (auto *stmt{std::get_if<
            parser::Statement<common::Indirection<parser::StmtFunctionStmt>>>(
            &it->u)}) {
      if (const Symbol *
          symbol{std::get<parser::Name>(stmt->statement.value().t).symbol}) {
        const Symbol &ultimate{symbol->GetUltimate()};
        convert =
            ultimate.has<ObjectEntityDetails>() || ReturnsDataPointer(ultimate);
        if (convert) {
          auto newStmt{stmt->statement.value().ConvertToAssignment()};
          newStmt.source = stmt->source;
          block.insert(origFirst,
              parser::ExecutionPartConstruct{
                  parser::ExecutableConstruct{std::move(newStmt)}});
        }
      }
    }
    if (convert) {
      it = list.erase(it);
    } else {
      ++it;
    }
  }
}

bool RewriteMutator::Pre(parser::MainProgram &program) {
  FixMisparsedStmtFuncs(std::get<parser::SpecificationPart>(program.t),
      std::get<parser::ExecutionPart>(program.t).v);
  return true;
}

bool RewriteMutator::Pre(parser::FunctionSubprogram &func) {
  FixMisparsedStmtFuncs(std::get<parser::SpecificationPart>(func.t),
      std::get<parser::ExecutionPart>(func.t).v);
  return true;
}

bool RewriteMutator::Pre(parser::SubroutineSubprogram &subr) {
  FixMisparsedStmtFuncs(std::get<parser::SpecificationPart>(subr.t),
      std::get<parser::ExecutionPart>(subr.t).v);
  return true;
}

bool RewriteMutator::Pre(parser::SeparateModuleSubprogram &subp) {
  FixMisparsedStmtFuncs(std::get<parser::SpecificationPart>(subp.t),
      std::get<parser::ExecutionPart>(subp.t).v);
  return true;
}

bool RewriteMutator::Pre(parser::BlockConstruct &block) {
  FixMisparsedStmtFuncs(std::get<parser::BlockSpecificationPart>(block.t).v,
      std::get<parser::Block>(block.t));
  return true;
}

// Rewrite PRINT NML -> WRITE(*,NML=NML)
bool RewriteMutator::Pre(parser::ActionStmt &x) {
  if (auto *print{std::get_if<common::Indirection<parser::PrintStmt>>(&x.u)};
      print &&
      std::get<std::list<parser::OutputItem>>(print->value().t).empty()) {
    auto &format{std::get<parser::Format>(print->value().t)};
    if (std::holds_alternative<parser::Expr>(format.u)) {
      if (auto *name{parser::Unwrap<parser::Name>(format)}; name &&
          name->symbol && name->symbol->GetUltimate().has<NamelistDetails>() &&
          context_.IsEnabled(common::LanguageFeature::PrintNamelist)) {
        context_.Warn(common::LanguageFeature::PrintNamelist, name->source,
            "nonstandard: namelist in PRINT statement"_port_en_US);
        std::list<parser::IoControlSpec> controls;
        controls.emplace_back(std::move(*name));
        x.u = common::Indirection<parser::WriteStmt>::Make(
            parser::IoUnit{parser::Star{}}, std::optional<parser::Format>{},
            std::move(controls), std::list<parser::OutputItem>{});
      }
    }
  }
  return true;
}

// When a namelist group name appears (without NML=) in a READ or WRITE
// statement in such a way that it can be misparsed as a format expression,
// rewrite the I/O statement's parse tree node as if the namelist group
// name had appeared with NML=.
template <typename READ_OR_WRITE>
void FixMisparsedUntaggedNamelistName(READ_OR_WRITE &x) {
  if (x.iounit && x.format &&
      std::holds_alternative<parser::Expr>(x.format->u)) {
    if (const parser::Name * name{parser::Unwrap<parser::Name>(x.format)}) {
      if (name->symbol && name->symbol->GetUltimate().has<NamelistDetails>()) {
        x.controls.emplace_front(parser::IoControlSpec{std::move(*name)});
        x.format.reset();
      }
    }
  }
}

// READ(CVAR) [, ...] will be misparsed as UNIT=CVAR; correct
// it to READ CVAR [,...] with CVAR as a format rather than as
// an internal I/O unit for unformatted I/O, which Fortran does
// not support.
void RewriteMutator::Post(parser::ReadStmt &x) {
  if (x.iounit && !x.format && x.controls.empty()) {
    if (auto *var{std::get_if<parser::Variable>(&x.iounit->u)}) {
      const parser::Name &last{parser::GetLastName(*var)};
      DeclTypeSpec *type{last.symbol ? last.symbol->GetType() : nullptr};
      if (type && type->category() == DeclTypeSpec::Character) {
        x.format = common::visit(
            [](auto &&indirection) {
              return parser::Expr{std::move(indirection)};
            },
            std::move(var->u));
        x.iounit.reset();
      }
    }
  }
  FixMisparsedUntaggedNamelistName(x);
}

void RewriteMutator::Post(parser::WriteStmt &x) {
  FixMisparsedUntaggedNamelistName(x);
}

bool RewriteParseTree(SemanticsContext &context, parser::Program &program) {
  RewriteMutator mutator{context};
  parser::Walk(program, mutator);
  return !context.AnyFatalError();
}

} // namespace Fortran::semantics
