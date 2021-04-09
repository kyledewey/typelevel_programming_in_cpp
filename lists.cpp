#include <iostream>
#include "lists.h"
#include "peano.h"

int main() {
  using zero = Zero;
  using one = Succ<zero>;
  using two = Succ<one>;
  using three = Succ<two>;

  using len2 = Cons<Zero, Cons<Zero, Nil> >;
  using oneTwoThree = Cons<one, Cons<two, Cons<three, Nil> > >;
  
  // Cons(Zero, Cons(Zero, Nil)).length
  std::cout << "length of list with two elements: "
            << Length<len2>::result::value << std::endl;
  
  // Cons(Zero, Cons(Zero, Nil)).append(Cons(Zero, Cons(Zero, Nil))).length
  std::cout << "length of appending two two-element list together: "
            << Length<Append<len2, len2>::result>::result::value << std::endl;

  // Cons(1, Cons(2, Cons(3, Nil))).getNth(1)
  std::cout << "first element (starting from zero) from a list 1, 2, 3: "
            << GetNth<oneTwoThree, one>::result::value << std::endl;

  // Cons(1, Cons(2, Cons(3, Nil))).reverse[0]
  std::cout << "[1, 2, 3].reverse[0]: "
            << Reverse<oneTwoThree>::result::head::value << std::endl;

  std::cout << "[1, 2, 3].sum: "
            << Sum<oneTwoThree>::result::value << std::endl;
  
  return 0;
}
