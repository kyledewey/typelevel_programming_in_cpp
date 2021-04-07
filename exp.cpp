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

  // rec _0: nat = _0 in _0
  assert((TypeOf<RecExp<Zero, NatType, VariableExp<Zero>, VariableExp<Zero> >, EmptyMap>::result::debugFlag == 1));

  // if (true) 0 else 1
  assert((TypeOf<IfExp<BoolLiteral<True>, NatLiteral<Zero>, NatLiteral<Succ<Zero> > >, EmptyMap>::result::debugFlag) == 1);

  // (_0: Int) => _0
  assert((TypeOf<LambdaExp<Zero, NatType, VariableExp<Zero> >, EmptyMap>::result::debugFlag) == 2);

  // ((_0: Int) => _0)(1)
  assert((TypeOf<CallExp<LambdaExp<Zero, NatType, VariableExp<Zero> >, NatLiteral<Succ<Zero> > >, EmptyMap>::result::debugFlag) == 1);

  // (0, true)
  assert((TypeOf<ProductExp<NatLiteral<Zero>, BoolLiteral<True> >, EmptyMap>::result::debugFlag) == 3);

  // fst((0, true))
  assert((TypeOf<FstExp<ProductExp<NatLiteral<Zero>, BoolLiteral<True> > >, EmptyMap>::result::debugFlag) == 1);

  // snd((0, true))
  assert((TypeOf<SndExp<ProductExp<NatLiteral<Zero>, BoolLiteral<True> > >, EmptyMap>::result::debugFlag) == 0);

  return 0;
}
