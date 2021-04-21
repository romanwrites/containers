#pragma once
#include "IteratorTraits.h"
#include <iterator>
#include <utility>
namespace ft {

template<class Iterator>
class ReverseIterator {
 public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename ft::iterator_traits<Iterator>::value_type value_type;
  typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::pointer pointer;
  typedef typename ft::iterator_traits<Iterator>::reference reference;

 private:
  iterator_type it;

 public:
  ReverseIterator() {
  }

  explicit ReverseIterator(iterator_type it) : it(it) {
  }

  template<class Iter>
  ReverseIterator(const ReverseIterator<Iter> &rev_it) : it(rev_it.base()) {
  }

  iterator_type base() const {
    return it;
  }

// Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it.
// https://www.cplusplus.com/reference/iterator/reverse_iterator/operator*/
  reference operator*() const {
    iterator_type copy = it;
    --copy;
    return *copy;
  }

  pointer operator->() const {
    return &(operator*());
  }

// Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1].
// https://www.cplusplus.com/reference/iterator/reverse_iterator/operator[]/
  reference operator[](difference_type n) const {
    return it[-n - 1];
  }

//  Returns a reverse iterator pointing to the element located n positions away
//  from the element the iterator currently points to.
// https://www.cplusplus.com/reference/iterator/reverse_iterator/operator+/
  ReverseIterator operator+(difference_type n) const {
    return ReverseIterator(it - n);
  }

  ReverseIterator &operator++() {
    --it;
    return *this;
  }

  ReverseIterator operator++(int) {
    ReverseIterator temp = *this;
    ++(*this);
    return temp;
  }

  ReverseIterator &operator+=(difference_type n) {
    it -= n;
    return *this;
  }

  ReverseIterator operator-(difference_type n) const {
    return ReverseIterator(it + n);
  }

  ReverseIterator &operator--() {
    ++it;
    return *this;
  }

  ReverseIterator operator--(int) {
    ReverseIterator temp = *this;
    --(*this);
    return temp;
  }

  ReverseIterator &operator-=(difference_type n) {
    it += n;
    return *this;
  }

};

template<class Iterator>
bool operator==(const ReverseIterator<Iterator> &lhs,
                const ReverseIterator<Iterator> &rhs) {
  return lhs.base() == rhs.base();
}

template<class Iterator>
bool operator!=(const ReverseIterator<Iterator> &lhs,
                const ReverseIterator<Iterator> &rhs) {
  return lhs.base() != rhs.base();
}

template<class Iterator>
bool operator<(const ReverseIterator<Iterator> &lhs,
               const ReverseIterator<Iterator> &rhs) {
  return lhs.base() < rhs.base();
}

template<class Iterator>
bool operator<=(const ReverseIterator<Iterator> &lhs,
                const ReverseIterator<Iterator> &rhs) {
  return lhs.base() <= rhs.base();
}

template<class Iterator>
bool operator>(const ReverseIterator<Iterator> &lhs,
               const ReverseIterator<Iterator> &rhs) {
  return lhs.base() > rhs.base();
}

template<class Iterator>
bool operator>=(const ReverseIterator<Iterator> &lhs,
                const ReverseIterator<Iterator> &rhs) {
  return lhs.base() >= rhs.base();
}

// On cplusplus.com nothing is said about comparing the values of const and non const for std c++98

}
