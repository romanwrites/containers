#pragma once

#include <memory>
#include <list>
#include "Traits.h"

namespace ft {

// -------------------------------------- TAGS -------------------------------------
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<class T, class Alloc = std::allocator<T> >
class List;

template<class Category, class Iter>
class BidirectionalListIt;

template<class Category, class Iter>
class BidirectionalListReverseIt;
//	------------------------------------- LIST NODE -----------------------------------------
template<class T>
class NodeList {
 public:
  typedef T value_type;
  typedef ft::bidirectional_iterator_tag iterator_category;
 private:
  NodeList<T> *next;
  NodeList<T> *prev;
  value_type value;
  NodeList() : next(nullptr), prev(nullptr), value(value_type()) {}
  NodeList(const value_type &value) : next(nullptr), prev(nullptr), value(value) {} //todo
  //todo copy constructor
  friend class List<T>;
  friend class BidirectionalListIt<iterator_category, T>;
  friend class BidirectionalListReverseIt<iterator_category, T>;

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

//reverse_iterator rbegin(); todo
//const_reverse_iterator rbegin() const; todo
//	------------------------------------- LIST ITERATOR -----------------------------------------
template<class Category, class Iter>
class BidirectionalListIt {
 protected:
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
  typedef BidirectionalListIt<Category, Iter> iterator;

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

  BidirectionalListIt &operator++() {
    ptr = ptr->next;
    return *this;
  }

  BidirectionalListIt operator++(int) {
    BidirectionalListIt clone(*this);
    ptr = ptr->next;
    return clone;
  }

  BidirectionalListIt &operator--() {
    ptr = ptr->prev;
    return *this;
  }

  BidirectionalListIt operator--(int) {
    BidirectionalListIt clone(*this);
    ptr = ptr->prev;
    return clone;
  }
};

//	------------------------------------- LIST REVERSE ITERATOR -----------------------------------------
template<class Category, class Iter>
class BidirectionalListReverseIt : public BidirectionalListIt<Category, Iter> {
 private:
//  NodeList<Iter> *ptr;
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
  typedef BidirectionalListReverseIt<Category, Iter> reverse_iterator;
  typedef BidirectionalListIt<Category, Iter> iterator;
  typedef BidirectionalListIt<Category, Iter> base_iterator;

  explicit BidirectionalListReverseIt() throw(): base_iterator() {}
  explicit BidirectionalListReverseIt(NodeList<Iter> *p) throw(): base_iterator(p) {}
  explicit BidirectionalListReverseIt(const NodeList<const Iter> *p) throw() {
    this->ptr = const_cast<NodeList<const Iter> *>(p);
  }
  BidirectionalListReverseIt(const BidirectionalListReverseIt &p) throw() {
    this->ptr = p.ptr;
  }
  ~BidirectionalListReverseIt() {}

  BidirectionalListReverseIt &operator=(const BidirectionalListReverseIt &rhs) {
    this->ptr = rhs.ptr;
    return *this;
  }

  reverse_iterator &operator++() {
    this->ptr = this->ptr->prev;
    return *this;
  }

  reverse_iterator operator++(int) {
    reverse_iterator clone(*this);
    this->ptr = this->ptr->prev;
    return clone;
  }

  reverse_iterator &operator--() {
    this->ptr = this->ptr->next;
    return *this;
  }

  reverse_iterator operator--(int) {
    reverse_iterator clone(*this);
    this->ptr = this->ptr->next;
    return clone;
  }
};

//	------------------------------------- LIST CONTAINER -----------------------------------------
template<class T, class Alloc>
class List {
 public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef bidirectional_iterator_tag iterator_category;
  typedef BidirectionalListIt<iterator_category, T> iterator;
  typedef BidirectionalListIt<iterator_category, T> const_iterator;
  typedef BidirectionalListReverseIt<iterator_category, T> reverse_iterator;
  typedef BidirectionalListReverseIt<iterator_category, T> const_reverse_iterator;

 private:
  NodeList<value_type> *shadow;
  size_type currentSize;

 public:
  explicit List() : shadow(new NodeList<value_type>()), currentSize(0) {
    shadow->next = shadow;
    shadow->prev = shadow;
  }

  explicit List(size_type n, const value_type &val = value_type()) : List() {
    shadow_constructor(n, val, ft::type_true());
  }

  template<class InputIterator>
  List(InputIterator first, InputIterator last) : List() {
    shadow_constructor(first, last, ft::type_is_primitive<InputIterator>());
  }

 private:
  template<class InputIterator>
  void shadow_constructor(InputIterator first, InputIterator last, ft::type_false) {
    insert(begin(), first, last);
  }

  void shadow_constructor(size_type n, const value_type &val, ft::type_true) {
    insert(begin(), n, val);
  }

 public:
  List(const List &x) {
    this();
    insert(begin(), x.begin(), x.end());
  }

  ~List() {
    clear();
    delete shadow;
  }

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

  reverse_iterator rbegin() {
    return reverse_iterator(shadow->prev);
  }

  reverse_iterator rend() {
    return reverse_iterator(shadow);
  }

  const_reverse_iterator rbegin() const {
    return reverse_iterator(shadow->prev);
  }

