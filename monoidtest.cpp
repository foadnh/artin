// main.cpp - some tests for the algebra system.
// compile with:
//   g++-mp-4.7 -o monoidtest monoidtest.cpp -Iinc -std=c++11
//

#include <iostream>
#include <functional>
#include <cassert>

#include "monoid.hpp"
#include "function_composition_monoid.hpp"



int main(int agrc, const char** argv)
{

  artin::monoid<artin::unary_func<int> > cm = artin::function_composition_monoid<int>::mon();
  const artin::unary_func<int> fx([](int a){return a+a;});
  const artin::unary_func<int> gx([](int b){return b*b;});
  auto r = cm.Op(fx, gx)(3);

  static artin::monoid<int> integer_additive_monoid(std::plus<int>(), 0);
  static artin::monoid<int> integer_additive_monoid2(std::plus<int>(), 0);
  static artin::monoid<int> integer_multiplicative_monoid(std::multiplies<int>(), 0);

  assert(integer_additive_monoid == integer_additive_monoid2);

  std::cout << "answer: " << integer_additive_monoid.Op(1, 1) << std::endl;
  std::cout << "answer: " << integer_multiplicative_monoid.Op(1, 1) << std::endl;
  std::cout << "answer: " << r << std::endl;
  return 0;

}

