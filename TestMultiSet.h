#pragma once
#include "MultiSet.h"
#include <set>

namespace TestMultiSet {
void TestAll();
}

// MULTISET OUTPUT

template<class K>
std::ostream &operator<<(std::ostream &os, std::multiset<K> const &m) {
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
std::ostream &operator<<(std::ostream &os, ft::MultiSet<K> const &m) {
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

// STD::MULTISET vs FT::MULTISET
template<class K>
bool operator==(ft::MultiSet<K> const &fm, std::multiset<K> const &m) {
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
bool operator!=(ft::MultiSet<K> const &fm, std::multiset<K> const &m) {
  return !(fm == m);
}

template<class K>
bool operator==(std::multiset<K> const &m, ft::MultiSet<K> const &fm) {
  return fm == m;
}

template<class K>
bool operator!=(std::multiset<K> const &m, ft::MultiSet<K> const &fm) {
  return !(fm == m);
}
