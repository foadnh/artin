// main.cpp - some tests for the algebra system.
// complie with:
//   g++-mp-4.7 -o monoidtest monoidtest.cpp -Iinc -std=c++11
//

#include <iostream>
#include <functional>
#include "monoid.hpp"

int main(int agrc, const char** argv)
{
  static artin::monoid<int> integer_additive_monoid(std::plus<int>(), 0);
  static artin::monoid<int> integer_multiplicative_monoid(std::multiplies<int>(), 0);

  std::cout << "answer: " << integer_additive_monoid.Op(1, 1) << std::endl;
  std::cout << "answer: " << integer_multiplicative_monoid.Op(1, 1) << std::endl;
  return 0;

}

