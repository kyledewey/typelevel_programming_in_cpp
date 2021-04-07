#include <iostream>
#include <cassert>
#include "exp.h"
#include "peano.h"
#include "map.h"

int main() {
  assert((TypeOf<BoolLiteral<False>, EmptyMap>::result::debugFlag) == 0);
  assert((TypeOf<NatLiteral<Zero>, EmptyMap>::result::debugFlag) == 1);
  assert((TypeOf<AddExp<NatLiteral<Zero>, NatLiteral<Zero> >, EmptyMap>::result::debugFlag) == 1);
  assert((TypeOf<AndExp<BoolLiteral<False>, BoolLiteral<True> >, EmptyMap>::result::debugFlag) == 0);
  
  return 0;
}
