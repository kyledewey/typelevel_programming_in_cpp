#ifndef LISTS_H
#define LISTS_H

#include "peano.h"

// ---BEGIN BASIC LIST DEFINITION---
struct Nil {};

template <typename Head, typename Tail>
struct Cons {
  Head typedef head;
  Tail typedef tail;
};
// ---END BASIC LIST DEFINITION---

// ---BEGIN DEFINITIONS FOR LENGTH---
template <typename L>
struct Length {};

template <>
struct Length<Nil> {
  Zero typedef result;
};

template <typename H, typename L>
struct Length<Cons<H, L> > {
  Succ<typename Length<L>::result> typedef result;
};
// ---END DEFINITIONS FOR LENGTH---

// ---BEGIN DEFINITIONS FOR APPEND---
template <typename L1, typename L2>
struct Append {};

template <typename L>
struct Append<Nil, L> {
  L typedef result;
};

template <typename Head, typename Tail, typename L2>
struct Append<Cons<Head, Tail>, L2> {
  Cons<Head, typename Append<Tail, L2>::result> typedef result;
};
// ---END DEFINITIONS FOR APPEND---

// ---BEGIN DEFINITIONS FOR GETNTH---
template <typename L, typename N>
struct GetNth {};

template <typename Head, typename Tail>
struct GetNth<Cons<Head, Tail>, Zero> {
  Head typedef result;
};

template <typename Head, typename Tail, typename N>
struct GetNth<Cons<Head, Tail>, Succ<N> > {
  typename GetNth<Tail, N>::result typedef result;
};
// ---END DEFINITIONS FOR GETNTH

// ---BEGIN DEFINITIONS FOR REVERSE---

// % if this were Prolog...
// reverse(Input, Output) :-
//   reverse(Input, [], Output).
//
// reverse([], Accum, Accum).
// reverse([Head|Tail], Accum, Rest) :-
//   reverse(Tail, [Head|Accum], Rest).
//

// helper routine that does the actual work
// this avoids needing to expose the accumulator
template <typename Input, typename Accum>
struct ReverseHelper {};

template <typename Accum>
struct ReverseHelper<Nil, Accum> {
  Accum typedef result;
};

template <typename Head, typename Tail, typename Accum>
struct ReverseHelper<Cons<Head, Tail>, Accum> {
  typename ReverseHelper<Tail, Cons<Head, Accum> >::result typedef result;
};

// top-level procedure to be called directly
template <typename Input>
struct Reverse {
  typename ReverseHelper<Input, Nil>::result typedef result;
};

// ---END DEFINITIONS FOR REVERSE---


// ---BEGIN DEFINITIONS FOR SUM---
template <typename L>
struct Sum {};

template <>
struct Sum<Nil> {
  Zero typedef result;
};

template <typename Head, typename Tail>
struct Sum<Cons<Head, Tail> > {
  typename Add<Head, typename Sum<Tail>::result>::result typedef result;
};

// ---END DEFINITIONS FOR SUM---

#endif
