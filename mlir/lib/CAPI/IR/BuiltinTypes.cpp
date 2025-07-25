//===- BuiltinTypes.cpp - C Interface to MLIR Builtin Types ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "mlir-c/BuiltinTypes.h"
#include "mlir-c/AffineMap.h"
#include "mlir-c/IR.h"
#include "mlir-c/Support.h"
#include "mlir/CAPI/AffineMap.h"
#include "mlir/CAPI/IR.h"
#include "mlir/CAPI/Support.h"
#include "mlir/IR/AffineMap.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Types.h"

#include <algorithm>

using namespace mlir;

//===----------------------------------------------------------------------===//
// Integer types.
//===----------------------------------------------------------------------===//

MlirTypeID mlirIntegerTypeGetTypeID() { return wrap(IntegerType::getTypeID()); }

bool mlirTypeIsAInteger(MlirType type) {
  return llvm::isa<IntegerType>(unwrap(type));
}

MlirType mlirIntegerTypeGet(MlirContext ctx, unsigned bitwidth) {
  return wrap(IntegerType::get(unwrap(ctx), bitwidth));
}

MlirType mlirIntegerTypeSignedGet(MlirContext ctx, unsigned bitwidth) {
  return wrap(IntegerType::get(unwrap(ctx), bitwidth, IntegerType::Signed));
}

MlirType mlirIntegerTypeUnsignedGet(MlirContext ctx, unsigned bitwidth) {
  return wrap(IntegerType::get(unwrap(ctx), bitwidth, IntegerType::Unsigned));
}

unsigned mlirIntegerTypeGetWidth(MlirType type) {
  return llvm::cast<IntegerType>(unwrap(type)).getWidth();
}

bool mlirIntegerTypeIsSignless(MlirType type) {
  return llvm::cast<IntegerType>(unwrap(type)).isSignless();
}

bool mlirIntegerTypeIsSigned(MlirType type) {
  return llvm::cast<IntegerType>(unwrap(type)).isSigned();
}

bool mlirIntegerTypeIsUnsigned(MlirType type) {
  return llvm::cast<IntegerType>(unwrap(type)).isUnsigned();
}

//===----------------------------------------------------------------------===//
// Index type.
//===----------------------------------------------------------------------===//

MlirTypeID mlirIndexTypeGetTypeID() { return wrap(IndexType::getTypeID()); }

bool mlirTypeIsAIndex(MlirType type) {
  return llvm::isa<IndexType>(unwrap(type));
}

MlirType mlirIndexTypeGet(MlirContext ctx) {
  return wrap(IndexType::get(unwrap(ctx)));
}

//===----------------------------------------------------------------------===//
// Floating-point types.
//===----------------------------------------------------------------------===//

bool mlirTypeIsAFloat(MlirType type) {
  return llvm::isa<FloatType>(unwrap(type));
}

unsigned mlirFloatTypeGetWidth(MlirType type) {
  return llvm::cast<FloatType>(unwrap(type)).getWidth();
}

MlirTypeID mlirFloat4E2M1FNTypeGetTypeID() {
  return wrap(Float4E2M1FNType::getTypeID());
}

bool mlirTypeIsAFloat4E2M1FN(MlirType type) {
  return llvm::isa<Float4E2M1FNType>(unwrap(type));
}

MlirType mlirFloat4E2M1FNTypeGet(MlirContext ctx) {
  return wrap(Float4E2M1FNType::get(unwrap(ctx)));
}

MlirTypeID mlirFloat6E2M3FNTypeGetTypeID() {
  return wrap(Float6E2M3FNType::getTypeID());
}

bool mlirTypeIsAFloat6E2M3FN(MlirType type) {
  return llvm::isa<Float6E2M3FNType>(unwrap(type));
}

MlirType mlirFloat6E2M3FNTypeGet(MlirContext ctx) {
  return wrap(Float6E2M3FNType::get(unwrap(ctx)));
}

MlirTypeID mlirFloat6E3M2FNTypeGetTypeID() {
  return wrap(Float6E3M2FNType::getTypeID());
}

bool mlirTypeIsAFloat6E3M2FN(MlirType type) {
  return llvm::isa<Float6E3M2FNType>(unwrap(type));
}

MlirType mlirFloat6E3M2FNTypeGet(MlirContext ctx) {
  return wrap(Float6E3M2FNType::get(unwrap(ctx)));
}

