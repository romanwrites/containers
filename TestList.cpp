#include "TestRunner.h"
#include "List.hpp"

namespace TestList {
void TestInsert() {
  std::list<std::string> lst;
  ft::List<std::string> ftlst;

  lst.insert(lst.begin(), "+");
  lst.insert(lst.begin(), "С");
  lst.insert(lst.end(), "+");

  ftlst.insert(ftlst.begin(), "+");
  ftlst.insert(ftlst.begin(), "С");
  ftlst.insert(ftlst.end(), "+");

  AssertEqual(ftlst, lst, HintList("Basic insert() 2 at begin, 1 at end"));
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

  Assert(ftlst.size() == lst.size(), HintList("Test push_back() size()"));
  AssertEqual(ftlst, lst, HintList("Test push_back() equality"));
}

void TestPushFront() {
  std::list<int> lst;
  ft::List<int> ftlst;

  for (int i = 0; i < 500; i++) {
    lst.push_front(i);
    ftlst.push_front(i);
  }

  Assert(ftlst.size() == lst.size(), HintList("Test push_front() size()"));
  AssertEqual(ftlst, lst, HintList("Test push_front() equality"));
}

void TestParamConstructor() {
  //    std::list<int> lst(21,42);
  //    for (auto it = lst.begin(); it != lst.end(); ++it) {
  //        std::cout << *it << " ";
  //    }
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

void TestRbeginRend() { //todo
//        std::list<int> lst;
//        ft::List<int> ftlst;
//
//        for (int i = 0; i < 50; i++) {
//            lst.push_front(i);
//            ftlst.push_front(i);
//        }
//
//        auto itLst = lst.rbegin();
//        auto itFtlst = ftlst.rbegin();
//
//        while (itLst != lst.rend()) {
//            AssertEqual(*itFtlst, *itLst, HintList("Test begin() to end() step: " + std::to_string(*itLst)));
//            ++itLst;
//            ++itFtlst;
//        }
//        Assert(itFtlst == ftlst.rend(), HintList("Test if iterated over ft::List to the end successfully"));
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

//void TestAssign() {
//  std::list<int>  lstFirst;
//  std::list<int>  lstSecond;
//  ft::List<int>   ftlstFirst;
//  ft::List<int>   ftlstSecond;
//
//  lstFirst.assign (7,100);
//  ftlstFirst.assign (7,100);
//  AssertEqual(ftlstFirst, lstFirst, HintList("Test assign() fill"));
//
//  lstSecond.assign (lstFirst.begin(),lstFirst.end());
//  ftlstSecond.assign (ftlstFirst.begin(),ftlstFirst.end());
//  AssertEqual(ftlstSecond, lstSecond, HintList("Test assign() range"));
//
//  int myints[]={1776,7,4};
//  lstFirst.assign (myints,myints+3);
//  ftlstSecond.assign (myints,myints+3);
//  AssertEqual(ftlstSecond, lstSecond, HintList("Test assign() range from array"));
//
//  std::cout << "Size of lstFirst: " << int (lstFirst.size()) << '\n';
//  std::cout << "Size of second: " << int (lstSecond.size()) << '\n';
//}

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


void TestAll() {
  TestRunner tr;
  tr.RunTest(TestBeginEnd, "TestBeginEnd");
//  tr.RunTest(TestRbeginRend, "TestRbeginRend");
  tr.RunTest(TestInsert, "TestListInsert");
  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestPushBack, "TestPushBack");
  tr.RunTest(TestPushFront, "TestPushFront");
  tr.RunTest(TestMaxSize, "TestMaxSize");
  tr.RunTest(TestFrontBack, "TestFrontBack");
//  tr.RunTest(TestAssign, "TestAssign");
  tr.RunTest(TestErase, "TestErase");

}
}
