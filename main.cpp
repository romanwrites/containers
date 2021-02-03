#include "Vector.hpp"
#include <iostream>
#include <vector>
#include <set>
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

template <class T>
void testList() {
	std::list<int> lst;
	ft::List<int> ftlst;
	std::cout << *(lst.begin()) <<std::endl;
	std::cout << *(ftlst.begin()) <<std::endl;
}

int main() {

//	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
//		std::cout << *it << std::endl;
//	}

//	testElemsConstructor();
//	testPushPop();
//	testAssign();
//	testIterator();
    return 0;
}


//int main() {
//	std::vector<std::string> vv;
//	try {
//		vv.at(45);
//	} catch (std::exception &ex) {
//		std::cout << ex.what() << std::endl;
//	}
//
//	std::string str = "Hello world\n";
//	printMap(str);
//
//	auto root = std::make_unique<Node<std::string>>("a1", nullptr, nullptr, nullptr);
//	root->left = std::make_unique<Node<std::string>>("b1", nullptr, nullptr, root.get()); // get raw pointer
//	root->right = std::make_unique<Node<std::string>>("b2", nullptr, nullptr, root.get());
//
//	auto b1 = root->left.get();
//	auto b2 = root->right.get();
//	b1->left = std::make_unique<Node<std::string>>("c1", nullptr, nullptr, b1);
//	b1->right = std::make_unique<Node<std::string>>("c2", nullptr, nullptr, b1);
//	b2->left = std::make_unique<Node<std::string>>("c3", nullptr, nullptr, b2);
//	b2->right = std::make_unique<Node<std::string>>("c4", nullptr, nullptr, b2);
////	auto c1 = b1->left.get();
////	auto c2 = b1->right.get();
////	auto c3 = b2->left.get();
////	auto c4 = b2->right.get();
//
//	for (auto it = root->begin(); it != root->end(); ++it) {
//		std::cout << *it << std::endl;
//	}
//
//	std::cout << std::endl;
//
//	for (auto &&node : *root) {
//		std::cout << node << std::endl;
//	}
//
//	std::set<Point> points{ {5,3}, {1,2}, {0,0}, {3, 2} }; //фигурная инициализация
//	for (auto &&point : points) {
//		std::cout << point.x << " " << point.y << std::endl;
//	}
//
//}

//#include <list>
//int main() {
//	std::vector<std::string> vv;
//	try {
//		vv.at(28);
//	} catch (std::exception &ex) {
//		std::cout << ex.what() << "WHAAAAAAT" << std::endl;
//	}
//}
