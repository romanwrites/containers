#include "Vector.hpp"
#include <iostream>
#include <vector>

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
class Node {
private:
	template<class Iter>
	class NodeIterator {
		friend class Node;

	public:
		typedef Iter iterator_type;
		typedef std::input_iterator_tag iterator_category;
		typedef iterator_type value_type;
		typedef ptrdiff_t difference_type;
		typedef iterator_type& reference;
		typedef iterator_type* pointer;

		iterator_type *value;
	private:
		NodeIterator(Iter* p) : value(p) { }
	public:
		NodeIterator(const NodeIterator& it) : value(it.value) { }

		bool operator!=(NodeIterator const& other) const {
			return value != other.value;
		}
		bool operator==(NodeIterator const& other) const {
			return value == other.value;
		}

		typename NodeIterator::reference operator*() const {
			return *value;
		}

		NodeIterator& operator++() { // prefix increment. doesn't create a copy
			if (value->parent == nullptr) {
				value = nullptr;
			} else if (value->parent->right.get() == value) {
				value = value->parent;
			} else {
				value = value->parent;
				if (value->right.get() != nullptr) {
					value = value->right.get();
					while (value->left.get() != nullptr) {
						value = value->left.get();
					}
				}
			}
			return *this;
		}
	};

public:
	T value;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
	Node* parent;

	Node(const T& value, std::unique_ptr<Node> left, std::unique_ptr<Node> right, Node *parent)
							: value(value), left(std::move(left)), right(std::move(right)), parent(parent) {}
	Node(const Node&) = delete;

	typedef NodeIterator<Node> iterator;
	typedef NodeIterator<const Node> const_iterator;

	iterator begin() {
		Node* node = this;
		while (node->left != nullptr) {
			node = node->left.get();
		}
		return iterator(node); // call private constructor. that's why friend
	}
	iterator end() {
		return nullptr; // todo shadow node
	}
	const_iterator begin() const {
		const Node* node = this;
		while (node->left != nullptr) {
			node = node->left.get();
		}
		return const_iterator(node);
	}
	const_iterator end() const {
		return nullptr; // todo shadow node
	}
	friend std::ostream& operator<<(std::ostream& os, const Node& n) {
		return os << n.value;
	}
};

//int main() {

////	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
////		std::cout << *it << std::endl;
////	}
//
////	testElemsConstructor();
////	testPushPop();
////	testAssign();
////	testIterator();
//    return 0;
//}

//// Member types
//value_type //тип, который возвращает итератор
//pointer // pointer to this type
//reference // reference to this type
//iterator_category // category of iterator
//difference_type // difference between two iterators

int main() {
	std::string str = "Hello world\n";
	printMap(str);

	auto root = std::make_unique<Node<std::string>>("a1", nullptr, nullptr, nullptr);
	root->left = std::make_unique<Node<std::string>>("b1", nullptr, nullptr, root.get()); // get raw pointer
	root->right = std::make_unique<Node<std::string>>("b2", nullptr, nullptr, root.get());

	auto b1 = root->left.get();
	auto b2 = root->right.get();
	b1->left = std::make_unique<Node<std::string>>("c1", nullptr, nullptr, b1);
	b1->right = std::make_unique<Node<std::string>>("c2", nullptr, nullptr, b1);
	b2->left = std::make_unique<Node<std::string>>("c3", nullptr, nullptr, b2);
	b2->right = std::make_unique<Node<std::string>>("c4", nullptr, nullptr, b2);
//	auto c1 = b1->left.get();
//	auto c2 = b1->right.get();
//	auto c3 = b2->left.get();
//	auto c4 = b2->right.get();
//
//	std::cout << root->value << std::endl;
//	std::cout << b1->value << std::endl;
//	std::cout << b2->value << std::endl;
//	std::cout << c1->value << std::endl;
//	std::cout << c2->value << std::endl;
//	std::cout << c3->value << std::endl;
//	std::cout << c4->value << std::endl;
	auto it = root->begin();
	std::cout << *it << std::endl; // most left node
	++it;
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;

	for (auto it = root->begin())

}