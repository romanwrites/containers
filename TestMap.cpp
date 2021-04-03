#include "TestRunner.h"
#include <array>
#include "TreePrinter.h"

namespace TestMap {

//void PrintTree() {
//  ft::TreePrinter tree_printer;
//
//  std::array<int, 13> arr = {931, 39, 1960, 385, 388, 2070, 185, 9, 957, 54, 904, 49800, 394};
//  for (int i = 0; i < (int)arr.size(); ++i) {
//    tree_printer.add(arr[i]);
//  }
//  tree_printer.printTree();
//}

void TestEmpty() {
//  std::map<std::string, int> m;
//  ft::Map<std::string, int> fm;
//  Assert(fm.empty() == m.empty(), HintMap("test empty"));
}

void TestAll() {
  TestRunner tr;

  std::cerr << std::endl
            << WITH_BG << "                      Running Map Tests                      "
            << RESET << std::endl;

  tr.RunTest(TestEmpty, "TestEmpty");

  ft::Map<int, int> map;

  map[6] = 9;
  map[7] = 9;
  map[4] = 9;
  map[5] = 9;
  map[8] = 9;
  map.printIntTree();


//  PrintTree();
}
}
