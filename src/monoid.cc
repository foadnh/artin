#include "monoid.h"

namespace artin {

template<typename T>
Monoid<T>::Monoid(const BinaryOperator& bin_op, const ValueType& identity)
  : bin_op_(bin_op), identity_(identity) {
}

template<typename T>
Monoid<T>::Monoid(const Monoid& other)
  : bin_op_(other.bin_op_), identity_(other.identity_) {
}

template<typename T>
Monoid<T>::~Monoid() {
}

template<typename T>
Monoid<T>& Monoid<T>::operator=(const Monoid& other) {
  bin_op_ = other.bin_op_;
  identity_ = other.identity_;
  return *this;
}

template<typename T>
bool Monoid<T>::operator==(const Monoid& other) {
  return bin_op_ == other.bin_op_ && identity_ == other.identity_;
}
template<typename T>
bool Monoid<T>::operator!=(const Monoid& other) {
  return !(*this == other);
}

// This function products power of x to n recursively. But it compute it
// straitly for small powers (less or equal to 30).
// Returns identity for zero or negative numbers.
template<typename T>
T Monoid<T>::Power(const ValueType& x, const int& n) const {
  if (n <= 0)
    return identity_;

  ValueType result = x;

  if (n < 31) {  // This number may not be the best one.
    for (int i = 1; i < n; i++)
      result = bin_op_(result, x);

    return result;
  }

  result = Power(x, n / 2);  // result variable is not final result.

  if (n % 2)
    return bin_op_(bin_op_(result, result), x);
  else
    return bin_op_(result, result);
}  // Speed: O(lg(n))
}  // namespace artin
