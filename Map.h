#pragma once

#include <map>

namespace ft {
//	------------------------------------- MAP ITERATOR -----------------------------------------

enum RB_tree_color {
  red = false,
  black = true
};

template<class T>
class Node {
 private:
  template<class Iter>
  class NodeIterator {
    friend class Node;

   public:
    typedef Iter iterator_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef iterator_type value_type;
    typedef ptrdiff_t difference_type;
    typedef iterator_type &reference;
    typedef iterator_type *pointer;

    iterator_type *value;
   private:
    NodeIterator(Iter *p) : value(p) {}
   public:
    NodeIterator(const NodeIterator &it) : value(it.value) {}

    bool operator!=(NodeIterator const &other) const {
      return value != other.value;
    }
    bool operator==(NodeIterator const &other) const {
      return value == other.value;
    }

    typename NodeIterator::reference operator*() const {
      return *value;
    }

    NodeIterator &operator++() { // prefix increment. doesn't create a copy
      if (value->parent == nullptr) {
        value = nullptr;
      } else if (value->parent->right.get() == value) {
        value = value->parent;
      } else {
        value = value->parent;
        if (value->right.get() != nullptr) {
          value = value->right.get();
          while (value->left.get() != nullptr) {
            value = value->left.get();
          }
        }
      }
      return *this;
    }
  };

 private:
  Node() : color(RB_tree_color::black), parent(nullptr), left(nullptr), right(nullptr) {}
 public:
  T value;
  RB_tree_color color;
  Node *parent;
  Node *left;
  Node *right;

  Node(const T &value) : value(value), left(nullptr), right(nullptr), parent(nullptr) {}

  Node(const T &value, Node *left, Node *right, Node *parent)
      : value(value), left(std::move(left)), right(std::move(right)), parent(parent) {}
  Node(const Node &) = delete;

  typedef NodeIterator<Node> iterator;
  typedef NodeIterator<const Node> const_iterator;

  iterator begin() {
    Node *node = this;
    while (node->left != nullptr) {
      node = node->left.get();
    }
    return iterator(node); // call private constructor. that's why friend
  }
  iterator end() {
    return nullptr; // todo shadow node
  }
  const_iterator begin() const {
    const Node *node = this;
    while (node->left != nullptr) {
      node = node->left.get();
    }
    return const_iterator(node);
  }
  const_iterator end() const {
    return nullptr; // todo shadow node
  }
  friend std::ostream &operator<<(std::ostream &os, const Node &n) {
    return os << n.value;
  }
};

template<class Key,                                           // map::key_type
    class T,                                                   // map::mapped_type
    class Compare = less<Key>,                                // map::key_compare
    class Alloc = std::allocator<std::pair<const Key, T> >    // map::allocator_type
>
class Map {
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

  //todo iterator typedefs
//  typedef mapIterator iterator;
//  typedef mapIterator const_iterator;
//  typedef mapIterator reverse_iterator;
//  typedef mapIterator const_reverse_iterator;

 private:
  size_type currentSize;


//  todo constructors...

 public:
  bool empty() const {
    return currentSize == 0; //mock todo implement
  }

  size_type size() const {
    return size;
  }
};
}
