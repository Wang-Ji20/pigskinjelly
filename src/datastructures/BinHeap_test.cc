//===--- BinHeap_test.cc - Binary Heap Impl ---------------------*- C++ -*-===//
// pigskinjelly 2023
//
// Identification: src/datastructures/BinHeap_test.cc
//
// Author: Ji Wang <jiwangcdi@gmail.com>
//
// SPDX-License-Identifier: MIT
//===----------------------------------------------------------------------===//

#include "gtest/gtest.h"

template <typename T>
class BinHeap {
public:
  BinHeap() = default;
  ~BinHeap() = default;

  constexpr static inline auto
  GetLeft(int node) -> int {
    return 2 * node + 1;
  }

  constexpr static inline auto
  GetRight(int node) -> int {
    return 2 * node + 2;
  }

  constexpr static inline auto
  GetParent(int node) -> int {
    return (node - 1) / 2;
  }

  void
  AddElem(T val) {
    data_.push_back(val);
    BubbleUp(data_.size() - 1);
  }

  void
  BubbleUp(int idx) {
    int parentIdx = GetParent(idx);
    while (idx > 0 && data_[idx] < data_[parentIdx]) {
      std::swap(data_[idx], data_[parentIdx]);
      idx = parentIdx;
      parentIdx = GetParent(idx);
    }
  }

  auto
  RemoveElem() -> T {
    T ret = data_[0];
    data_[0] = data_.back();
    data_.pop_back();
    TrickleDown(0);
    return ret;
  }

  void
  TrickleDown(int idx) {
    for (;;) {
      int candidate = GetSmallestElemIdxInFamily(idx);
      if (candidate == idx) {
        return;
      }
      std::swap(data_[idx], data_[candidate]);
      idx = candidate;
    };
  }

  auto
  GetSmallestElemIdxInFamily(int idx) -> int {
    int left = GetLeft(idx);
    int right = GetRight(idx);
    if (left >= data_.size()) {
      return idx;
    }
    if (right >= data_.size()) {
      return data_[left] < data_[idx] ? left : idx;
    }
    if (data_[left] < data_[right]) {
      return data_[left] < data_[idx] ? left : idx;
    }
    return data_[right] < data_[idx] ? right : idx;
  }

  std::vector<T> data_;
};

// NOLINTNEXTLINE
TEST(HeapSortTest, BasicTest) {
  BinHeap<int> heap;
  heap.AddElem(5);
  heap.AddElem(3);
  heap.AddElem(1);
  heap.AddElem(2);
  heap.AddElem(4);
  heap.AddElem(6);
  heap.AddElem(7);
  heap.AddElem(8);
  ASSERT_EQ(heap.RemoveElem(), 1);
  ASSERT_EQ(heap.RemoveElem(), 2);
  ASSERT_EQ(heap.RemoveElem(), 3);
  ASSERT_EQ(heap.RemoveElem(), 4);
  ASSERT_EQ(heap.RemoveElem(), 5);
  ASSERT_EQ(heap.RemoveElem(), 6);
  ASSERT_EQ(heap.RemoveElem(), 7);
  ASSERT_EQ(heap.RemoveElem(), 8);
}
