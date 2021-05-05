#pragma once

#include "Allocator.h"
#include <map>
#include "TestRunner.h"
#include "RedBlackTree.h"

#define RED_BG_SET "\033[38;5;202m"
#define BLACK_BG_SET "\033[38;5;33m"
#define RESET "\033[0m"

namespace ft {

//	------------------------------------- MAP -----------------------------------------

template<class Key,                                           // map::key_type
    class T,                                                   // map::mapped_type
    class Compare = ft::less<Key>,                                // map::key_compare
    class Alloc = ft::Allocator<std::pair<const Key, T> >    // map::allocator_type
>
class Map {
 public:
  //	------------------------------------- MAP TYPEDEFS -----------------------------------------
  typedef Key key_type;
  typedef T mapped_type;
  typedef std::pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
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


  class value_compare : public std::binary_function<value_type, value_type, bool> {
    friend class map;
   protected:
    Compare comp;
    explicit value_compare(Compare c) : comp(c) {}
   public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };

  typedef RbTree<key_type, value_type, value_type, Compare, Alloc> Tree;

 private:
  Tree *tree;

 public:
  explicit Map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type()) {
//    treeAllocator.allocate()
    this->tree = new RbTree<key_type, value_type, value_type, Compare, Alloc>(comp, alloc);
  }

  template<class InputIterator>
  Map(InputIterator first,
      InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type()) {
    this->tree = new RbTree<key_type, value_type, value_type, Compare, Alloc>(comp, alloc);
    insert(first, last);
  }

  Map(const Map &x) {
    this->tree = new RbTree<key_type, value_type, value_type, Compare, Alloc>;
    insert(x.begin(), x.end());
  }

  ~Map() {
    delete tree;
  }

  Map &operator=(const Map &x) {
    this->tree = x.tree;

    return *this;
  }

 public:

  mapped_type &operator[](const key_type &k) {
    return (*((this->insert(std::make_pair(k, mapped_type()))).first)).second;
  }

  std::pair<iterator, bool> insert(const value_type &val) {
    return tree->insert(val);
  }

  iterator insert(iterator position, const value_type &val) {
    return tree->insert(position, val);
  }

  template<class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    tree->insert(first, last);
  }

  void erase(iterator position) {
    tree->erase(position);
  }

  size_type erase(const key_type &k) {
    return tree->erase(k);
  }

  void erase(iterator first, iterator last) {
    tree->erase(first, last);
  }

  void swap(Map &x) {
    Tree *tmp = this->tree;
    this->tree = x.tree;
    x.tree = tmp;
  }

  void clear() {
    tree->clear();
  }

  key_compare key_comp() const {
    return tree->key_comp();
  }

  value_compare value_comp() const {
    return tree->value_comp();
  }

  iterator find(const key_type &k) {
    return tree->find(k);
  }

  const_iterator find(const key_type &k) const {
    return tree->find(k);
  }

  size_type count(const key_type &k) const {
    return tree->count(k);
  }

  iterator lower_bound(const key_type &k) {
    return tree->lower_bound(k);
  }

  const_iterator lower_bound(const key_type &k) const {
    return tree->lower_bound(k);
  }

  iterator upper_bound(const key_type &k) {
    return tree->upper_bound(k);
  }

  const_iterator upper_bound(const key_type &k) const {
    return tree->upper_bound(k);
  }

  std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
    return tree->equal_range(k);
  }

  std::pair<iterator, iterator> equal_range(const key_type &k) {
    return tree->equal_range(k);
  }

  allocator_type get_allocator() const {
    return tree->get_allocator();
  }

 public:
  bool empty() const {
    return tree->empty(); //mock todo implement
  }

  size_type size() const {
    return tree->size();
  }

// private:
//  const Tree &constTreeWrapper(Tree &treeToWrap) const {
//    return treeToWrap;
//  }
//
// public:
//
//  // ITERATORS ----------------------------------------------------------------------
//  const_iterator begin() const {
//    return constTreeWrapper(*tree).begin();
//  }
//
//  iterator begin() {
//    return tree->begin();
//  }
//
//  iterator end() {
//    return tree->end();
//  }
//
//  const_iterator end() const {
//    return constTreeWrapper(*tree).end();
//  }

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
//  'ft::RbTree<std::__1::basic_string<char>, std::__1::pair<const std::__1::basic_string<char>, int>, std::__1::pair<const std::__1::basic_string<char>, int>, ft::less<std::__1::basic_string<char> >, ft::Allocator<std::__1::pair<const std::__1::basic_string<char>, int> > >::iterator'
//  (aka 'RbTreeIterator<std::__1::pair<const std::__1::basic_string<char>, int> >')
//
//  'ft::Map<std::__1::basic_string<char>, int, ft::less<std::__1::basic_string<char> >, ft::Allocator<std::__1::pair<const std::__1::basic_string<char>, int> > >::const_iterator'
//  (aka 'RbTreeConstIterator<pair<const std::__1::basic_string<char>, int> >')

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

  size_type max_size() const {
    return tree->max_size();
  }

  void printIntegerTree() const {
    tree->printIntTree();
  }

};

}
