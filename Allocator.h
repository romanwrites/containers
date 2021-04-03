#pragma once

namespace ft {

template<class T>
class Allocator;

//It must be lower than generic variation
template<>
class Allocator<void> {
 public:
  typedef void *pointer;
  typedef const void *const_pointer;
  typedef void value_type;
  template<class U>
  struct rebind { typedef Allocator<U> other; };
};

template<class T>
class Allocator {
 public:
  typedef T value_type;       //	Element type
  typedef T *pointer;          //	Pointer to element
  typedef T &reference;        //  Reference to element
  typedef const T *const_pointer;    //	Pointer to constant element
  typedef const T &const_reference;    //  Reference to constant element
  typedef size_t size_type;        //  Quantities of elements
  typedef ptrdiff_t difference_type;  //  Difference between two pointers

  // Its member type other is the equivalent allocator type to allocate elements of type Type
  // ::template when take template type from other template type
  template<class Type>
  struct rebind {
    typedef Allocator<Type> other;
  };

  // std::allocator just has empty coplien form
  Allocator() throw() {}

  Allocator(const Allocator &alloc) throw() { (void) alloc; }

  template<class U>
  Allocator(const Allocator<U> &alloc) throw() { (void) alloc; }

  ~Allocator() throw() {}

  pointer address(reference x) const {
    return &x;
  }

  const_pointer address(const_reference x) const {
    return &x;
  }

  // new throws bad_alloc
  // hint where to allocate memory
  pointer allocate(size_type n, Allocator<void>::const_pointer hint = nullptr) {
    (void) hint;

    if (n > max_size()) {
      throw std::bad_alloc();
    }

    return static_cast<pointer>( ::operator new(n));
  }

  void deallocate(pointer p, size_type n) {
    (void) n; // we can pass size to delete only in std c++14

    ::operator delete(p);
  }

  size_type max_size() const throw() {
    return std::numeric_limits<size_t>::max() / sizeof(value_type);
  }

  // The function constructs an object of member type value_type (an alias of allocator's template parameter)
  // using its copy constructor to initialize its value to a copy of val, as if the following code was used:
  void construct(pointer p, const_reference val) {
    ::new((void *) p) value_type(val);
  }

  void destroy(pointer p) {
    (*p).~value_type();
  }

};

}
