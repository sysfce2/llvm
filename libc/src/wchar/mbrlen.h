//===-- Implementation header for mbrlen ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIBC_SRC_WCHAR_MBRLEN_H
#define LLVM_LIBC_SRC_WCHAR_MBRLEN_H

#include "hdr/types/mbstate_t.h"
#include "hdr/types/size_t.h"
#include "src/__support/macros/config.h"

namespace LIBC_NAMESPACE_DECL {

size_t mbrlen(const char *__restrict s, size_t n, mbstate_t *__restrict ps);

} // namespace LIBC_NAMESPACE_DECL

#endif // LLVM_LIBC_SRC_WCHAR_MBRLEN_H
