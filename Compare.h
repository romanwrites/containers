#pragma once

namespace ft {
// -------------------------------------- COMPARE -------------------------------------
template<class Arg1, class Arg2, class Result>
struct binary_function {
  typedef Arg1 first_argument_type;
  typedef Arg2 second_argument_type;
  typedef Result result_type;
};

template<class T>
struct less : binary_function<T, T, bool> {
  bool operator()(T const &x, T const &y) const {
    return x < y;
  }
};

template<class T>
struct greater : binary_function<T, T, bool> {
  bool operator()(T const &x, T const &y) const {
    return x > y;
  }
};

template<class T>
struct equal_to : binary_function<T, T, bool> {
  bool operator()(T const &x, T const &y) const {
    return x == y;
  }
};
}
