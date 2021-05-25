#include "Settings.h"

#if !TEST_STD98
#include "TestRunner.h"
#include "TestList.h"
#include "TestVector.h"
#include "TestMap.h"
#include "TestMultiMap.h"
#include "TestQueue.h"
#include "TestStack.h"
#include "TestSet.h"
#include "TestMultiSet.h"

#if PRINT_INT_TREE
void TestPrintSet() {
  ft::Set<int> randSet;
  ft::Set<int> ascSet;
  ft::MultiSet<int> randMultiSet;

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    ascSet.insert(i);
    randSet.insert(r);
    randMultiSet.insert(r);
  }

  std::cout << std::endl << "ASCENDING SET:" << std::endl;
  ascSet.printIntegerTree();

  std::cout << "RANDOM SET:" << std::endl;
  std::cout << "random Set size: " << randSet.size() << std::endl;
  randSet.printIntegerTree();

  std::cout << "RANDOM MULTISET:" << std::endl;
  std::cout << "random MultiSet size: " << randMultiSet.size() << std::endl;
  randMultiSet.printIntegerTree();
}
#endif

int main() {
  TestRunner::printOrange("MANDATORY PART");

  TestList::TestAll();
  TestVector::TestAll();
  TestQueue::TestAll();
  TestStack::TestAll();

  srand(time(NULL));
  TestMap::TestAll();

  TestRunner::printOrange("BONUSES");
  TestMultiMap::TestAll();
  TestSet::TestAll();
  TestMultiSet::TestAll();

#if PRINT_INT_TREE
  TestPrintSet();
#endif

  return 0;
}
#endif

#if TEST_STD98
#include "Stack.h"
#include "List.h"
#include "Vector.hpp"
#include "Map.h"
#include "Set.h"
#include "MultiSet.h"
#include "MultiMap.h"
#include "Queue.h"
using namespace std;

int main() {
  //  LIST
  ft::List<std::string> ftlst;
  ftlst.insert(ftlst.begin(), "+");
  ftlst.insert(ftlst.begin(), "C");
  ftlst.insert(ftlst.end(), "+");

  ft::List<std::string> ftlst2(ftlst.begin(), ftlst.end());

  //  VECTOR
  ft::Vector<std::string> v;
  v.insert(v.begin(), "+");
  v.insert(v.begin(), "C");
  v.insert(v.end(), "+");

  ft::Vector<std::string> v2(v.begin(), v.end());

  //  QUEUE
  ft::Queue<std::string> q;
  q.push("+");
  q.push("C");
  q.push("+");

  //  STACK
  ft::Stack<std::string> st;
  st.push("+");
  st.push("C");
  st.push("+");

  // MAP
  ft::Map<std::string, int> m;
  m["one"] = 1;
  m["two"] = 2;

  ft::Map<std::string, int> m2(m.begin(), m.end());

  // MULTIMAP
  ft::MultiMap<std::string, int> mm;
  mm.insert(std::make_pair("one", 1));
  mm.insert(std::make_pair("two", 2));

  ft::MultiMap<std::string, int> mm2(mm.begin(), mm.end());

  // SET
  ft::Set<std::string> s;
  s.insert("one");
  s.insert("two");

  ft::Set<std::string> s2(s.begin(), s.end());

  // MULTISET
  ft::MultiSet<std::string> ms;
  ms.insert("one");
  ms.insert("two");

  ft::Set<std::string> ms2(ms.begin(), ms.end());

  std::cout << "everything went great" << std::endl;

  return 0;
}
#endif
