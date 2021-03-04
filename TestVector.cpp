#include "TestRunner.h"

namespace TestVector {

void TestEmpty() {
  std::vector<std::string> v;
  ft::Vector<std::string> fv;

  Assert(fv.empty() == v.empty(), HintVector("Test empty() method"));
  AssertEqual(fv, v, HintVector("Test empty lists"));
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

void TestInsert() {
  std::vector<Auto> v;
  ft::Vector<Auto> fv;
  v.insert(v.begin(), 2);
  v.insert(v.begin(), 1);
  v.insert(v.end(), 3);
  fv.insert(fv.begin(), 2);
  fv.insert(fv.begin(), 1);
  fv.insert(fv.end(), 3);
  AssertEqual(fv, v, HintVector("Basic insert() 2 at begin, 1 at end"));

  v.insert(v.begin(), 10, 4);
  fv.insert(fv.begin(), 10, 4);
  AssertEqual(fv, v, HintVector("Fill insert() 1"));

  auto itv = v.begin();
  ++itv;
  ++itv;
  auto itfv = fv.begin();
  ++itfv;
  ++itfv;

  v.insert(itv, 15, 5);
  fv.insert(itfv, 15, 5);
  AssertEqual(fv, v, HintVector("Fill insert() 2"));

  itv = v.begin();
  ++itv;
  ++itv;
  itfv = fv.begin();
  ++itfv;
  ++itfv;

  std::vector<Auto> vauto{1,2,3,4,5,6,7,8,9,10};

  v.insert(itv, vauto.begin(), vauto.end());
  fv.insert(itfv, vauto.begin(), vauto.end());
  AssertEqual(fv, v, HintVector("Range insert()"));
}

void TestReserve() {
  std::vector<int> v(10);
  ft::Vector<int> fv(10);
  v.reserve(5);
  fv.reserve(5);
  Assert(fv.capacity() == v.capacity(), HintVector("Reserve() with lesser value than capacity. Compare capacity")); //todo add capacity
  AssertEqual(fv, v, HintVector("Reserve() with lesser value than capacity"));
  v.reserve(50);
  fv.reserve(50);
  Assert(fv.capacity() == v.capacity(), HintVector("Reserve() with greater value than capacity. Compare capacity")); //todo add capacity
  AssertEqual(fv, v, HintVector("Reserve() with lesser value than capacity)"));
}

void TestPushBack() {
  std::vector<int> v;
  ft::Vector<int> fv;

  for (int i = 0; i < 5000; ++i) {
    v.push_back(i);
    fv.push_back(i);
  }
  AssertEqual(fv, v, HintVector("push_back()"));
}

void TestMaxSize() {
  std::vector<int> vi;
  ft::Vector<int> fvi;
  Assert(fvi.max_size() == vi.max_size(), "kek");

  std::vector<std::string> vs;
  ft::Vector<std::string> fvs;
  Assert(fvs.max_size() == vs.max_size(), "kek");
}

void TestAll() {
  TestRunner tr;

  std::cerr << WITH_BG << "--------------------- Running Vector Tests ---------------------"
            << RESET << std::endl;
  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestReserve, "TestReserve");
  tr.RunTest(TestInsert, "TestInsert");
  tr.RunTest(TestPushBack, "TestPushBack");
  tr.RunTest(TestMaxSize, "TestMaxSize");
}
}
