#pragma once

#include <map>

namespace ft {

enum RB_tree_color {
  RED = true,
  BLACK = false
};

//	------------------------------------- MAP NODE -----------------------------------------
template<class T>
class Node {
 public:
  typedef T value_type;

  Node() : color(RB_tree_color::BLACK), parent(nullptr), left(nullptr), right(nullptr) {}
  value_type value;
  RB_tree_color color;
  Node *parent;
  Node *left;
  Node *right;

  Node(const value_type &value)
      : color(RB_tree_color::BLACK), value(value), left(nullptr), right(nullptr), parent(nullptr) {}

      //todo
//  Node &operator++() {
//
//  }
};

//	------------------------------------- MAP ITERATOR -----------------------------------------

template<class U>
class NodeIterator {
 public:
  typedef U iterator_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef iterator_type value_type;
  typedef ptrdiff_t difference_type;
  typedef iterator_type &reference;
  typedef iterator_type *pointer;
  typedef Node<U> Node;

 private:
  Node *node;
  const Node *nil; //todo what's inside?

 public:
  //  Is default-constructible, copy-constructible, copy-assignable and destructible
  NodeIterator() : node(nullptr), nil(nullptr) {}
  NodeIterator(Node *p) : node(p), nil(nullptr) {}
  NodeIterator(const NodeIterator &it) : node(it.node), nil(nullptr) {}

  NodeIterator &operator=(const NodeIterator &it) {
    node = it.node;
    nil = it.nil;
    return *this;
  }

  bool operator!=(NodeIterator const &other) const {
    return node != other.node;
  }
  bool operator==(NodeIterator const &other) const {
    return node == other.node;
  }

  typename NodeIterator::reference operator*() const {
    return node->value;
  }

  typename NodeIterator::reference operator->() const {
    return &(node->value);
  }

  //todo
//  NodeIterator &operator++() { // prefix increment. doesn't create a copy
//    if (node->parent == nullptr) {
//      node = nullptr;
//    } else if (node->parent->right.get() == node) {
//      node = node->parent;
//    } else {
//      node = node->parent;
//      if (node->right.get() != nullptr) {
//        node = node->right.get();
//        while (node->left.get() != nullptr) {
//          node = node->left.get();
//        }
//      }
//    }
//    return *this;
//  }
};
//	------------------------------------- MAP -----------------------------------------

template<class Key,                                           // map::key_type
    class T,                                                   // map::mapped_type
    class Compare = less<Key>,                                // map::key_compare
    class Alloc = std::allocator<std::pair<const Key, T> >    // map::allocator_type
>
class Map {
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

  typedef Node<value_type> Node;

  typedef NodeIterator<value_type> iterator;
  //todo
//  typedef NodeConstIterator<Node> const_iterator;
//  typedef NodeConstIterator<Node> reverse_iterator;
//  typedef NodeConstIterator<Node> const_reverse_iterator;

//todo do need inherit?
 class value_compare : public std::binary_function<value_type, value_type, bool>  {
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

 private:
  size_type currentSize;
  key_compare key_compare_;
  value_compare value_compare_;
  Node *root;

 public:

  mapped_type &operator[](const key_type &k) {
    return (*((this->insert(make_pair(k, mapped_type()))).first)).second;
  }

  std::pair<iterator, bool> insert(const value_type &val) {

  }

  iterator insert(iterator position, const value_type &val) {

  }

  template<class InputIterator>
  void insert(InputIterator first, InputIterator last) {

  }

//  todo constructors...

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
    return size;
  }

  key_compare key_comp() const {
    return key_compare_;
  }

  value_compare value_comp() const {
    return value_compare_;
  }

  int compareTo(const key_type &o1, const key_type &o2) {
    if (o1 == o2) { return 0; }
    else if (o1 < o2) { return -1; }
    else { return 1; };
  }

  iterator find(const key_type &k) {
    Node *x = root;

    while (x != nullptr) {
      int cmp = compareTo(k, x->value.first); //todo check
      if (cmp < 0) { x = x->left; }
      else if (cmp > 0) { x = x->right; }
      else { return iterator(x->value); }
    }
    return nullptr; //todo sentinel
  }

//  const_iterator find (const key_type& k) const {
//    return const_iterator(*find(k)); //todo check
//  }

};

}
