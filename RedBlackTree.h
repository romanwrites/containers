#pragma once

#include "TestRunner.h"
#include "RbTreeNode.h"

#define RED_BG_SET "\033[38;5;202m"
#define BLACK_BG_SET "\033[38;5;33m"
#define RESET "\033[0m"

namespace ft {









//	------------------------------------- RB TREE ITERATOR -----------------------------------------
template<class P>
class RbTreeIterator {
 public:
  typedef P iterator_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef iterator_type value_type;
  typedef ptrdiff_t difference_type;
  typedef P &reference;
  typedef P *pointer;
  typedef RbTreeNode<P> Node;

  // add const in const iterator

 private:
  Node *node;
  const Node *nil; //todo what's inside?

 public:
  //  Is default-constructible, copy-constructible, copy-assignable and destructible
  RbTreeIterator() : node(nullptr), nil(nullptr) {}
  RbTreeIterator(Node *p, Node *nil) : node(p), nil(nil) {}
  RbTreeIterator(const RbTreeIterator &it) : node(it.node), nil(it.nil) {}

  RbTreeIterator &operator=(const RbTreeIterator &it) {
    node = it.node;
    nil = it.nil;
    return *this;
  }

  // kind of static
  friend
  bool operator==(RbTreeIterator const &lhs, RbTreeIterator const &rhs) {
    return lhs.node == rhs.node; // compare pointers
  }

  friend
  bool operator!=(RbTreeIterator const &lhs, RbTreeIterator const &rhs) {
    return !(lhs.node == rhs.node);
  }

  reference operator*() const {
    return node->value;
  }

  pointer operator->() const {
    return &(node->value);
  }


  // find successor
  // find predecessor

  //todo inc dec
};

}