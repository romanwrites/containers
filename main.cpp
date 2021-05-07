#include "TestRunner.h"
#include "TestList.h"
#include "TestVector.h"
#include "TestMap.h"
#include "TestMultiMap.h"
#include "TestQueue.h"
#include "TestStack.h"
#include "TestSet.h"

int main() {
  TestRunner::printOrange("MANDATORY PART");

  TestList::TestAll();
  TestVector::TestAll();
  TestQueue::TestAll();
  TestStack::TestAll();

  srand(time(NULL));
  TestMap::TestAll();

  TestRunner::printOrange("BONUSES");
  TestMultiMap::TestAll();
  TestSet::TestAll();

  return 0;
}
