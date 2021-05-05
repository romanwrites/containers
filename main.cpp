#include "TestList.h"
#include "TestVector.h"
#include "TestMap.h"
#include "TestMultiMap.h"
#include "TestQueue.h"
#include "TestStack.h"

int main() {
  TestList::TestAll();
  TestVector::TestAll();
  TestQueue::TestAll();
  TestStack::TestAll();

  srand(time(NULL));
  TestMap::TestAll();
  TestMultiMap::TestAll();

  return 0;
}
