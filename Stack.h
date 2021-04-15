#pragma once
#include "List.h"

namespace ft {
template<class T, class Container = ft::List<T> >
class Stack {
 protected:
  Container list;

 public:
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef Container container_type;

  explicit Stack(container_type const &ctnr = container_type()) : list(ctnr) {
  }

  Stack(Stack const &o) : list(o.list) {
  }

  Stack &operator=(Stack const &o) {
    list = o.list;
    return *this;
  }

  bool empty() const {
    return list.empty();
  }

  size_type size() const {
    return list.size();
  }

  value_type& top() {
    return list.back();
  }

  const value_type& top() const {
    return list.back();
  }

  void push(const value_type &val) {
    list.push_back(val);
  }

  void pop() {
    list.pop_back();
  }

  template<class T_friend, class Container_friend>
  friend bool operator==(const Stack<T_friend, Container_friend> &lhs,
                         const Stack<T_friend, Container_friend> &rhs);

  template<class T_friend, class Container_friend>
  friend bool operator<(const Stack<T_friend, Container_friend> &lhs,
                        const Stack<T_friend, Container_friend> &rhs);
};


template<class T, class Container>
bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return lhs.list == rhs.list;
}

template<class T, class Container>
bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return !(lhs == rhs);
}

template<class T, class Container>
bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return lhs.list < rhs.list;
}

template<class T, class Container>
bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return !(lhs > rhs);
}

template<class T, class Container>
bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return rhs < lhs;
}

template<class T, class Container>
bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs) {
  return !(lhs < rhs);
}

}
