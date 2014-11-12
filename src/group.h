/* group.h
 * a template class for defining group objects.  The groups are
 * defined by applying a type to the group class.  The type
 * defines the set on which the group operations and definitions
 * operate.
 *
 * See grouptest.cpp for an example construction and constraint.
 */
#ifndef ARTIN_GROUP_H_
#define ARTIN_GROUP_H_

#include <functional>

#include "monoid.h"

namespace artin {
template<class T>
class Group : public Monoid<T> {
 public:
  typedef T ValueType;

  // group binary function
  typedef Monoid<ValueType> BaseType;
  typedef typename BaseType::BinaryOperator BinaryOperator;
  typedef std::function<ValueType(ValueType)> UnaryOperator;

  Group(const BinaryOperator& bin_op, const ValueType& identity,
        const UnaryOperator& invert);
  Group(const BaseType& monoid, const UnaryOperator& invert);
  // Copy constructor
  explicit Group(const Group& other);

  virtual ~Group();

  inline ValueType Invert(const ValueType& value) {
    return invert_(value);
  }

  virtual Group& operator=(const Group& other);

  // User need to overload == for binary function and ivert function
  // if wants to use compare operators.
  // These functions need to be inline so can't be virtual to prevent
  // compiling errors when == is not overloaded for functions.
  inline bool operator==(const Group& other) const {
    return BaseType::operator==(other) && invert_ == other.invert_;
  }
  inline bool operator!=(const Group& other) const {
    return !(*this == other);
  }

  virtual ValueType Power(const ValueType& x, const int& n) const;

 protected:
  UnaryOperator invert_;
};
}  // namespace artin

#include "group.cc"
#endif  // ARTIN_GROUP_H_