MlirTypeID mlirFloat8E5M2TypeGetTypeID() {
  return wrap(Float8E5M2Type::getTypeID());
}

bool mlirTypeIsAFloat8E5M2(MlirType type) {
  return llvm::isa<Float8E5M2Type>(unwrap(type));
}

MlirType mlirFloat8E5M2TypeGet(MlirContext ctx) {
  return wrap(Float8E5M2Type::get(unwrap(ctx)));
}

MlirTypeID mlirFloat8E4M3TypeGetTypeID() {
  return wrap(Float8E4M3Type::getTypeID());
}

bool mlirTypeIsAFloat8E4M3(MlirType type) {
  return llvm::isa<Float8E4M3Type>(unwrap(type));
}

MlirType mlirFloat8E4M3TypeGet(MlirContext ctx) {
  return wrap(Float8E4M3Type::get(unwrap(ctx)));
}

MlirTypeID mlirFloat8E4M3FNTypeGetTypeID() {
  return wrap(Float8E4M3FNType::getTypeID());
}

bool mlirTypeIsAFloat8E4M3FN(MlirType type) {
  return llvm::isa<Float8E4M3FNType>(unwrap(type));
}

MlirType mlirFloat8E4M3FNTypeGet(MlirContext ctx) {
  return wrap(Float8E4M3FNType::get(unwrap(ctx)));
}

MlirTypeID mlirFloat8E5M2FNUZTypeGetTypeID() {
  return wrap(Float8E5M2FNUZType::getTypeID());
}

bool mlirTypeIsAFloat8E5M2FNUZ(MlirType type) {
  return llvm::isa<Float8E5M2FNUZType>(unwrap(type));
}

MlirType mlirFloat8E5M2FNUZTypeGet(MlirContext ctx) {
  return wrap(Float8E5M2FNUZType::get(unwrap(ctx)));
}

MlirTypeID mlirFloat8E4M3FNUZTypeGetTypeID() {
  return wrap(Float8E4M3FNUZType::getTypeID());
}

bool mlirTypeIsAFloat8E4M3FNUZ(MlirType type) {
  return llvm::isa<Float8E4M3FNUZType>(unwrap(type));
}

MlirType mlirFloat8E4M3FNUZTypeGet(MlirContext ctx) {
  return wrap(Float8E4M3FNUZType::get(unwrap(ctx)));
}

MlirTypeID mlirFloat8E4M3B11FNUZTypeGetTypeID() {
  return wrap(Float8E4M3B11FNUZType::getTypeID());
}

bool mlirTypeIsAFloat8E4M3B11FNUZ(MlirType type) {
  return llvm::isa<Float8E4M3B11FNUZType>(unwrap(type));
}

MlirType mlirFloat8E4M3B11FNUZTypeGet(MlirContext ctx) {
  return wrap(Float8E4M3B11FNUZType::get(unwrap(ctx)));
}

MlirTypeID mlirFloat8E3M4TypeGetTypeID() {
  return wrap(Float8E3M4Type::getTypeID());
}

bool mlirTypeIsAFloat8E3M4(MlirType type) {
  return llvm::isa<Float8E3M4Type>(unwrap(type));
}

MlirType mlirFloat8E3M4TypeGet(MlirContext ctx) {
  return wrap(Float8E3M4Type::get(unwrap(ctx)));
}

MlirTypeID mlirFloat8E8M0FNUTypeGetTypeID() {
  return wrap(Float8E8M0FNUType::getTypeID());
}

bool mlirTypeIsAFloat8E8M0FNU(MlirType type) {
  return llvm::isa<Float8E8M0FNUType>(unwrap(type));
}

MlirType mlirFloat8E8M0FNUTypeGet(MlirContext ctx) {
  return wrap(Float8E8M0FNUType::get(unwrap(ctx)));
}

MlirTypeID mlirBFloat16TypeGetTypeID() {
  return wrap(BFloat16Type::getTypeID());
}

bool mlirTypeIsABF16(MlirType type) {
  return llvm::isa<BFloat16Type>(unwrap(type));
}

MlirType mlirBF16TypeGet(MlirContext ctx) {
  return wrap(BFloat16Type::get(unwrap(ctx)));
}

