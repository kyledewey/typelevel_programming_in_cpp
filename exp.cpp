#include <iostream>
#include <cassert>
#include "exp.h"
#include "peano.h"
#include "map.h"

int main() {
  assert((TypeOf<BoolLiteral<False>, EmptyMap>::result::debugFlag) == 0);
  assert((TypeOf<NatLiteral<Zero>, EmptyMap>::result::debugFlag) == 1);
  assert((TypeOf<VariableExp<Zero>, NonEmptyMap<Zero, BoolType, EmptyMap> >::result::debugFlag) == 0);  
  assert((TypeOf<AddExp<NatLiteral<Zero>, NatLiteral<Zero> >, EmptyMap>::result::debugFlag) == 1);
  assert((TypeOf<AndExp<BoolLiteral<False>, BoolLiteral<True> >, EmptyMap>::result::debugFlag) == 0);
  assert((TypeOf<EqualsExp<NatLiteral<Zero>, NatLiteral<Succ<Zero> > >, EmptyMap>::result::debugFlag) == 0);
  assert((TypeOf<EqualsExp<BoolLiteral<True>, BoolLiteral<False> >, EmptyMap>::result::debugFlag) == 0);

  // let _0 = false in _0
  assert((TypeOf<LetExp<Zero, BoolLiteral<False>, VariableExp<Zero> >, EmptyMap>::result::debugFlag == 0));
  return 0;
}
