#include <memory>
#include <list>

namespace ft {
	//	------------------------------------- LIST NODE -----------------------------------------
	template <class T>
	class NodeList {
		// typedef
	private:
		typedef T value_type;
		NodeList<T> *next;
		NodeList<T> *prev;
		value_type value;
		NodeList() : next(nullptr), prev(nullptr), value(value_type()) {}
		NodeList(const value_type& value) : next(nullptr), prev(nullptr), value(value) {} //todo
		//todo copy constructor

		NodeList &operator=(const NodeList<value_type>& obj) {
			next = obj.next;
			prev = obj.prev;
		}
	public:
		bool operator==(const NodeList &rhs) const {
			return value == rhs.value;
		}

		bool operator!=(const NodeList &rhs) const {
			return !(rhs == *this);
		}

		bool operator<(const NodeList &rhs) const {
			return value < rhs.value;
		}

		bool operator>(const NodeList &rhs) const {
			return rhs < *this;
		}

		bool operator<=(const NodeList &rhs) const {
			return !(rhs < *this);
		}

		bool operator>=(const NodeList &rhs) const {
			return !(*this < rhs);
		}
	};

	// -------------------------------------- TAGS -------------------------------------
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	//	------------------------------------- LIST ITERATOR -----------------------------------------
	template <class Iter>
	class BidirectionalListIt {
	private:
		NodeList<Iter> *ptr;
	public:
		typedef std::ptrdiff_t 					difference_type;
		typedef Iter							value_type;
		typedef ft::bidirectional_iterator_tag	iterator_category;
//		typedef value_type& 					reference;
//		typedef value_type* 					pointer;

		explicit BidirectionalListIt() throw() : ptr(nullptr) {}
		explicit BidirectionalListIt(NodeList<Iter> *p) throw() : ptr(p) {}
		explicit BidirectionalListIt(const NodeList<const Iter> *p) throw() : ptr(const_cast<Node<const Iter> *>(p)) {}
		BidirectionalListIt(const BidirectionalListIt& p) throw() : ptr(p.ptr) {}

		BidirectionalListIt& operator=(const BidirectionalListIt& rhs) {
			ptr = rhs.ptr;
			return *this;
		}

		bool operator==(const BidirectionalListIt &rhs) const {
			return ptr == rhs.ptr;
		}

		bool operator!=(const BidirectionalListIt &rhs) const {
			return !(rhs == *this);
		}

		bool operator<(const BidirectionalListIt &rhs) const {
			return ptr < rhs.ptr;
		}

		bool operator>(const BidirectionalListIt &rhs) const {
			return rhs < *this;
		}

		bool operator<=(const BidirectionalListIt &rhs) const {
			return !(rhs < *this);
		}

		bool operator>=(const BidirectionalListIt &rhs) const {
			return !(*this < rhs);
		}
	};

	//	------------------------------------- LIST CONTAINER -----------------------------------------
	template < class T, class Alloc = std::allocator<T> >
    class List {
	private:

        typedef T						value_type;
        typedef Alloc					allocator_type;
        typedef T&						reference;
        typedef const T&				const_reference;
        typedef T*						pointer;
		typedef const T*				const_pointer;
		typedef ptrdiff_t				difference_type;
		typedef size_t 					size_type;
		typedef BidirectionalListIt<T>	iterator;
//		typedef node_pointer
//		typedef
//		typedef

		NodeList<value_type>* shadow;

		friend class NodeList; // to list todo
    public:
    	List() : shadow(new NodeList<value_type>()) {}

    	iterator begin() {
    		return shadow->next;
    	}

		iterator end() {
			return shadow;
		}

    	void push_back(value_type const &value) {
    		//todo use insert
//			NodeList<value_type> *ptr = new NodeList<value_type>();
//			end->next = ptr;
//			ptr->prev = end;
//			end->prev = ptr;
    	}

    	void insert(value_type const &value) {

    	}
	};
}
