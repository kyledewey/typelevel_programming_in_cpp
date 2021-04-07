#include <iostream>
#include "exp.h"
#include "peano.h"
#include "map.h"

int main() {
  // gives back nat type - ok
  std::cout << TypeOf<AddExp<NatLiteral<Zero>, NatLiteral<Zero> >, EmptyMap>::result::debugFlag << std::endl;

  return 0;
}
