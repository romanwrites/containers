#include "Vector.hpp"
#include <iostream>

template<typename T>
void PrintVector(const ft::Vector<T>& v) {
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
	v.clear();
	PrintVector(v);
    return 0;
}
