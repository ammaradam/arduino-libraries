// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "./StringCopier.hpp"
#include "./StringMover.hpp"

namespace ARDUINOJSON_NAMESPACE {

template <typename TInput, typename Enable = void>
struct StringStorage {
  typedef StringCopier type;

  static type create(MemoryPool& pool, TInput&) {
    return type(&pool);
  }
};

template <typename TChar>
struct StringStorage<TChar*,
                     typename enable_if<!is_const<TChar>::value>::type> {
  typedef StringMover<TChar> type;

  static type create(MemoryPool&, TChar* input) {
    return type(input);
  }
};

template <typename TInput>
typename StringStorage<TInput>::type makeStringStorage(MemoryPool& pool,
                                                       TInput& input) {
  return StringStorage<TInput>::create(pool, input);
}

template <typename TChar>
typename StringStorage<TChar*>::type makeStringStorage(MemoryPool& pool,
                                                       TChar* input) {
  return StringStorage<TChar*>::create(pool, input);
}
}  // namespace ARDUINOJSON_NAMESPACE
