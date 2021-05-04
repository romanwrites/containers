#include "RedBlackTree.h"
#include <iostream>
#include <map>

void TestConstIterator(ft::RbTree<int, std::pair<const int, int>, int, ft::less<int> > const &tree) {
  const ft::RbTree<int, std::pair<const int, int>, int, ft::less<int> >::const_iterator cit = tree.begin();

  std::cout << "Const iter test: " << cit->first << " " << cit->second << std::endl;

}

void TestReverseIterator(ft::RbTree<int, std::pair<const int, int>, int, ft::less<int> > const &tree) {
  std::cout << "test reverse iterator" << std::endl;
  for (auto rit = tree.rbegin();
       rit != tree.rend(); rit++) {
    std::cout << rit->first << " " << rit->second << " ";
  }
  std::cout << std::endl;
}

int main() {
  ft::RbTree<int, std::pair<const int, int>, int, ft::less<int> > tree((ft::less<int>()), ft::Allocator<int>(), true);

//  tree.insert(std::make_pair(5, 5));
//  tree.insert(std::make_pair(3, 3));
//  tree.insert(std::make_pair(7, 7));
//  tree.insert(std::make_pair(2, 2));
//  tree.insert(std::make_pair(1, 1));
//  tree.insert(std::make_pair(6, 6));
//  tree.insert(std::make_pair(10, 10));
  srand (time(NULL));

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    tree.insert(std::make_pair(r, r));
  }

  tree.printIntTree();

//  TestConstIterator(tree);
//  TestReverseIterator(tree);
//
//  for (auto it = tree.begin(); it != tree.end(); ++it) {
//    std::cout << it->first << " ";
//  }
//  std::cout << std::endl;
//
//  auto it = tree.end();
//  --it;
//  for (; it != tree.begin(); --it) {
//    std::cout << it->first << " ";
//  }
//  std::cout << std::endl;
//
//  std::cout << "find: " << tree.find(std::make_pair(6, 6))->value.first << std::endl;
//
//  std::cout << "count: " << tree.count(6) << std::endl;
}
