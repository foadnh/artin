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
  class group
  {
    public:
      typedef T value_type;
    
      // group binary function
      typedef monoid<value_type> monoid_type;
      typedef typename monoid_type::binary_operator binary_operator;
      typedef typename monoid_type::result_type result_type;
      typedef typename monoid_type::first_argument_type first_argument_type;
      typedef typename monoid_type::second_argument_type second_argument_type;
      typedef std::function<value_type(value_type)> unary_operator;

    private:
      monoid_type _monoid;
      unary_operator _invert;

    public:
      group(const binary_operator& func, const value_type& unit, const unary_operator& invert)
      :_monoid(func,unit), _invert(invert) {}
      group(const monoid_type& mon, const unary_operator& invert)
      :_monoid(mon), _invert(invert){}
      group(const group& grp)
      :_monoid(grp._monoid), _invert(grp._invert){}

      /* assignment
      group& operator=(const group& grp)
      {
        _moinoid = grp._monoid;
        _invert = grp._invert;
      }
      */

      result_type Op(const first_argument_type& lhs, const second_argument_type& rhs) const
      { return _monoid.Op(lhs, rhs); }

      value_type Unit()
      { return _monoid.Unit(); }

      value_type Invert(const value_type& value)
      { return _invert(value); }
  };
};

#endif //GROUP_H

