#pragma once
#include <iostream>

//#include "TestRunner.h"
#include "RbTreeNode.h"

#define RED_BG_SET "\033[38;5;202m"
#define BLACK_BG_SET "\033[38;5;33m"
#define RESET "\033[0m"

namespace ft {

//	------------------------------------- RB TREE ITERATOR -----------------------------------------
template<typename T>
class RbTreeIterator {
 public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  typedef RbTreeIterator<T> self;
  typedef RbTreeNodeBase::base_ptr base_ptr;
  typedef RbTreeNodeBase::const_base_ptr const_base_ptr;
  typedef RbTreeNode<T> *link_type;
  typedef RbTreeIterator<T> iterator;

  base_ptr node;
  const_base_ptr nil;

  // Constructors --------------------------------------------------------
  // Is default-constructible, copy-constructible, copy-assignable and destructible
  RbTreeIterator() : node(NULL), nil(NULL) {}

  explicit RbTreeIterator(base_ptr x, const_base_ptr nil) : node(x), nil(nil) {}

  RbTreeIterator(iterator &p) : node(p.x), nil(p.nil) {}

  virtual ~RbTreeIterator() {}

  reference operator*() const {
    return *static_cast<link_type>(this->node)->_M_valptr();
  }

  pointer operator->() const {
    return static_cast<link_type> (this->node)->_M_valptr();
  }

  self &operator++() {
    this->node = RbTreeNodeBase::increment(this->node, this->nil);
    return *this;
  }

  self operator++(int) {
    self copy = *this;
    this->node = RbTreeNodeBase::increment(this->node, this->nil);
    return copy;
  }

  self &operator--() {
    this->node = RbTreeNodeBase::decrement(this->node, this->nil);
    return *this;
  }

  self operator--(int) {
    self copy = *this;
    this->node = RbTreeNodeBase::decrement(this->node, this->nil);
    return copy;
  }

  friend bool operator==(const self &x, const self &y) {
    return x.node == y.node;
  }

  friend bool operator!=(const self &x, const self &y) {
    return x.node != y.node;
  }
};

//	------------------------------------- RB TREE ITERATOR -----------------------------------------
template<typename T>
class RbTreeConstIterator {
 public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  typedef RbTreeConstIterator<T> self;
  typedef RbTreeNodeBase::const_base_ptr base_ptr;
  typedef RbTreeNodeBase::const_base_ptr const_base_ptr;
  typedef RbTreeNode<T> *link_type;
  typedef RbTreeConstIterator<T> iterator;

  const_base_ptr node;
  const_base_ptr nil;

  // Constructors --------------------------------------------------------
  // Is default-constructible, copy-constructible, copy-assignable and destructible
  RbTreeConstIterator() : node(NULL), nil(NULL) {}

  explicit RbTreeConstIterator(base_ptr x, const_base_ptr nil) : node(x), nil(nil) {}

  RbTreeConstIterator(iterator &p) : node(p.x), nil(p.nil) {}
  RbTreeConstIterator(RbTreeIterator<T> &p) : node(p.x), nil(p.nil) {}

  virtual ~RbTreeConstIterator() {}

  reference operator*() const {
    return *static_cast<link_type>(this->node)->_M_valptr();
  }

  pointer operator->() const {
    return static_cast<link_type> (this->node)->_M_valptr();
  }

  self &operator++() {
    this->node = RbTreeNodeBase::increment(this->node, this->nil);
    return *this;
  }

  self operator++(int) {
    self copy = *this;
    ++(*this);
    return copy;
  }

  self &operator--() {
    this->node = RbTreeNodeBase::decrement(this->node, this->nil);
    return *this;
  }

  self operator--(int) {
    self copy = *this;
    --(*this);
    return copy;
  }

  friend bool operator==(const self &x, const self &y) {
    return x.node == y.node;
  }

  friend bool operator!=(const self &x, const self &y) {
    return x.node != y.node;
  }
};




//template<class P>
//class RbTreeIterator {
// public:
//  typedef P iterator_type;
//  typedef std::bidirectional_iterator_tag iterator_category;
//  typedef iterator_type value_type;
//  typedef ptrdiff_t difference_type;
//  typedef P &reference;
//  typedef P *pointer;
//  typedef RbTreeNode<P> Node;
//
//  // add const in const iterator
//
// private:
//  Node *node;
//  const Node *nil; //todo what's inside?
//
// public:
//  //  Is default-constructible, copy-constructible, copy-assignable and destructible
//  RbTreeIterator() : node(nullptr), nil(nullptr) {}
//  RbTreeIterator(Node *p, Node *nil) : node(p), nil(nil) {}
//  RbTreeIterator(const RbTreeIterator &it) : node(it.node), nil(it.nil) {}
//
//  RbTreeIterator &operator=(const RbTreeIterator &it) {
//    node = it.node;
//    nil = it.nil;
//    return *this;
//  }
//
//  // kind of static
//  friend
//  bool operator==(RbTreeIterator const &lhs, RbTreeIterator const &rhs) {
//    return lhs.node == rhs.node; // compare pointers
//  }
//
//  friend
//  bool operator!=(RbTreeIterator const &lhs, RbTreeIterator const &rhs) {
//    return !(lhs.node == rhs.node);
//  }
//
//  reference operator*() const {
//    return node->value;
//  }
//
//  pointer operator->() const {
//    return &(node->value);
//  }
//
//
//  // find successor
//  // find predecessor
//
//  //todo inc dec
//};

}