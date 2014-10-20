// monoid.hpp
// A template class for defining monoids.  This class defines a set 
// of delegated functions using std::function.  you can construct 
// the class by providing an associative binary operator and a type
// that defines the "set" on which the monoid applies.
//
//
// Here are some simple single instance examples of the monoid:
// integer additive monoid:
//    static monoid<int> integer_additive_monoid(std::plus<int>(), 0);
// integer multiplicative monoid:
//    static monoid<int> integer_multiplicative_monoid(std::multiply<int>(), 0);
// etc. (remember to #include <functional> for plus<> and multiply<>)
// you can run the binary operation by supplying parameters to the operator:
//
//    integer_additive_monoid.Op(1, 1) will output "2".
//    integer_multiplicative_monoid.Op(1,1) will output "1"

#ifndef MONOID_HPP
#define MONOID_HPP

#include <functional>
#include <typeinfo>

namespace artin
{
  template<class T>
  class monoid
  {
  public:
    // various useful typedefs
    typedef T value_type;
    
    // monoid binary function
    typedef monoid self_type;
    typedef std::function<value_type(const value_type&, const value_type&)> binary_operator;
    typedef typename binary_operator::result_type result_type;
    typedef typename binary_operator::first_argument_type first_argument_type;
    typedef typename binary_operator::second_argument_type second_argument_type;
    
  private:
    binary_operator _bin_op;
    const value_type _unit;
    
  public:
    monoid(const binary_operator& func, const value_type& unit):_bin_op(func), _unit(unit){}

	monoid(const monoid<value_type>& other) : _bin_op(other._bin_op), _unit(other._unit) {}

	// Do we need assignment operator or not? If yes, we have to remove const from data members.
	/*monoid& operator=(const monoid<value_type>& other) {
		_bin_op = other._bin_op;
		_unit = other._unit;
		return *this;
	}*/
    
    result_type Op(const first_argument_type& lhs, const second_argument_type& rhs) const
    { return _bin_op(lhs, rhs); }
    
    const value_type& Unit() { return _unit; }

	  friend
    const bool operator==(const self_type& left, const self_type& right) {
      return typeid(left) == typeid(right)  && 
      left._unit == right._unit             && 
      typeid(left._bin_op) == typeid(right._bin_op);
    }

    friend
    const bool operator!=(const self_type& left, const self_type& right) {
      return !(left==right);
    }

  };
/*
  /// compare operators for monoids of potentially different value_types
  template<class MONOID1, class MONOID2>
  bool operator==(const MONOID1& lhs, const MONOID& rhs) const
  {
    // compare types
    if (typeid(MONOID1::value_type) != typeid(MONOID2::value_type))
    {
      return false;
    }
    return lhs == rhs;
  }

  template<class MONOID1, class MONOID2>
  bool operator==(const MONOID1& lhs, const MONOID& rhs) const
  {
    return !(lhs == rhs);
  }
*/
};
#endif //MONOID_HPP
