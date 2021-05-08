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
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef std::ptrdiff_t difference_type;
  typedef size_t size_type;

  typedef RbTree<key_type, value_type, ft::Identity<value_type>, Compare, Alloc> Tree;
  typedef typename Tree::iterator iterator;
  typedef typename Tree::const_iterator const_iterator;
  typedef ReverseIterator<iterator> reverse_iterator;
  typedef ReverseIterator<const_iterator> const_reverse_iterator;

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
    insert(first, last);
  }

//  copy
  Set(const Set &x) : tree(new Tree(UNIQUE)) {
    operator=(x);
  }

  ~Set() {
    delete tree;
  }

  Set &operator=(const Set &x) {
    if (this != &x) {
      *this->tree = *x.tree;
    }

    return *this;
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

  void erase(iterator position) {
    tree->erase(position);
  }

  size_type erase(const value_type &val) {
    return tree->erase(val);
  }

  void erase(iterator first, iterator last) {
    tree->erase(first, last);
  }

 public:
  void swap(Set &x) {
    Tree *tmp = x.tree;
    x.tree = this->tree;
    this->tree = tmp;
  }

  void clear() {
    tree->clear();
  }

  key_compare key_comp() const {
    return tree->key_comp();
  }

  value_compare value_comp() const {
    return tree->key_comp();
  }

  iterator find(const value_type &val) {
    return tree->findNode(val);
  }

  const_iterator find(const value_type &val) const {
    return tree->findNode(val);
  }

  size_type count(const value_type &val) const {
    return tree->count(val);
  }

  iterator lower_bound(const value_type &val) {
    return tree->lower_bound(val);
  }

  iterator upper_bound(const value_type &val) {
    return tree->upper_bound(val);
  }

  std::pair<iterator, iterator> equal_range(const value_type &val) {
    return tree->equal_range(val);
  }

  const_iterator lower_bound(const value_type &val) const {
    return tree->lower_bound(val);
  }

  const_iterator upper_bound(const value_type &val) const {
    return tree->upper_bound(val);
  }

  std::pair<const_iterator, const_iterator> equal_range(const value_type &val) const {
    return tree->equal_range(val);
  }

  allocator_type get_allocator() const {
    return tree->get_allocator();
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

  template<class T_friend, class Compare_f, class Alloc_f>
  friend bool operator==(const Set<T_friend, Compare_f, Alloc_f> &lhs,
                         const Set<T_friend, Compare_f, Alloc_f> &rhs);

  template<class T_friend, class Compare_f, class Alloc_f>
  friend bool operator<(const Set<T_friend, Compare_f, Alloc_f> &lhs,
                        const Set<T_friend, Compare_f, Alloc_f> &rhs);

#if PRINT_INT_TREE
  void printIntegerTree() const {
    tree->printIntTree();
  }
#endif

};

template<class T, class Compare, class Alloc>
bool operator==(const Set<T, Compare, Alloc> &lhs,
                const Set<T, Compare, Alloc> &rhs) {
  return *lhs.tree == *rhs.tree;
}

template<class T, class Compare, class Alloc>
bool operator!=(const Set<T, Compare, Alloc> &lhs,
                const Set<T, Compare, Alloc> &rhs) {
  return !(lhs == rhs);
}

template<class T, class Compare, class Alloc>
bool operator<(const Set<T, Compare, Alloc> &lhs,
               const Set<T, Compare, Alloc> &rhs) {
  return *lhs.tree < *rhs.tree;
}

template<class T, class Compare, class Alloc>
bool operator<=(const Set<T, Compare, Alloc> &lhs,
                const Set<T, Compare, Alloc> &rhs) {
  return !(rhs < lhs);
}

template<class T, class Compare, class Alloc>
bool operator>(const Set<T, Compare, Alloc> &lhs,
               const Set<T, Compare, Alloc> &rhs) {
  return rhs < lhs;
}

template<class T, class Compare, class Alloc>
bool operator>=(const Set<T, Compare, Alloc> &lhs,
                const Set<T, Compare, Alloc> &rhs) {
  return !(lhs < rhs);
}

template<class T, class Compare, class Alloc>
void swap(Set<T, Compare, Alloc> &x, Set<T, Compare, Alloc> &y) {
  x.swap(y);
}
}
