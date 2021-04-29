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
  //  template<typename Key, typename Val, typename KeyOfValue,
//      typename Compare, typename Alloc = ft::Allocator<Val> >
  RbTree<key_type, value_type, value_type, Compare, Alloc> tree;

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
    return tree.empty(); //mock todo implement
  }

  size_type size() const {
    return tree.size();
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
};

}
