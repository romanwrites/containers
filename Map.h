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

  typedef RbTreeNode<value_type> Node;

  typedef RbTreeIterator<value_type> iterator;

  typedef typename Alloc::template rebind<Node>::other node_allocator_type;
  //todo
//  typedef NodeConstIterator<Node> const_iterator;
//  typedef NodeConstIterator<Node> reverse_iterator;
//  typedef NodeConstIterator<Node> const_reverse_iterator;

//todo do need inherit?
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

//  todo constructors...
 public:
  explicit Map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : key_compare_(comp),
        allocator(alloc),
        nodeAllocator(allocator_type(allocator)),
        root(nullptr),
        nil(nullptr),
        currentSize(0) {
    nil = createNilNode();

  }
//
//  template <class InputIterator>
//  Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
//
//  }
//
//  Map (const Map& x) {
//    Map(x.begin(), x.end(), x.key_compare_, x.allocator);
//  }

 private:
  key_compare key_compare_;
  allocator_type allocator;
  node_allocator_type nodeAllocator;
  Node *root;
  Node *nil;
  size_type currentSize;

 public:

  mapped_type &operator[](const key_type &k) {
    return (*((this->insert(std::make_pair(k, mapped_type()))).first)).second;
  }

  std::pair<iterator, bool> insert(const value_type &val) {
    Node *node;

    node = put(root, val);

    if (root == NULL) {
      root = node;
    }

    std::pair<iterator, bool> res;
    res.first = iterator(node, nil);
    res.second = true;

    return res;
  }
//
//  iterator insert(iterator position, const value_type &val) {
//
//  }
//
//  template<class InputIterator>
//  void insert(InputIterator first, InputIterator last) {
//
//  }


//  explicit Map (const key_compare& comp = key_compare(),
//                const allocator_type& alloc = allocator_type()) {
//    key_compare_ = comp;
//
//  }
//
//  template <class InputIterator>
//  Map (InputIterator first, InputIterator last,
//  const key_compare& comp = key_compare(),
//  const allocator_type& alloc = allocator_type()) {
//
//  }
//
//  Map (const Map& x) {
//
//  }

 public:
  bool empty() const {
    return currentSize == 0; //mock todo implement
  }

  size_type size() const {
    return currentSize;
  }

  key_compare key_comp() const {
    return key_compare_;
  }

  value_compare value_comp() const {
    return value_compare();
  }

  int compareTo(const key_type &o1, const key_type &o2) {
    if (o1 == o2) {
      return 0;
    } else if (key_compare_(o1, o2)) {
      return -1;
    } else {
      return 1;
    }
  }

// private: //todo
 public:
  iterator get(const key_type &k) {
    Node *x = root;

    while (x != nil) {

      int cmp = compareTo(k, x->value.first);

      if (cmp < 0) {
        x = x->left;
      } else if (cmp > 0) {
        x = x->right;
      } else {
        return iterator(x->value);
      }
    }
    return iterator(nil);
  }

  Node *put(Node *h, value_type const &value) {
    if (h == nil || h == nullptr) {
      return createNode(value);
    }

    int cmp = compareTo(value.first, h->value.first);

    if (cmp < 0) {
      h->left = put(h->left, value);
      h->left->parent = h;
    } else if (cmp > 0) {
      h->right = put(h->right, value);
      h->right->parent = h;
    } else {
//      allocator.destroy(h->value);
      allocator.construct(&(h->value), value); // todo fail
//      h->value = value;
    }
    if (h->right->isRed() && !h->left->isRed()) {
      h = rotateLeft(h);
    }
    if (h->left->isRed() && h->left->left) {
      h = rotateRight(h);
    }
    if (h->left->isRed() && h->right->isRed()) {
      flipColors(h);
    }

    return h;
  }

  Node *createNode(value_type const &value) {
    Node *node = nodeAllocator.allocate(1);

    node->color = RbTreeColor::RED;
    node->left = nil;
    node->right = nil;
    node->parent = nil;

    allocator.construct(&(node->value), value);

    return node;
  }

  Node *createNilNode() {
    Node *node = nodeAllocator.allocate(1);

    node->color = RbTreeColor::RED;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;

    return node;
  }

  void destroyNode(Node *node) {
    allocator.destroy(node);
    allocator.deallocate(node, 1);
  }

  Node *rotateLeft(Node *h) {
    if (!h->right->isRed()) {
      return h; //todo
    }

    Node *x = h->right;

    h->right = x->left;
    if (h->right != nil) {
      h->right->parent = h;
    }

    x->parent = h->parent;

    if (x->parent == nil) {
      root = x;
    } else if (x->parent->left == h) {
      x->parent->left = x;
    } else {
      x->parent->right = x;
    }

    x->left = h;
    h->parent = x;

    x->color = h->color;
    h->color = RbTreeColor::RED;
    return x;
  }

  Node *rotateRight(Node *h) {
    if (!h->right->isRed()) {
      return h; //todo
    }

    Node *x = h->left;

    h->left = x->right;
    if (h->left != nil) {
      h->left->parent = h;
    }

    x->parent = h->parent;
    if (x->parent == nil) {
      root = x;
    } else if (x->parent->left == nil) {
      x->parent->left = x;
    } else {
      x->parent->right = x;
    }

    x->right = h;
    h->parent = x;

    x->color = h->color;
    h->color = RbTreeColor::RED;
    return h;
  }

  void flipColors(Node *h) {
    if (!h->isRed() && h->left->isRed() && h->right->isRed()) {
      h->color = RbTreeColor::RED;
      h->left->color = RbTreeColor::BLACK;
      h->right->color = RbTreeColor::BLACK;
    }
  }


//  const_iterator find (const key_type& k) const {
//    return const_iterator(*find(k)); //todo check
//  }

 private:
  void fillAppend(Node *tree,
                  bool isRight,
                  std::string &appendLeft,
                  std::string &appendRight) const {
    std::string valStr = std::to_string(tree->value.first);

    if (isRight) {
      if (tree->parent != nullptr) {
        appendLeft += "│" + std::string(valStr.length() - 1, ' ');
      } else {
        appendLeft += std::string(valStr.length(), ' ');
      }
      appendRight += std::string(valStr.length(), ' ');
    } else {
      appendLeft += std::string(valStr.length(), ' ');
      if (tree->parent != nullptr) {
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
      ret += print(tree->right, space + appendRight, true);
    }

    ret += space;
    if (tree->parent != nil) {
      if (tree->parent->right == tree) {
        ret += "┌";
      } else {
        ret += "└";
      }
    }
    if (tree->color == RbTreeColor::RED) {
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
      ret += print(tree->left, space + appendLeft, false);
    }
    return ret;
  }

 public:
  void printIntTree() const {
    if (root != nullptr) {
      std::cout << print(root, "", true);
    }
  }

};

}
