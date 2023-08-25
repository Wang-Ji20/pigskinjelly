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

#include <memory>
#include <optional>
#include <unordered_map>

template <typename Key = char>
class TrieNode {
public:
  TrieNode(bool hasValue = false) : hasValue_(hasValue) {}

  TrieNode(const TrieNode &) = delete;

  auto
  operator=(const TrieNode &) -> TrieNode & = delete;

  TrieNode(TrieNode &&) noexcept = default;
  TrieNode(TrieNode &&other, bool hasValue)
      : hasValue_(hasValue), children_(std::move(other.children_)) {}

  auto
  operator=(TrieNode &&) noexcept -> TrieNode & = default;

  bool hasValue_;

  inline auto
  GetChildUnmanaged(Key key) -> TrieNode * {
    auto childIter = children_.find(key);
    if (childIter == children_.end()) {
      return nullptr;
    }
    return childIter->second.get();
  }

  inline auto
  GetChildMut(Key key) -> std::unique_ptr<TrieNode> * {
    auto childIter = children_.find(key);
    if (childIter == children_.end()) {
      return nullptr;
    }
    return &childIter->second;
  }

  inline auto
  CreateChild(Key key) -> std::unique_ptr<TrieNode> * {
    children_.emplace(key, std::make_unique<TrieNode>());
    return &children_.at(key);
  }

  inline auto
  GetOrCreateChildMut(Key key) -> std::unique_ptr<TrieNode> * {
    if (auto child = GetChildMut(key); child != nullptr) {
      return child;
    }
    return CreateChild(key);
  }

protected:
  std::unordered_map<Key, std::unique_ptr<TrieNode>> children_;
};

template <typename Key, typename Value>
class TrieNodeWithValue : public TrieNode<Key> {
public:
  TrieNodeWithValue(Value value) : TrieNode<Key>(true), value_(value) {}

  TrieNodeWithValue(const TrieNodeWithValue &) = delete;

  auto
  operator=(const TrieNodeWithValue &) -> TrieNodeWithValue & = delete;

  TrieNodeWithValue(TrieNodeWithValue &&) noexcept = default;

  TrieNodeWithValue(std::unique_ptr<TrieNode<Key>> promoteNode, Value value)
      : TrieNode<Key>(std::move(*promoteNode), true),
        value_(std::move(value)) {}

  auto
  operator=(TrieNodeWithValue &&) noexcept -> TrieNodeWithValue & = default;

  Value value_;
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
    auto iter = &root_;
    for (auto &&key : cont) {
      iter = (*iter)->GetOrCreateChildMut(key);
    }
    if ((*iter)->hasValue_) {
      throw std::runtime_error("Duplicate key");
    }

    *iter = std::make_unique<TrieNodeWithValue<Key, Value>>(std::move(*iter),
                                                            value);
  }

  template <typename Value>
  auto
  Lookup(const Container &cont) -> std::optional<Value> {
    auto iterator = root_.get();
    for (auto &&key : cont) {
      iterator = iterator->GetChildUnmanaged(key);
      if (iterator == nullptr) {
        return std::nullopt;
      }
    }
    if (!iterator->hasValue_) {
      return std::nullopt;
    }
    return static_cast<TrieNodeWithValue<Key, Value> *>(iterator)->value_;
  }

  auto
  StartWith(const Container &cont) -> bool {
    auto iterator = root_.get();
    for (auto &&key : cont) {
      iterator = iterator->GetChildUnmanaged(key);
      if (iterator == nullptr) {
        return false;
      }
    }
    return true;
  }

private:
  std::unique_ptr<TrieNode<Key>> root_;
};

// NOLINTNEXTLINE
TEST(ACAutomaton, Trie) {
  Trie<char, std::string> trie;
  std::string str = "apple";
  EXPECT_EQ(trie.Lookup<std::string>("hello"), str);
}
