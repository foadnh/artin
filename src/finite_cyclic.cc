#include "finite_cyclic.h"

namespace artin {

int finite_cyclic_bin_op(const int& order, const int& lhs, const int& rhs);
int finite_cyclic_invert(const int& order, const int& value);

FiniteCyclic::FiniteCyclic(const int& order)
  : BaseType(std::bind(finite_cyclic_bin_op,
                       order,
                       std::placeholders::_1,
                       std::placeholders::_2),
             0,
             std::bind(finite_cyclic_invert,
                       order,
                       std::placeholders::_1),
             order) {
}

// Copy constructor
FiniteCyclic::FiniteCyclic(const FiniteCyclic& other)
  : BaseType(other) {
}

FiniteCyclic::~FiniteCyclic() {
}

// Calculates order of a value with order / gcd(order, value) if order > 60
// otherwise it uses FiniteGroup's order function. 60 could be changed for
// better performance.
int FiniteCyclic::order(const ValueType& value) const {
  if (BaseType::order_ < 60)
    return BaseType::order(value);
  else
    return BaseType::order_ / GCDWithOrder(value % BaseType::order_);
}  // Speed: O(GCDWithOrder)

int FiniteCyclic::Power(const ValueType& x, const int& n) const {
  return (x * (n % order_)) % order_;
}  // Speed: O(1)

bool FiniteCyclic::IsAbelian() const {
  return true;
}  // Speed: O(1)

bool FiniteCyclic::IsCyclic() const {
  return true;
}  // Speed: O(1)

// This function uses Stein's binary GCD algorithm.
// This algorithm only works with posetive numbers.
int FiniteCyclic::GCDWithOrder(int x) const {
  // x and order can't be const, this algorithm change them.
  int shift, order = BaseType::order_;
  // Uncomment following line if x could be < 0 or > order.
  // x %= order;

  if (x == 0)
    return order;

  // Let shift := lg K, where K is the greatest power of 2
  // dividing both x and order.
  for (shift = 0; ((x | order) & 1) == 0; ++shift) {
    x >>= 1;
    order >>= 1;
  }

  // I'm not sure if order and x should swap or not for better performance.
  while ((order & 1) == 0)
    order >>= 1;

  // From here on, order is always odd.
  do {
    // Remove all factors of 2 in x -- they are not common
    // Note: x is not zero, so while will terminate
    while ((x & 1) == 0)
      x >>= 1;

    /* Now order and x are both odd. Swap if necessary so x <= order,
     * then set order = order - x (which is even). For bignums, the
     * swapping is just pointer movement, and the subtraction
     * can be done in-place.
     */
    if (x > order) {
      int t = order;
      order = x;
      x = t;
    }  // Swap order and x.

    order = order - x;  // Here order >= x.
  } while (order != 0);

  // Restore common factors of 2.
  return x << shift;
}  // Speed: 60% more efficient on average than the Euclidean algorithm

int finite_cyclic_bin_op(const int& order, const int& lhs, const int& rhs) {
  return (lhs + rhs) % order;
}  // Speed: O(1)

int finite_cyclic_invert(const int& order, const int& value) {
  return (order - value) % order;
}  // Speed: O(1)
}  // namespace artin
