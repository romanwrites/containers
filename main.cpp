#include "Vector.hpp"
#include <iostream>

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

int main() {
	testPushPop();
	testAssign();
	testIterator();
    return 0;
}