MlirTypeID mlirFloat16TypeGetTypeID() { return wrap(Float16Type::getTypeID()); }

bool mlirTypeIsAF16(MlirType type) {
  return llvm::isa<Float16Type>(unwrap(type));
}

MlirType mlirF16TypeGet(MlirContext ctx) {
  return wrap(Float16Type::get(unwrap(ctx)));
}

MlirTypeID mlirFloatTF32TypeGetTypeID() {
  return wrap(FloatTF32Type::getTypeID());
}

bool mlirTypeIsATF32(MlirType type) {
  return llvm::isa<FloatTF32Type>(unwrap(type));
}

MlirType mlirTF32TypeGet(MlirContext ctx) {
  return wrap(FloatTF32Type::get(unwrap(ctx)));
}

MlirTypeID mlirFloat32TypeGetTypeID() { return wrap(Float32Type::getTypeID()); }

bool mlirTypeIsAF32(MlirType type) {
  return llvm::isa<Float32Type>(unwrap(type));
}

MlirType mlirF32TypeGet(MlirContext ctx) {
  return wrap(Float32Type::get(unwrap(ctx)));
}

MlirTypeID mlirFloat64TypeGetTypeID() { return wrap(Float64Type::getTypeID()); }

bool mlirTypeIsAF64(MlirType type) {
  return llvm::isa<Float64Type>(unwrap(type));
}

MlirType mlirF64TypeGet(MlirContext ctx) {
  return wrap(Float64Type::get(unwrap(ctx)));
}

//===----------------------------------------------------------------------===//
// None type.
//===----------------------------------------------------------------------===//

MlirTypeID mlirNoneTypeGetTypeID() { return wrap(NoneType::getTypeID()); }

bool mlirTypeIsANone(MlirType type) {
  return llvm::isa<NoneType>(unwrap(type));
}

MlirType mlirNoneTypeGet(MlirContext ctx) {
  return wrap(NoneType::get(unwrap(ctx)));
}

//===----------------------------------------------------------------------===//
// Complex type.
//===----------------------------------------------------------------------===//

MlirTypeID mlirComplexTypeGetTypeID() { return wrap(ComplexType::getTypeID()); }

bool mlirTypeIsAComplex(MlirType type) {
  return llvm::isa<ComplexType>(unwrap(type));
}

MlirType mlirComplexTypeGet(MlirType elementType) {
  return wrap(ComplexType::get(unwrap(elementType)));
}

MlirType mlirComplexTypeGetElementType(MlirType type) {
  return wrap(llvm::cast<ComplexType>(unwrap(type)).getElementType());
}

//===----------------------------------------------------------------------===//
// Shaped type.
//===----------------------------------------------------------------------===//

bool mlirTypeIsAShaped(MlirType type) {
  return llvm::isa<ShapedType>(unwrap(type));
}

MlirType mlirShapedTypeGetElementType(MlirType type) {
  return wrap(llvm::cast<ShapedType>(unwrap(type)).getElementType());
}

bool mlirShapedTypeHasRank(MlirType type) {
  return llvm::cast<ShapedType>(unwrap(type)).hasRank();
}

int64_t mlirShapedTypeGetRank(MlirType type) {
  return llvm::cast<ShapedType>(unwrap(type)).getRank();
}

bool mlirShapedTypeHasStaticShape(MlirType type) {
  return llvm::cast<ShapedType>(unwrap(type)).hasStaticShape();
}

bool mlirShapedTypeIsDynamicDim(MlirType type, intptr_t dim) {
  return llvm::cast<ShapedType>(unwrap(type))
      .isDynamicDim(static_cast<unsigned>(dim));
}

bool mlirShapedTypeIsStaticDim(MlirType type, intptr_t dim) {
  return llvm::cast<ShapedType>(unwrap(type))
      .isStaticDim(static_cast<unsigned>(dim));
}

int64_t mlirShapedTypeGetDimSize(MlirType type, intptr_t dim) {
  return llvm::cast<ShapedType>(unwrap(type))
      .getDimSize(static_cast<unsigned>(dim));
}

int64_t mlirShapedTypeGetDynamicSize() { return ShapedType::kDynamic; }

bool mlirShapedTypeIsDynamicSize(int64_t size) {
  return ShapedType::isDynamic(size);
}

bool mlirShapedTypeIsStaticSize(int64_t size) {
  return ShapedType::isStatic(size);
}

