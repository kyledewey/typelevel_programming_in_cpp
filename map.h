#ifndef MAP_H
#define MAP_H

// ---BEGIN BASIC MAP DEFINITION---
struct EmptyMap {};

template <typename Key, typename Value, typename Rest>
struct NonEmptyMap {
  using key = Key;
  using value = Value;
  using rest = Rest;
};
// ---END BASIC MAP DEFINITION---

// ---BEGIN DEFINITIONS FOR LOOKUP---

template <typename Map, typename Key>
struct Lookup {};

template <typename Key, typename Value, typename Rest>
struct Lookup<NonEmptyMap<Key, Value, Rest>, Key> {
  using result = Value;
};

template <typename OtherKey, typename OtherValue, typename Rest, typename Key>
struct Lookup<NonEmptyMap<OtherKey, OtherValue, Rest>, Key> {
  using result = typename Lookup<Rest, Key>::result;
};
// ---END DEFINITIONS FOR LOOKUP---

#endif
