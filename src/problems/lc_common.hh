//===--- lc_common.hh - LC common headers -----------------------*- C++ -*-===//
// pigskinjelly 2023
//
// Identification: src/problems/lc_common.hh
//
// Author: Ji Wang <jiwangcdi@gmail.com>
//
// SPDX-License-Identifier: MIT
//===----------------------------------------------------------------------===//

#ifndef SRC_PROBLEMS_LC_COMMON_HH
#define SRC_PROBLEMS_LC_COMMON_HH

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef> // size_t
#include <cstdint> // int32_t
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility> // pair, move
#include <variant>
#include <vector>
using namespace std;

#define LEETCODE_SOLUTION(ret, ...)                                            \
  class Solution {                                                             \
  public:                                                                      \
    auto solve(__VA_ARGS__) -> ret;                                            \
  };                                                                           \
  auto Solution::solve(__VA_ARGS__) -> ret

#endif // SRC_PROBLEMS_LC_COMMON_HH
