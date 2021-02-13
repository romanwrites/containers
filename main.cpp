#include "Vector.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include "List.hpp"

template<typename T>
void PrintVector(const T& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl << "-------------------------------" << std::endl;
}

void testPushPop() {
    std::cout << "---------Test push_back, pop--------" << std::endl;
    ft::Vector<int>		v;
    for (int i = 1, j = 0; j < 16; i*=2, j++)
        v.push_back(i);
    PrintVector(v);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    PrintVector(v);
}

void testElemsConstructor() {
    std::cout << "---------Test elems constructor--------" << std::endl;
    ft::Vector<int> v(15, 50);
    PrintVector(v);
    std::cout << "v size: " << v.size() << std::endl;
    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();
    std::cout << "v size: " << v.size() << std::endl;
    v.push_back(18);
    v.push_back(18);
    v.push_back(18);
    PrintVector(v);
    std::cout << "v size: " << v.size() << std::endl;
}

void testAssign() {
    std::cout << "---------Test assign--------" << std::endl;
    ft::Vector<int>		v;
    std::vector<int>	stl;
    for (int i = 1, j = 0; j < 16; i*=2, j++)
        stl.push_back(i);
    v.assign(stl.begin(), stl.end());
    PrintVector(v);
}

void testIterator() {
    std::cout << "---------Test iterators--------" << std::endl;
    ft::Vector<int>		v;
    for (int i = 1, j = 0; j < 16; i*=2, j++)
        v.push_back(i);
    ft::Vector<int>::iterator it = v.begin();
    while (it != v.end()) {
        std::cout << *it << "\t";
        it++;
    }
}

template <class T>
void printMap(const T& t) {
    for (typename T::const_iterator it = t.begin(); it != t.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

//void emptyBegin() {
//	std::list<int> lst;
//	ft::List<int> ftlst;
//	std::cout << *(lst.begin()) <<std::endl;
//	std::cout << *(ftlst.begin()) <<std::endl;
//}

void testVector() {
    testElemsConstructor();
    testPushPop();
    testAssign();
    testIterator();
}

void testList() {
    std::list<std::string> lst;
    ft::List<std::string> ftlst;

    lst.insert(lst.begin(), "+");
    lst.insert(lst.begin(), "С");
    lst.insert(lst.end(), "+");

    ftlst.insert(ftlst.begin(), "+");
    ftlst.insert(ftlst.begin(), "С");
    ftlst.insert(ftlst.end(), "+");

    std::cout << "0: " << ftlst.at(0) << ", 1: " << ftlst.at(1) << ", 2: " << ftlst.at(2)  << ", 3: " << ftlst.at(3) << std::endl << std::endl;

    auto it = lst.begin();
//	std::cout << "test lst: " << *it << std::endl;
//    it++;
//	std::cout << "test lst: " << *it << std::endl;
//    it++;
//    std::cout << "test lst: " << *it << std::endl;

    for (ft::List<std::string>::iterator i = ftlst.begin(); i != ftlst.end(); ++i) {
		std::cout << "test lst: " << *i << std::endl;
    }

//    for (auto &i : lst) {
//        std::cout << i << std::endl;
//    }
//
//    for (std::list<std::string>::iterator it = lst.begin(); it != lst.end(); it++) {
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl << "FTLST: \n";

//    for (auto &i : ftlst) {
//        std::cout << i << std::endl;
//    }


    std::cout << "================= emptyBegin() ===============\n";
//    emptyBegin();
}



int main() {
    testList();
//    testVector();

    return 0;
}
