#ifndef MAP_H
#define MAP_H

// ---BEGIN BASIC MAP DEFINITION---
struct EmptyMap {};

template <typename Key, typename Value, typename Rest>
struct NonEmptyMap {
  Key typedef key;
  Value typedef value;
  Rest typedef rest;
};
// ---END BASIC MAP DEFINITION---

// ---BEGIN DEFINITIONS FOR LOOKUP---

template <typename Map, typename Key>
struct Lookup {};

template <typename Key, typename Value, typename Rest>
struct Lookup<NonEmptyMap<Key, Value, Rest>, Key> {
  Value typedef result;
};

template <typename OtherKey, typename OtherValue, typename Rest, typename Key>
struct Lookup<NonEmptyMap<OtherKey, OtherValue, Rest>, Key> {
  typename Lookup<Rest, Key>::result typedef result;
};
// ---END DEFINITIONS FOR LOOKUP---

#endif
