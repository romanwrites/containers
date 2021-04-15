#include "TestList.h"
#include "TestVector.h"
#include "TestMap.h"
#include "TestQueue.h"
#include "TestStack.h"

int main() {
  TestList::TestAll();
  TestVector::TestAll();
  TestMap::TestAll();
  TestQueue::TestAll();
  TestStack::TestAll();

  return 0;
}
