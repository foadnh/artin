/* finite_group.h
 *
 * There are some problems if we use general set az template T with orders.
 * We should fix it.
*/

#ifndef ARTIN_FINITE_GROUP_H_
#define ARTIN_FINITE_GROUP_H_

#include "group.h"

namespace artin {
template<typename T = int>
class FiniteGroup : public Group<T> {
 public:
  typedef T ValueType;
  typedef Group<ValueType> BaseType;
  typedef typename BaseType::BinaryOperator BinaryOperator;
  typedef std::function<ValueType(ValueType)> UnaryOperator;

  FiniteGroup(const BinaryOperator& bin_op, const ValueType& identity,
              const UnaryOperator& invert, const ValueType& order);
  FiniteGroup(const BaseType& group, const ValueType& order);
  // Copy constructor
  explicit FiniteGroup(const FiniteGroup& other);

  virtual ~FiniteGroup();

  virtual FiniteGroup& operator=(const FiniteGroup& other);

  inline ValueType order() const {
    return order_;
  }
  virtual ValueType order(const ValueType& value) const;
  virtual void GenerateStaticOrders();

  virtual ValueType Power(const ValueType& x, const int& n) const;
  virtual bool IsAbelian() const;
  virtual bool IsCyclic() const;

 protected:
  ValueType order_;
  ValueType* orders_;  // It is not meaningful if TypeValue is not integer.

 private:
  // Need by GenerateStaticOrders.
  // ValueType RecursiveCalculateOrders(ValueType base, ValueType now);
};
};  // namespace artin

#include "finite_group.cc"
#endif  // ARTIN_FINITE_GROUP_H_
