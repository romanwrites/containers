#pragma once

#include "RbTreeIterator.h"
#include "Allocator.h"

namespace ft {

template<typename Key, typename Val, typename KeyOfValue,
    typename Compare, typename Alloc = ft::Allocator<Val> >
class RbTree {
 public:
  typedef RbTreeNodeBase* base_ptr;
  typedef const RbTreeNodeBase* const_base_ptr;
  typedef RbTreeNode<Val>* link_type;
  typedef const RbTreeNode<Val>* const_link_type;
  typedef typename Alloc::template rebind<RbTreeNode<Val>>::other node_allocator_type;
  typedef Key key_type;
  typedef Val value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef Alloc allocator_type;
  typedef RbTreeNode<Val> Node;
  typedef Compare key_compare;

 private:
  size_type currentSize;
//  allocator_type allocator; // only needed in get_allocator()
  node_allocator_type nodeAllocator;
  Node *root;
  Node *nil;
  key_compare comp;

 public:

  explicit RbTree(const key_compare &comp = key_compare(),
                  const allocator_type &alloc = allocator_type())
      : comp(comp),
        nodeAllocator(alloc),
        root(NULL),
        nil(NULL), // maybe call static method, but how to pass nodeAllocator
        currentSize(0) {
    nil = createNilNode();
  }

  RbTree(const RbTree &x) {
    this->currentSize = x.currentSize;
    this->nodeAllocator = x.nodeAllocator;
    this->root = x.root;
    this->nil = x.nil;
    this->comp = x.comp;
  }

  RbTree &operator=(const RbTree &x) {
    this->currentSize = x.currentSize;
    this->nodeAllocator = x.nodeAllocator;
    this->root = x.root;
    this->nil = x.nil;
    this->comp = x.comp;
    return *this;
  }

  ~RbTree() {
//    todo
//    _M_erase(begin());
  }

  // PLAN
  // 1. insert
  //   a. find insert point
  // 2. find
  // 3. count
  // 4. remove tree
  // 5. rebalance (rbtree insert fix)
  //   a. rotations
  // 6. remove rebalance
  //   a. rotations
  //   b. transplant

 private:

  Node *createNilNode() {
    Node *node = nodeAllocator.allocate(1);

    node->color = RbTreeColor::RED;
    node->left = node;
    node->right = node;
    node->parent = node;

    return node;
  }


};

}