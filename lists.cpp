#include <iostream>
#include "lists.h"
#include "peano.h"

int main() {
  Zero typedef zero;
  Succ<zero> typedef one;
  Succ<one> typedef two;
  Succ<two> typedef three;
  
  Cons<Zero, Cons<Zero, Nil> > typedef len2;
  Cons<one, Cons<two, Cons<three, Nil> > > typedef oneTwoThree;
  
  // Cons(Zero, Cons(Zero, Nil)).length
  //std::cout << Length<Cons<Zero, Cons<Zero, Nil> > >::result::value << std::endl;
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
  
  return 0;
}
