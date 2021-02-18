#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include "List.hpp"
#include "TestList.h"

#define GREEN(x) ("\033[32m" + x + "\033[0m")
#define RED_SET "\033[0;31m"
#define KHAKI_SET "\033[38;2;240;230;140m"
#define RESET "\033[0m"
#define PINK_SET "\033[38:5:225m"
#define SPRING_GREEN_SET "\033[38;2;0;255;127m"
#define    WITH_BG "\033[48;2;0;250;154m\033[38;2;0;0;0m"

class TestRunner {
 public:
  template<class TestFunc>
  void RunTest(TestFunc func, std::string const &test_name) {
    try {
      func();
      // Use cerr to not mix tests output and program output
      std::cerr << test_name << ": "
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

 private:
  int fail_count = 0;
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

void Assert(bool b, std::string const &hint) {
  AssertEqual(b, true, hint);
}

// MAP OUTPUT

template<class K, class V>
std::ostream &operator<<(std::ostream &os, std::map<K, V> const &m) {
  os << "{";
  bool first = true;
  for (auto const &kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T>
std::ostream &operator<<(std::ostream &os, std::set<T> const &s) {
  os << "{";
  bool first = true;
  for (auto const &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template<class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &s) {
  os << "[";
  bool first = true;
  for (auto const &x : s) {
    os << ", ";
    first = false;
    os << x;
  }
  return os << "]";
}

std::string HintList(std::string const &str) {
  return "List: " + str;
}
