#pragma once

#include <iostream>
#include <vector>
#include "Traits.h"
#include "List.h"
#include "ReverseIterator.h"

namespace ft {
//	------------------------------------- VECTOR ITERATOR -----------------------------------------
template<class T>
class V_iterator {
 public:
  typedef T *pointer;
  typedef T &reference;
  typedef const T *const_pointer;
  typedef const T &const_reference;
  typedef V_iterator iterator;

  V_iterator() throw() {
    ptr = nullptr;
  }

  V_iterator(pointer p) throw() {
    ptr = p;
  }

  V_iterator(V_iterator const &p) throw() {
    *this = p;
  }

  virtual ~V_iterator() throw() {}

  iterator &operator=(V_iterator const &p) throw() {
    ptr = p.ptr;
    return *this;
  }

  iterator &operator++() throw() {
    ptr++;
    return *this;
  }

  iterator operator++(int) throw() {
    V_iterator it = *this;
    ++(*this);
    return it;
  }

  iterator &operator--() throw() {
    ptr--;
    return *this;
  }

  iterator operator--(int) throw() {
    iterator it = *this;
    --(*this);
    return it;
  }

  reference operator*() const throw() {
    return *ptr;
  }

  pointer operator->() const throw() {
    return ptr;
  }

  reference operator[](int idx) const throw() {
    return ptr[idx];
  }

  friend bool operator==(iterator const &lhs,
                         iterator const &rhs) {
    return lhs.ptr == rhs.ptr;
  }

  friend bool operator!=(iterator const &lhs,
                         iterator const &rhs) {
    return lhs.ptr != rhs.ptr;
  }

  friend bool operator<(iterator const &lhs,
                         iterator const &rhs) {
    return lhs.ptr < rhs.ptr;
  }

  friend bool operator>(iterator const &lhs,
                         iterator const &rhs) {
    return lhs.ptr > rhs.ptr;
  }

  friend bool operator<=(iterator const &lhs,
                         iterator const &rhs) {
    return lhs.ptr <= rhs.ptr;
  }

  friend bool operator>=(iterator const &lhs,
                         iterator const &rhs) {
    return lhs.ptr >= rhs.ptr;
  }

  iterator operator+(int n) throw() {
    iterator ret(ptr + n);
    return ret;
  }

  iterator operator-(int n) throw() {
    iterator ret(ptr - n);
    return ret;
  }

  iterator operator+=(int n) throw() {
    ptr += n;
    return *this;
  }

  iterator operator-=(int n) throw() {
    ptr -= n;
    return *this;
  }

 private:
  T *ptr;
};

//	------------------------------------- VECTOR -----------------------------------------
template<class T, typename Alloc = std::allocator<T> > // pass any type and compiler auto generate Vector parametrized with this type
class Vector {
 public:
  typedef T value_type;
  typedef value_type &reference;
  typedef value_type *pointer;
  typedef value_type const &const_reference;
  typedef value_type const *const_pointer;
  typedef V_iterator<T> iterator;
  typedef V_iterator<T> const const_iterator;
  typedef ft::reverse_iterator<T> reverse_iterator;
  typedef ft::reverse_iterator<T> const const_reverse_iterator;
  typedef size_t size_type;
  typedef Alloc allocator_type;
  typedef ptrdiff_t difference_type;

 private:
  T *data;

  size_t currentSize;
  size_t dataCapacity;
  allocator_type allocator;

 public:
  explicit Vector(const allocator_type &alloc = allocator_type())
      : data(nullptr), currentSize(0), dataCapacity(0), allocator(alloc) {
    reserve(2);
  }

  explicit Vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
      : data(nullptr), currentSize(0), dataCapacity(0), allocator(alloc) {
    reserve(n);
    currentSize = n;
    for (size_t i = 0; i < currentSize; i++) {
      data[i] = val;
    }
    (void) alloc;
  }

  template<class InputIterator>
  Vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
      : data(nullptr), currentSize(0), dataCapacity(0), allocator(alloc) {
    reserve(2);
    insert(begin(), first, last);
  }

  Vector(const Vector &x) {
    (void) x;
  }

  Vector(T arr[], int n) throw() {
    data = new T[n];
    for (int i = 0; i < n; i++) {
      data[i] = arr[i];
    }
  }

  Vector &operator=(Vector const &obj) throw() {
    clear();
    if (data && dataCapacity) {
      ::operator delete(data); // , capacity * sizeof(T)
    }
    reserve(obj.dataCapacity);
    for (int i = 0; i < obj.currentSize; i++) {
      data[i] = obj.data[i];
    }
    currentSize = obj.currentSize;
  }

  virtual ~Vector() throw() {
    for (size_type i = 0; i < currentSize; ++i) {
      allocator.destroy(data + i);
    }
    allocator.deallocate(data, dataCapacity);
  }

  iterator erase(iterator position) {
    return erase(position, position + 1);
  }

  iterator erase(iterator first, iterator last) {
    size_type pos_first = &(*first) - data;
    size_type pos_last = &(*last) - data;

    for (size_type i = pos_first, j = pos_last; last != end(); ++i, ++j) {
      allocator.destroy(data + i);
      allocator.construct(&data[i], data[j]);
      ++last;
    }
    currentSize -= pos_last - pos_first;
    return iterator(data + pos_first);
  }

  iterator begin() throw() {
    return iterator(data);
  }

  iterator end() throw() {
    return iterator(data + currentSize);
  }

  const_iterator begin() const {
    return iterator(data);
  }

  const_iterator end() const {
    return iterator(data + currentSize);
  }

  reverse_iterator rbegin() throw() {
    return reverse_iterator(end());
  }

  reverse_iterator rend() throw() {
    return reverse_iterator(begin());
  }

