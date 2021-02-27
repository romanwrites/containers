#pragma once

#include <iostream>
#include <vector>
#include "Traits.h"

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
class V_reverse_iterator {
 public:
  typedef T *pointer;
  typedef T &reference;
  typedef const T *const_pointer;
  typedef const T &const_reference;
  typedef V_reverse_iterator reverse_iterator;

  V_reverse_iterator() throw() {
    ptr = nullptr;
  }

  V_reverse_iterator(pointer p) throw() {
    ptr = p;
  }

  V_reverse_iterator(V_reverse_iterator const &p) throw() {
    *this = p;
  }

  virtual ~V_reverse_iterator() throw() {}

  reverse_iterator &operator=(V_reverse_iterator const &p) throw() {
    ptr = p.ptr;
    return *this;
  }

  reverse_iterator &operator++() throw() {
    ptr--;
    return *this;
  }

  reverse_iterator operator++(int) throw() {
    V_reverse_iterator it = *this;
    --(*this);
    return it;
  }

  reverse_iterator &operator--() throw() {
    ptr++;
    return *this;
  }

  reverse_iterator operator--(int) throw() {
    reverse_iterator it = *this;
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

  bool operator==(reverse_iterator rhs) const throw() {
    return ptr == rhs.ptr;
  }

  bool operator!=(reverse_iterator rhs) const throw() {
    return ptr != rhs.ptr;
  }

  reverse_iterator operator+(int n) throw() {
    reverse_iterator ret(ptr - n);
    return ret;
  }

  reverse_iterator operator-(int n) throw() {
    reverse_iterator ret(ptr + n);
    return ret;
  }

  reverse_iterator operator+=(int n) throw() {
    ptr -= n;
    return *this;
  }

  reverse_iterator operator-=(int n) throw() {
    ptr += n;
    return *this;
  }

  bool operator<(reverse_iterator const &rhs) {
    return ptr < rhs.ptr;
  }

  bool operator>(reverse_iterator const &rhs) {
    return ptr > rhs.ptr;
  }

  bool operator<=(reverse_iterator const &rhs) {
    return ptr <= rhs.ptr;
  }

  bool operator>=(reverse_iterator const &rhs) {
    return ptr >= rhs.ptr;
  }

 private:
  T *ptr;
};

//	------------------------------------- VECTOR -----------------------------------------
template<class T> // pass any type and compiler auto generate Vector parametrized with this type
class Vector {
 public:
  typedef T value_type;
  typedef value_type& reference;
  typedef value_type* pointer;
  typedef value_type const& const_reference;
  typedef value_type const* const_pointer;
  typedef V_iterator<T> iterator;
  typedef V_iterator<T> const const_iterator;
  typedef V_reverse_iterator<T> reverse_iterator;
  typedef V_reverse_iterator<T> const const_reverse_iterator;
  typedef size_t size_type;
  typedef std::allocator<value_type> allocator_type;
  typedef ptrdiff_t difference_type;

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
      ::operator delete(data); // , capacity * sizeof(T)
    }
    Realloc(obj.capacity);
    for (int i = 0; i < obj.currentSize; i++) {
      data[i] = obj.data[i];
    }
    currentSize = obj.currentSize;
  }

  virtual ~Vector() throw() {
    clear();
	::operator delete(data, capacity * sizeof(T)); // to not call any destructors // , capacity * sizeof(T)
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

  bool empty() const throw() {
    return this->_begin == this->_end;
  }

  void push_back(const T &val) throw() {
    if (currentSize >= capacity) {
      Realloc(capacity + capacity);
    }

    data[currentSize] = val; //
    currentSize++;
  }

  void pop_back() throw() {
    if (currentSize > 0) {
      currentSize--;
      data[currentSize].~T();
    }
  }

  iterator insert (iterator position, const value_type& val){
	if (currentSize > 0 && position == end()) {
	  push_back(val);
	  return iterator(data + currentSize - 1);
	}

	iterator it = begin();
	size_type pos = 0;
	while (it != position) {
	  ++pos;
	  ++it;
	}
	if (currentSize >= capacity) {
	  Realloc(capacity + capacity);
	} // position changed
	position = (data + pos); // update position

	it = begin();
	while (it != position) {
	  ++it;
	}
	bool first = true;
	value_type tmp1 = val;
	value_type tmp2;

	for (size_t i = pos; it != end(); ++i) {
	  if (first) {
	    tmp2 = *it;
	    *it = tmp1;
	    first = false;
	  } else {
		tmp1 = *it;
		*it = tmp2;
		first = true;
	  }
	  ++it;
	}
	if (first) {
	  *it = tmp1;
	} else {
	  *it = tmp2;
	}
	currentSize++;
	return position;
  }

//  void insert (iterator position, size_type n, const value_type& val){
//
//  }
//
//  template <class InputIterator>
//  void insert (iterator position, InputIterator first, InputIterator last){
//
//  }


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

    if (data != nullptr) {
	  ::operator delete(data, capacity * sizeof(T));
    }
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
