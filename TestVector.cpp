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

//  fv.insert(fv.begin(), 2);
//  std::cout << fv << std::endl;
//  fv.insert(fv.begin(), 1);
//  std::cout << fv << std::endl;
//  fv.insert(fv.end(), 3);
//  std::cout << fv << std::endl;

//  std::vector<std::string> v;
//  ft::Vector<std::string> fv;
//
//  v.insert(v.begin(), "+");
//  v.insert(v.begin(), "C");
//  v.insert(v.end(), "+");
//
//  fv.insert(fv.begin(), "+");
//  std::cout << fv << std::endl;
//  fv.insert(fv.begin(), "C");
//  std::cout << fv << std::endl;
//  fv.insert(fv.end(), "+");
//  std::cout << fv << std::endl;
//
//  AssertEqual(fv, v, HintList("Basic insert() 2 at begin, 1 at end"));
//
//  std::vector<std::string> v{"one", "two", "three", "four", "five"};
//  v.insert(v.begin(), v.begin(), v.end());
//  fv.insert(fv.begin(), v.begin(), v.end());
//  AssertEqual(fv, v, HintList("Range fill insert() begin from vector<string>"));
//
//  v.insert(v.end(), v.begin(), v.end());
//  fv.insert(fv.end(), v.begin(), v.end());
//  AssertEqual(fv, v, HintList("Range fill insert() end from vector<string>"));
//
//  auto itv = std::find(v.begin(), v.end(), "C");
//  auto itfv = std::find(fv.begin(), fv.end(), "C");
//
//  v.insert(itv, v.begin(), v.end());
//  fv.insert(itfv, v.begin(), v.end());
//  AssertEqual(fv, v, HintList("Range fill insert() mid from vector<string>"));
//
//  itv = std::find(v.begin(), v.end(), "+");
//  itfv = std::find(fv.begin(), fv.end(), "+");
//
//  v.insert(itv, 5, "+");
//  fv.insert(itfv, 5, "+");
//  AssertEqual(fv, v, HintList("Range fill insert() end from vector<string>"));
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

void TestAll() {
  TestRunner tr;

  std::cerr << WITH_BG << "--------------------- Running Vector Tests ---------------------"
            << RESET << std::endl;
  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestReserve, "TestReserve");
  tr.RunTest(TestInsert, "TestInsert");
}
}
