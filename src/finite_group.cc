#include "finite_group.h"

namespace artin {
template<typename T>
FiniteGroup<T>::FiniteGroup(const BinaryOperator& bin_op,
                            const ValueType& identity,
                            const UnaryOperator& invert,
                            const ValueType& order)
  : BaseType(bin_op, identity, invert), order_(order), orders_(nullptr) {
}

template<typename T>
FiniteGroup<T>::FiniteGroup(const BaseType& group, const ValueType& order)
  : BaseType(group), order_(order), orders_(nullptr) {
}

// Copy constructor
template<typename T>
FiniteGroup<T>::FiniteGroup(const FiniteGroup& other)
  : BaseType(other), order_(other.order_) {
  if (other.orders_) {
    orders_ = new ValueType[other.order_];

    for (ValueType i = 0; i < other.order_; i++)
      orders_[i] = other.orders_[i];
  } else {
    orders_ = nullptr;
  }
}

template<typename T>
FiniteGroup<T>::~FiniteGroup() {
  if (orders_)
    delete[] orders_;
}

template<typename T>
FiniteGroup<T>& FiniteGroup<T>::operator=(const FiniteGroup& other) {
  BaseType::operator=(other);
  order_ = other.order_;

  if (orders_)
    delete[] orders_;

  if (other.orders_) {
    orders_ = new ValueType[other.order_];

    for (ValueType i = 0; i < other.order_; i++)
      orders_[i] = other.orders_[i];
  } else {
    orders_ = nullptr;
  }

  return *this;
}

template<typename T>
T FiniteGroup<T>::order(const ValueType& value) const {
  if (orders_)
    return orders_[value];

  ValueType now = value;

  for (ValueType i = 1; i <= order_; i++) {
    if (now == BaseType::identity_)
      return i;

    now = BaseType::Op(now, value);
  }

  return 0;
}  // Speed: O(1) if GenerateStaticOrders() called. Otherwise O(order_).

// This function calculate orders of elements and store them in orders_ array.
// It do it with recursive function, RevursiveCalculateOrders;
template<typename T>
void FiniteGroup<T>::GenerateStaticOrders() {
  if (orders_)
    return;

  orders_ = new ValueType[order_];
  orders_[BaseType::identity_] = 1;

  ValueType now;

  for (ValueType i = 0; i < order_; i++) {
    now = i;

    for (ValueType j = 1; j <= order_; j++) {
      if (now == BaseType::identity_) {
        orders_[i] = j;
        break;
      } else {
        now = BaseType::Op(now, i);
      }

      // TODO(Reduce speed time)
      // if (!orders_[i])
      // RecursiveCalculateOrders(i, i);
    }
  }
}  // Speed: O(order_^2), Memory: O(order_)

// It reduce exponent by mod of orders_[x] (if exists), or order_.
// Then calculate it with BaseType Power.
template<typename T>
T FiniteGroup<T>::Power(const ValueType & x, const int& n) const {
  if (orders_)
    return BaseType::Power(x, n % orders_[x]);
  else
    return BaseType::Power(x, n % order_);
}
// Speed: if static orders generated: O(min{lg(n), lg(orders_[x])})
// else O(min{lg(n), lg(order_)})

// This function checks if all Op(i, j) == Op(j, i) or not.
template<typename T>
bool FiniteGroup<T>::IsAbelian() const {
  for (ValueType i = order_ - 1; i >= 0; i--)
    for (ValueType j = 0; j < i; j++)
      if (BaseType::Op(i, j) != BaseType::Op(j, i))
        return false;

  return true;
}  // Speed: O(order_^2)

// This function checks if order of an element equals to order_.
template<typename T>
bool FiniteGroup<T>::IsCyclic() const {
  if (orders_) {
    for (ValueType i = 0; i < order_; i++)
      if (orders_[i] == order_)
        return true;
  } else {
    for (ValueType i = 0; i < order_; i++)
      if (order(i) == order_)
        return true;
  }

  return false;
}  // Speed: if static orders generated: O(order_) else: O(order_^3)

/* TODO(Fix it)
/* TODO(Fix it)
// Private funtion
// Used by GenerateStaticOrders
template<typename T>
ValueType FiniteGroup<T>::RecursiveCalculateOrders(ValueType base, ValueType now) {
  if (!orders_[now])
    orders_[now] = RecursiveCalculateOrders(base, BaseType::bin_op_(now, base)) + 1;

  return orders_[now];
}*/
}  // namespace artin
