#include <iostream>

struct Zero {
  enum { value = 0 };
};

template <typename N>
struct Succ {
  enum { value = N::value + 1 };
};

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

int main() {
  // 3 + 2
  std::cout << Add<Succ<Succ<Succ<Zero> > >, Succ<Succ<Zero> > >::result::value << std::endl;
  return 0;
}
