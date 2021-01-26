#pragma once
#include "List.hpp"

template <typename T>
struct d_lst {
	T				*content;
	struct d_lst 	*next;
	struct d_lst 	*prev;
};

namespace ft {
	template <class T>
	class BidirectionalListIt {
	public:
		typedef BidirectionalListIt< List<T> > iterator;
		typedef T*					pointer;
		typedef const T*			constPointer;
		typedef T&					reference;
		typedef const T&			constReference;

		BidirectionalListIt() : ptr(NULL) {}
		explicit BidirectionalListIt(pointer p) : ptr(p) {}

		iterator	begin() {
			return BidirectionalListIt();
		}
		iterator	end() {

		}
	private:
		pointer ptr;
	};
}
