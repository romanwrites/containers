#include "TestRunner.h"
#include "List.hpp"

namespace TestList {
    void TestInsert() {
        std::list<std::string> lst;
        ft::List<std::string> ftlst;

        lst.insert(lst.begin(), "+");
        lst.insert(lst.begin(), "С");
        lst.insert(lst.end(), "+");

        ftlst.insert(ftlst.begin(), "+");
        ftlst.insert(ftlst.begin(), "С");
        ftlst.insert(ftlst.end(), "+");

        AssertEqual(ftlst, lst, HintList("Basic insert() 2 at begin, 1 at end"));
    }

    void TestEmpty() {
        std::list<std::string> lst;
        ft::List<std::string> ftlst;

        Assert(ftlst.empty() == lst.empty(), HintList("Test empty() method"));
        AssertEqual(ftlst, lst, HintList("Test empty lists"));
    }

    void TestPushBack() {
        std::list<int> lst;
        ft::List<int> ftlst;

        for (int i = 0; i < 500; i++) {
            lst.push_back(i);
            ftlst.push_back(i);
        }

        Assert(ftlst.size() == lst.size(), HintList("Test push_back() size()"));
        AssertEqual(ftlst, lst, HintList("Test push_back() equality"));
    }

    void TestPushFront() {
        std::list<int> lst;
        ft::List<int> ftlst;

        for (int i = 0; i < 500; i++) {
            lst.push_front(i);
            ftlst.push_front(i);
        }

        Assert(ftlst.size() == lst.size(), HintList("Test push_front() size()"));
        AssertEqual(ftlst, lst, HintList("Test push_front() equality"));
    }

    void TestParamConstructor() {
    //    std::list<int> lst(21,42);
    //    for (auto it = lst.begin(); it != lst.end(); ++it) {
    //        std::cout << *it << " ";
    //    }
    }

    void TestBeginEnd() {
        std::list<int> lst;
        ft::List<int> ftlst;

        for (int i = 0; i < 50; i++) {
            lst.push_front(i);
            ftlst.push_front(i);
        }

        auto itLst = lst.begin();
        auto itFtlst = ftlst.begin();

        while (itLst != lst.end()) {
            AssertEqual(*itFtlst, *itLst, HintList("Test begin() to end() step: " + std::to_string(*itLst)));
            ++itLst;
            ++itFtlst;
        }
        Assert(itFtlst == ftlst.end(), HintList("Test if iterated over ft::List to the end successfully"));
    }

    void TestRbeginRend() {
//        std::list<int> lst;
//        ft::List<int> ftlst;
//
//        for (int i = 0; i < 50; i++) {
//            lst.push_front(i);
//            ftlst.push_front(i);
//        }
//
//        auto itLst = lst.rbegin();
//        auto itFtlst = ftlst.rbegin();
//
//        while (itLst != lst.rend()) {
//            AssertEqual(*itFtlst, *itLst, HintList("Test begin() to end() step: " + std::to_string(*itLst)));
//            ++itLst;
//            ++itFtlst;
//        }
//        Assert(itFtlst == ftlst.rend(), HintList("Test if iterated over ft::List to the end successfully"));
    }

    void TestAll() {
        TestRunner tr;
        tr.RunTest(TestBeginEnd, "TestBeginEnd");
//        tr.RunTest(TestRbeginRend, "TestRbeginRend");
        tr.RunTest(TestInsert, "TestListInsert");
        tr.RunTest(TestEmpty, "TestEmpty");
        tr.RunTest(TestPushBack, "TestPushBack");
        tr.RunTest(TestPushFront, "TestPushFront");
    }
}
