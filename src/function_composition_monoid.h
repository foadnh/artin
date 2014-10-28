// function_composition_monoid.h
// create a monoid that composes unary functions.
// for example:
//      monoid<unary_func<int> > cm = function_composition_monoid<int>::mon();
//      const unary_func<int> fx([](int a){return a+a;});
//      const unary_func<int> gx([](int b){return b*b;});
//      auto r = cm.Op(fx, gx)(3);
//     at this point r = (3*3) + (3*3) = 18
//
//
#ifndef ARTIN_FUNCTION_COMPOSITION_MONOID_H_
#define ARTIN_FUNCTION_COMPOSITION_MONOID_H_

#include <functional>

namespace artin {
/**!
* unary_function wraps std::function for the unary function special case.
* Note that copy constructor and assignment are commented out.  these could
* be established if needed later.
*/
template<class P>
struct unary_func {
 public:
    typedef P value_type;

    typedef std::function<value_type(const value_type&)> unary_operator;
    typedef typename unary_operator::result_type result_type;
    typedef typename unary_operator::argument_type argument_type;

 private:
    const unary_operator _unary_op;

 public:
    unary_func(const unary_operator& op): _unary_op(op) {}
    //    unary_func(const unary_func& u):_unary_op(u._unary_op) {}
    //
    //    unary_func& operator=(const unary_func& u)
    //    {
    //      if (this != &u)
    //      {
    //        _unary_op = u._unary_op;
    //      }
    //      return *this;
    //    }

    result_type operator()(const argument_type& p) const {
        return _unary_op(p);
    }
};

template<class P>
class function_composition_monoid {
 public:
    typedef P value_type;
    typedef unary_func<value_type> func_type;
 private:
    static const func_type _unit;

    static func_type compose(const func_type& lhs, const func_type& rhs) {
        return func_type([lhs, rhs](const typename func_type::result_type & a)
            -> typename func_type::result_type { return lhs(rhs(a)); });
    }

    static const typename func_type::value_type& identity
    (const typename func_type::value_type& a) {
        return a;
    }

 public:
    static monoid<func_type> mon() {
        typename monoid<func_type>::binary_operator c = compose;
        return monoid<func_type>(compose, func_type(identity));
    }
};
};  // namespace artin

#endif  // ARTIN_FUNCTION_COMPOSITION_MONOID_H_

