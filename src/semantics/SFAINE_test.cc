//===--- SFAINE_test.cc - TEST SFAINE eg ------------------------*- C++ -*-===//
// pigskinjelly 2023
//
// Identification: src/semantics/SFAINE_test.cc
//
// Author: Ji Wang <jiwangcdi@gmail.com>
//
// SPDX-License-Identifier: MIT
//===----------------------------------------------------------------------===//

#include "gtest/gtest.h"
#include <type_traits>
#include <concepts>

class Serializer {};

class EnhancedInteger {
public:
  static void
  serialize(Serializer &serializer) {}
};

template <typename T, typename V = T>
struct has_serialize_sfaine : std::false_type {};

template <typename T>
struct has_serialize_sfaine<
    T,
    typename std::enable_if<
        std::is_same<decltype(T::serialize), void(Serializer &)>::value,
        T>::type> : std::true_type {};

template <typename T>
concept has_serialize_concept = requires(T t, Serializer &serializer) {
  t.serialize(serializer);
};

template<typename T, typename = T>
struct has_serialize_concept_t : std::false_type {};

template <has_serialize_concept T>
struct has_serialize_concept_t<T, T> : std::true_type {};

static_assert(std::is_same<decltype(EnhancedInteger::serialize),
                           void(Serializer &)>::value,
              "world collapse");

// NOLINTNEXTLINE
TEST(SFAINE, simpleTest) {
  EXPECT_FALSE(has_serialize_sfaine<int>::value);
  static_assert(std::is_same<decltype(EnhancedInteger::serialize),
                             void(Serializer &)>::value,
                "world collapse");
  EXPECT_TRUE(has_serialize_sfaine<EnhancedInteger>::value);
}

// NOLINTNEXTLINE
TEST(SFAINE, conceptTest) {
  EXPECT_FALSE(has_serialize_concept_t<int>::value);
  EXPECT_TRUE(has_serialize_concept_t<EnhancedInteger>::value);
  has_serialize_concept;
}
