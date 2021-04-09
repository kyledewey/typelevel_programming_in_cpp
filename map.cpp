#include <iostream>
#include "map.h"
#include "peano.h"

int main() {
  using zero = Zero;
  using one = Succ<zero>;
  using two = Succ<one>;
  using three = Succ<two>;

  // 1 -> 2, 2 -> 3
  using map = NonEmptyMap<one, two, NonEmptyMap<two, three, EmptyMap> >;

  std::cout << "lookup 1: "
            << Lookup<map, one>::result::value << std::endl;

  std::cout << "lookup 2: "
            << Lookup<map, two>::result::value << std::endl;

  return 0;
}
