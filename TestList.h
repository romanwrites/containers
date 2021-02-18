#pragma once

#include <iostream>
#include <list>
#include "List.hpp"

namespace TestList {
void TestAll();
}

// LIST vs FT::LIST
template<class T>
bool operator==(ft::List<T> const &ftlst, std::list<T> const &lst) {
  if (ftlst.size() != lst.size()) {
    return false;
  }

  auto ft_it = ftlst.begin();
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    if (*it != *ft_it) {
      return false;
    }
    ++ft_it;
  }
  return true;
}

template<class T>
bool operator!=(ft::List<T> const &ftlst, std::list<T> const &lst) {
  return !(ftlst == lst);
}

template<class T>
bool operator==(std::list<T> const &lst, ft::List<T> const &ftlst) {
  return ftlst == lst;
}

template<class T>
bool operator!=(std::list<T> const &lst, ft::List<T> const &ftlst) {
  return !(ftlst == lst);
}

template<class T>
std::ostream &operator<<(std::ostream &os, std::list<T> const &s) {
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

template<class T>
std::ostream &operator<<(std::ostream &os, ft::List<T> const &s) {
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