  const_reverse_iterator rend() const {
    return reverse_iterator(shadow);
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

  void pop_front() {
    erase(begin());
  }
  void pop_back() {
    iterator pos = end();
    --pos;
    erase(pos);
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

  // fill
  void insert(iterator position, size_type n, const value_type &val) {
    iterator tmp = position;
    for (size_type i = 0; i < n; i++) {
      ++position;
      insert(tmp, val);
    }
  }

  // range [first,last)
  template<class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {
    iterator tmp = position;
    while (first != last) {
      ++position;
      insert(tmp, *first);
      ++first;
    }
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

  reference front() {
    return shadow->next->value;
  }

  const_reference front() const {
    return shadow->next->value;
  }

  reference back() {
    return shadow->prev->value;
  }

  const_reference back() const {
    return shadow->prev->value;
  }

 private:
  template<class InputIterator>
  void shadow_assign(InputIterator first, InputIterator last, ft::type_false) {
    iterator it = begin();
//    currentSize = 0;
    while (first != last) {
      if (it == end()) {
        insert(it, first, last);
        return;
      }
      *it = *(first);
//      ++currentSize;
      ++it;
      ++first;
    }
    if (it != end()) {
      erase(it, end());
    }
  }

  void shadow_assign(size_type n, const value_type &val, ft::type_true) {
    iterator it = begin();
    iterator tmp = it;
//    currentSize = 0;
    if (it == end()) {
      insert(begin(), n, val);
      return;
    }
    for (size_type i = 0; i < n; i++) {
      if (it == end()) {
        insert(it, n - i - 1, val);
        return;
      }
      ++it;
      *tmp = val;
      tmp = it;
    }
    if (it != end()) {
      erase(it, end());
    }
  }

 public:
  template<class InputIterator>
  void assign(InputIterator first, InputIterator last) {
    shadow_assign(first, last, ft::type_is_primitive<InputIterator>());
  }

  void assign(size_type n, const value_type &val) {
    shadow_assign(n, val, ft::type_true());
  }

  iterator erase(iterator position) {
    NodeList<value_type> *pos = position.ptr;
    currentSize--;
    NodeList<value_type> *prev = pos->prev;
    prev->next = pos->next;
    pos->next->prev = prev;
    delete pos;
    return iterator(prev->next);
  }

  iterator erase(iterator first, iterator last) {
    iterator tmp = first;
    while (first != last) {
      ++first;
      erase(tmp);
      tmp = first;
    }
    return iterator(first);
  }

  void clear() {
    erase(begin(), end());
  }

  void swap(List &x) {
    NodeList<value_type> *tmp = shadow;
    shadow = x.shadow;
    x.shadow = tmp;

    size_type tmpSize = currentSize;
    currentSize = x.currentSize;
    x.currentSize = tmpSize;
  }

  void resize(size_type n, value_type val = value_type()) {
    if (n < currentSize) {
      typename ft::List<value_type>::iterator it = end();
      --it;
      typename ft::List<value_type>::iterator tmp = it;
      while (currentSize > n) {
        --it;
        erase(tmp);
        tmp = it;
      }
    } else {
      insert(end(), n - currentSize, val);
    }
  }

  void splice(iterator position, List &x) {
    splice(position, x, x.begin(), x.end());
  }

  void splice(iterator position, List &x, iterator i) {
    iterator last = i;
    ++last;
    splice(position, x, i, last);
  }

  void splice(iterator position, List &x, iterator first, iterator last) {
    iterator start = first;
    iterator finish = last;

    size_type dist = 0;

    while (start != finish) {
      ++dist;
      ++start;
    }

    NodeList<T> *tmp_last_prev = last.ptr->prev;
    first.ptr->prev->next = last.ptr;
    last.ptr->prev = first.ptr->prev;
    NodeList<T> *tmp_pos_prev = position.ptr->prev;
    position.ptr->prev->next = first.ptr;
    position.ptr->prev = tmp_last_prev;
    first.ptr->prev = tmp_pos_prev;
    tmp_last_prev->next = position.ptr;

    currentSize += dist;
    x.currentSize -= dist;
  }

};

template<class T, class Alloc>
void swap(List<T, Alloc> &x, List<T, Alloc> &y) {
  x.swap(y);
}

template<class T, class Alloc>
bool operator==(ft::List<T, Alloc> const &lhs, ft::List<T, Alloc> const &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  typename ft::List<T>::iterator itLhs = lhs.begin();
  typename ft::List<T>::iterator itRhs = rhs.begin();

  while (itLhs != lhs.end() && itRhs != rhs.end()) {
    if (*itLhs != *itRhs) {
      return false;
    }
    ++itLhs;
    ++itRhs;
  }
  return true;
}

template<class T, class Alloc>
bool operator!=(ft::List<T, Alloc> const &lhs, ft::List<T, Alloc> const &rhs) {
  return !(lhs == rhs);
}

template<class T, class Alloc>
bool operator<(ft::List<T, Alloc> const &lhs, ft::List<T, Alloc> const &rhs) {
  typename ft::List<T, Alloc>::iterator itLhs = lhs.begin();
  typename ft::List<T, Alloc>::iterator itRhs = rhs.begin();

  while (itLhs != lhs.end() && itRhs != rhs.end()) {
    if (*itLhs < *itRhs) {
      return true;
    }
    ++itLhs;
    ++itRhs;
  }
  return lhs.size() < rhs.size();
}

template<class T, class Alloc>
bool operator>(ft::List<T, Alloc> const &lhs, ft::List<T, Alloc> const &rhs) {
  return rhs < lhs;
}

template<class T, class Alloc>
bool operator<=(ft::List<T, Alloc> const &lhs, ft::List<T, Alloc> const &rhs) {
  return lhs < rhs || lhs == rhs;
}

template<class T, class Alloc>
bool operator>=(ft::List<T, Alloc> const &lhs, ft::List<T, Alloc> const &rhs) {
  return lhs > rhs || lhs == rhs;
}
}
