#include <queue>
#include "Queue.h"
#include "TestRunner.h"

namespace TestQueue {

void TestEmpty(TestRunner const &tr) {
  std::queue<std::string> q;
  ft::Queue<std::string> fq;

  Assert(q.empty() == fq.empty(), tr.hintMessage("empty 1"));

  q.push("one");
  q.push("two");
  fq.push("one");
  fq.push("two");

  Assert(q.empty() == fq.empty(), tr.hintMessage("empty 2"));
}

void TestSize(TestRunner const &tr) {
  std::queue<int> q;
  ft::Queue<int> fq;

  Assert(q.size() == fq.size(), tr.hintMessage("empty 1"));

  for (int i = 0; i < 555; ++i) {
    q.push(i);
    fq.push(i);
  }

  Assert(q.size() == fq.size(), tr.hintMessage("empty 2"));
}

void TestPush(TestRunner const &tr) {
  std::queue<int> q;
  ft::Queue<int> fq;

  for (int i = 0; i < 10000; ++i) {
    q.push(i);
    fq.push(i);
    Assert(q.back() == fq.back(), tr.hintMessage("push " + std::to_string(i)));
  }

}

void TestFront(TestRunner const &tr) {
  std::queue<int> q;
  ft::Queue<int> fq;

  for (int i = 0; i < 10; ++i) {
    q.push(i);
    q.front() -= 15;
    fq.push(i);
    fq.front() -= 15;

    Assert(q.front() == fq.front(), tr.hintMessage("front " + std::to_string(i)));
  }

  std::queue<int> const &const_q = q;
  ft::Queue<int> const &const_fq = fq;

  Assert(const_fq.front() == const_q.front(), tr.hintMessage("front on const object"));
}

void TestBack(TestRunner const &tr) {
  std::queue<int> q;
  ft::Queue<int> fq;

  for (int i = 0; i < 10; ++i) {
    q.push(i);
    q.back() -= 15;
    fq.push(i);
    fq.back() -= 15;

    Assert(q.back() == fq.back(), tr.hintMessage("back " + std::to_string(i)));
  }

  std::queue<int> const &const_q = q;
  ft::Queue<int> const &const_fq = fq;

  Assert(const_fq.back() == const_q.back(), tr.hintMessage("back on const object"));
}

void TestPop(TestRunner const &tr) {
  std::queue<int> q;
  ft::Queue<int> fq;

  for (int i = 0; i < 1000; ++i) {
    q.push(i);
    fq.push(i);
  }

  for (int i = 0; i < 999; ++i) {
    q.pop();
    fq.pop();
    Assert(q.front() == fq.front(), tr.hintMessage("pop. iteration: " + std::to_string(i)));
  }
}

template<class T>
void ProcessOperatorsCompare(std::queue<T> const &q1, std::queue<T> const &q2,
                             ft::Queue<T> const &fq1, ft::Queue<T> const &fq2,
                             TestRunner const &tr) {
  Assert((q1 == q2) == (fq1 == fq2), tr.hintMessage("operator =="));
  Assert((q1 != q2) == (fq1 != fq2), tr.hintMessage("operator !="));
  Assert((q1 < q2) == (fq1 < fq2), tr.hintMessage("operator =="));
  Assert((q1 <= q2) == (fq1 <= fq2), tr.hintMessage("operator !="));
  Assert((q1 > q2) == (fq1 > fq2), tr.hintMessage("operator =="));
  Assert((q1 >= q2) == (fq1 >= fq2), tr.hintMessage("operator !="));
}

void TestRelationalOperators(TestRunner const &tr) {
  std::queue<int> q1;
  std::queue<int> q2;
  ft::Queue<int> fq1;
  ft::Queue<int> fq2;

  for (int i = 0; i < 10; ++i) {
    q1.push(i);
    q2.push(i);
    fq1.push(i);
    fq2.push(i);
    ProcessOperatorsCompare(q1, q2, fq1, fq2, tr);
  }

  q1.pop();
  fq1.pop();
  ProcessOperatorsCompare(q1, q2, fq1, fq2, tr);

  q2.pop();
  q2.pop();
  fq2.pop();
  fq2.pop();
  ProcessOperatorsCompare(q1, q2, fq1, fq2, tr);
}

void TestAll() {
  TestRunner tr("Queue");

  tr.RunTest(TestPush, "TestPush");
  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestSize, "TestSize");
  tr.RunTest(TestFront, "TestFront");
  tr.RunTest(TestBack, "TestBack");
  tr.RunTest(TestPop, "TestPop");
  tr.RunTest(TestRelationalOperators, "TestRelationalOperators");
}

}
