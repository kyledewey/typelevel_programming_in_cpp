#ifndef LISTS_H
#define LISTS_H

#include "peano.h"

struct Nil {};

template <typename Head, typename Tail>
struct Cons {
  Head typedef head;
  Tail typedef tail;
};

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

#endif
