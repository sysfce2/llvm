//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <unordered_set>

// Dereference non-dereferenceable iterator.

// REQUIRES: has-unix-headers, libcpp-hardening-mode={{extensive|debug}}
// UNSUPPORTED: c++03
// XFAIL: libcpp-hardening-mode=debug && availability-verbose_abort-missing

#include <unordered_set>

#include "check_assertion.h"
#include "min_allocator.h"

int main(int, char**) {
  {
    typedef int T;
    typedef std::unordered_set<T> C;
    C c(1);
    C::local_iterator i = c.end(0);
    TEST_LIBCPP_ASSERT_FAILURE(
        *i, "Attempted to dereference a non-dereferenceable unordered container const_local_iterator");
    C::const_local_iterator i2 = c.cend(0);
    TEST_LIBCPP_ASSERT_FAILURE(
        *i2, "Attempted to dereference a non-dereferenceable unordered container const_local_iterator");
  }

  {
    typedef int T;
    typedef std::unordered_set<T, std::hash<T>, std::equal_to<T>, min_allocator<T>> C;
    C c(1);
    C::local_iterator i = c.end(0);
    TEST_LIBCPP_ASSERT_FAILURE(
        *i, "Attempted to dereference a non-dereferenceable unordered container const_local_iterator");
    C::const_local_iterator i2 = c.cend(0);
    TEST_LIBCPP_ASSERT_FAILURE(
        *i2, "Attempted to dereference a non-dereferenceable unordered container const_local_iterator");
  }

  return 0;
}
