#include "TestRunner.h"

namespace TestVector {

void TestEmpty() {
  std::vector<std::string> v;
  ft::Vector<std::string> fv;

  Assert(fv.empty() == v.empty(), HintVector("Test empty() method"));
  AssertEqual(fv, v, HintVector("Test empty lists"));
}

void TestAll() {
  TestRunner tr;

  std::cerr << WITH_BG << "--------------------- Running Vector Tests ---------------------" << RESET << std::endl;
  tr.RunTest(TestEmpty, "TestEmpty");
}
}
