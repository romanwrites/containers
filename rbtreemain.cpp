#include "RedBlackTree.h"
#include <iostream>

int main() {
//  template<typename Key, typename Val, typename KeyOfValue,
//      typename Compare, typename Alloc = ft::Allocator<Val> >
  ft::RbTree<int, std::pair<const int, int>, int, ft::less<int> > tree((ft::less<int>()), ft::Allocator<int>());

  tree.insert(std::make_pair(5, 5));
  tree.insert(std::make_pair(3, 3));
  tree.insert(std::make_pair(7, 7));
  tree.insert(std::make_pair(1, 1));
  tree.insert(std::make_pair(2,2));
  tree.insert(std::make_pair(6,6));
  tree.insert(std::make_pair(10,10));

  tree.insert(std::make_pair(3, 3));
  tree.insert(std::make_pair(7, 7));
  tree.insert(std::make_pair(1, 1));
  tree.insert(std::make_pair(2,2));
  tree.insert(std::make_pair(6,6));
  tree.insert(std::make_pair(10,10));
  tree.printIntTree();

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    std::cout << it->first << " ";
  }
  std::cout << std::endl;

//  std::cout << tree.find(std::make_pair(6,6))->value.first << std::endl;

}
