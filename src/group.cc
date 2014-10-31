#include "monoid.h"

namespace artin {
template<typename T>
Group<T>::Group(const BinaryOperator& bin_op, const ValueType& identity,
                const UnaryOperator& invert)
  : BaseType(bin_op, identity), invert_(invert) {
}

template<typename T>
Group<T>::Group(const BaseType& monoid, const UnaryOperator& invert)
  : BaseType(monoid), invert_(invert) {
}

// Copy constructor
template<typename T>
Group<T>::Group(const Group& other)
  : BaseType(other), invert_(other.invert_) {
}

template<typename T>
Group<T>::~Group() {
}

template<typename T>
Group<T>& Group<T>::operator=(const Group& other) {
  BaseType::operator=(other);
  invert_ = other.invert_;
  return *this;
}

// If n is negetive, we first calculate invert of x, then use parents Power.
template<typename T>
T Group<T>::Power(const ValueType& x, const int& n) const {
  if (n < 0)
    return BaseType::Power(invert_(x), -n);
  else
    return BaseType::Power(x, n);
}  // Speed: O(lg(n))
};  // namespace artin
