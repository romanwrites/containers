#pragma once
#include "Set.h"
#include <set>

namespace TestSet {
void TestAll();
#if PRINT_INT_TREE
void TestPrintSet();
#endif
}

// SET OUTPUT

template<class K>
std::ostream &operator<<(std::ostream &os, std::set<K> const &m) {
  os << "{";
  bool first = true;
  for (auto const &v : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << v;
  }
  return os << "}";
}

template<class K>
std::ostream &operator<<(std::ostream &os, ft::Set<K> const &m) {
  os << "{";
  bool first = true;
  for (auto const &v : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << v;
  }
  return os << "}";
}

// SET vs FT::SET
template<class K>
bool operator==(ft::Set<K> const &fm, std::set<K> const &m) {
  if (fm.size() != m.size()) {
    return false;
  }

  auto ft_it = fm.begin();
  for (auto it = m.begin(); it != m.end(); ++it) {
    if (*it != *ft_it) {
      return false;
    }
    ++ft_it;
  }
  return true;
}

template<class K>
bool operator!=(ft::Set<K> const &fm, std::set<K> const &m) {
  return !(fm == m);
}

template<class K>
bool operator==(std::set<K> const &m, ft::Set<K> const &fm) {
  return fm == m;
}

template<class K>
bool operator!=(std::set<K> const &m, ft::Set<K> const &fm) {
  return !(fm == m);
}
