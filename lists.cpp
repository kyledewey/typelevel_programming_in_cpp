#include <iostream>
#include "lists.h"
#include "peano.h"

int main() {
  Cons<Zero, Cons<Zero, Nil> > typedef len2;
  
  // Cons(Zero, Cons(Zero, Nil)).length
  //std::cout << Length<Cons<Zero, Cons<Zero, Nil> > >::result::value << std::endl;
  std::cout << Length<len2>::result::value << std::endl;
  
  // Cons(Zero, Cons(Zero, Nil)).append(Cons(Zero, Cons(Zero, Nil))).length
  std::cout << Length<Append<len2, len2>::result>::result::value << std::endl;
  
  return 0;
}
