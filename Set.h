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

  typedef RbTree<key_type, value_type, ft::Identity<value_type>, Compare, Alloc> Tree;

 private:
  Tree *tree;

  //	------------------------------------- SET CONSTRUCTORS AND COPLIEN -----------------------------------------
 public:
//  empty
  explicit Set(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : tree(new Tree(UNIQUE, comp, alloc)) {
  }

//  range
  template<class InputIterator>
  Set(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type())
      : tree(new Tree(UNIQUE, comp, alloc)) {
    this->tree->insert(first, last);
  }

//  copy
  Set(const Set &x) : tree(new Tree(UNIQUE)) {
    this->tree->insert(x.begin(), x.end());
  }

  ~Set() {
    delete tree;
  }

  Set &operator=(const Set &x) {
    this->tree = x.tree;
  }

  bool empty() const {
    return tree->empty();
  }

  size_type size() const {
    return tree->size();
  }

  size_type max_size() const {
    return tree->max_size();
  }

//  single element
  std::pair<iterator, bool> insert(const value_type &val) {
    return tree->insert(val);
  }

//  with hint
  iterator insert(iterator position, const value_type &val) {
    return tree->insert(position, val);
  }

//  range
  template<class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    tree->insert(first, last);
  }

  // ITERATORS ----------------------------------------------------------------------
  const_iterator begin() const {
    return tree->begin();
  }

  iterator begin() {
    return tree->begin();
  }

  iterator end() {
    return tree->end();
  }

  const_iterator end() const {
    return tree->end();
  }

  reverse_iterator rbegin() {
    return tree->rbegin();
  }

  const_reverse_iterator rbegin() const {
    return tree->rbegin();
  }

  reverse_iterator rend() {
    return tree->rend();
  }

  const_reverse_iterator rend() const {
    return tree->rend();
  }

#if PRINT_INT_TREE
  void printIntegerTree() const {
    tree->printIntTree();
  }
#endif

};

}
