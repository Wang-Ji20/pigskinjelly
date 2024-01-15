//===--- ACAutomaton_test.cc - ACAutomaton ----------------------*- C++ -*-===//
// pigskinjelly 2023
//
// Identification: src/datastructures/ACAutomaton_test.cc
//
// Author: Ji Wang <jiwangcdi@gmail.com>
//
// SPDX-License-Identifier: MIT
//===----------------------------------------------------------------------===//

#include "gtest/gtest.h"

#include <any>
#include <memory>
#include <optional>
#include <queue>
#include <unordered_map>

template <typename Key = char>
class TrieNode {
public:
  TrieNode() = default;

  TrieNode(const TrieNode &) = delete;

  auto
  operator=(const TrieNode &) -> TrieNode & = delete;

  TrieNode(TrieNode &&) noexcept = default;

  auto
  operator=(TrieNode &&) noexcept -> TrieNode & = default;

  [[nodiscard]] inline auto
  HasValue() const -> bool {
    return value_.type() != typeid(std::nullopt_t);
  }

  inline auto
  GetChild(Key key) -> TrieNode * {
    auto childIter = children_.find(key);
    if (childIter == children_.end()) {
      return nullptr;
    }
    return childIter->second.get();
  }

  inline auto
  CreateChild(Key key) -> TrieNode * {
    children_.emplace(key, std::make_unique<TrieNode>());
    return children_.at(key).get();
  }

  inline auto
  GetOrCreateChild(Key key) -> TrieNode * {
    if (auto child = GetChild(key); child != nullptr) {
      return child;
    }
    return CreateChild(key);
  }

  template <typename Value>
  inline auto
  AddValue(const Value &value) -> void {
    value_ = value;
  }

  std::any value_ = std::nullopt;
  std::unordered_map<Key, std::unique_ptr<TrieNode>> children_;
  TrieNode *fail_ = nullptr;
};

template <typename Key = char, typename Container = std::string>
class Trie {
public:
  Trie() : root_(std::make_unique<TrieNode<Key>>()) {}

  Trie(const Trie &) = delete;
  auto
  operator=(const Trie &) -> Trie & = delete;

  Trie(Trie &&) noexcept = default;
  auto
  operator=(Trie &&) noexcept -> Trie & = default;

  template <typename Value>
  auto
  Insert(const Container &cont, const Value &value) -> void {
    auto iter = root_.get();
    for (auto &&key : cont) {
      iter = iter->GetOrCreateChild(key);
    }
    if (iter->HasValue()) {
      throw std::runtime_error("Duplicate key");
    }
    iter->AddValue(value);
  }

  template <typename Value>
  auto
  Lookup(const Container &cont) -> std::optional<Value> {
    auto iterator = root_.get();
    for (auto &&key : cont) {
      iterator = iterator->GetChild(key);
      if (iterator == nullptr) {
        return std::nullopt;
      }
    }
    if (!iterator->HasValue()) {
      return std::nullopt;
    }
    return std::any_cast<Value>(iterator->value_);
  }

  auto
  StartWith(const Container &cont) -> bool {
    auto iterator = root_.get();
    for (auto &&key : cont) {
      iterator = iterator->GetChild(key);
      if (iterator == nullptr) {
        return false;
      }
    }
    return true;
  }

  void
  BuildFailPtr() {
    std::queue<TrieNode<Key> *> nodeQueue;
    PushChildren(root_.get(), nodeQueue);
    while (!nodeQueue.empty()) {
      auto node = nodeQueue.front();
      nodeQueue.pop();
      for (auto &&[key, child] : node->children_) {
        child->fail_ = BuildNodeFailPtr(key, node);
        PushChildren(child.get(), nodeQueue);
      }
    }
  }

  void
  PushChild(TrieNode<Key> *node, std::queue<TrieNode<Key> *> &nodeQueue) {
    for (auto &&[key, child] : node->children_) {
      nodeQueue.push(child.get());
    }
  }

  auto
  BuildNodeFailPtr(Key key, TrieNode<Key> *node) -> TrieNode<Key> * {
    // iterate, decrease one prefix per iteration, to find text with max prefix-suffix overlapping
    for (auto fail = node->fail_; fail != nullptr; fail = fail->fail_) {
      auto failChild = fail->GetChild(key);
      if (failChild != nullptr) {
        return failChild;
      }
    }
    return root_.get();
  }

private:
  std::unique_ptr<TrieNode<Key>> root_;
};

// NOLINTNEXTLINE
TEST(ACAutomaton, Trie) {
  Trie<char, std::string> trie;
  std::string str = "apple";
  trie.Insert(str, str);
  EXPECT_EQ(trie.Lookup<std::string>("apple"), str);
}
