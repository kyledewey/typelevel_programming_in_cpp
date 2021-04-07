#include <iostream>
#include "map.h"
#include "peano.h"

int main() {
  Zero typedef zero;
  Succ<zero> typedef one;
  Succ<one> typedef two;
  Succ<two> typedef three;

  // 1 -> 2, 2 -> 3
  NonEmptyMap<one, two, NonEmptyMap<two, three, EmptyMap> > typedef map;

  std::cout << "lookup 1: "
            << Lookup<map, one>::result::value << std::endl;

  std::cout << "lookup 2: "
            << Lookup<map, two>::result::value << std::endl;

  return 0;
}
