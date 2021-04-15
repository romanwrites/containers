#pragma once
#include "IteratorTraits.h"

namespace ft {

template <class Iterator>
class reverse_iterator {
 public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename ft::iterator_traits<Iterator>::value_type	value_type;
  typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::pointer pointer;
  typedef typename ft::iterator_traits<Iterator>::reference reference;

 private:
  iterator_type it;

 public:
  reverse_iterator() {
  }

  explicit reverse_iterator (iterator_type it) : it(it) {
  }

  template <class Iter>
  reverse_iterator (const reverse_iterator<Iter>& rev_it) : it(rev_it.base()) {
  }

  iterator_type base() const {
    return it;
  }

// Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it.
  reference operator*() const {
    iterator_type copy = it;
    --copy;
    return *copy;
  }






};




}