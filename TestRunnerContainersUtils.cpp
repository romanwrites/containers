#include <string>
#include "TestRunner.h"

void Assert(bool b, std::string const &hint) {
  AssertEqual(b, true, hint);
}

std::string HintList(std::string const &str) {
  return "List: " + str;
}

std::string HintVector(std::string const &str) {
  return "Vector: " + str;
}

std::string HintMap(std::string const &str) {
  return "Map: " + str;
}

std::string HintSet(std::string const &str) {
  return "Set: " + str;
}

std::string HintStack(std::string const &str) {
  return "Stack: " + str;
}

std::string HintQueue(std::string const &str) {
  return "Queue : " + str;
}
