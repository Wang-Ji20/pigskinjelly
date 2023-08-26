//===--- 228_lc_test.cc - Leetcode No.228 -----------------------*- C++ -*-===//
// pigskinjelly 2023
//
// Identification: src/problems/228_lc_test.cc
//
// Author: Ji Wang <jiwangcdi@gmail.com>
//
// SPDX-License-Identifier: MIT
//===----------------------------------------------------------------------===//

#include "lc_common.hh"

#include "gtest/gtest.h"

class Solution {
public:
  auto
  summaryRanges(vector<int> &nums) -> vector<string> {
    rangeStart = rangeMid = nums[0];
    for (auto &&num: nums) {
      preceedRange(num);
    }
    generateAnswer();
    return answer;
  }

  inline void
  preceedRange(int num) {
    if (rangeStart == rangeMid && rangeMid == num) {
      return;
    }
    if (rangeMid + 1 == num) {
      ++rangeMid;
      return;
    }
    closeRange(num);
  }

  inline void
  closeRange(int num) {
    generateAnswer();
    rangeStart = rangeMid = num;
  }

  inline void
  generateAnswer() {
    string sol(to_string(rangeStart));
    if (rangeMid != rangeStart) {
      sol += "->" + to_string(rangeMid);
    }
    answer.push_back(std::move(sol));
  }


private:
  int rangeStart;
  int rangeMid;
  vector<string> answer;
};

TEST(Leetcode, BasicTest) {
  vector<int> vecInput = {0,2,3,4,6,8,9};
  Solution algorithm;
  auto myAns = algorithm.summaryRanges(vecInput);
  for (auto &&str: myAns) {
    std::cerr << str << std::endl;
  }
}
