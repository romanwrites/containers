#include "TestRunner.h"
#include <array>
#include "TreePrinter.h"

namespace TestMap {

void TestEmpty(TestRunner const &tr) {
  std::map<std::string, int> m;
  ft::Map<std::string, int> fm;
  Assert(fm.empty() == m.empty(), tr.hintMessage("empty"));
}

void TestSize(TestRunner const &tr) {
  std::map<std::string, int> m;
  ft::Map<std::string, int> fm;
  Assert(fm.size() == m.size(), tr.hintMessage("test empty size"));

  m["one"] = 1;
  m["two"] = 2;

  fm["one"] = 1;
  fm["two"] = 2;

  Assert(fm.size() == m.size(), tr.hintMessage("test size"));
}

void TestAdd(TestRunner const &tr) {
  std::map<std::string, int> m;
  ft::Map<std::string, int> fm;

  m["one"] = 1;
  m["two"] = 2;

  fm["one"] = 1;
  fm["two"] = 2;

  AssertEqual(fm, m, tr.hintMessage("add, operator[]"));
}

void TestAll() {
  TestRunner tr("Map");

  tr.RunTest(TestAdd, "TestAdd");
  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestSize, "TestSize");

}
}
