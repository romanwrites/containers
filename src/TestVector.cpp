#include "TestRunner.h"

namespace TestVector {

void TestEmpty(TestRunner const &tr) {
  std::vector<std::string> v;
  ft::Vector<std::string> fv;

  Assert(fv.empty() == v.empty(), tr.hintMessage("Test empty() method"));
  AssertEqual(fv, v, tr.hintMessage("Test empty lists"));
}

class Auto {
 public:
  int val;
  Auto() {
//    std::cout << "----- default constructor called -----" << std::endl;
  }
  Auto(int i) : val(i) {
//    std::cout << "----- param constructor called -----" << std::endl;
  }
  virtual ~Auto() {
//    std::cout << "----- destructor called -----" << std::endl;
  }
};

bool operator!=(Auto const &a, Auto const &b) {
  return a.val != b.val;
}

std::ostream &operator<<(std::ostream &os, std::vector<Auto> const &s) {
  os << "[";
  bool first = true;
  for (auto const &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x.val;
  }
  return os << "]";
}

std::ostream &operator<<(std::ostream &os, ft::Vector<Auto> const &s) {
  os << "[";
  bool first = true;
  for (auto const &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x.val;
  }
  return os << "]";
}

void TestInsert(TestRunner const &tr) {
  std::vector<Auto> v;
  ft::Vector<Auto> fv;
  v.insert(v.begin(), 2);
  v.insert(v.begin(), 1);
  v.insert(v.end(), 3);
  fv.insert(fv.begin(), 2);
  fv.insert(fv.begin(), 1);
  fv.insert(fv.end(), 3);
  AssertEqual(fv, v, tr.hintMessage("Basic insert() 2 at begin, 1 at end"));

  v.insert(v.begin(), 10, 4);
  fv.insert(fv.begin(), 10, 4);
  AssertEqual(fv, v, tr.hintMessage("Fill insert() 1"));

  auto itv = v.begin();
  ++itv;
  ++itv;
  auto itfv = fv.begin();
  ++itfv;
  ++itfv;

  v.insert(itv, 15, 5);
  fv.insert(itfv, 15, 5);
  AssertEqual(fv, v, tr.hintMessage("Fill insert() 2"));

  itv = v.begin();
  ++itv;
  ++itv;
  itfv = fv.begin();
  ++itfv;
  ++itfv;

  std::vector<Auto> vauto{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  v.insert(itv, vauto.begin(), vauto.end());
  fv.insert(itfv, vauto.begin(), vauto.end());
  AssertEqual(fv, v, tr.hintMessage("Range insert()"));
}

void TestReserve(TestRunner const &tr) {
  std::vector<int> v(10);
  ft::Vector<int> fv(10);
  v.reserve(5);
  fv.reserve(5);
  Assert(fv.capacity() == v.capacity(),
         tr.hintMessage("Reserve() with lesser value than capacity. Compare capacity")); //todo add capacity
  AssertEqual(fv, v, tr.hintMessage("Reserve() with lesser value than capacity"));
  v.reserve(50);
  fv.reserve(50);
  Assert(fv.capacity() == v.capacity(),
         tr.hintMessage("Reserve() with greater value than capacity. Compare capacity")); //todo add capacity
  AssertEqual(fv, v, tr.hintMessage("Reserve() with lesser value than capacity)"));
}

void TestPushBack(TestRunner const &tr) {
  std::vector<int> v;
  ft::Vector<int> fv;

  for (int i = 0; i < 5000; ++i) {
    v.push_back(i);
    fv.push_back(i);
  }
  AssertEqual(fv, v, tr.hintMessage("push_back()"));
}

void TestMaxSize(TestRunner const &tr) {
  (void)tr;
  std::vector<int> vi;
  ft::Vector<int> fvi;
  Assert(fvi.max_size() == vi.max_size(), "int vector max_size()");

  std::vector<std::string> vs;
  ft::Vector<std::string> fvs;
  Assert(fvs.max_size() == vs.max_size(), "string vector max_size()");
}

void TestFrontBackAt(TestRunner const &tr) {
  std::vector<int> v;
  ft::Vector<int> fv;

  for (int i = 0; i < 5000; ++i) {
    v.push_back(i);
    fv.push_back(i);
  }
  Assert(fv.front() == v.front(), tr.hintMessage("front()"));
  Assert(fv.back() == v.back(), tr.hintMessage("back()"));
  Assert(fv.at(553) == v.at(553), tr.hintMessage("at()"));

  std::vector<int> const v_const(v.begin(), v.end());
  ft::Vector<int> const fv_const(fv.begin(), fv.end());
  Assert(fv_const.front() == v_const.front(), tr.hintMessage("const front()"));
  Assert(fv_const.back() == v_const.back(), tr.hintMessage("const back()"));
  Assert(fv.at(1324) == v.at(1324), tr.hintMessage("at()"));
}

void TestGetAllocator(TestRunner const &tr) {
  // Example from cplusplus.com
  std::vector<int> v;
  ft::Vector<int> fv;
  int *p;
  int *fp;
  unsigned int i;

  p = v.get_allocator().allocate(5);
  fp = fv.get_allocator().allocate(5);

  for (i = 0; i < 5; i++) {
    v.get_allocator().construct(&p[i], i);
    fv.get_allocator().construct(&fp[i], i);
  }

  for (i = 0; i < 5; ++i) {
    Assert(fp[i] == p[i], tr.hintMessage("get_allocator() compare array elements"));
  }

  for (i = 0; i < 5; i++) {
    v.get_allocator().destroy(&p[i]);
    fv.get_allocator().destroy(&fp[i]);
  }
  v.get_allocator().deallocate(p, 5);
  fv.get_allocator().deallocate(fp, 5);
}

void TestResize(TestRunner const &tr) {
  std::vector<int> v;
  ft::Vector<int> fv;

  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
    fv.push_back(i);
  }

  v.resize(7);
  fv.resize(7);
  AssertEqual(fv, v, tr.hintMessage("resize() smaller"));

  v.resize(9);
  fv.resize(9);
  AssertEqual(fv, v, tr.hintMessage("resize() greater deefault value"));

  v.resize(15, 100);
  fv.resize(15, 100);
  AssertEqual(fv, v, tr.hintMessage("resize() greater set value"));

}

template<class T>
void printTmp(std::vector<T> const &a) {
  std::cout << "[";
  for (int i = 0; i < (int) a.size(); ++i) {
    std::cout << a[i];
    if (i + 1 != (int) a.size()) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;
}

void TestAssign(TestRunner const &tr) {
  std::vector<int> v;
  ft::Vector<int> fv;

  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
    fv.push_back(i);
  }

  v.assign(4, 3);
  fv.assign(4, 3);
  AssertEqual(fv, v, tr.hintMessage("assign() fill"));

  std::list<int> lst{10, 20, 30, 40, 50};
  v.assign(lst.begin(), lst.end());
  fv.assign(lst.begin(), lst.end());
  AssertEqual(fv, v, tr.hintMessage("assign() range"));
}

void TestErase(TestRunner const &tr) {
  std::vector<int> v;
  ft::Vector<int> fv;

  for (int i = 1; i <= 50; i++) {
    v.push_back(i);
    fv.push_back(i);
  }

  v.erase(v.begin() + 5);
  fv.erase(fv.begin() + 5);
  AssertEqual(fv, v, tr.hintMessage("erase() one element"));

  v.erase(v.begin(), v.begin() + 10);
  fv.erase(fv.begin(), fv.begin() + 10);
  AssertEqual(fv, v, tr.hintMessage("erase() range begin"));

  v.erase(v.begin() + 10, v.end());
  fv.erase(fv.begin() + 10, fv.end());
  AssertEqual(fv, v, tr.hintMessage("erase() range till end"));
}

void TestSwap(TestRunner const &tr) {
  std::vector<int> v1;
  std::vector<int> v2;
  ft::Vector<int> fv1;
  ft::Vector<int> fv2;

  for (int i = 1; i <= 50; i++) {
    v1.push_back(i);
    fv1.push_back(i);
  }

  for (int i = 25; i > 0; i--) {
    v2.push_back(i);
    fv2.push_back(i);
  }

  v1.swap(v2);
  fv1.swap(fv2);
  AssertEqual(fv1, v1, tr.hintMessage("swap() first vector"));
  AssertEqual(fv2, v2, tr.hintMessage("swap() second vector"));

  std::swap(v1, v2);
  ft::swap(fv1, fv2);
  AssertEqual(fv1, v1, tr.hintMessage("swap() non member vector1"));
  AssertEqual(fv2, v2, tr.hintMessage("swap() non member vector2"));
}

void TestComparisonOperators(TestRunner const &tr) {
  std::vector<std::string> l1{"a", "b"};
  std::vector<std::string> l2{"a", "b"};
  ft::Vector<std::string> fl1;
  ft::Vector<std::string> fl2;
  fl1.push_back("a");
  fl2.push_back("a");
  fl1.push_back("b");
  fl2.push_back("b");

  Assert(fl1 == fl2 && l1 == l2, tr.hintMessage("Test operator==()"));

  Assert(fl1 <= fl2 && l1 <= l2, tr.hintMessage("Test operator<=() 1"));

  l1.push_back("a");
  fl1.push_back("a");
  Assert(fl1 != fl2 && l1 != l2, tr.hintMessage("Test operator!=()"));
  Assert(fl1 > fl2 && l1 > l2, tr.hintMessage("Test operator>()"));
  Assert(fl1 >= fl2 && l1 >= l2, tr.hintMessage("Test operator>=() 2"));
  Assert(fl2 <= fl1 && l2 <= l1, tr.hintMessage("Test operator<=() 2"));
}

void TestAll() {
  TestRunner tr("Vector");

  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestReserve, "TestReserve");
  tr.RunTest(TestInsert, "TestInsert");
  tr.RunTest(TestPushBack, "TestPushBack");
  tr.RunTest(TestMaxSize, "TestMaxSize");
  tr.RunTest(TestFrontBackAt, "TestFrontBackAt");
  tr.RunTest(TestGetAllocator, "TestGetAllocator");
  tr.RunTest(TestResize, "TestResize");
  tr.RunTest(TestAssign, "TestAssign");
  tr.RunTest(TestErase, "TestErase");
  tr.RunTest(TestSwap, "TestSwap");
  tr.RunTest(TestComparisonOperators, "TestComparisonOperators");
}
}
