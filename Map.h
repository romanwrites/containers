#pragma once
//#include <map>

namespace ft {
	//	------------------------------------- MAP ITERATOR -----------------------------------------
	struct input_iterator_tag {};

	template <class T>
	class Node {
	private:
		template<class Iter>
		class NodeIterator {
			friend class Node;

		public:
			typedef Iter iterator_type;
			typedef ft::input_iterator_tag iterator_category;
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

	template<class T>
	class Map {

	};