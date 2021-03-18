#include "TestRunner.h"

namespace TestMap {

void TestEmpty() {
  std::map<std::string, int> m;
  ft::Map<std::string, int> fm;
  Assert(fm.empty() == m.empty(), HintMap("test empty"));
}

void TestAll() {
  TestRunner tr;

  std::cerr << WITH_BG << "--------------------- Running Map Tests ---------------------"
            << RESET << std::endl;

  tr.RunTest(TestEmpty, "TestEmpty");
}
}
