// grouptest.cpp - some tests for the algebra system.
// compile with:
//   g++-mp-4.7 -o grouptest grouptest.cpp -Iinc -std=c++11
//

#include <iostream>
#include <functional>

#include "group.hpp"
#include "function_composition_monoid.hpp"

int main(int argc, const char** argv)
{
  static artin::group<int> integer_additive_group(std::plus<int>(), 0, std::negate<int>());
  if (integer_additive_group.Op(1, integer_additive_group.Invert(1)) 
      == integer_additive_group.Unit())
  {
    std::cout << "True" << std::endl;
  }
  else
  {
    std::cout << "False" << std::endl;
  }

  return 0;

}