bool mlirShapedTypeIsDynamicStrideOrOffset(int64_t val) {
  return ShapedType::isDynamic(val);
}

bool mlirShapedTypeIsStaticStrideOrOffset(int64_t val) {
  return ShapedType::isStatic(val);
}

int64_t mlirShapedTypeGetDynamicStrideOrOffset() {
  return ShapedType::kDynamic;
}

//===----------------------------------------------------------------------===//
// Vector type.
//===----------------------------------------------------------------------===//

MlirTypeID mlirVectorTypeGetTypeID() { return wrap(VectorType::getTypeID()); }

bool mlirTypeIsAVector(MlirType type) {
  return llvm::isa<VectorType>(unwrap(type));
}

MlirType mlirVectorTypeGet(intptr_t rank, const int64_t *shape,
                           MlirType elementType) {
  return wrap(VectorType::get(llvm::ArrayRef(shape, static_cast<size_t>(rank)),
                              unwrap(elementType)));
}

MlirType mlirVectorTypeGetChecked(MlirLocation loc, intptr_t rank,
                                  const int64_t *shape, MlirType elementType) {
  return wrap(VectorType::getChecked(
      unwrap(loc), llvm::ArrayRef(shape, static_cast<size_t>(rank)),
      unwrap(elementType)));
}

MlirType mlirVectorTypeGetScalable(intptr_t rank, const int64_t *shape,
                                   const bool *scalable, MlirType elementType) {
  return wrap(VectorType::get(
      llvm::ArrayRef(shape, static_cast<size_t>(rank)), unwrap(elementType),
      llvm::ArrayRef(scalable, static_cast<size_t>(rank))));
}

MlirType mlirVectorTypeGetScalableChecked(MlirLocation loc, intptr_t rank,
                                          const int64_t *shape,
                                          const bool *scalable,
                                          MlirType elementType) {
  return wrap(VectorType::getChecked(
      unwrap(loc), llvm::ArrayRef(shape, static_cast<size_t>(rank)),
      unwrap(elementType),
      llvm::ArrayRef(scalable, static_cast<size_t>(rank))));
}

bool mlirVectorTypeIsScalable(MlirType type) {
  return cast<VectorType>(unwrap(type)).isScalable();
}

bool mlirVectorTypeIsDimScalable(MlirType type, intptr_t dim) {
  return cast<VectorType>(unwrap(type)).getScalableDims()[dim];
}

//===----------------------------------------------------------------------===//
// Ranked / Unranked tensor type.
//===----------------------------------------------------------------------===//

bool mlirTypeIsATensor(MlirType type) {
  return llvm::isa<TensorType>(unwrap(type));
}

MlirTypeID mlirRankedTensorTypeGetTypeID() {
  return wrap(RankedTensorType::getTypeID());
}

bool mlirTypeIsARankedTensor(MlirType type) {
  return llvm::isa<RankedTensorType>(unwrap(type));
}

MlirTypeID mlirUnrankedTensorTypeGetTypeID() {
  return wrap(UnrankedTensorType::getTypeID());
}

bool mlirTypeIsAUnrankedTensor(MlirType type) {
  return llvm::isa<UnrankedTensorType>(unwrap(type));
}

MlirType mlirRankedTensorTypeGet(intptr_t rank, const int64_t *shape,
                                 MlirType elementType, MlirAttribute encoding) {
  return wrap(
      RankedTensorType::get(llvm::ArrayRef(shape, static_cast<size_t>(rank)),
                            unwrap(elementType), unwrap(encoding)));
}

MlirType mlirRankedTensorTypeGetChecked(MlirLocation loc, intptr_t rank,
                                        const int64_t *shape,
                                        MlirType elementType,
                                        MlirAttribute encoding) {
  return wrap(RankedTensorType::getChecked(
      unwrap(loc), llvm::ArrayRef(shape, static_cast<size_t>(rank)),
      unwrap(elementType), unwrap(encoding)));
}

MlirAttribute mlirRankedTensorTypeGetEncoding(MlirType type) {
  return wrap(llvm::cast<RankedTensorType>(unwrap(type)).getEncoding());
}

MlirType mlirUnrankedTensorTypeGet(MlirType elementType) {
  return wrap(UnrankedTensorType::get(unwrap(elementType)));
}

