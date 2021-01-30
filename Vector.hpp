#pragma once
#include <vector>

namespace ft {
	template<class T>
	class V_iterator {
	public:
		typedef T* pointer;
		typedef T& reference;
		typedef const T* const_pointer;
		typedef const T& const_reference;
		typedef V_iterator iterator;

		V_iterator() throw() {
			ptr = nullptr;
		}

		V_iterator(pointer p) throw() {
			ptr = p;
		}

		V_iterator(V_iterator const &p) throw() {
			*this = p;
		}

		virtual ~V_iterator() throw() {}

		iterator &operator=(V_iterator const &p) throw() {
			ptr = p.ptr;
			return *this;
		}

		iterator &operator++() throw() {
			ptr++;
			return *this;
		}

		iterator operator++(int) throw() {
			V_iterator it = *this;
			++(*this);
			return it;
		}

		iterator &operator--() throw() {
			ptr--;
			return *this;
		}

		iterator operator--(int) throw() {
			iterator it = *this;
			--(*this);
			return it;
		}

		reference operator*() const throw() {
			return *ptr;
		}

		pointer operator->() const throw() {
			return ptr;
		}

		reference operator[](int idx) const throw() {
			return ptr[idx];
		}

		bool operator==(iterator rhs) const throw() {
			return ptr == rhs.ptr;
		}

		bool operator!=(iterator rhs) const throw() {
			return ptr != rhs.ptr;
		}

		iterator operator+(int n) throw() {
			iterator ret(ptr + n);
			return ret;
		}

		iterator operator-(int n) throw() {
			iterator ret(ptr - n);
			return ret;
		}

		iterator operator+=(int n) throw() {
			ptr += n;
			return *this;
		}

		iterator operator-=(int n) throw() {
			ptr -= n;
			return *this;
		}

		bool operator<(iterator const &rhs) {
			return ptr < rhs.ptr;
		}

		bool operator>(iterator const &rhs) {
			return ptr > rhs.ptr;
		}

		bool operator<=(iterator const &rhs) {
			return ptr <= rhs.ptr;
		}

		bool operator>=(iterator const &rhs) {
			return ptr >= rhs.ptr;
		}

	private:
		T*	ptr;
	};

	template<class T> // pass any type and compiler auto generate Vector parametrized with this type
	class Vector {
	public:
		typedef V_iterator<T> iterator;
	public:
		Vector() throw() {
			data = nullptr;
			currentSize = 0;
			capacity = 0;
			Realloc(2);
		}
		Vector(T arr[], int n) throw() {
			data = new T[n];
			for (int i = 0; i < n; i++) {
				data[i] = arr[i];
			}
		}
		~Vector() throw() {
			clear();
			::operator delete(data, capacity * sizeof(T)); // to not call any destructors
		}

		iterator	begin() throw() {
			return iterator(data);
		}

		iterator	end() throw() {
			return iterator(data + currentSize);
		}

		void push_back(const T& val) throw() {
			if (currentSize >= capacity) {
				Realloc(capacity * 2);
			}

			data[currentSize] = val;
			currentSize++;
		}

		void pop_back() throw() {
			if (currentSize > 0) {
				currentSize--;
				data[currentSize].~T();
			}
		}

		void clear() throw() {
			for (size_t i = 0; i < currentSize; i++) {
				data[i].~T();
			}
			currentSize = 0;
		}

		template<class ITER>
		void assign(ITER begin, ITER end) throw() {
			clear();
			while (begin != end) {
				push_back(*begin);
				begin++;
			}
		}

		size_t size() const throw() { return currentSize; }

		const T&	operator[](size_t idx) const throw() {
			return data[idx];
		}

		T&	operator[](size_t idx) throw() {
			return data[idx];
		}

	private:
		void	Realloc(size_t newCapacity) throw() {
			T*	newBlock = (T*)::operator new(newCapacity * sizeof(T)); // we don't want to call a constructor at all

			size_t	allocSize = currentSize;
			if (newCapacity < allocSize) {
				allocSize = newCapacity;
			}

			for (size_t i = 0; i < allocSize; i++) {
				newBlock[i] = data[i];
			}

			for (size_t i = 0; i < currentSize; i++) { // clear, but don't set size to zero
				data[i].~T();
			}

			::operator delete(data, capacity * sizeof(T));
			data = newBlock;
			capacity = newCapacity;
		}

	private:
		T*  data;

		size_t	currentSize;
		size_t	capacity;

	};
}
