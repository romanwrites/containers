#pragma once
#include "List.h"

namespace ft {

template<class T, class Container = ft::List<T> >
class Queue {
 protected:
  Container list;

 public:
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef Container container_type;

  explicit Queue(container_type const &ctnr = container_type()) : list(ctnr) {
  }

  Queue(Queue const &o) : list(o.list) {
  }

  Queue &operator=(Queue const &o) {
    list = o.list;
    return *this;
  }

  bool empty() const {
    return list.empty();
  }

  size_type size() const {
    return list.size();
  }

  void push(const value_type &val) {
    list.push_back(val);
  }

  value_type &front() {
    return list.front();
  }

  const value_type &front() const {
    return list.front();
  }

  value_type &back() {
    return list.back();
  }

  const value_type &back() const {
    return list.back();
  }

  void pop() {
    list.pop_front();
  }

  template<class T_friend, class Container_friend>
  friend bool operator==(const Queue<T_friend, Container_friend> &lhs,
      const Queue<T_friend, Container_friend> &rhs);

  template<class T_friend, class Container_friend>
  friend bool operator<(const Queue<T_friend, Container_friend> &lhs,
      const Queue<T_friend, Container_friend> &rhs);

};

template<class T, class Container>
bool operator==(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return lhs.list == rhs.list;
}

template<class T, class Container>
bool operator!=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return !(lhs == rhs);
}

template<class T, class Container>
bool operator<(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return lhs.list < rhs.list;
}

template<class T, class Container>
bool operator<=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return !(lhs > rhs);
}

template<class T, class Container>
bool operator>(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return rhs < lhs;
}

template<class T, class Container>
bool operator>=(const Queue<T, Container> &lhs, const Queue<T, Container> &rhs) {
  return !(lhs < rhs);
}

}
