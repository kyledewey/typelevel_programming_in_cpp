#include <iostream>
#include "peano.h"

int main() {
  // 3 + 2
  std::cout << Add<Succ<Succ<Succ<Zero> > >, Succ<Succ<Zero> > >::result::value << std::endl;
  return 0;
}
