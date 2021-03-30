#pragma once

#include "Allocator.h"
#include <map>

namespace ft {

enum RB_tree_color {
  RED = true,
  BLACK = false
};

//	------------------------------------- MAP NODE -----------------------------------------
template<class T>
class MapNode {

 public:
  typedef T value_type;

  value_type value;
  RB_tree_color color;
  MapNode *parent;
  MapNode *left;
  MapNode *right;

  MapNode() : color(RB_tree_color::BLACK), parent(nullptr), left(nullptr), right(nullptr) {}

  MapNode(const value_type &value)
      : color(RB_tree_color::BLACK), value(value), left(nullptr), right(nullptr), parent(nullptr) {}

  MapNode(const MapNode &o)
      : color(o.color), value(o.value), left(o.left), right(o.right), parent(o.parent) {}

  MapNode &operator=(const MapNode &o) {
    color = o.color;
    value = o.value;
    left = o.left;
    right = o.right;
    parent = o.parent;
  }

  virtual ~MapNode() {}
};

//	------------------------------------- MAP ITERATOR -----------------------------------------
template<class P>
class MapIterator {
 public:
  typedef P iterator_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef iterator_type value_type;
  typedef ptrdiff_t difference_type;
  typedef P &reference;
  typedef P *pointer;
  typedef MapNode<P> Node;

  // add const in const iterator

 private:
  Node *node;
  const Node *nil; //todo what's inside?

 public:
  //  Is default-constructible, copy-constructible, copy-assignable and destructible
  MapIterator() : node(nullptr), nil(nullptr) {}
  MapIterator(Node *p, Node *nil) : node(p), nil(nil) {}
  MapIterator(const MapIterator &it) : node(it.node), nil(it.nil) {}

  MapIterator &operator=(const MapIterator &it) {
    node = it.node;
    nil = it.nil;
    return *this;
  }

  // kind of static
  friend
  bool operator==(MapIterator const &lhs, MapIterator const &rhs) {
    return lhs.node == rhs.node; // compare pointers
  }

  friend
  bool operator==(MapIterator const &lhs, MapIterator const &rhs) {
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
//	------------------------------------- MAP -----------------------------------------

template<class Key,                                           // map::key_type
    class T,                                                   // map::mapped_type
    class Compare = less<Key>,                                // map::key_compare
    class Alloc = ft::Allocator<std::pair<const Key, T> >    // map::allocator_type
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

  typedef MapNode<value_type> Node;

  typedef MapIterator<value_type> iterator;
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
//  explicit Map (const key_compare& comp = key_compare(),
//				const allocator_type& alloc = allocator_type()) : key_compare_(comp), allocator(alloc) {
//
//  }
//
//  template <class InputIterator>
//  Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
//
//  }
//
//  Map (const Map& x) {
//
//  }

 private:
  key_compare key_compare_;
  value_compare value_compare_;
  allocator_type allocator;
  Node *root;
  size_type currentSize;

 public:

  mapped_type &operator[](const key_type &k) {
    return (*((this->insert(make_pair(k, mapped_type()))).first)).second;
  }

//  std::pair<iterator, bool> insert(const value_type &val) {
//
//  }
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
