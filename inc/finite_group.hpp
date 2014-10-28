/* finite_group.hpp
 *
 * There are some problems if we use general set az template T with orders.
 * We should fix it.
**/

#ifndef FINITE_GROUP_HPP
#define FINITE_GROUP_HPP

#include "group.hpp"

namespace artin {
template<typename T = int>
class FiniteGroup : public group<T> {
public:
	typedef T value_type;

	// group binary function
	typedef group<value_type> base_type;
	typedef typename base_type::binary_operator binary_operator;
	typedef std::function<value_type(value_type)> unary_operator;

protected:
	value_type _order;
	value_type* _orders;

private:
	value_type recursive_calculate_orders(value_type base, value_type now) {
		if (!_orders[now])
			_orders[now] = recursive_calculate_orders(base, base_type::_bin_op(now, base)) + 1;

		return _orders[now];
	}

public:
	FiniteGroup(const binary_operator& func, const value_type& unit,
				const unary_operator& invert, const value_type& order)
		: base_type(func, unit, invert), _order(order), _orders(NULL) {}
	FiniteGroup(const base_type& group, const value_type& order)
		: base_type(group), _order(order), _orders(NULL) {}
	// Copy constructor
	FiniteGroup(const FiniteGroup& other)
		: base_type(other), _order(other._order) {
		if (other._orders) {
			_orders = new value_type[other._order];

			for (value_type i = 0; i < other._order; i++)
				_orders[i] = other._orders[i];
		} else
			_orders = NULL;
	}

	~FiniteGroup() {
		if (_orders)
			delete[] _orders;
	}

	FiniteGroup& operator=(const FiniteGroup& other) {
		base_type::operator=(other);
		_order = other._order;

		if (_orders)
			delete[] _orders;

		if (other._orders) {
			_orders = new value_type[other._order];

			for (value_type i = 0; i < other._order; i++)
				_orders[i] = other._orders[i];
		} else
			_orders = NULL;
	}

	value_type order() {
		return _order;
	}

	value_type order(const value_type& value) {
		if (_orders)
			return _orders[value];

		value_type now = value;

		for (value_type i = 1; i <= _order; i++) {
			if (now == base_type::_unit)
				return i;

			now = base_type::Op(now, value);
		}

		return 0;
	}

	void generate_static_orders() {
		if (_orders)
			return;

		_orders = new value_type[_order]();
		_orders[base_type::_unit] = 1; // Why do we need base_type:: here?

		for (value_type i = 0; i < _order; i++)
			if (!_orders[i])
				recursive_calculate_orders(i, i);
	}

	virtual value_type power(const value_type& x, const int& n) const {
		if (_orders)
			return base_type::power(x, n % _orders[x]);
		else
			return base_type::power(x, n % _order);
	} // Speed: if static orders generated: O(min{lg(n), lg(_orders[x])}) else O(min{lg(n), lg(_order)})

};

}; // namespace artin

#endif //FINITE_GROUP_HPP
