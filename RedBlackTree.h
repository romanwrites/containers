#pragma once

#include "RbTreeIterator.h"
#include "Allocator.h"
#include "Compare.h"

namespace ft {

template<typename Key, typename Val, typename KeyOfValue,
    typename Compare, typename Alloc = ft::Allocator<Val> >
class RbTree {
 public:
  typedef RbTreeNodeBase *base_ptr;
  typedef const RbTreeNodeBase *const_base_ptr;
  typedef RbTreeNode<Val> *link_type;
  typedef const RbTreeNode<Val> *const_link_type;
  typedef typename Alloc::template rebind<RbTreeNode<Val> >::other node_allocator_type;
  typedef typename Alloc::template rebind<RbTreeNodeBase>::other node_base_allocator_type;
  typedef Key key_type;
  typedef Val value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef Alloc allocator_type;
  typedef RbTreeNode<Val> Node;
  typedef Compare key_compare;
  typedef RbTreeIterator<Val> iterator;
  typedef RbTreeConstIterator<Val> const_iterator;

 private:
  key_compare comp;
  node_allocator_type nodeAllocator;
  allocator_type allocator; // only needed in get_allocator()
  node_base_allocator_type baseAllocator;
  Node *root;
  Node *nil;
  size_type currentSize;
  bool isUniqueTree;

 public:

  explicit RbTree(const key_compare &comp = key_compare(),
                  const allocator_type &alloc = allocator_type(),
                  bool uniqueTree = true)
      : comp(comp),
        nodeAllocator(alloc),
        allocator(alloc),
        baseAllocator(alloc),
        root(NULL),
        nil(NULL), // maybe call static method, but how to pass nodeAllocator
        currentSize(0),
        isUniqueTree(uniqueTree) {
    nil = createNilNode();
    root = nil;
  }

  RbTree(const RbTree &x) {
    operator=(x);
  }

  RbTree &operator=(const RbTree &x) {
    this->currentSize = x.currentSize;
    this->nodeAllocator = x.nodeAllocator;
    this->root = x.root;
    this->nil = x.nil;
    this->comp = x.comp;
    this->isUniqueTree = x.isUniqueTree;
    return *this;
  }

  ~RbTree() {
//    todo
//    _M_erase(begin());
  }

  // PLAN
  // 1. insert ✅
  //   a. find insert point
  // 2. find ✅
  // 3. count ✅
  // 4. remove tree
  // 5. rebalance (rbtree insert fix)
  //   a. rotations
  // 6. remove rebalance
  //   a. rotations
  //   b. transplant

  Node *find(const key_type &key) const {
    Node *node;

    for (node = root; node != nil && node->value.first != key;) {
      if (comp(key, node->value.first)) {
        node = reinterpret_cast<Node *>(node->left);
      } else {
        node = reinterpret_cast<Node *>(node->right);
      }
    }

    return node;
  }

  size_type count(const key_type &k) const {
    if (isUniqueTree) {
      if (find(k) != nil) {
        return 1;
      }
      return 0;
    }

    size_type i = 0;
    for (auto it = begin(); it != end(); ++it) {
      if (it->first == k) {
        ++i;
      }
    }
    return i;
  }

  void destroyNode(Node *node) {
    nodeAllocator.destroy(node);
    nodeAllocator.deallocate(node, 1);
  }

  std::pair<iterator, bool> insert(value_type val) {
    if (root == nil) {
      root = createNode(nil, val);
      nil->left = root;
      nil->right = root;
      return std::make_pair(iterator(root, nil), true);
    } else {
      Node *node = root;

      while (node != nil) {
        if (comp(val.first, node->value.first)) {
          if (node->left != nil) {
            node = reinterpret_cast<Node *>(node->left);
          } else {
            node->left = createNode(node, val);
            currentSize++;
            return std::make_pair(iterator(node->left, nil), true);
          }
        } else if (isUniqueTree && !comp(node->value.first, val.first)) {
          return std::make_pair(iterator(node, nil), false);
        } else {
          if (node->right != nil) {
            node = reinterpret_cast<Node *>(node->right);
          } else {
            node->right = createNode(node, val);
            currentSize++;
            return std::make_pair(iterator(node->right, nil), true);
          }
        }
      }
    }
    std::cout
        << "LOOK HERE!!!!!!!! HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        << std::endl;
    return std::make_pair(iterator(nil, nil), false);
  }

