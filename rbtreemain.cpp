#include "RedBlackTree.h"
#include <iostream>

int main() {
//  template<typename Key, typename Val, typename KeyOfValue,
//      typename Compare, typename Alloc = ft::Allocator<Val> >
  ft::RbTree<int, int, int, ft::less<int>> tree((ft::less<int>()), ft::Allocator<int>());


}