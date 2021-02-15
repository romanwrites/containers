#include "List.hpp"
#include <list>
#include "TestRunner.h"

void TestListInsert() {
    std::list<std::string> lst;
    ft::List<std::string> ftlst;

    lst.insert(lst.begin(), "+");
    lst.insert(lst.begin(), "С");
    lst.insert(lst.end(), "+");

    ftlst.insert(ftlst.begin(), "+");
    ftlst.insert(ftlst.begin(), "С");
    ftlst.insert(ftlst.end(), "+");

    AssertEqual(ftlst, lst, "List: Insert 2 at begin, 1 at end");
}

void TestAllList() {
    TestRunner tr;
    tr.RunTest(TestListInsert, "TestListInsert");
}
