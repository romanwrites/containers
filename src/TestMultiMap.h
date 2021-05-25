#pragma once

#include <iostream>
#include <map>
#include "MultiMap.h"

namespace TestMultiMap {
void TestAll();
}

// MULTI MAP OUTPUT

template<class K, class V>
std::ostream &operator<<(std::ostream &os, std::multimap<K, V> const &m) {
  os << "{";
  bool first = true;
  for (auto const &kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class K, class V>
std::ostream &operator<<(std::ostream &os, ft::MultiMap<K, V> const &m) {
  os << "{";
  bool first = true;
  for (auto const &kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

// STD::MULTIMAP vs FT::MULTIMAP
template<class K, class V>
bool operator==(ft::MultiMap<K, V> const &fm, std::multimap<K, V> const &m) {
  if (fm.size() != m.size()) {
    return false;
  }

  auto ft_it = fm.begin();
  for (auto it = m.begin(); it != m.end(); ++it) {
    if (it->first != ft_it->first || it->second != ft_it->second) {
      return false;
    }
    ++ft_it;
  }
  return true;
}

template<class K, class V>
bool operator!=(ft::MultiMap<K, V> const &fm, std::multimap<K, V> const &m) {
  return !(fm == m);
}

template<class K, class V>
bool operator==(std::multimap<K, V> const &m, ft::MultiMap<K, V> const &fm) {
  return fm == m;
}

template<class K, class V>
bool operator!=(std::multimap<K, V> const &m, ft::MultiMap<K, V> const &fm) {
  return !(fm == m);
}
