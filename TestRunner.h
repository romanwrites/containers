#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <string>
#include "List.h"
#include "TestList.h"
#include "Vector.hpp"
#include "TestVector.h"
#include "Map.h"
#include "TestMap.h"
#include "MultiMap.h"
#include "TestMultiMap.h"
#include "Queue.h"
#include "TestQueue.h"

#define GREEN "\033[32m"
#define RED_SET "\033[0;31m"
#define KHAKI_SET "\033[38;2;240;230;140m"
#define RESET "\033[0m"
#define PINK_SET "\033[38:5:225m"
#define SPRING_GREEN_SET "\033[38;2;0;255;127m"
#define SPRING_GREEN_BG "\033[48;2;0;250;154m\033[38;2;0;0;0m"
#define ORANGE_BG "\033[48;5;202;154m\033[38;2;0;0;0m"
#define RED_BG_SET "\033[38;5;202m"
#define BLACK_BG_SET "\033[38;5;33m"

class TestRunner {
 public:

  template<class TestFunc>
  void RunTest(TestFunc func, std::string const &test_name) {
    try {
      func(*this);
      // Use cerr to not mix tests output and program output
      std::cerr << KHAKI_SET << test_name << ": "
                << SPRING_GREEN_SET << "OK" << RESET << std::endl;
    } catch (std::runtime_error &ex) {
      ++fail_count;
      std::cerr << test_name << " fail: " << ex.what() << std::endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      std::cerr << fail_count << " tests failed. Terminate" << std::endl;
      exit(1);
    }
  }

  TestRunner(const std::string &container_name = "") : containerName(container_name) {
    runningWhichTests();
  }

  void runningWhichTests() const {
    std::cerr << std::endl
              << SPRING_GREEN_BG << "                      Running "
                  + containerName
                  + " Tests                      "
              << RESET << std::endl;
  }

  std::string hintMessage(std::string const &str) const {
    return containerName + ": " + str;
  }

 private:
  std::string containerName;
  int fail_count = 0;

 public:
  static void printOrange(std::string const &str) {
    std::cerr << std::endl
              << ORANGE_BG
              << "                      "
              << str
              << "                      "
              << RESET << std::endl;
  }
};

template<class T, class U>
void AssertEqual(T const &t, U const &u, std::string const &hint) {
  if (t != u) {
    std::ostringstream os;
    os << "Assertion failed: " << RED_SET << t << " != " << u
       << RESET << ". "
       << PINK_SET << hint << RESET;
    throw std::runtime_error(os.str());
  }
}

void Assert(bool b, std::string const &hint);
