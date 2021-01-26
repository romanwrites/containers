#pragma once
#include <vector>

template<class T> // pass any type and compiler auto generate Vector parametrized with this type
class Vector {
public:
    Vector() {
        Realloc(2);
    }
    Vector(T arr[], int n) {
        data = new T[n];
        for (int i = 0; i < n; i++) {
            data[i] = arr[i];
        }
    }

    void push_back(const T& val) throw() {
    	if (currentSize >= capacity) {
    		Realloc(capacity * 2);
    	}

    	data[currentSize] = val;
    	currentSize++;
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
    	T*	newBlock = new T[newCapacity];

    	size_t	allocSize = currentSize;
    	if (newCapacity < allocSize) {
			allocSize = newCapacity;
    	}

    	for (size_t i = 0; i < allocSize; i++) {
    		newBlock[i] = data[i];
    	}

    	delete[] data;
    	data = newBlock;
    	capacity = newCapacity;
    }

private:
    T*  data = nullptr;

    size_t	currentSize = 0;
    size_t	capacity = 0;

};