#pragma once
#include <vector>

namespace ft {
	template<class T>
	struct v_iterator {
	public:
		typedef T* pointer;
		typedef T& reference;
		typedef v_iterator iterator;

		v_iterator() {
			ptr = nullptr;
		}

		v_iterator(T* p) {
			ptr = p;
		}

		iterator &operator++() {
			ptr++;
			return *this;
		}

		iterator operator++(int) {
			v_iterator it = *this;
			++(*this);
			return it;
		}

		iterator &operator--() {
			ptr--;
			return *this;
		}

		iterator operator--(int) {
			iterator it = *this;
			--(*this);
			return it;
		}

		reference operator*() const {
			return *ptr;
		}

		reference operator[](int idx) const {
			return ptr[idx];
		}

		bool operator!=(iterator rhs) const {
			return ptr != rhs.ptr;
		}

		T*	ptr;
	};

	template<class T> // pass any type and compiler auto generate Vector parametrized with this type
	class Vector {
	public:
		typedef v_iterator<T> iterator;
	public:
		Vector() {
			data = nullptr;
			currentSize = 0;
			capacity = 0;
			Realloc(2);
		}
		Vector(T arr[], int n) {
			data = new T[n];
			for (int i = 0; i < n; i++) {
				data[i] = arr[i];
			}
		}
		~Vector() {
			clear();
			::operator delete(data, capacity * sizeof(T)); // to not call any destructors
		}

		iterator	begin() {
			return iterator(data);
		}

		iterator	end() {
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
