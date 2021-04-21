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
  typedef RbTreeIterator<T> iterator;
  typedef RbTreeNodeBase::base_ptr base_ptr;
  typedef RbTreeNodeBase::const_base_ptr const_base_ptr;
  typedef RbTreeNode<T> *link_type;
  typedef RbTreeNode<T> Node;

//  base_ptr node;
//  const_base_ptr nil;
  base_ptr node;
  const_base_ptr nil;

  // Constructors --------------------------------------------------------
  // Is default-constructible, copy-constructible, copy-assignable and destructible
  RbTreeIterator() : node(NULL), nil(NULL) {}

//  explicit RbTreeIterator(Node *x, Node *nil) : node(x), nil(nil) {}
  explicit RbTreeIterator(base_ptr x, const_base_ptr nil) : node(x), nil(nil) {}

  RbTreeIterator(iterator const &p) : node(p.node), nil(p.nil) {}

  virtual ~RbTreeIterator() {}

  reference operator*() const {
    return *static_cast<link_type>(node)->val;
  }

  pointer operator->() const {
//    return &(static_cast<link_type>(node)->value);
    return static_cast<link_type>(node)->val();
  }

  iterator &operator++() {
    this->node = reinterpret_cast<Node *>(RbTreeNodeBase::increment(this->node, this->nil));
    return *this;
  }

  iterator operator++(int) {
    iterator copy = *this;
    this->node = reinterpret_cast<Node *>(RbTreeNodeBase::increment(this->node, this->nil));
    return copy;
  }

  iterator &operator--() {
    this->node = reinterpret_cast<Node *>(RbTreeNodeBase::decrement(this->node, this->nil));
    return *this;
  }

  iterator operator--(int) {
    iterator copy = *this;
    this->node = reinterpret_cast<Node *>(RbTreeNodeBase::decrement(this->node, this->nil));
    return copy;
  }

  friend bool operator==(const iterator &x, const iterator &y) {
    return x.node == y.node;
  }

  friend bool operator!=(const iterator &x, const iterator &y) {
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
  typedef RbTreeConstIterator<T> iterator;
  typedef RbTreeNodeBase::const_base_ptr base_ptr;
  typedef RbTreeNodeBase::const_base_ptr const_base_ptr;
  typedef RbTreeNode<T> *link_type;
  typedef const RbTreeNode<T> *const_link_type;

  const_base_ptr node;
  const_base_ptr nil;

  // Constructors --------------------------------------------------------
  // Is default-constructible, copy-constructible, copy-assignable and destructible
  RbTreeConstIterator() : node(NULL), nil(NULL) {}

  explicit RbTreeConstIterator(base_ptr x, const_base_ptr nil) : node(x), nil(nil) {}

  RbTreeConstIterator(iterator &p) : node(p.node), nil(p.nil) {}
  RbTreeConstIterator(RbTreeIterator<T> &p) : node(p.x), nil(p.nil) {}

  virtual ~RbTreeConstIterator() {}

  reference operator*() const {
//    return static_cast<link_type>(node)->value;
    return *static_cast<link_type>(node)->val();
  }

  pointer operator->() const {
    return static_cast<link_type>(node)->val();
  }

  iterator &operator++() {
    this->node = RbTreeNodeBase::increment(this->node, this->nil);
    return *this;
  }

  iterator operator++(int) {
    iterator copy = *this;
    ++(*this);
    return copy;
  }

  iterator &operator--() {
    this->node = RbTreeNodeBase::decrement(this->node, this->nil);
    return *this;
  }

  iterator operator--(int) {
    iterator copy = *this;
    --(*this);
    return copy;
  }

  friend bool operator==(const iterator &x, const iterator &y) {
    return x.node == y.node;
  }

  friend bool operator!=(const iterator &x, const iterator &y) {
    return x.node != y.node;
  }
};

}