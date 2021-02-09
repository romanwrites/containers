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
		typedef value_type& 					reference;
		typedef value_type* 					pointer;

		explicit BidirectionalListIt() throw() : ptr(nullptr) {}
		explicit BidirectionalListIt(NodeList<Iter> *p) throw() : ptr(p) {}
		explicit BidirectionalListIt(const NodeList<const Iter> *p) throw() : ptr(const_cast<NodeList<const Iter> *>(p)) {}
		BidirectionalListIt(const BidirectionalListIt& p) throw() : ptr(p.ptr) {}

		BidirectionalListIt& operator=(const BidirectionalListIt& rhs) {
			ptr = rhs.ptr;
			return *this;
		}

		// ? or this ? //todo
        reference operator*() {
            return *(this->ptr);
        }

        pointer operator->() {
		    return &(this->ptr);
		}

		// const -> * todo


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
        friend class NodeList<T>; // todo

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

		NodeList<value_type>* shadow;
		NodeList<value_type>* start;
        NodeList<value_type>* finish;
        int currentSize;


    public:
    	List() : shadow(new NodeList<value_type>()), start(nullptr), finish(nullptr), currentSize(0) {}

    	iterator begin() {
    		return shadow->next;
    	}

		iterator end() {
			return shadow;
		}

    	void push_back(value_type const &value) {
    		//todo use insert
			insert(finish, value);
    	}

    	void push_front(value_type const &value) {
            insert(start, value);
    	}

    	// single element
        iterator insert(iterator position, const value_type& val) {
            NodeList<value_type> *insert_node = new NodeList<value_type>();
            insert_node->value = val;
            if (currentSize == 0) {
                shadow->next = insert_node;
                shadow->prev = insert_node;
                insert_node->next = shadow;
                insert_node->prev = shadow;
            } else {
                NodeList<value_type> *pos = position.ptr;
                insert_node->next = pos;
                insert_node->prev = pos->prev;
                insert_node->prev->next = insert_node;
                insert_node->next->prev = insert_node;
            }
            ++currentSize;
            return iterator(insert_node);
    	}

    	// fill
        void insert(iterator position, size_type n, const value_type& val) {

    	}

    	// range
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last) {

    	}

	};
}
