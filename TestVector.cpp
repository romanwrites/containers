#include "TestRunner.h"

namespace TestVector {

void TestEmpty() {
  std::vector<std::string> v;
  ft::Vector<std::string> fv;

  Assert(fv.empty() == v.empty(), HintVector("Test empty() method"));
  AssertEqual(fv, v, HintVector("Test empty lists"));
}

void TestInsert() {
  std::vector<std::string> v;
  ft::Vector<std::string> fv;

  v.insert(v.begin(), "+");
  v.insert(v.begin(), "C");
  v.insert(v.end(), "+");

  fv.insert(fv.begin(), "+");
  std::cout << fv << std::endl;
  fv.insert(fv.begin(), "C");
  std::cout << fv << std::endl;
  fv.insert(fv.end(), "+");
  std::cout << fv << std::endl;

  AssertEqual(fv, v, HintList("Basic insert() 2 at begin, 1 at end"));
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

void TestAll() {
  TestRunner tr;

  std::cerr << WITH_BG << "--------------------- Running Vector Tests ---------------------" 
  			<< RESET << std::endl;
  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestInsert, "TestInsert");
}
}
