#include "Vector.hpp"
#include <iostream>

template<typename T>
void PrintVector(const T& v) {
	for (size_t i = 0; i < v.size(); i++) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl << "-------------------------------" << std::endl;
}

int main() {
	ft::Vector<std::string> v;
	v.push_back("C++");
	v.push_back("STL");
	v.push_back("my Vector");
	v.push_back("C++");
	v.push_back("C++");
	PrintVector(v);
	v.pop_back();
	PrintVector(v);
	ft::Vector<std::string>::iterator it = v.begin();
	std::cout <<  "---------test iterators-------\n";
	while (it != v.end()) {
		std::cout << *it << " ";
		it++;
	}
    return 0;
}
