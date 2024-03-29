#include "TestRunner.h"

namespace TestMultiMap {

void TestEmpty(TestRunner const &tr) {
  std::multimap<std::string, int> m;
  ft::MultiMap<std::string, int> fm;
  Assert(fm.empty() == m.empty(), tr.hintMessage("empty"));
}

void TestMaxSize(TestRunner const &tr) {
  std::multimap<std::string, int> m;
  ft::MultiMap<std::string, int> fm;

//  std::cout << "m.max_size(): " << m.max_size() << " fm.max_size(): " << fm.max_size() << std::endl;
//  if (m.max_size() > fm.max_size()) {
//    std::cout << "m.max_size() - fm.max_size() res: " << m.max_size() - fm.max_size() << std::endl;
//  } else {
//    std::cout << "fm.max_size() - m.max_size() res: " << fm.max_size() - m.max_size() << std::endl;
//  }
  Assert((fm.max_size() > 200000000000000000 && m.max_size() > 200000000000000000) ||
      (fm.max_size() <= 200000000000000000 && m.max_size() <= 200000000000000000), tr.hintMessage("max_size"));
}

void TestSize(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;
  Assert(fm.size() == m.size(), tr.hintMessage("test empty size"));

  for (int i = 0; i < 50; ++i) {
    m.insert(std::make_pair(i, i));
    m.insert(std::make_pair(50, 50));
    fm.insert(std::make_pair(i, i));
    fm.insert(std::make_pair(50, 50));
  }

  Assert(fm.size() == m.size(), tr.hintMessage("test size"));
}

void TestConstructorsConst(std::multimap<int, int> const &m, ft::MultiMap<int, int> const &fm, TestRunner const &tr) {
  std::multimap<int, int> m2(m.begin(), m.end());
  ft::MultiMap<int, int> fm2(fm.begin(), fm.end());
  AssertEqual(fm2, m2, tr.hintMessage("range constructor const"));

  std::multimap<int, int> m3(m2.begin(), m2.end());
  ft::MultiMap<int, int> fm3(fm2.begin(), fm2.end());
  AssertEqual(fm3, m3, tr.hintMessage("copy constructor const"));
}

void TestConstructors(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;
  AssertEqual(fm, m, tr.hintMessage("empty constructor"));

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  std::multimap<int, int> m2(m.begin(), m.end());
  ft::MultiMap<int, int> fm2(fm.begin(), fm.end());
  AssertEqual(fm2, m2, tr.hintMessage("range constructor"));

  std::multimap<int, int> m3(m2.begin(), m2.end());
  ft::MultiMap<int, int> fm3(fm2.begin(), fm2.end());
  AssertEqual(fm3, m3, tr.hintMessage("copy constructor"));

  TestConstructorsConst(m, fm, tr);
}

void TestTestAssignationOperatorConst(std::multimap<int, int> const &m, ft::MultiMap<int, int> const &fm, TestRunner const &tr) {
  std::multimap<int, int> m2 = m;
  ft::MultiMap<int, int> fm2 = fm;
  AssertEqual(fm2, m2, tr.hintMessage("operator= const"));

  m2 = std::multimap<int, int>();
  fm2 = ft::MultiMap<int, int>();
  AssertEqual(fm2, m2, tr.hintMessage("operator= empty constructor on non const"));

  m2 = m;
  fm2 = fm;
  AssertEqual(fm2, m2, tr.hintMessage("operator= assign again from const"));
}

void TestAssignationOperator(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  
  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  std::multimap<int, int> m2 = m;
  ft::MultiMap<int, int> fm2 = fm;
  AssertEqual(fm2, m2, tr.hintMessage("operator="));

  m = std::multimap<int, int>();
  fm = ft::MultiMap<int, int>();
  AssertEqual(fm, m, tr.hintMessage("operator= empty constructor"));

  m = m2;
  fm = fm2;
  AssertEqual(fm, m, tr.hintMessage("operator= assign again"));

  TestTestAssignationOperatorConst(m, fm, tr);
}

void TestConstIterator(std::multimap<int, int> const &m, ft::MultiMap<int, int> const &fm, TestRunner const &tr) {
  auto it = m.begin();
  auto fit = fm.begin();

  for (; it != m.end() && fit != fm.end(); ++it, ++fit) {
    Assert(it->first == fit->first && it->second == fit->second,
           tr.hintMessage("iterator"));
  }
}

void TestIterator(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  
  for (int i = 0; i < 200; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  auto it = m.begin();
  auto fit = fm.begin();

  for (; it != m.end() && fit != fm.end(); ++it, ++fit) {
    Assert(it->first == fit->first && it->second == fit->second,
           tr.hintMessage("iterator"));
  }

  TestConstIterator(m, fm, tr);
}

void TestConstReverseIterator(std::multimap<int, int> const &m, ft::MultiMap<int, int> const &fm, TestRunner const &tr) {
  auto it = m.rbegin();
  auto fit = fm.rbegin();

  for (; it != m.rend() && fit != fm.rend(); ++it, ++fit) {
    Assert(it->first == fit->first && it->second == fit->second,
           tr.hintMessage("iterator"));
  }
}

void TestReverseIterator(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  
  for (int i = 0; i < 200; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  auto it = m.rbegin();
  auto fit = fm.rbegin();

  for (; it != m.rend() && fit != fm.rend(); ++it, ++fit) {
    Assert(it->first == fit->first && it->second == fit->second,
           tr.hintMessage("iterator"));
  }

  TestConstReverseIterator(m, fm, tr);
}

void TestInsert(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }
  AssertEqual(m, fm, tr.hintMessage("insert single element"));

  auto it = m.begin();
  auto fit = fm.begin();

  for (int i = 0;
       i < 10 && it != m.end() && fit != fm.end();
       ++i, ++it, ++fit) {
  }

  int r = rand() % 100 + 1;
  m.insert(it, std::make_pair(r, r));
  fm.insert(fit, std::make_pair(r, r));
  AssertEqual(m, fm, tr.hintMessage("insert with hint"));

  std::multimap<int, int> m2;
  ft::MultiMap<int, int> fm2;
  m2.insert(it, m.end());
  fm2.insert(fit, fm.end());
  AssertEqual(m2, fm2, tr.hintMessage("insert range"));
}

void TestErase(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  Assert(m.erase(m.begin()->first) == fm.erase(fm.begin()->first), tr.hintMessage("erase by key"));
  AssertEqual(m, fm, tr.hintMessage("erase by key compare maps"));

  auto it = m.begin();
  auto fit = fm.begin();
  m.erase(it++);
  fm.erase(fit++);
  AssertEqual(m, fm, tr.hintMessage("erase by position"));

  for (int i = 0; i < 4; ++i, ++it, ++fit) {}

  m.erase(m.begin(), it);
  fm.erase(fm.begin(), fit);

  for (int i = 0; i < 5; ++i, ++it, ++fit) {}

  m.erase(it, m.end());
  fm.erase(fit, fm.end());

  AssertEqual(m, fm, tr.hintMessage("erase by range"));
}

void TestSwap(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  std::multimap<int, int> m2;
  ft::MultiMap<int, int> fm2;

  for (int i = 0; i < 10; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  m.swap(m2);
  fm.swap(fm2);

  AssertEqual(m, fm, tr.hintMessage("swap"));
  AssertEqual(m2, fm2, tr.hintMessage("swap m2"));
}

void TestClear(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  for (int i = 0; i < 200; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  m.clear();
  fm.clear();

  for (int i = 0; i < 50; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  AssertEqual(m, fm, tr.hintMessage("clear"));
}

void TestFindConst(std::multimap<int, int> const &m, ft::MultiMap<int, int> const &fm, TestRunner const &tr) {
  Assert(m.find(0)->first == fm.find(0)->first, tr.hintMessage("find 0 const"));
  Assert(m.find(42)->first == fm.find(42)->first, tr.hintMessage("find 42 const"));
  Assert(m.find(142)->first == fm.find(142)->first, tr.hintMessage("find 142 const"));
  Assert(m.find(199)->first == fm.find(199)->first, tr.hintMessage("find 199 const"));
}

void TestFind(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  for (int i = 0; i < 200; ++i) {
    m.insert(std::make_pair(i, i));
    m.insert(std::make_pair(42, 42));
    fm.insert(std::make_pair(i, i));
    fm.insert(std::make_pair(42, 42));
  }

  Assert(m.find(0)->first == fm.find(0)->first, tr.hintMessage("find 0"));
  Assert(m.find(42)->first == fm.find(42)->first, tr.hintMessage("find 42"));
  Assert(m.find(142)->first == fm.find(142)->first, tr.hintMessage("find 142"));
  Assert(m.find(199)->first == fm.find(199)->first, tr.hintMessage("find 199"));

  TestFindConst(m, fm, tr);
}

void TestCount(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  for (int i = 0; i < 200; ++i) {
    m.insert(std::make_pair(i, i));
    m.insert(std::make_pair(42, 42));
    fm.insert(std::make_pair(i, i));
    fm.insert(std::make_pair(42, 42));
  }

  Assert(m.count(0) == fm.count(0), tr.hintMessage("count 0"));
  Assert(m.count(42) == fm.count(42), tr.hintMessage("count 42"));
  Assert(m.count(199) == fm.count(199), tr.hintMessage("count 199"));
  Assert(m.count(-1) == fm.count(-1), tr.hintMessage("count -1"));
}

void TestLowerBoundConst(std::multimap<int, int> const &m, ft::MultiMap<int, int> const &fm, TestRunner const &tr) {
  Assert(m.lower_bound(0)->first == fm.lower_bound(0)->first, tr.hintMessage("lower_bound 0 const"));
  Assert(m.lower_bound(42)->first == fm.lower_bound(42)->first, tr.hintMessage("lower_bound 42 const"));
  Assert(m.lower_bound(199)->first == fm.lower_bound(199)->first, tr.hintMessage("lower_bound 199 const"));
  Assert(m.lower_bound(-1)->first == fm.lower_bound(-1)->first, tr.hintMessage("lower_bound -1 const"));
  Assert((m.lower_bound(2000) == m.end()) && (fm.lower_bound(2000) == fm.end()), tr.hintMessage("lower_bound 2000 const"));

}

void TestLowerBound(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  for (int i = 0; i < 200; ++i) {
    m.insert(std::make_pair(i, i));
    m.insert(std::make_pair(42, 42));
    fm.insert(std::make_pair(i, i));
    fm.insert(std::make_pair(42, 42));
  }

  Assert(m.lower_bound(0)->first == fm.lower_bound(0)->first, tr.hintMessage("lower_bound 0"));
  Assert(m.lower_bound(42)->first == fm.lower_bound(42)->first, tr.hintMessage("lower_bound 42"));
  Assert(m.lower_bound(199)->first == fm.lower_bound(199)->first, tr.hintMessage("lower_bound 199"));
  Assert(m.lower_bound(-1)->first == fm.lower_bound(-1)->first, tr.hintMessage("lower_bound -1"));
  Assert((m.lower_bound(2000) == m.end()) && (fm.lower_bound(2000) == fm.end()), tr.hintMessage("lower_bound 2000"));

  TestLowerBoundConst(m, fm, tr);
}

void TestUpperBoundConst(std::multimap<int, int> const &m, ft::MultiMap<int, int> const &fm, TestRunner const &tr) {
  Assert(m.upper_bound(0)->first == fm.upper_bound(0)->first, tr.hintMessage("upper_bound 0 const"));
  Assert(m.upper_bound(42)->first == fm.upper_bound(42)->first, tr.hintMessage("upper_bound 42 const"));
  Assert(m.upper_bound(198)->first == fm.upper_bound(198)->first, tr.hintMessage("upper_bound 198 const"));
  Assert((m.upper_bound(199) == m.end()) && (fm.upper_bound(199) == fm.end()), tr.hintMessage("upper_bound 199 const"));
  Assert(m.upper_bound(-1)->first == fm.upper_bound(-1)->first, tr.hintMessage("upper_bound -1 const"));
}

void TestUpperBound(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  for (int i = 0; i < 200; ++i) {
    m.insert(std::make_pair(i, i));
    m.insert(std::make_pair(42, 42));
    fm.insert(std::make_pair(i, i));
    fm.insert(std::make_pair(42, 42));
  }

  Assert(m.upper_bound(0)->first == fm.upper_bound(0)->first, tr.hintMessage("upper_bound 0"));
  Assert(m.upper_bound(42)->first == fm.upper_bound(42)->first, tr.hintMessage("upper_bound 42"));
  Assert(m.upper_bound(198)->first == fm.upper_bound(198)->first, tr.hintMessage("upper_bound 198"));
  Assert((m.upper_bound(199) == m.end()) && (fm.upper_bound(199) == fm.end()), tr.hintMessage("upper_bound 199"));
  Assert(m.upper_bound(-1)->first == fm.upper_bound(-1)->first, tr.hintMessage("upper_bound -1"));

  TestUpperBoundConst(m, fm, tr);
}

void TestEqualRangeConst(std::multimap<int, int> const &m, ft::MultiMap<int, int> const &fm, TestRunner const &tr) {
  auto mIters = m.equal_range(99);
  auto fmIters = fm.equal_range(99);

  for (; mIters.first != mIters.second; ++mIters.first, ++fmIters.first) {
    Assert(mIters.first->first == fmIters.first->first, tr.hintMessage("equal_range 99"));
  }
  Assert(fmIters.first == fmIters.second, tr.hintMessage("equal_range 99 check iterators range"));

  mIters = m.equal_range(199);
  fmIters = fm.equal_range(199);

  for (; mIters.first != mIters.second; ++mIters.first, ++fmIters.first) {
    Assert(mIters.first->first == fmIters.first->first, tr.hintMessage("equal_range 199"));
  }
  Assert(fmIters.first == fmIters.second, tr.hintMessage("equal_range 199 check iterators range"));
}

void TestEqualRange(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  for (int i = 0; i < 200; ++i) {
    m.insert(std::make_pair(i, i));
    m.insert(std::make_pair(99, 99));
    fm.insert(std::make_pair(i, i));
    fm.insert(std::make_pair(99, 99));
  }

  auto mIters = m.equal_range(99);
  auto fmIters = fm.equal_range(99);

  for (; mIters.first != mIters.second; ++mIters.first, ++fmIters.first) {
    Assert(mIters.first->first == fmIters.first->first, tr.hintMessage("equal_range 99"));
  }
  Assert(fmIters.first == fmIters.second, tr.hintMessage("equal_range 99 check iterators range"));

  mIters = m.equal_range(199);
  fmIters = fm.equal_range(199);

  for (; mIters.first != mIters.second; ++mIters.first, ++fmIters.first) {
    Assert(mIters.first->first == fmIters.first->first, tr.hintMessage("equal_range 199"));
  }
  Assert(fmIters.first == fmIters.second, tr.hintMessage("equal_range 199 check iterators range"));

  TestEqualRangeConst(m, fm, tr);
}

void TestRelationalNonMemberOperatorsConst(std::multimap<int, int> const &m1,
                                           std::multimap<int, int> const &m2,
                                           ft::MultiMap<int, int> const &fm1,
                                           ft::MultiMap<int, int> const &fm2,
                                           TestRunner const &tr) {
  AssertEqual(m1 == m2, fm1 == fm2, tr.hintMessage("operator== const"));
  AssertEqual(m1 != m2, fm1 != fm2, tr.hintMessage("operator!= const"));
  AssertEqual(m1 < m2, fm1 < fm2, tr.hintMessage("operator< const"));
  AssertEqual(m1 <= m2, fm1 <= fm2, tr.hintMessage("operator<= const"));
  AssertEqual(m1 >= m2, fm1 >= fm2, tr.hintMessage("operator>= const"));
  AssertEqual(m1 > m2, fm1 > fm2, tr.hintMessage("operator> const"));
}

void TestRelationalNonMemberOperatorsNonConst(std::multimap<int, int> &m1,
                                              std::multimap<int, int> &m2,
                                              ft::MultiMap<int, int> &fm1,
                                              ft::MultiMap<int, int> &fm2,
                                              TestRunner const &tr) {
  AssertEqual(m1 == m2, fm1 == fm2, tr.hintMessage("operator=="));
  AssertEqual(m1 != m2, fm1 != fm2, tr.hintMessage("operator!="));
  AssertEqual(m1 < m2, fm1 < fm2, tr.hintMessage("operator<"));
  AssertEqual(m1 <= m2, fm1 <= fm2, tr.hintMessage("operator<="));
  AssertEqual(m1 >= m2, fm1 >= fm2, tr.hintMessage("operator>="));
  AssertEqual(m1 > m2, fm1 > fm2, tr.hintMessage("operator>"));
}

void TestRelationalNonMemberOperators(TestRunner const &tr) {
  std::multimap<int, int> m1;
  ft::MultiMap<int, int> fm1;
  std::multimap<int, int> m2;
  ft::MultiMap<int, int> fm2;

  for (int i = 0; i < 100; ++i) {
    if (i % 2 == 0) {
      m1.insert(std::make_pair(i, i));
      fm1.insert(std::make_pair(i, i));
    } else if (i % 3 == 0 || i % 5 == 0) {
      m2.insert(std::make_pair(i, i));
      fm2.insert(std::make_pair(i, i));
    } else {
      m1.insert(std::make_pair(i, i));
      fm1.insert(std::make_pair(i, i));
      m2.insert(std::make_pair(i, i));
      fm2.insert(std::make_pair(i, i));
    }
    TestRelationalNonMemberOperatorsNonConst(m1, m2, fm1, fm2, tr);
    TestRelationalNonMemberOperatorsConst(m1, m2, fm1, fm2, tr);
  }

  for (int i = 0; i < 100; ++i) {
    if (i % 2 == 0) {
      m1.erase(i);
      fm1.erase(i);
    } else if (i % 3 == 0 || i % 5 == 0) {
      m2.erase(i);
      fm2.erase(i);
    } else {
      m1.erase(i);
      fm1.erase(i);
      m2.erase(i);
      fm2.erase(i);
    }
    TestRelationalNonMemberOperatorsNonConst(m1, m2, fm1, fm2, tr);
    TestRelationalNonMemberOperatorsConst(m1, m2, fm1, fm2, tr);
  }
}

void TestSwapNonMember(TestRunner const &tr) {
  std::multimap<int, int> m;
  ft::MultiMap<int, int> fm;

  for (int i = 0; i < 20; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  std::multimap<int, int> m2;
  ft::MultiMap<int, int> fm2;

  for (int i = 0; i < 50; ++i) {
    int r = rand() % 100 + 1;
    m.insert(std::make_pair(r, r));
    fm.insert(std::make_pair(r, r));
  }

  std::swap(m, m2);
  ft::swap(fm, fm2);

  AssertEqual(m, fm, tr.hintMessage("swap"));
  AssertEqual(m2, fm2, tr.hintMessage("swap m2"));
}

void TestAll() {
  TestRunner tr("MultiMap");

  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestSize, "TestSize");
  tr.RunTest(TestMaxSize, "TestMaxSize");
  tr.RunTest(TestConstructors, "TestConstructors");
  tr.RunTest(TestAssignationOperator, "TestAssignationOperator");
  tr.RunTest(TestIterator, "TestIterator");
  tr.RunTest(TestReverseIterator, "TestReverseIterator");
  tr.RunTest(TestInsert, "TestInsert");
  tr.RunTest(TestErase, "TestErase");
  tr.RunTest(TestSwap, "TestSwap");
  tr.RunTest(TestClear, "TestClear");
  tr.RunTest(TestFind, "TestFind");
  tr.RunTest(TestCount, "TestCount");
  tr.RunTest(TestLowerBound, "TestLowerBound");
  tr.RunTest(TestUpperBound, "TestUpperBound");
  tr.RunTest(TestEqualRange, "TestEqualRange");
  tr.RunTest(TestRelationalNonMemberOperators, "TestRelationalNonMemberOperators");
  tr.RunTest(TestSwapNonMember, "TestSwapNonMember");
}
}
