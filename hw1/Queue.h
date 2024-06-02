/**
* Title: Binary Search Trees
* Author : Mehmet Akif Şahin
* ID: 22203673
* Section : 3
* Homework : 1
* Description : Header file for queue data structure
*/


#ifndef QUEUE_H_
#define QUEUE_H_
template< typename T >
class Queue {
public:
	Queue();
	Queue(Queue& cp);
	~Queue();
	Queue& operator= ( Queue& right );
	void push( T item );
	void pop();
	T peek();
	int size();
	void clear();
private:
	typedef struct Node {
		T item;
		Node* next;
	} Node;
	Node *front, *back;
	int _size;
	void copy ( Node*& to, Node* from );
};
#endif
