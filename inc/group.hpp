// group.hpp
// a template class for defining group objects.  The groups are
//  defined by applying a type to the group class.  The type 
//  defines the set on which the group operations and definitions 
//  operate.
//
//  See grouptest.cpp for an example construction and constraint.
//
#ifndef GROUP_HPP
#define GROUP_H

#include <functional>

#include "monoid.hpp"
#include "function_composition_monoid.hpp"

namespace artin
{
  template<class T>
  class group : public monoid<T>
  {
    public:
      typedef T value_type;
    
      // group binary function
      typedef monoid<value_type> base_type;
      typedef typename base_type::binary_operator binary_operator;
      typedef std::function<value_type(value_type)> unary_operator;

    private:
      unary_operator _invert;

    public:
      group(const binary_operator& func, const value_type& unit, const unary_operator& invert)
      :base_type(func,unit), _invert(invert) {}
      group(const base_type& mon, const unary_operator& invert)
      :base_type(mon), _invert(invert){}
      group(const group& grp)
      :base_type(grp._monoid), _invert(grp._invert){}

      /* assignment
      group& operator=(const group& grp)
      {
        _moinoid = grp._monoid;
        _invert = grp._invert;
      }
      */

      value_type Invert(const value_type& value)
      { return _invert(value); }
  };
};

#endif //GROUP_H

