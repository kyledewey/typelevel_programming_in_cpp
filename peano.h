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
  using ok = True;
};

template <>
struct IsBool<False> {
  using ok = True;
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
  using result = N;
};

template <typename N1, typename N2>
struct Add<Succ<N1>, N2> {
  using result = Succ<typename Add<N1, N2>::result>;
};
// ---END DEFINITIONS FOR ADD

// ---BEGIN DEFINITIONS FOR ISNAT
template <typename N>
struct IsNat {};

template <>
struct IsNat<Zero> {
  using ok = True;
};

template <typename N>
struct IsNat<Succ<N> > {
  using ok = typename IsNat<N>::ok;
};
// ---END DEFINITIONS FOR ISNAT

#endif
