#pragma once

#include <memory>
#include <list>
#include "Traits.h"
#include "ReverseIterator.h"
#include "Compare.h"
#include "Algorithm.h"

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t) -1)
#endif

namespace ft {

// -------------------------------------- TAGS -------------------------------------
//struct input_iterator_tag {};
//struct output_iterator_tag {};
//struct forward_iterator_tag : public input_iterator_tag {};
//struct bidirectional_iterator_tag : public forward_iterator_tag {};
//struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<class T, class Alloc = std::allocator<T> >
class List;

template<class Category, class Iter>
class BidirectionalListIt;

//	------------------------------------- LIST NODE -----------------------------------------
template<class T>
class NodeList {
 public:
  typedef T value_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  NodeList<T> *next;
  NodeList<T> *prev;
  value_type value;

 private:
  NodeList() : next(NULL), prev(NULL), value(value_type()) {}
  NodeList(const value_type &value) : next(NULL), prev(NULL), value(value) {}
  friend class List<T>;
  friend class BidirectionalListIt<iterator_category, T>;

  NodeList &operator=(const NodeList<value_type> &obj) {
    next = obj.next;
    prev = obj.prev;
    return *this;
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

//	------------------------------------- LIST ITERATOR -----------------------------------------
template<class Category, class Iter>
class BidirectionalListIt {
 protected:
  friend class List<Iter>;
 public:
  typedef std::ptrdiff_t difference_type;
  typedef Iter value_type;
  typedef Iter const const_value_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef value_type &reference;
  typedef value_type *pointer;
  typedef size_t size_type;
  typedef BidirectionalListIt<Category, Iter> iterator;

  explicit BidirectionalListIt() throw(): ptr(NULL) {}

  explicit BidirectionalListIt(NodeList<Iter> *p) throw(): ptr(p) {}

  BidirectionalListIt(const BidirectionalListIt &p) throw(): ptr(p.ptr) {}

  virtual ~BidirectionalListIt() {
  }

  BidirectionalListIt &operator=(const BidirectionalListIt &rhs) {
    ptr = rhs.ptr;
    return *this;
  }

  reference operator*() const {
    return this->ptr->value;
  }

  pointer operator->() const {
    return &(this->ptr->value);
  }

  friend bool operator==(const iterator &lhs,
                         const iterator &rhs) {
    return lhs.ptr == rhs.ptr;
  }

  friend bool operator!=(const iterator &lhs,
                         const iterator &rhs) {
    return lhs.ptr != rhs.ptr;
  }

  iterator &operator++() {
    ptr = ptr->next;
    return *this;
  }

  iterator operator++(int) {
    iterator clone(*this);
    ptr = ptr->next;
    return clone;
  }

  iterator &operator--() {
    ptr = ptr->prev;
    return *this;
  }

  iterator operator--(int) {
    iterator clone(*this);
    ptr = ptr->prev;
    return clone;
  }

 private:
  NodeList<Iter> *ptr;

 public:
  pointer p() const {
    return ptr;
  }
};

//	------------------------------------- LIST ITERATOR -----------------------------------------
template<class Category, class Iter>
class BidirectionalConstListIt {
 protected:
  NodeList<Iter> *ptr;
  friend class List<Iter>;
 public:
  typedef std::ptrdiff_t difference_type;
  typedef Iter value_type;
  typedef Iter const const_value_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef const value_type &reference;
  typedef const value_type *pointer;
  typedef size_t size_type;
  typedef BidirectionalConstListIt<Category, Iter> iterator;

  explicit BidirectionalConstListIt() throw(): ptr(NULL) {}

  explicit BidirectionalConstListIt(NodeList<Iter> *p) throw(): ptr(p) {}

  BidirectionalConstListIt(const BidirectionalConstListIt &p) throw(): ptr(p.ptr) {}

  BidirectionalConstListIt(const BidirectionalListIt<Category, Iter> &p) throw(): ptr(p.p()) {}

  virtual ~BidirectionalConstListIt() {}

  BidirectionalConstListIt &operator=(const BidirectionalConstListIt &rhs) {
    ptr = rhs.ptr;
    return *this;
  }

  reference operator*() const {
    return this->ptr->value;
  }

  pointer operator->() const {
    return &(this->ptr->value);
  }

  friend bool operator==(const iterator &lhs,
                         const iterator &rhs) {
    return lhs.ptr == rhs.ptr;
  }

  friend bool operator!=(const iterator &lhs,
                         const iterator &rhs) {
    return lhs.ptr != rhs.ptr;
  }

  iterator &operator++() {
    ptr = ptr->next;
    return *this;
  }

  iterator operator++(int) {
    iterator clone(*this);
    ptr = ptr->next;
    return clone;
  }

  iterator &operator--() {
    ptr = ptr->prev;
    return *this;
  }

  iterator operator--(int) {
    iterator clone(*this);
    ptr = ptr->prev;
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
  typedef std::ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef BidirectionalListIt<iterator_category, T> iterator;
  typedef BidirectionalConstListIt<iterator_category, T> const_iterator;
  typedef ft::ReverseIterator<iterator> reverse_iterator;
  typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;
  typedef std::allocator<value_type> allocator_type;

 private:
  NodeList<value_type> *shadow;
  size_type currentSize;

  void ListConstructorInit() {
    shadow = new NodeList<value_type>();
    shadow->next = shadow;
    shadow->prev = shadow;
    currentSize = 0;
  }

 public:
  explicit List() {
    ListConstructorInit();
  }

  explicit List(size_type n, const value_type &val = value_type()) {
    ListConstructorInit();
    shadow_constructor(n, val, ft::true_type());
  }

  template<class InputIterator>
  List(InputIterator first, InputIterator last) {
    ListConstructorInit();
    shadow_constructor(first, last, ft::is_primitive_type<InputIterator>());
  }

  List(const List &x) {
    ListConstructorInit();
    insert(begin(), x.begin(), x.end());
  }

  virtual ~List() {
    clear();
    delete shadow;
  }

  List &operator=(const List &x) {
    clear();
    insert(begin(), x.begin(), x.end());
    return *this;
  }

 private:
  template<class InputIterator>
  void shadow_constructor(InputIterator first, InputIterator last, ft::false_type) {
    insert(begin(), first, last);
  }

  void shadow_constructor(size_type n, const value_type &val, ft::true_type) {
    insert(begin(), n, val);
  }

 public:
  // ------------------- ITERATORS ----------------------
  iterator begin() {
    return iterator(shadow->next);
  }

  iterator end() {
    return iterator(shadow);
  }

  const_iterator begin() const {
    return const_iterator(shadow->next);
  }

  const_iterator end() const {
    return const_iterator(shadow);
  }

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
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
    shadow_insert(position, n, val, ft::true_type());
  }

  // range [first,last)
  template<class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {
    shadow_insert(position, first, last, ft::is_primitive_type<InputIterator>());
  }

 private:
  template<class InputIterator>
  void shadow_insert(iterator position, InputIterator first, InputIterator last, ft::false_type) {
    iterator tmp = position;

    while (first != last) {
      ++position;
      insert(tmp, *first);
      ++first;
    }
  }

  void shadow_insert(iterator position, size_type n, const value_type &val, ft::true_type) {
    iterator tmp = position;

    for (size_type i = 0; i < n; i++) {
      ++position;
      insert(tmp, val);
    }
  }

 public:

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
  void shadow_assign(InputIterator first, InputIterator last, ft::false_type) {
    iterator it = begin();

    while (first != last) {
      if (it == end()) {
        insert(it, first, last);
        return;
      }
      *it = *(first);
      ++it;
      ++first;
    }
    if (it != end()) {
      erase(it, end());
    }
  }

  void shadow_assign(size_type n, const value_type &val, ft::true_type) {
    iterator it = begin();
    iterator tmp = it;

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
    shadow_assign(first, last, ft::is_primitive_type<InputIterator>());
  }

  void assign(size_type n, const value_type &val) {
    shadow_assign(n, val, ft::true_type());
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
    size_type dist = distance(first, last);

    NodeList<T> *tmp_lastprev = last.ptr->prev;
    first.ptr->prev->next = last.ptr;
    last.ptr->prev = first.ptr->prev;
    NodeList<T> *tmp_posprev = position.ptr->prev;
    position.ptr->prev->next = first.ptr;
    position.ptr->prev = tmp_lastprev;
    first.ptr->prev = tmp_posprev;
    tmp_lastprev->next = position.ptr;

    this->currentSize += dist;
    x.currentSize -= dist;
  }

  void remove(const value_type &val) {
    iterator it = begin();
    iterator tmp = it;

    --tmp;
    while (it != end()) {
      if (*it == val) {
        erase(it);
        it = tmp;
      }
      tmp = it;
      ++it;
    }
  }

  template<class Predicate>
  void remove_if(Predicate pred) {
    iterator it = begin();
    iterator tmp = it;

    --tmp;
    while (it != end()) {
      if (pred(*it)) {
        erase(it);
        it = tmp;
      }
      tmp = it;
      ++it;
    }
  }

  void unique() {
    unique(ft::equal_to<value_type>());
  }

  template<class BinaryPredicate>
  void unique(BinaryPredicate binary_pred) {
    iterator it = begin();

    if (it == end()) {
      return;
    }

    iterator tmp;
    ++it;
    while (it != end()) {
      if (binary_pred(it.ptr->prev->value, it.ptr->value)) {
        tmp = it;
        ++it;
        erase(tmp);
        continue;
      }
      ++it;
    }
  }

  void sort() {
    if (currentSize <= 1) {
      return;
    }
    iterator start = begin();
    iterator finish = end();
    sort(ft::less<value_type>());
  }

  template<class Compare>
  void sort(Compare comp) {
    if (currentSize <= 1) {
      return;
    }
    size_type tmp = currentSize;
    merge_sort(*this, comp);
    currentSize = tmp;
  }

 private:
  template<class Compare>
  void merge_sort(List<value_type> &lst, Compare comp) {
    if (lst.size() <= 1) {
      return;
    }

    iterator itmid = lst.begin();

    size_type mid = lst.size() / 2;
    while (mid > 0) {
      --mid;
      ++itmid;
    }

    List<value_type> left;
    List<value_type> right;
    left.splice(left.begin(), lst, lst.begin(), itmid);
    right.splice(right.begin(), lst, itmid, lst.end());

    merge_sort(left, comp);
    merge_sort(right, comp);

    left.merge(right, comp);
    lst.swap(left);
  }

 public:
  void merge(List &x) {
    if (x.size() < 1) {
      return;
    }
    merge(x, ft::less<value_type>());
  }

  template<class Compare>
  void merge(List &x, Compare comp) {
    iterator this_it = this->begin();
    iterator x_it = x.begin();
    size_type this_size = this->currentSize;
    size_type x_size = x.currentSize;

    while (this_it != this->end() && x_it != x.end()) {
      if (comp(*x_it, *this_it)) {
        splice(this_it, *this, x_it);
        x_it = x.begin();
      } else {
        ++this_it;
      }
    }
    if (x_it != x.end()) {
      splice(this_it, *this, x_it, x.end());
    }
    this->currentSize = this_size + x_size;
    x.currentSize = 0;
  }

  void reverse() {
    iterator it = begin();
    NodeList<T> *tmp_prev;
    NodeList<T> *it_tmp;

    while (it != end()) {
      it_tmp = it.ptr;
      tmp_prev = it_tmp->prev;
      ++it;
      it_tmp->prev = it_tmp->next;
      it_tmp->next = tmp_prev;
    }
    it_tmp = it.ptr;
    tmp_prev = it_tmp->prev;
    it_tmp->prev = it_tmp->next;
    it_tmp->next = tmp_prev;
  }

 private:
  void swap(value_type *a, value_type *b) {
    value_type tmp = *a;
    *a = *b;
    *b = tmp;
  }

  template<class S>
  void swap(S &a, S &b) {
    S &tmp = a;
    a = b;
    b = tmp;
  }

  size_type distance(iterator start, iterator finish) {
    size_type dist = 0;

    while (start != finish) {
      ++dist;
      ++start;
    }
    return dist;
  }

  size_type distance(NodeList<T> *start, NodeList<T> *finish) {
    size_type dist = 0;

    while (start != finish) {
      ++dist;
      start = start->next;
    }
    return dist;
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

  typename ft::List<T>::const_iterator itLhs = lhs.begin();
  typename ft::List<T>::const_iterator itRhs = rhs.begin();

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
  typename ft::List<T, Alloc>::const_iterator first1 = lhs.begin();
  typename ft::List<T, Alloc>::const_iterator first2 = rhs.begin();
  typename ft::List<T, Alloc>::const_iterator last1 = lhs.end();
  typename ft::List<T, Alloc>::const_iterator last2 = rhs.end();

  return ft::lexicographical_compare_custom(first1, last1, first2, last2, ft::less<T>());
}

template<class T, class Alloc>
bool operator<=(ft::List<T, Alloc> const &lhs, ft::List<T, Alloc> const &rhs) {
  return lhs < rhs || lhs == rhs;
}

template<class T, class Alloc>
bool operator>(ft::List<T, Alloc> const &lhs, ft::List<T, Alloc> const &rhs) {
  return !(lhs <= rhs);
}

template<class T, class Alloc>
bool operator>=(ft::List<T, Alloc> const &lhs, ft::List<T, Alloc> const &rhs) {
  return lhs > rhs || lhs == rhs;
}

}
