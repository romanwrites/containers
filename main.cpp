#include "TestList.h"
#include "TestVector.h"
#include "TestMap.h"

int main() {
  TestList::TestAll();
  TestVector::TestAll();
  TestMap::TestAll();

  return 0;
}
