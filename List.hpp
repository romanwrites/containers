#pragma once

#include <memory>
#include <list>

namespace ft {
template<class T>
class List;

template<class Iter>
class BidirectionalListIt;
//	------------------------------------- LIST NODE -----------------------------------------
template<class T>
class NodeList {
 public:
  typedef T value_type;
 private:
  NodeList<T> *next;
  NodeList<T> *prev;
  value_type value;
  NodeList() : next(nullptr), prev(nullptr), value(value_type()) {}
  NodeList(const value_type &value) : next(nullptr), prev(nullptr), value(value) {} //todo
  //todo copy constructor
  friend class List<T>;
  friend class BidirectionalListIt<T>;

  NodeList &operator=(const NodeList<value_type> &obj) {
    next = obj.next;
    prev = obj.prev;
  }
 public:

  bool operator==(const NodeList &rhs) const {
    return value == rhs.value;
  }

  bool operator!=(const NodeList &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const NodeList &rhs) const {
    return value < rhs.value;
  }

  bool operator>(const NodeList &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const NodeList &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const NodeList &rhs) const {
    return !(*this < rhs);
  }
};

// -------------------------------------- TAGS -------------------------------------
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//	------------------------------------- LIST ITERATOR -----------------------------------------
template<class Iter>
class BidirectionalListIt {
 private:
  NodeList<Iter> *ptr;
  friend class List<Iter>;
 public:
  typedef std::ptrdiff_t difference_type;
  typedef Iter value_type;
  typedef Iter const const_value_type;
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef value_type &reference;
  typedef value_type *pointer;
  typedef const_value_type &const_reference;
  typedef const_value_type *const_pointer;
  typedef size_t size_type;

  explicit BidirectionalListIt() throw(): ptr(nullptr) {}
  explicit BidirectionalListIt(NodeList<Iter> *p) throw(): ptr(p) {}
  explicit BidirectionalListIt(const NodeList<const Iter> *p) throw(): ptr(const_cast<NodeList<const Iter> *>(p)) {}
  BidirectionalListIt(const BidirectionalListIt &p) throw(): ptr(p.ptr) {}
  ~BidirectionalListIt() {}

  BidirectionalListIt &operator=(const BidirectionalListIt &rhs) {
    ptr = rhs.ptr;
    return *this;
  }

  reference operator*() {
    return this->ptr->value;
  }

  const_reference operator*() const {
    return this->ptr->value;
  }

  pointer operator->() {
    return &(this->ptr->value);
  }

  const_pointer operator->() const {
    return &(this->ptr->value);
  }

  bool operator==(const BidirectionalListIt &rhs) const {
    return ptr == rhs.ptr;
  }

  bool operator!=(const BidirectionalListIt &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const BidirectionalListIt &rhs) const {
    return ptr < rhs.ptr;
  }

  bool operator>(const BidirectionalListIt &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const BidirectionalListIt &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const BidirectionalListIt &rhs) const {
    return !(*this < rhs);
  }

  BidirectionalListIt<Iter> &operator++() {
    ptr = ptr->next;
    return *this;
  }

  BidirectionalListIt<Iter> operator++(int) {
    BidirectionalListIt<Iter> clone(*this);
    ptr = ptr->next;
    return clone;
  }

  BidirectionalListIt<Iter> &operator--() {
    ptr = ptr->prev;
    return *this;
  }

  BidirectionalListIt<Iter> operator--(int) {
    BidirectionalListIt<Iter> clone(*this);
    ptr = ptr->prev;
    return clone;
  }
};

//	------------------------------------- LIST CONTAINER -----------------------------------------
template<class T>
class List {
 public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef BidirectionalListIt<T> iterator;
  typedef BidirectionalListIt<T> const_iterator;
  typedef bidirectional_iterator_tag iterator_category;

 private:
  NodeList<value_type> *shadow;
  NodeList<value_type> *start;
  NodeList<value_type> *finish;
  size_type currentSize;

 public:
  List() : shadow(new NodeList<value_type>()), start(nullptr), finish(nullptr), currentSize(0) {}

  // ------------------- ITERATORS ----------------------
  iterator begin() {
    return iterator(shadow->next);
  }

  iterator end() {
    return iterator(shadow);
  }

  iterator begin() const {
    return iterator(shadow->next);
  }

  iterator end() const {
    return iterator(shadow);
  }

  value_type &at(int idx) {
    NodeList<value_type> *ptr = shadow->next;
    for (int i = 0; i < idx; i++) {
      ptr = ptr->next;
    }
    return ptr->value;
  }

  void push_back(value_type const &value) {
    insert(end(), value);
  }

  void push_front(value_type const &value) {
    insert(begin(), value);
  }

  // single element
  iterator insert(iterator position, const value_type &val) {
    NodeList<value_type> *insert_node = new NodeList<value_type>();
    insert_node->value = val;
    if (currentSize == 0) {
      shadow->next = insert_node;
      shadow->prev = insert_node;
      insert_node->next = shadow;
      insert_node->prev = shadow;
    } else {
      NodeList<value_type> *pos = position.ptr;
      insert_node->next = pos;
      insert_node->prev = pos->prev;
      insert_node->prev->next = insert_node;
      insert_node->next->prev = insert_node;
    }
    ++currentSize;
    return iterator(insert_node);
  }

  size_type size() const {
    return currentSize;
  }

  bool empty() const {
    return currentSize == 0;
  }

  size_type max_size() const {
    return SIZE_MAX / sizeof(NodeList<T>);
  }

  reference front();
  const_reference front() const;


//    	// fill
//        void insert(iterator position, size_type n, const value_type& val) {
//
//    	}
//
//    	// range
//        template <class InputIterator>
//        void insert(iterator position, InputIterator first, InputIterator last) {
//
//    	}

};

//todo list operator==, operator<= etc
}