  const_iterator begin() const {
    base_ptr ptr = RbTreeNodeBase::minimum(root, nil);

    return const_iterator(reinterpret_cast<Node *>(ptr), nil);
  }

  iterator begin() {
    base_ptr ptr = RbTreeNodeBase::minimum(root, nil);

    return iterator(reinterpret_cast<Node *>(ptr), nil);
  }

  iterator end() {
    base_ptr ptr = RbTreeNodeBase::maximum(root, nil);

    iterator it = iterator(reinterpret_cast<Node *>(ptr), nil);

    return ++it;
  }

  const_iterator end() const {
    base_ptr ptr = RbTreeNodeBase::maximum(root, nil);

    const_iterator it = const_iterator(reinterpret_cast<Node *>(ptr), nil);

    return ++it;
  }

  Node *find(value_type val) {
    return find(val.first);
//    Node *node;
//
//    for (node = root; node != nil && node->value.first != val.first; ) {
//      if (comp(val.first, node->value.first)) {
//        node = reinterpret_cast<Node *>(node->left);
//      } else {
//        node = reinterpret_cast<Node *>(node->right);
//      }
//    }
//
//    return node;
  }

  bool empty() const {
    return currentSize == 0;
  }

  size_type size() const {
    return currentSize;
  }

  size_type max_size() const {
    return nodeAllocator.max_size();
  }

 private:

  Node *createNode(Node *parent, value_type val) {
    Node *node = nodeAllocator.allocate(1);

    // Constructing NODE BASE is needed because of inheritance
    // efficient method. calling only copy constructor
    baseAllocator.construct(node, *node);
    // inefficient method
    // nodeAllocator.construct(node, Node(val));

    allocator.construct(&(node->value), val);
    node->color = RED;
    node->left = nil;
    node->right = nil;
    node->parent = parent;

    return node;
  }

  Node *createNilNode() {
    Node *node = nodeAllocator.allocate(1);

    node->color = RED;
    node->left = node;
    node->right = node;
    node->parent = node;

    return node;
  }

 private:
  void fillAppend(Node *tree,
                  bool isRight,
                  std::string &appendLeft,
                  std::string &appendRight) const {
    std::string valStr = std::to_string(tree->value.first);

    if (isRight) {
      if (tree->parent != nil) {
        appendLeft += "│" + std::string(valStr.length() - 1, ' ');
      } else {
        appendLeft += std::string(valStr.length(), ' ');
      }
      appendRight += std::string(valStr.length(), ' ');
    } else {
      appendLeft += std::string(valStr.length(), ' ');
      if (tree->parent != nil) {
        appendRight += "│" + std::string(valStr.length() - 1, ' ');
      } else {
        appendRight += std::string(valStr.length(), ' ');
      }
    }
  }

  std::string print(Node *tree, std::string space, bool isRight) const {
    if (tree == nil) {
      return "";
    }
    if (tree->parent != nil && tree->parent->parent != nil) {
      space += " ";
    }
    std::string ret;

    std::string appendLeft;
    std::string appendRight;
    fillAppend(tree, isRight, appendLeft, appendRight);

    if (tree->right != nil) {
      ret += print(reinterpret_cast<Node *>(tree->right), space + appendRight, true);
    }

    ret += space;
    if (tree->parent != nil) {
      if (tree->parent->right == tree) {
        ret += "┌";
      } else {
        ret += "└";
      }
    }
    if (tree->isRed()) {
      ret += std::string(RED_BG_SET + std::to_string(tree->value.first) + RESET);
    } else {
      ret += std::string(BLACK_BG_SET + std::to_string(tree->value.first) + RESET);
    }

    if (tree->left != nil && tree->right != nil) {
      ret += "┤";
    } else if (tree->left == nil && tree->right != nil) {
      ret += "┘";
    } else if (tree->right == nil && tree->left != nil) {
      ret += "┐";
    }
    ret += "\n";

    if (tree->left != nil) {
      ret += print(reinterpret_cast<Node *>(tree->left), space + appendLeft, false);
    }
    return ret;
  }

 public:
  void printIntTree() const {
    if (root != NULL && root != nil) {
      std::cout << print(root, "", true);
    }
  }
};

}
