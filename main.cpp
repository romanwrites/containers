#include "TestList.h"
#include "TestVector.h"
#include "TestMap.h"
#include "TestQueue.h"

int main() {
  TestList::TestAll();
  TestVector::TestAll();
  TestMap::TestAll();
  TestQueue::TestAll();

  return 0;
}
