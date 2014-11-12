/* finite_cyclic.h
 */

#ifndef ARTIN_FINITE_CYCLIC_H_
#define ARTIN_FINITE_CYCLIC_H_

#include "finite_group.h"

namespace artin {

class FiniteCyclic : public FiniteGroup<int> {
 public:
  typedef int ValueType;
  typedef FiniteGroup<ValueType> BaseType;

  explicit FiniteCyclic(const int& order);
  explicit FiniteCyclic(const FiniteCyclic& order);

  virtual ~FiniteCyclic();

  // Why we need this function when the other order is defined? Otherwise not.
  inline ValueType order() const {
    return BaseType::order();
  }

  virtual ValueType order(const ValueType& value) const;

  virtual ValueType Power(const ValueType& x, const int& n) const;
  virtual bool IsAbelian() const;
  virtual bool IsCyclic() const;

 private:
  ValueType GCDWithOrder(int x) const;
};
}  // namespace artin

#include "finite_cyclic.cc"
#endif  // ARTIN_FINITE_CYCLIC_H_
