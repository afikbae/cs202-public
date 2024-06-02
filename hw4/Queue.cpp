/**
* Author : Mehmet Akif Şahin
* ID: 22203673
* Section : 3
* Homework : 4
* Description : Implementation file for queue data structure
*/

#include "Queue.h"
#include <stdexcept>

template< typename T >
Queue<T>::Queue() {
	front = nullptr;
	back = nullptr;
	_size = 0;
}

template< typename T >
Queue<T>::Queue( Queue& cp ) {
	clear();
	copy( front, cp->front );
	_size = cp._size;
}

template< typename T >
Queue<T>::~Queue() {
	clear();
}

template< typename T >
Queue<T>& Queue<T>::operator=( Queue& right ) {
	clear();
	copy( front, right.front );
	_size = right._size;
	return *this;
}

template< typename T > 
void Queue<T>::push( T item ) {
	Node* newItem = new Node;
	*newItem = { item, nullptr };
	if ( front == nullptr ) {
		front = newItem;
		back = newItem;
	} else {
		back->next = newItem;
		back = back->next;
	}
	_size++;
}

template< typename T > 
void Queue<T>::pop() {
	if ( front == nullptr ) {
		throw std::runtime_error( "pop on empty queue" );
	} else {
		auto temp = front;
		front = front->next;
		delete temp;
		_size--;
	}
}

template< typename T >
T Queue<T>::peek() {
	if ( front == nullptr ) {
		throw std::runtime_error( "peek on empty queue" );
	} else {
		return front->item;
	}
}

template< typename T >
int Queue<T>::size() {
	return _size;
}

template< typename T >
void Queue<T>::copy( Node*& to, Node* from ) {
	if ( from == nullptr ) {
		return;
	}
	to = new Node;
	*to = { from->item, nullptr };
	if ( from->next == nullptr ) back = to;
	copy( to->next, from->next );
}

template< typename T >
void Queue<T>::clear() {
	_size = 0;
	Node* temp;
	while ( front != nullptr ) {
		temp = front;
		front = front->next;
		delete temp;
		
	}
}
