#ifndef PEANO_H
#define PEANO_H

// ---BEGIN DEFINITIONS FOR BOOLEANS---
struct True {};
struct False {};
// ---END DEFINITIONS FOR BOOLEANS---

// ---BEGIN ISBOOL DEFINITION---
template <typename B>
struct IsBool {};

template <>
struct IsBool<True> {
  True typedef ok;
};

template <>
struct IsBool<False> {
  True typedef ok;
};
// ---END ISBOOL DEFINITION---

// ---BEGIN NAT DEFINITION---
struct Zero {
  enum { value = 0 };
};

template <typename N>
struct Succ {
  enum { value = N::value + 1 };
};
// ---END NAT DEFINITION

// ---BEGIN DEFINITIONS FOR ADD---
template <typename N1, typename N2>
struct Add {};

template <typename N>
struct Add<Zero, N> {
  N typedef result;
};

template <typename N1, typename N2>
struct Add<Succ<N1>, N2> {
  Succ<typename Add<N1, N2>::result> typedef result;
};
// ---END DEFINITIONS FOR ADD

// ---BEGIN DEFINITIONS FOR ISNAT
template <typename N>
struct IsNat {};

template <>
struct IsNat<Zero> {
  True typedef ok;
};

template <typename N>
struct IsNat<Succ<N> > {
  typename IsNat<N>::ok typedef ok;
};
// ---END DEFINITIONS FOR ISNAT

#endif
