#pragma once
#include "Compare.h"

namespace ft {
template<class Iter, class Compare>
bool lexicographical_compare(Iter first1, Iter last1, Iter first2, Iter last2, Compare comp) {
  while (first2 != last2) {
    if (first1 == last1 || comp(*first1, *first2)) {
      return true;
    }
    if (comp(*first2, *first1)) {
      return false;
    }
    ++first1,
        (void) ++first2;
  }
  return false;
}

template<class Iter1, class Iter2, class Predicate>
bool equal(Iter1 first1, Iter1 last1, Iter2 first2, Predicate pred) {
  while (first1 != last1) {
    if (!pred(*first1, *first2)) {
      return false;
    }
    ++first1;
    ++first2;
  }
  return true;
}
}