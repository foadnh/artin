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

    protected:
      unary_operator _invert;

    public:
      group(const binary_operator& func, const value_type& unit, const unary_operator& invert)
      :base_type(func,unit), _invert(invert) {}
      group(const base_type& mon, const unary_operator& invert)
      :base_type(mon), _invert(invert){}
      group(const group& grp)
      :base_type(grp), _invert(grp._invert){}

      value_type Invert(const value_type& value)
      { return _invert(value); }

      group& operator=(const group& other)
      {
		  base_type::operator=(other);
		  _invert = other._invert;
      }

	// User need to overload == for binary function and ivert function if wants to use compare operators
	// We can get rid of friend and templates, if we don't want to compare 2 different types
	template<typename T2>
	friend class group;
	template<typename T2>
	bool operator==(const group<T2>& other) {
		return base_type::operator==(other) && _invert == other._invert;
	}
	template<typename T2>
	bool operator!=(const group<T2>& other) {
		return !(*this==other);
	}

	virtual value_type power(const value_type& x, const int& n) const {
		if (n < 0)
			return base_type::power(_invert(x), -n);
		else
			return base_type::power(x, n);
	} // Speed: O(lg(n))

  };
};

#endif //GROUP_H

