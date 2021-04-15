#include "TestStack.h"
#include "TestRunner.h"

namespace TestStack {

void TestEmpty(TestRunner const &tr) {
  std::stack<std::string> s;
  ft::Stack<std::string> fs;

  Assert(s.empty() == fs.empty(), tr.hintMessage("empty 1"));

  s.push("one");
  s.push("two");
  fs.push("one");
  fs.push("two");

  Assert(s.empty() == fs.empty(), tr.hintMessage("empty 2"));
}

void TestSize(TestRunner const &tr) {
  std::stack<int> s;
  ft::Stack<int> fs;

  Assert(s.size() == fs.size(), tr.hintMessage("empty 1"));

  for (int i = 0; i < 555; ++i) {
    s.push(i);
    fs.push(i);
  }

  Assert(s.size() == fs.size(), tr.hintMessage("empty 2"));
}

void TestPush(TestRunner const &tr) {
  std::stack<int> s;
  ft::Stack<int> fs;

  for (int i = 0; i < 10000; ++i) {
    s.push(i);
    fs.push(i);
    Assert(s.top() == fs.top(), tr.hintMessage("push " + std::to_string(i)));
  }

}

void TestTop(TestRunner const &tr) {
  std::stack<int> s;
  ft::Stack<int> fs;

  for (int i = 0; i < 10; ++i) {
    s.push(i);
    fs.push(i);
    Assert(s.top() == fs.top(), tr.hintMessage("front " + std::to_string(i)));

    s.top() -= 15;
    fs.top() -= 15;
    Assert(s.top() == fs.top(), tr.hintMessage("front " + std::to_string(i)));
  }

  std::stack<int> const &const_q = s;
  ft::Stack<int> const &const_fq = fs;

  Assert(const_fq.top() == const_q.top(), tr.hintMessage("front on const object"));
}

void TestPop(TestRunner const &tr) {
  std::stack<int> s;
  ft::Stack<int> fs;

  for (int i = 0; i < 1000; ++i) {
    s.push(i);
    fs.push(i);
  }

  for (int i = 0; i < 999; ++i) {
    s.pop();
    fs.pop();
    Assert(s.top() == fs.top(), tr.hintMessage("pop. iteration: " + std::to_string(i)));
  }
}

template<class T>
void ProcessOperatorsCompare(std::stack<T> const &q1, std::stack<T> const &q2,
                             ft::Stack<T> const &fq1, ft::Stack<T> const &fq2,
                             TestRunner const &tr) {
  Assert((q1 == q2) == (fq1 == fq2), tr.hintMessage("operator =="));
  Assert((q1 != q2) == (fq1 != fq2), tr.hintMessage("operator !="));
  Assert((q1 < q2) == (fq1 < fq2), tr.hintMessage("operator =="));
  Assert((q1 <= q2) == (fq1 <= fq2), tr.hintMessage("operator !="));
  Assert((q1 > q2) == (fq1 > fq2), tr.hintMessage("operator =="));
  Assert((q1 >= q2) == (fq1 >= fq2), tr.hintMessage("operator !="));
}

void TestRelationalOperators(TestRunner const &tr) {
  std::stack<int> q1;
  std::stack<int> q2;
  ft::Stack<int> fq1;
  ft::Stack<int> fq2;

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
  TestRunner tr("Stack");

  tr.RunTest(TestPush, "TestPush");
  tr.RunTest(TestEmpty, "TestEmpty");
  tr.RunTest(TestSize, "TestSize");
  tr.RunTest(TestTop, "TestTop");
  tr.RunTest(TestPop, "TestPop");
  tr.RunTest(TestRelationalOperators, "TestRelationalOperators");
}

}
