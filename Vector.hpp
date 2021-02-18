#pragma once

#include <iostream>
//#include <vector>

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

  bool operator==(iterator rhs) const throw() {
    return ptr == rhs.ptr;
  }

  bool operator!=(iterator rhs) const throw() {
    return ptr != rhs.ptr;
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

  bool operator<(iterator const &rhs) {
    return ptr < rhs.ptr;
  }

  bool operator>(iterator const &rhs) {
    return ptr > rhs.ptr;
  }

  bool operator<=(iterator const &rhs) {
    return ptr <= rhs.ptr;
  }

  bool operator>=(iterator const &rhs) {
    return ptr >= rhs.ptr;
  }

 private:
  T *ptr;
};
//	------------------------------------- REVERSE ITERATOR -----------------------------------------
template<class T>
class V_rev_iterator {
 public:
  typedef T *pointer;
  typedef T &reference;
  typedef const T *const_pointer;
  typedef const T &const_reference;
  typedef V_rev_iterator rev_iterator;

  V_rev_iterator() throw() {
    ptr = nullptr;
  }

  V_rev_iterator(pointer p) throw() {
    ptr = p;
  }

  V_rev_iterator(V_rev_iterator const &p) throw() {
    *this = p;
  }

  virtual ~V_rev_iterator() throw() {}

  rev_iterator &operator=(V_rev_iterator const &p) throw() {
    ptr = p.ptr;
    return *this;
  }

  rev_iterator &operator++() throw() {
    ptr--;
    return *this;
  }

  rev_iterator operator++(int) throw() {
    V_rev_iterator it = *this;
    --(*this);
    return it;
  }

  rev_iterator &operator--() throw() {
    ptr++;
    return *this;
  }

  rev_iterator operator--(int) throw() {
    rev_iterator it = *this;
    ++(*this);
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

  bool operator==(rev_iterator rhs) const throw() {
    return ptr == rhs.ptr;
  }

  bool operator!=(rev_iterator rhs) const throw() {
    return ptr != rhs.ptr;
  }

  rev_iterator operator+(int n) throw() {
    rev_iterator ret(ptr - n);
    return ret;
  }

  rev_iterator operator-(int n) throw() {
    rev_iterator ret(ptr + n);
    return ret;
  }

  rev_iterator operator+=(int n) throw() {
    ptr -= n;
    return *this;
  }

  rev_iterator operator-=(int n) throw() {
    ptr += n;
    return *this;
  }

  bool operator<(rev_iterator const &rhs) {
    return ptr < rhs.ptr;
  }

  bool operator>(rev_iterator const &rhs) {
    return ptr > rhs.ptr;
  }

  bool operator<=(rev_iterator const &rhs) {
    return ptr <= rhs.ptr;
  }

  bool operator>=(rev_iterator const &rhs) {
    return ptr >= rhs.ptr;
  }

 private:
  T *ptr;
};

//	------------------------------------- VECTOR -----------------------------------------
template<class T> // pass any type and compiler auto generate Vector parametrized with this type
class Vector {
 public:
  typedef V_iterator<T> iterator;
  typedef V_rev_iterator<T> rev_iterator;
 public:
  Vector() throw() {
    data = nullptr;
    currentSize = 0;
    capacity = 0;
    _begin = _end = data;
    Realloc(2);
  }
  Vector(T arr[], int n) throw() {
    data = new T[n];
    for (int i = 0; i < n; i++) {
      data[i] = arr[i];
    }
  }
  Vector(Vector const &obj) throw() {
    *this = obj;
  }
  Vector(int elems, T val) {
    Realloc(elems);
    currentSize = elems;
    for (size_t i = 0; i < currentSize; i++) {
      data[i] = val;
    }
  }
  Vector &operator=(Vector const &obj) throw() {
    clear();
    if (data && capacity) {
      ::operator delete(data, capacity * sizeof(T));
    }
    Realloc(obj.capacity);
    for (int i = 0; i < obj.currentSize; i++) {
      data[i] = obj.data[i];
    }
    currentSize = obj.currentSize;
  }
  virtual ~Vector() throw() {
    clear();
    ::operator delete(data, capacity * sizeof(T)); // to not call any destructors
  }

  iterator begin() throw() {
    return iterator(data);
  }

  iterator end() throw() {
    return iterator(data + currentSize);
  }

  rev_iterator rbegin() throw() {
    return rev_iterator(end());
  }

  rev_iterator rend() throw() {
    return rev_iterator(begin());
  }

  bool empty() const throw() {
    return this->_begin == this->_end;
  }

  void push_back(const T &val) throw() {
    if (currentSize >= capacity) {
      Realloc(capacity * 2);
    }

    data[currentSize] = val;
    currentSize++;
  }

  void pop_back() throw() {
    if (currentSize > 0) {
      currentSize--;
      data[currentSize].~T();
    }
  }

  void clear() throw() {
    for (size_t i = 0; i < currentSize; i++) {
      data[i].~T();
    }
    currentSize = 0;
  }

  template<class ITER>
  void assign(ITER begin, ITER end) throw() {
    clear();
    while (begin != end) {
      push_back(*begin);
      begin++;
    }
  }

  size_t size() const throw() { return currentSize; }

  const T &operator[](size_t idx) const throw() {
    return data[idx];
  }

  T &operator[](size_t idx) throw() {
    return data[idx];
  }

  bool operator==(Vector<T> const &rhs) throw() {
    if (size() != rhs.size())
      return false;
    for (int i = 0; i < currentSize; i++) {
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

 private:
  void Realloc(size_t newCapacity) throw() {
    T *newBlock = (T *) ::operator new(newCapacity * sizeof(T)); // we don't want to call a constructor at all

    size_t allocSize = currentSize;
    if (newCapacity < allocSize) {
      allocSize = newCapacity;
    }

    for (size_t i = 0; i < allocSize; i++) {
      newBlock[i] = data[i];
    }

    for (size_t i = 0; i < currentSize; i++) { // clear, but don't set size to zero
      data[i].~T();
    }

    ::operator delete(data, capacity * sizeof(T));
    data = newBlock;
    capacity = newCapacity;
  }

 private:
  T *data;
  T *_begin;
  T *_end;

  size_t currentSize;
  size_t capacity;

};
}
