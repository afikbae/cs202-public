/*
* Author : Mehmet Akif Sahin 
* ID: 22203673
* Section : 1
* Homework : 2
* Description : heap class implementation file
*/

#include "Heap.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

template < typename T >
Heap<T>::Heap ( int _size ) {
	arr = new T[_size];
	cap = _size;
	this->_size = 0;
}

template < typename T >
Heap<T>::Heap ( int _size, T* from, int from_size ) {
	cap = _size;
	this->_size = from_size;

	arr = new T[_size];
	memcpy ( arr, from, from_size * sizeof(T) );
	
	for ( int i = this->_size / 2 - 1; i >= 0; i-- ) {
		heapify(i);
	}
}

template < typename T >
Heap<T>::Heap ( Heap& from ) {
	this->_size = from._size;
	this->cap = from.cap;
	this->arr = new T[ from.cap ];
	memcpy ( this->arr, from.arr, from._size * sizeof(T) );
}

template < typename T >
Heap<T>& Heap<T>::operator= ( Heap& from ) {
	if (this != &from) {
		delete[] this->arr;
		this->_size = from._size;
		this->cap = from.cap;
		this->arr = new T[from.cap];
		memcpy(this->arr, from.arr, from._size * sizeof(T));
	}
	return *this;
}

template < typename T >
Heap<T>::~Heap () {
	delete[] arr;
}

template < typename T >
int Heap<T>::size () {
	return _size;
}

template < typename T >
bool Heap<T>::empty () {
	return _size == 0;
}

template < typename T >
bool Heap<T>::full () {
	return _size == cap;
}

template < typename T >
T Heap<T>::top () {
	if ( empty() ) {
		throw std::runtime_error( "top on empty heap" );
	}
	return arr[0];
}

template < typename T >
void Heap<T>::push ( T item ) {
	if ( full() ) {
		throw std::runtime_error( "push on full heap" );
	}
	int n = _size++;
	arr [ n ] = item;
	int parent = ( n - 1 ) / 2;

	while ( parent >= 0 && compare ( arr [ n ], arr [ parent ] ) ) {
		T temp = arr [ n ];
		arr [ n ] = arr [ parent ];
		arr [ parent ] = temp;
		n = parent;
		parent = ( parent - 1 ) / 2;
	}
}

template < typename T >
void Heap<T>::pop () {
	if ( empty() ) {
		throw std::runtime_error ( "pop on empty heap" );
	}
	arr [ 0 ] = arr [ --_size ];
	heapify( 0 );
}

template < typename T >
bool Heap<T>::compare ( T item1, T item2 ) {
	return item1 > item2;
}

template < typename T >
void Heap<T>::heapify ( int root ) {
	int child = ( root << 1 ) + 1;
	while ( child < _size ) {
		int right = child + 1;

		if ( right < _size && compare( arr [ right ], arr [ child ] ) ) {
			child = right;
		}

		if ( compare( arr [ child ], arr [ root ] ) ) {
			T temp = arr [ child ];
			arr [ child ] = arr [ root ];
			arr [ root ] = temp;
			root = child;
			child = ( root << 1 ) + 1;
		} else {
			break;
		}
	}
}

#include <string>

//template <typename T>
//void Heap<T>::printTreeLike(int index, int level, std::string indent) const {
//    if (index < _size) {
//        printTreeLike((index * 2) + 2, level + 1, indent + "    ");
//        std::cout << indent << arr[index] << std::endl;
//        printTreeLike((index * 2) + 1, level + 1, indent + "    "); 
//    }
//}
