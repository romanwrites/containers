#pragma once
#include "RedBlackTree.h"

namespace ft {
template<class T,                   // set::key_type/value_type
    class Compare = less<T>,        // set::key_compare/value_compare
    class Alloc = ft::Allocator<T>      // set::allocator_type
>
class Set {
  //	------------------------------------- SET TYPEDEFS -----------------------------------------
 public:
  typedef T key_type;
  typedef T value_type;
//  typedef T mapped_type;
//  typedef std::pair<const key_type, mapped_type> value_type_rb_tree;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef std::ptrdiff_t difference_type;
  typedef size_t size_type;

  typedef RbTreeIterator<value_type> iterator;
  typedef RbTreeConstIterator<value_type> const_iterator;
  typedef ReverseIterator<iterator> reverse_iterator;
  typedef ReverseIterator<const_iterator> const_reverse_iterator;

  typedef RbTree<key_type, value_type, value_type, Compare, Alloc> Tree;

 private:
  Tree *tree;

  //	------------------------------------- SET CONSTRUCTORS AND COPLIEN -----------------------------------------
 public:
//  empty
  explicit Set(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : tree(new RbTree<key_type, value_type, value_type, Compare, Alloc>(UNIQUE, comp, alloc)) {
  }

//  range
  template<class InputIterator>
  Set(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type())
      : tree(new RbTree<key_type, value_type, value_type, Compare, Alloc>(UNIQUE, comp, alloc)) {
    this->tree->insert(first, last);
  }

//  copy
  Set(const Set &x) : tree(new RbTree<key_type, value_type, value_type, Compare, Alloc>(UNIQUE)) {
    this->tree->insert(x.begin(), x.end());
  }

  ~Set() {
    delete tree;
  }

  Set &operator=(const Set &x) {
    this->tree = x.tree;
  }

};

}
