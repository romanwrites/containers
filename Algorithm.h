#pragma once
#include "Compare.h"

namespace ft {
template<class Iter1, class Iter2, class Compare>
bool lexicographical_compare_custom(Iter1 first1, Iter1 last1,
                             Iter2 first2, Iter2 last2, Compare comp) {
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

template<class Iter1, class Iter2>
bool lexicographical_compare(Iter1 first1, Iter1 last1,
                             Iter2 first2, Iter2 last2) {
  while (first1 != last1) {
    if (first2 == last2 || *first2 < *first1) {
      return false;
    }
    else if (*first1 < *first2) {
      return true;
    }
    ++first1;
    ++first2;
  }
  return (first2 != last2);
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