MlirType mlirUnrankedTensorTypeGetChecked(MlirLocation loc,
                                          MlirType elementType) {
  return wrap(UnrankedTensorType::getChecked(unwrap(loc), unwrap(elementType)));
}

MlirType mlirUnrankedTensorTypeGetElementType(MlirType type) {
  return wrap(llvm::cast<UnrankedTensorType>(unwrap(type)).getElementType());
}

//===----------------------------------------------------------------------===//
// Ranked / Unranked MemRef type.
//===----------------------------------------------------------------------===//

MlirTypeID mlirMemRefTypeGetTypeID() { return wrap(MemRefType::getTypeID()); }

bool mlirTypeIsAMemRef(MlirType type) {
  return llvm::isa<MemRefType>(unwrap(type));
}

MlirType mlirMemRefTypeGet(MlirType elementType, intptr_t rank,
                           const int64_t *shape, MlirAttribute layout,
                           MlirAttribute memorySpace) {
  return wrap(MemRefType::get(
      llvm::ArrayRef(shape, static_cast<size_t>(rank)), unwrap(elementType),
      mlirAttributeIsNull(layout)
          ? MemRefLayoutAttrInterface()
          : llvm::cast<MemRefLayoutAttrInterface>(unwrap(layout)),
      unwrap(memorySpace)));
}

MlirType mlirMemRefTypeGetChecked(MlirLocation loc, MlirType elementType,
                                  intptr_t rank, const int64_t *shape,
                                  MlirAttribute layout,
                                  MlirAttribute memorySpace) {
  return wrap(MemRefType::getChecked(
      unwrap(loc), llvm::ArrayRef(shape, static_cast<size_t>(rank)),
      unwrap(elementType),
      mlirAttributeIsNull(layout)
          ? MemRefLayoutAttrInterface()
          : llvm::cast<MemRefLayoutAttrInterface>(unwrap(layout)),
      unwrap(memorySpace)));
}

MlirType mlirMemRefTypeContiguousGet(MlirType elementType, intptr_t rank,
                                     const int64_t *shape,
                                     MlirAttribute memorySpace) {
  return wrap(MemRefType::get(llvm::ArrayRef(shape, static_cast<size_t>(rank)),
                              unwrap(elementType), MemRefLayoutAttrInterface(),
                              unwrap(memorySpace)));
}

MlirType mlirMemRefTypeContiguousGetChecked(MlirLocation loc,
                                            MlirType elementType, intptr_t rank,
                                            const int64_t *shape,
                                            MlirAttribute memorySpace) {
  return wrap(MemRefType::getChecked(
      unwrap(loc), llvm::ArrayRef(shape, static_cast<size_t>(rank)),
      unwrap(elementType), MemRefLayoutAttrInterface(), unwrap(memorySpace)));
}

MlirAttribute mlirMemRefTypeGetLayout(MlirType type) {
  return wrap(llvm::cast<MemRefType>(unwrap(type)).getLayout());
}

MlirAffineMap mlirMemRefTypeGetAffineMap(MlirType type) {
  return wrap(llvm::cast<MemRefType>(unwrap(type)).getLayout().getAffineMap());
}

MlirAttribute mlirMemRefTypeGetMemorySpace(MlirType type) {
  return wrap(llvm::cast<MemRefType>(unwrap(type)).getMemorySpace());
}

MlirLogicalResult mlirMemRefTypeGetStridesAndOffset(MlirType type,
                                                    int64_t *strides,
                                                    int64_t *offset) {
  MemRefType memrefType = llvm::cast<MemRefType>(unwrap(type));
  SmallVector<int64_t> strides_;
  if (failed(memrefType.getStridesAndOffset(strides_, *offset)))
    return mlirLogicalResultFailure();

  (void)std::copy(strides_.begin(), strides_.end(), strides);
  return mlirLogicalResultSuccess();
}

MlirTypeID mlirUnrankedMemRefTypeGetTypeID() {
  return wrap(UnrankedMemRefType::getTypeID());
}

bool mlirTypeIsAUnrankedMemRef(MlirType type) {
  return llvm::isa<UnrankedMemRefType>(unwrap(type));
}

MlirType mlirUnrankedMemRefTypeGet(MlirType elementType,
                                   MlirAttribute memorySpace) {
  return wrap(
      UnrankedMemRefType::get(unwrap(elementType), unwrap(memorySpace)));
}

