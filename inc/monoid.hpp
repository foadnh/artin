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
    typedef std::function<value_type(const value_type&, const value_type&)> binary_operator;
    typedef typename binary_operator::result_type result_type;
    typedef typename binary_operator::first_argument_type first_argument_type;
    typedef typename binary_operator::second_argument_type second_argument_type;
    
  private:
    binary_operator _bin_op;
    value_type _unit;
    
  public:
    monoid(const binary_operator& func, const value_type& unit):_bin_op(func), _unit(unit){}

	monoid(const monoid<value_type>& other) : _bin_op(other._bin_op), _unit(other._unit) {}

	monoid& operator=(const monoid<value_type>& other) {
		_bin_op = other._bin_op;
		_unit = other._unit;
		return *this;
	}
    
    result_type Op(const first_argument_type& lhs, const second_argument_type& rhs) const
    { return _bin_op(lhs, rhs); }
    
    const value_type& Unit() { return _unit; }

	// User need to overload == for binary function if wants to use compare operators
	// We can get rid of friend and templates, if we don't want to compare 2 different types
	template<typename T2>
	friend class monoid;
	template<typename T2>
	bool operator==(const monoid<T2>& other) {
		return typeid(value_type) == typeid(T2) &&
			(_bin_op == other._bin_op && _unit == other._unit);
	}
	template<typename T2>
	bool operator!=(const monoid<T2>& other) {
		return !(*this==other);
	}

  };
} //namespace artin
#endif //MONOID_HPP
