// monoid.h
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

#ifndef ARTIN_MONOID_H_
#define ARTIN_MONOID_H_

#include <functional>
#include <typeinfo>

namespace artin {
template<typename T>
class Monoid {
 public:
  // various useful typedefs
  typedef T ValueType;

  // Monoid binary function
  typedef std::function<ValueType(const ValueType&,
                                  const ValueType&)> BinaryOperator;

  Monoid(const BinaryOperator& bin_op, const ValueType& identity);
  // Copy constructor
  explicit Monoid(const Monoid& other);

  virtual ~Monoid();

  virtual Monoid& operator=(const Monoid<ValueType>& other);

  inline ValueType Op(const ValueType& lhs, const ValueType& rhs) const {
    return bin_op_(lhs, rhs);
  }

  inline ValueType& identity() {
    return identity_;
  }

  // User need to overload == for binary function if wants to use
  // compare operators.
  virtual bool operator==(const Monoid& other);
  virtual bool operator!=(const Monoid& other);

  virtual ValueType Power(const ValueType& x, const int& n) const;

 protected:
  BinaryOperator bin_op_;
  ValueType identity_;
};
}  // namespace artin

#include "monoid.cc"
#endif  // ARTIN_MONOID_H_