  const_reverse_iterator rbegin() const throw() {
    return reverse_iterator(end());
  }

  const_reverse_iterator rend() const throw() {
    return reverse_iterator(begin());
  }

  bool empty() const throw() {
    return currentSize == 0;
  }

  void push_back(const T &val) throw() {
    insert(end(), val);
  }

  void pop_back() throw() {
    if (currentSize > 0) {
      currentSize--;
      allocator.destroy(&data[currentSize]);
    }
  }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

  reference front() {
    return *(data + 0);
  }

  const_reference front() const {
    return data[0];
  }

  reference at(size_type n) {
    return data[n];
  }

  const_reference at(size_type n) const {
    return data[n];
  }

  reference back() { return *(data + currentSize - 1); }

  const_reference back() const { return *(data + currentSize - 1); }

  iterator insert(iterator position, const value_type &val) {
    size_type pos = &(*position) - data;

    if (currentSize >= dataCapacity) {
      reserve(dataCapacity + dataCapacity);
    }

    for (size_t i = 0; i < currentSize - pos; ++i) {
      allocator.construct(&data[currentSize - i], data[currentSize - i - 1]);
      allocator.destroy(&data[currentSize - i - 1]);
    }
    allocator.construct(data + pos, val);
    ++currentSize;

    return iterator(data + pos);
  }

  void insert(iterator position, size_type n, const value_type &val) {
    shadow_insert(position, n, val, ft::true_type());
  }

  template<class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {
    shadow_insert(position, first, last, ft::is_primitive_type<InputIterator>());
  }
 private:
  template<class InputIterator>
  void shadow_insert(iterator position, InputIterator first, InputIterator last, ft::false_type) {
    size_type pos = &(*position) - data;

    for (size_type i = 0; first != last; ++i) {
      insert(iterator(data + pos), *first);
      ++first;
      ++pos;
    }
  }

  void shadow_insert(iterator position, size_type n, const value_type &val, ft::true_type) {
    size_type pos = &(*position) - data;

    for (size_type i = 0; i < n; ++i) {
      insert(iterator(data + pos), val);
      ++pos;
    }
  }

  void shadow_assign(size_type n, const value_type &val, ft::true_type) {
    clear();
    insert(begin(), n, val);
  }

  template<class InputIterator>
  void shadow_assign(InputIterator first, InputIterator last, ft::false_type) {
    clear();
    insert(begin(), first, last);
  }

 public:

  template<class InputIterator>
  void assign(InputIterator first, InputIterator last) {
    shadow_assign(first, last, ft::is_primitive_type<InputIterator>());
  }

  void assign(size_type n, const value_type &val) {
    shadow_assign(n, val, ft::true_type());
  }

  void clear() throw() {
    for (size_t i = 0; i < currentSize; i++) {
      data[i].~T();
    }
    currentSize = 0;
  }

  size_t size() const throw() { return currentSize; }
  size_type capacity() const { return dataCapacity; }

  const_reference operator[](size_t idx) const throw() {
    return data[idx];
  }

  reference operator[](size_t idx) throw() {
    return data[idx];
  }

  bool operator==(Vector<T> const &rhs) throw() {
    if (size() != rhs.size())
      return false;
    for (size_type i = 0; i < currentSize; i++) {
      if (data[i] != rhs.data[i])
        return false;
    }
    return true;
  }

  bool operator!=(Vector<T> const &rhs) throw() {
    return !(*this == rhs);
  }

  T &at(int idx) {
    return (*this)[idx];
  }

  void reserve(size_type newCapacity) throw() {
    if (newCapacity == 0 || newCapacity <= currentSize) {
      return;
    }

    T *newBlock = allocator.allocate(newCapacity);

    for (size_t i = 0; i < currentSize; i++) {
      allocator.construct(&newBlock[i], data[i]);
      allocator.destroy(data + i);
    }
    allocator.deallocate(data, dataCapacity);
    data = newBlock;
    dataCapacity = newCapacity;
  }

  void resize(size_type n, value_type val = value_type()) {
    if (n < currentSize) {
      currentSize = n;
      return;
    }
    insert(end(), n - currentSize, val);
  }

  void swap(Vector &x) {
    size_type tmp_currentSize = x.currentSize;
    x.currentSize = this->currentSize;
    this->currentSize = tmp_currentSize;

    size_type tmp_capacity = x.dataCapacity;
    x.dataCapacity = this->dataCapacity;
    this->dataCapacity = tmp_capacity;

    value_type *tmp_data = x.data;
    x.data = this->data;
    this->data = tmp_data;
  }

  allocator_type get_allocator() const {
    return allocator;
  }

};

template<class T, class Alloc>
void swap(Vector<T, Alloc> &x, Vector<T, Alloc> &y) {
  x.swap(y);
}

template<class T, class Alloc>
bool operator==(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }

  typename ft::Vector<T>::iterator itLhs = lhs.begin();
  typename ft::Vector<T>::iterator itRhs = rhs.begin();

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
bool operator!=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) {
  return !(lhs == rhs);
}

template<class T, class Alloc>
bool operator<(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) {
  typename ft::Vector<T, Alloc>::iterator first1 = lhs.begin();
  typename ft::Vector<T, Alloc>::iterator first2 = rhs.begin();
  typename ft::Vector<T, Alloc>::iterator last1 = lhs.end();
  typename ft::Vector<T, Alloc>::iterator last2 = rhs.end();

  return lexicographical_compare(first1, last1, first2, last2, ft::less<T>());
}

template<class T, class Alloc>
bool operator<=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) {
  return lhs < rhs || lhs == rhs;
}

template<class T, class Alloc>
bool operator>(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) {
  return !(lhs <= rhs);
}

template<class T, class Alloc>
bool operator>=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs) {
  return lhs > rhs || lhs == rhs;
}

}
