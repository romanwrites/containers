#include <string>
#include "TestRunner.h"

void Assert(bool b, std::string const &hint) {
  AssertEqual(b, true, hint);
}