MlirType mlirUnrankedMemRefTypeGetChecked(MlirLocation loc,
                                          MlirType elementType,
                                          MlirAttribute memorySpace) {
  return wrap(UnrankedMemRefType::getChecked(unwrap(loc), unwrap(elementType),
                                             unwrap(memorySpace)));
}

MlirAttribute mlirUnrankedMemrefGetMemorySpace(MlirType type) {
  return wrap(llvm::cast<UnrankedMemRefType>(unwrap(type)).getMemorySpace());
}

//===----------------------------------------------------------------------===//
// Tuple type.
//===----------------------------------------------------------------------===//

MlirTypeID mlirTupleTypeGetTypeID() { return wrap(TupleType::getTypeID()); }

bool mlirTypeIsATuple(MlirType type) {
  return llvm::isa<TupleType>(unwrap(type));
}

MlirType mlirTupleTypeGet(MlirContext ctx, intptr_t numElements,
                          MlirType const *elements) {
  SmallVector<Type, 4> types;
  ArrayRef<Type> typeRef = unwrapList(numElements, elements, types);
  return wrap(TupleType::get(unwrap(ctx), typeRef));
}

intptr_t mlirTupleTypeGetNumTypes(MlirType type) {
  return llvm::cast<TupleType>(unwrap(type)).size();
}

MlirType mlirTupleTypeGetType(MlirType type, intptr_t pos) {
  return wrap(
      llvm::cast<TupleType>(unwrap(type)).getType(static_cast<size_t>(pos)));
}

//===----------------------------------------------------------------------===//
// Function type.
//===----------------------------------------------------------------------===//

MlirTypeID mlirFunctionTypeGetTypeID() {
  return wrap(FunctionType::getTypeID());
}

bool mlirTypeIsAFunction(MlirType type) {
  return llvm::isa<FunctionType>(unwrap(type));
}

MlirType mlirFunctionTypeGet(MlirContext ctx, intptr_t numInputs,
                             MlirType const *inputs, intptr_t numResults,
                             MlirType const *results) {
  SmallVector<Type, 4> inputsList;
  SmallVector<Type, 4> resultsList;
  (void)unwrapList(numInputs, inputs, inputsList);
  (void)unwrapList(numResults, results, resultsList);
  return wrap(FunctionType::get(unwrap(ctx), inputsList, resultsList));
}

intptr_t mlirFunctionTypeGetNumInputs(MlirType type) {
  return llvm::cast<FunctionType>(unwrap(type)).getNumInputs();
}

intptr_t mlirFunctionTypeGetNumResults(MlirType type) {
  return llvm::cast<FunctionType>(unwrap(type)).getNumResults();
}

MlirType mlirFunctionTypeGetInput(MlirType type, intptr_t pos) {
  assert(pos >= 0 && "pos in array must be positive");
  return wrap(llvm::cast<FunctionType>(unwrap(type))
                  .getInput(static_cast<unsigned>(pos)));
}

MlirType mlirFunctionTypeGetResult(MlirType type, intptr_t pos) {
  assert(pos >= 0 && "pos in array must be positive");
  return wrap(llvm::cast<FunctionType>(unwrap(type))
                  .getResult(static_cast<unsigned>(pos)));
}

//===----------------------------------------------------------------------===//
// Opaque type.
//===----------------------------------------------------------------------===//

MlirTypeID mlirOpaqueTypeGetTypeID() { return wrap(OpaqueType::getTypeID()); }

bool mlirTypeIsAOpaque(MlirType type) {
  return llvm::isa<OpaqueType>(unwrap(type));
}

MlirType mlirOpaqueTypeGet(MlirContext ctx, MlirStringRef dialectNamespace,
                           MlirStringRef typeData) {
  return wrap(
      OpaqueType::get(StringAttr::get(unwrap(ctx), unwrap(dialectNamespace)),
                      unwrap(typeData)));
}

MlirStringRef mlirOpaqueTypeGetDialectNamespace(MlirType type) {
  return wrap(
      llvm::cast<OpaqueType>(unwrap(type)).getDialectNamespace().strref());
}

MlirStringRef mlirOpaqueTypeGetData(MlirType type) {
  return wrap(llvm::cast<OpaqueType>(unwrap(type)).getTypeData());
}
