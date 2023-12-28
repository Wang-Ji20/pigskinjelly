//===--- gem.cc - Gem Supply LCP 50. ----------------------------*- C++ -*-===//
// pigskinjelly 2023
//
// Identification: src/problems/gem.cc
//
// Author: Ji Wang <jiwangcdi@gmail.com>
//
// SPDX-License-Identifier: MIT
//===----------------------------------------------------------------------===//

#include "lc_common.hh"
#include "gtest/gtest.h"

class Solution {
public:
  static auto
  giveGem(vector<int> &gem, vector<vector<int>> &operations) -> int {
    for (auto &&op : operations) {
      auto deposite = gem[op[0]] / 2;
      gem[op[0]] -= deposite;
      gem[op[1]] += deposite;
    }
    return *max_element(gem.begin(), gem.end()) -
           *min_element(gem.begin(), gem.end());
  }
};

// NOLINTNEXTLINE
TEST(GemTest, SimpleTest) {
  vector<int> gem = {3, 1, 2};
  vector<vector<int>> operations = {{0, 2}, {2, 1}, {2, 0}};
  EXPECT_EQ(Solution::giveGem(gem, operations), 2);
}
