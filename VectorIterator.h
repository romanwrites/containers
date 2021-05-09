#pragma once

namespace ft {
//	------------------------------------- VECTOR ITERATOR -----------------------------------------
template<class T>
class VectorIterator {
 public:
  typedef T *pointer;
  typedef T &reference;
  typedef VectorIterator iterator;

  VectorIterator() throw() {
    ptr = NULL;
  }

  VectorIterator(pointer p) throw() {
    ptr = p;
  }

  VectorIterator(VectorIterator const &p) throw() {
    *this = p;
  }

  virtual ~VectorIterator() throw() {}

  iterator &operator=(iterator const &p) throw() {
    ptr = p.ptr;
    return *this;
  }

  iterator &operator++() throw() {
    ptr++;
    return *this;
  }

  iterator operator++(int) throw() {
    iterator it = *this;
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
  pointer ptr;

 public:
  pointer p() const {
    return ptr;
  }
};

//	------------------------------------- VECTOR CONST ITERATOR -----------------------------------------
template<class T>
class VectorConstIterator {
 public:
  typedef const T* pointer;
  typedef const T& reference;
  typedef const VectorConstIterator iterator;

  VectorConstIterator() throw() : ptr(NULL) {
  }

  explicit VectorConstIterator(pointer p) throw() : ptr(p) {
  }

  VectorConstIterator(VectorIterator<T> const &p) throw() : ptr(p.p()) {
  }

  VectorConstIterator(VectorConstIterator const &p) throw() : ptr(p.ptr) {
  }

  virtual ~VectorConstIterator() throw() {}

  iterator &operator=(iterator const &p) throw() {
    ptr = p.ptr;
    return *this;
  }

  iterator &operator++() throw() {
    ptr++;
    return *this;
  }

  iterator operator++(int) throw() {
    iterator it = *this;
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
  pointer ptr;
};

}
