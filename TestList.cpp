#include "TestRunner.h"
#include "List.hpp"

namespace TestList {

void TestInsert() {
  std::list<std::string> lst;
  ft::List<std::string> ftlst;

  lst.insert(lst.begin(), "+");
  lst.insert(lst.begin(), "C");
  lst.insert(lst.end(), "+");

  ftlst.insert(ftlst.begin(), "+");
  ftlst.insert(ftlst.begin(), "C");
  ftlst.insert(ftlst.end(), "+");

  AssertEqual(ftlst, lst, HintList("Basic insert() 2 at begin, 1 at end"));

  std::vector<std::string> v{"one", "two", "three", "four", "five"};
  lst.insert(lst.begin(), v.begin(), v.end());
  ftlst.insert(ftlst.begin(), v.begin(), v.end());
  AssertEqual(ftlst, lst, HintList("Range fill insert() begin from vector<string>"));

  lst.insert(lst.end(), v.begin(), v.end());
  ftlst.insert(ftlst.end(), v.begin(), v.end());
  AssertEqual(ftlst, lst, HintList("Range fill insert() end from vector<string>"));

  auto itLst = std::find(lst.begin(), lst.end(), "C");
  auto itFtlst = std::find(ftlst.begin(), ftlst.end(), "C");

  lst.insert(itLst, v.begin(), v.end());
  ftlst.insert(itFtlst, v.begin(), v.end());
  AssertEqual(ftlst, lst, HintList("Range fill insert() mid from vector<string>"));

  itLst = std::find(lst.begin(), lst.end(), "+");
  itFtlst = std::find(ftlst.begin(), ftlst.end(), "+");

  lst.insert(itLst, 5, "+");
  ftlst.insert(itFtlst, 5, "+");
  AssertEqual(ftlst, lst, HintList("Range fill insert() end from vector<string>"));
}

void TestEmpty() {
  std::list<std::string> lst;
  ft::List<std::string> ftlst;

  Assert(ftlst.empty() == lst.empty(), HintList("Test empty() method"));
  AssertEqual(ftlst, lst, HintList("Test empty lists"));
}

void TestPushBack() {
  std::list<int> lst;
  ft::List<int> ftlst;

  for (int i = 0; i < 500; i++) {
    lst.push_back(i);
    ftlst.push_back(i);
  }

  AssertEqual(ftlst, lst, HintList("Test push_back() equality"));
}

void TestPushFront() {
  std::list<int> lst;
  ft::List<int> ftlst;

  for (int i = 0; i < 500; i++) {
    lst.push_front(i);
    ftlst.push_front(i);
  }

  AssertEqual(ftlst, lst, HintList("Test push_front() equality"));
}

void TestParamConstructorFill() {
  std::list<int> lst(21, 42);
  ft::List<int> ftlst(21, 42);

  AssertEqual(ftlst, lst, HintList("Test fill constructor lists equality"));
}

void TestParamConstructorRange() {
  std::vector<std::string> v{"one", "two", "three", "four", "five", "six", "seven"};
  std::list<std::string> lst(v.begin(), v.end());
  ft::List<std::string> ftlst(v.begin(), v.end());

  AssertEqual(ftlst, lst, HintList("Test range constructor lists equality"));
}

void TestBeginEnd() {
  std::list<int> lst;
  ft::List<int> ftlst;

  for (int i = 0; i < 50; i++) {
    lst.push_front(i);
    ftlst.push_front(i);
  }

  auto itLst = lst.begin();
  auto itFtlst = ftlst.begin();

  while (itLst != lst.end()) {
    AssertEqual(*itFtlst, *itLst, HintList("Test begin() to end() step: " + std::to_string(*itLst)));
    ++itLst;
    ++itFtlst;
  }
  Assert(itFtlst == ftlst.end(), HintList("Test if iterated over ft::List to the end successfully"));
}

void TestRbeginRend() {
  std::list<int> lst;
  ft::List<int> ftlst;

  for (int i = 0; i < 50; i++) {
    lst.push_front(i);
    ftlst.push_front(i);
  }

  auto itLst = lst.rbegin();
  auto itFtlst = ftlst.rbegin();

  while (itLst != lst.rend()) {
    AssertEqual(*itFtlst, *itLst, HintList("Test begin() to end() step: " + std::to_string(*itLst)));
    ++itLst;
    ++itFtlst;
  }
  Assert(itFtlst == ftlst.rend(), HintList("Test if iterated over ft::List to the end successfully"));
}

void TestFrontBack() {
  std::list<int> lst;
  ft::List<int> ftlst;

  lst.push_back(77);
  lst.push_back(22);

  ftlst.push_back(77);
  ftlst.push_back(22);

  AssertEqual(ftlst.front(), lst.front(), HintList("Test front()"));
  AssertEqual(ftlst.back(), lst.back(), HintList("Test back()"));

  lst.front() -= lst.back();
  ftlst.front() -= ftlst.back();

  AssertEqual(ftlst.front(), lst.front(), HintList("Test front() change"));

  lst.back() = 1;
  ftlst.back() = 1;

  AssertEqual(ftlst.back(), lst.back(), HintList("Test back() change"));

  const int lstFront = lst.front();
  const int ftlstFront = ftlst.front();

  AssertEqual(ftlstFront, lstFront, HintList("Test const front()"));
}

void TestMaxSize() {
  std::list<int> lst;
  ft::List<int> ftlst;

  AssertEqual(ftlst.max_size(), lst.max_size(), HintList("Test max_size()"));
}

void TestAssign() {
  std::list<int> lstFirst;
  std::list<int> lstSecond;
  ft::List<int> ftlstFirst;
  ft::List<int> ftlstSecond;

  lstFirst.assign(7, 100);
  ftlstFirst.assign(7, 100);
  AssertEqual(ftlstFirst, lstFirst, HintList("Test assign() fill"));

  lstSecond.assign(lstFirst.begin(), lstFirst.end());
  ftlstSecond.assign(ftlstFirst.begin(), ftlstFirst.end());
  AssertEqual(ftlstSecond, lstSecond, HintList("Test assign() range"));
  Assert(ftlstSecond.size() == lstSecond.size(), HintList("Test assign() size() lstSecond"));

  int myints[] = {1776, 7, 4};
  lstFirst.assign(myints, myints + 3);
  ftlstFirst.assign(myints, myints + 3);
  AssertEqual(ftlstSecond, lstSecond, HintList("Test assign() range from array"));
  Assert(ftlstFirst.size() == lstFirst.size(), HintList("Test assign() size() lstFirst"));
}

void TestErase() {
  std::list<int> lst;
  ft::List<int> ftlst;

  for (int i = 0; i < 10; i++) {
    lst.push_back(i);
    ftlst.push_back(i);
  }

  lst.erase(lst.begin());
  ftlst.erase(ftlst.begin());
  AssertEqual(ftlst, lst, HintList("Test erase() begin()"));

  auto it = lst.begin();
  auto itFt = ftlst.begin();
  it++;
  it++;
  itFt++;
  itFt++;

  it = lst.erase(it);
  itFt = ftlst.erase(itFt);
  AssertEqual(*itFt, *it, HintList("Test erase() position iterators value equality"));
  AssertEqual(ftlst, lst, HintList("Test erase() position lists equality"));

  it++;
  it++;
  itFt++;
  itFt++;

  it = lst.erase(lst.begin(), it);
  itFt = ftlst.erase(ftlst.begin(), itFt);
  AssertEqual(*itFt, *it, HintList("Test erase() ranged iterators value equality"));
  AssertEqual(ftlst, lst, HintList("Test erase() ranged lists equality"));

  it = lst.erase(--(lst.end()));
  itFt = ftlst.erase(--(ftlst.end()));
  Assert((itFt == ftlst.end()) && (it == lst.end()), HintList("Test erase() ranged iterators value equality"));
  AssertEqual(ftlst, lst, HintList("Test erase() position last elem"));
}

void TestSwap() {
  std::list<int> lst1(5, 42);
  std::list<int> lst2(10, 21);
  ft::List<int> ftlst1(5, 42);
  ft::List<int> ftlst2(10, 21);

  lst1.swap(lst2);
  ftlst1.swap(ftlst2);

  AssertEqual(ftlst1, lst1, HintList("Test swap() lst1"));
  AssertEqual(ftlst2, lst2, HintList("Test swap() lst2"));

  Assert(ftlst2.size() == lst2.size(), HintList("Test swap() size() lst2"));

  std::swap(lst1, lst2);
  ft::swap(ftlst1, ftlst2);

  AssertEqual(ftlst1, lst1, HintList("Test nonmember swap() lst1"));
  AssertEqual(ftlst2, lst2, HintList("Test nonmember swap() lst2"));
}

void TestResize() {
  std::list<int> lst;
  ft::List<int> ftlst;

  for (int i = 1; i < 10; ++i) {
    lst.push_back(i);
    ftlst.push_back(i);
  }

  lst.resize(5);
  ftlst.resize(5);
  AssertEqual(ftlst, lst, HintList("Test resize() lower bound"));

  lst.resize(8, 100);
  ftlst.resize(8, 100);
  AssertEqual(ftlst, lst, HintList("Test resize() higher bound"));
  lst.resize(12);
  ftlst.resize(12);
  AssertEqual(ftlst, lst, HintList("Test resize() higher bound with default value"));
}

void TestComparisonOperators() {
  std::list<std::string> l1{"a", "b"};
  std::list<std::string> l2{"a", "b"};
  ft::List<std::string> fl1;
  ft::List<std::string> fl2;
  fl1.push_back("a");
  fl2.push_back("a");
  fl1.push_back("b");
  fl2.push_back("b");

  Assert(fl1 == fl2 && l1 == l2, HintList("Test operator==()"));

  Assert(fl1 <= fl2 && l1 <= l2, HintList("Test operator<=() 1"));

  l1.push_back("a");
  fl1.push_back("a");
  Assert(fl1 != fl2 && l1 != l2, HintList("Test operator!=()"));
  Assert(fl1 > fl2 && l1 > l2, HintList("Test operator>()"));
  Assert(fl1 >= fl2 && l1 >= l2, HintList("Test operator>=() 2"));
  Assert(fl2 <= fl1 && l2 <= l1, HintList("Test operator<=() 2"));
}

void TestPop() {
  std::list<int> lst(10, 21);
  ft::List<int> ftlst(10, 21);

  lst.pop_back();
  ftlst.pop_back();
  lst.pop_back();
  ftlst.pop_back();
  AssertEqual(ftlst, lst, HintList("Test pop_back()"));

  lst.pop_front();
  ftlst.pop_front();
  lst.pop_front();
  ftlst.pop_front();
  lst.pop_front();
  ftlst.pop_front();
  lst.pop_front();
  ftlst.pop_front();
  AssertEqual(ftlst, lst, HintList("Test pop_front()"));
}

void TestSplice() {
  std::list<int> lst(10, 21);
  std::list<int> lst1(3, 42);
  ft::List<int> ftlst(10, 21);
  ft::List<int> ftlst1(3, 42);

  // RANGE
  lst1.splice(lst1.end(), lst, lst.begin(), lst.end());
  ftlst1.splice(ftlst1.end(), ftlst, ftlst.begin(), ftlst.end());

  AssertEqual(ftlst, lst, HintList("Test splice() ranged lst"));
  AssertEqual(ftlst1, lst1, HintList("Test splice() ranged lst1"));

  lst.splice(lst.end(), lst1, lst1.begin(), lst1.end());
  ftlst.splice(ftlst.end(), ftlst1, ftlst1.begin(), ftlst1.end());

  AssertEqual(ftlst, lst, HintList("Test splice() ranged lst reversed"));
  AssertEqual(ftlst1, lst1, HintList("Test splice() ranged lst1 reversed"));

  // SINGLE
  lst1.splice(lst1.begin(), lst, lst.begin());
  ftlst1.splice(ftlst1.begin(), ftlst, ftlst.begin());

  AssertEqual(ftlst, lst, HintList("Test splice() single lst"));
  AssertEqual(ftlst1, lst1, HintList("Test splice() single lst1"));

  // ENTIRE LIST
  lst1.splice(lst1.begin(), lst);
  ftlst1.splice(ftlst1.begin(), ftlst);

  AssertEqual(ftlst, lst, HintList("Test splice() entire list lst"));
  AssertEqual(ftlst1, lst1, HintList("Test splice() entire list lst1"));
}

void TestRemove() {
  std::list<int> lst;
  ft::List<int> ftlst;

  for (int i = 1; i < 10; ++i) {
    lst.push_back(i);
    ftlst.push_back(i);
  }

  lst.resize(18, 100);
  ftlst.resize(18, 100);
  lst.resize(20);
  ftlst.resize(20);

  lst.remove(9);
  ftlst.remove(9);
  AssertEqual(ftlst, lst, HintList("Test remove() single element"));

  lst.remove(100);
  ftlst.remove(100);
  AssertEqual(ftlst, lst, HintList("Test remove() elements by value 100"));

  ft::List<std::string> l;
  l.push_back("one");
  l.push_back("two");
  l.push_back("one");
  l.push_back("two");
  l.push_back("onw");
  l.push_back("three");
  l.push_back("one");

  l.remove("one");
  Assert(l.size() == 4, HintList("Test remove() elements by value \"one\" size() after"));
}

bool isNegative(int const &val) {
  return val < 0;
}

struct IsEven {
  bool operator()(const int &val) {
    return (val % 2) == 0;
  }
};

void TestRemoveIf() {
  std::vector<int> v{2, 4, 6, 1, -5, -6, -1, 3, 7, 0, 4, 2, 1, -3, 5, 8, 10, 11, -10, 22, 21};
  std::list<int> lst(v.begin(), v.end());
  ft::List<int> ftlst(v.begin(), v.end());

  lst.remove_if(isNegative);
  ftlst.remove_if(isNegative);

  lst.remove_if(IsEven());
  ftlst.remove_if(IsEven());

  AssertEqual(ftlst, lst, HintList("Test remove_if()"));
}

void TestSort() {
  std::vector<int> v{2, 4, 6, 1, -5, -6, -1, 3, 7, 0, 4, 2, 1, -3, 5, 8, 10, 11, -10, 22, 21};
  std::list<int> lst(v.begin(), v.end());
  ft::List<int> ftlst(v.begin(), v.end());

  lst.sort();
  ftlst.sort();
  AssertEqual(ftlst, lst, HintList("Test sort() less"));

  lst.sort(std::greater());
  ftlst.sort(std::greater());
  AssertEqual(ftlst, lst, HintList("Test sort() greater"));
}

void TestMerge() {
  std::list<std::string> l1{"one", "two", "three"};
  std::list<std::string> l2{"one", "two", "three"};

  ft::List<std::string> f1;
  ft::List<std::string> f2;

  f1.push_back("one");
  f2.push_back("one");
  f1.push_back("two");
  f2.push_back("two");
  f1.push_back("three");
  f2.push_back("three");

  l1.merge(l2);
  f1.merge(f2);
  AssertEqual(f1, l1, HintList("Test merge() l1"));
  AssertEqual(f2, l2, HintList("Test merge() l2"));
}

void TestReverse() {
  std::vector<int> v{2, 4, 6, 1, -5, -6, -1, 3, 7, 0, 4, 2, 1, -3, 5, 8, 10, 11, -10, 22, 21};
  std::list<int> lst(v.begin(), v.end());
  ft::List<int> ftlst(v.begin(), v.end());

  lst.reverse();
  ftlst.reverse();
  AssertEqual(ftlst, lst, HintList("Test reverse() 1"));

  lst.reverse();
  ftlst.reverse();
  AssertEqual(ftlst, lst, HintList("Test reverse() 2"));
}

void TestUnique() {
  std::vector<int> v{2, 4, 6, 1, -5, -6, -1, 3, 7, 0, 0, 0, 4, 2, 1, -3, 5, 8, 10, 10, 11, -10, -10, 22, 21};
  std::list<int> lst(v.begin(), v.end());
  ft::List<int> ftlst(v.begin(), v.end());

  lst.unique();
  ftlst.unique();
  AssertEqual(ftlst, lst, HintList("Test unique() equal_to"));

  lst.unique(std::less());
  ftlst.unique(std::less());
  AssertEqual(ftlst, lst, HintList("Test unique() less"));

  lst.unique(std::greater());
  ftlst.unique(std::greater());
  AssertEqual(ftlst, lst, HintList("Test unique() greater"));
}

void TestAll() {
  TestRunner tr;

  std::cerr << WITH_BG << "--------------------- Running List Tests ---------------------" << RESET << std::endl;
  tr.RunTest(TestBeginEnd, "TestBeginEnd");
  tr.RunTest(TestRbeginRend, "TestRbeginRend");
  tr.RunTest(TestInsert, "TestListInsert");
  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestPushBack, "TestPushBack");
  tr.RunTest(TestPushFront, "TestPushFront");
  tr.RunTest(TestMaxSize, "TestMaxSize");
  tr.RunTest(TestFrontBack, "TestFrontBack");
  tr.RunTest(TestAssign, "TestAssign");
  tr.RunTest(TestErase, "TestErase");
  tr.RunTest(TestParamConstructorFill, "TestParamConstructorFill");
  tr.RunTest(TestParamConstructorRange, "TestParamConstructorRange");
  tr.RunTest(TestSwap, "TestSwap");
  tr.RunTest(TestResize, "TestResize");
  tr.RunTest(TestComparisonOperators, "TestComparisonOperators");
  tr.RunTest(TestPop, "TestPop");
  tr.RunTest(TestSplice, "TestSplice");
  tr.RunTest(TestRemove, "TestRemove");
  tr.RunTest(TestRemoveIf, "TestRemoveIf");
  tr.RunTest(TestSort, "TestSort");
  tr.RunTest(TestMerge, "TestMerge");
  tr.RunTest(TestReverse, "TestReverse");
  tr.RunTest(TestUnique, "TestUnique");
}
}
