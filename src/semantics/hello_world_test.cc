//===--- hello_world_test.cc - helloworld -----------------------*- C++ -*-===//
// pigskinjelly 2023
//
// Identification: src/semantics/hello_world_test.cc
//
// Author: Ji Wang <jiwangcdi@gmail.com>
//
// SPDX-License-Identifier: MIT
//===----------------------------------------------------------------------===//

#include <iostream>

#include "gtest/gtest.h"

TEST(Semantics, HelloWorld) {
  std::cout << "hello, world\n";
}
