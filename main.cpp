#include "TestList.h"
#include "TestVector.h"
#include "TestMap.h"
#include "TestQueue.h"
#include "TestStack.h"

int main() {
  TestList::TestAll();
  TestVector::TestAll();
  TestQueue::TestAll();
  TestStack::TestAll();
  TestMap::TestAll();

  return 0;
}
