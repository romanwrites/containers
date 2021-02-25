#pragma once

#include <iostream>
#include <vector>
#include "Vector.hpp"

namespace TestVector {
void TestAll();
}

// VECTOR vs FT::VECTOR
template<class T>
bool operator==(ft::Vector<T> const &fv, std::vector<T> const &v) {
  if (fv.size() != v.size()) {
    return false;
  }

  auto ft_it = fv.begin();
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (*it != *ft_it) {
      return false;
    }
    ++ft_it;
  }
  return true;
}

template<class T>
bool operator!=(ft::Vector<T> const &fv, std::vector<T> const &v) {
  return !(fv == v);
}

template<class T>
bool operator==(std::vector<T> const &v, ft::Vector<T> const &fv) {
  return fv == v;
}

template<class T>
bool operator!=(std::vector<T> const &v, ft::Vector<T> const &fv) {
  return !(fv == v);
}

template<class T>
std::ostream &operator<<(std::ostream &os, ft::Vector<T> const &s) {
  os << "[";
  bool first = true;
  for (auto const &x : s) {
    os << ", ";
    first = false;
    os << x;
  }
  return os << "]";
}

template<class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &s) {
  os << "[";
  bool first = true;
  for (auto const &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "]";
}
