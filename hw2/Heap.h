/*
* Author : Mehmet Akif Sahin 
* ID: 22203673
* Section : 1
* Homework : 2
* Description : heap class header file
*/

#ifndef HEAP_H_
#define HEAP_H_

template < typename T >
class Heap {
public:
	Heap ( int size );
	Heap ( int size, T* from, int fromSize );
	Heap ( Heap& cpfrom );
	Heap<T>& operator= ( Heap& cpfrom );
	~Heap ();

	int size ();
	bool empty ();
	bool full ();
	T top ();
	void push ( T item );
	void pop ();
	// void printTreeLike(int index, int level, std::string indent) const;
private:
	T* arr;
	int _size, cap;
	bool compare ( T item1, T item2 );
	void heapify ( int index );
};

#include "Heap.cpp"

#endif
