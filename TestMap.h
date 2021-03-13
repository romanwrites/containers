#pragma once

#include <iostream>
#include <map>
#include "Map.h"

namespace TestMap {
void TestAll();
}

// MAP OUTPUT

template<class K, class V>
std::ostream &operator<<(std::ostream &os, std::map<K, V> const &m) {
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
//todo
//template<class K, class V>
//std::ostream &operator<<(std::ostream &os, ft::Map<K, V> const &m) {
//  os << "{";
//  bool first = true;
//  for (auto const &kv : m) {
//    if (!first) {
//      os << ", ";
//    }
//    first = false;
//    os << kv.first << ": " << kv.second;
//  }
//  return os << "}";
//}
