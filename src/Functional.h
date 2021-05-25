#pragma once

namespace ft {

template<typename Arg, typename Result>
struct unary_function {
  typedef Arg argument_type;
  typedef Result result_type;
};

template<typename Pair>
struct SelectFirst : public ft::unary_function<Pair, typename Pair::first_type> {
  typename Pair::first_type &operator()(Pair &x) const {
    return x.first;
  }

  const typename Pair::first_type &operator()(const Pair &x) const {
    return x.first;
  }
};

template<typename T>
struct Identity : public ft::unary_function<T, T> {
  T &operator()(T &x) const {
    return x;
  }

  const T &operator()(const T &x) const {
    return x;
  }
};

}