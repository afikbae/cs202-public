/**
* Title: Binary Search Trees
* Author : Mehmet Akif Şahin
* ID: 22203673
* Section : 3
* Homework : 1
* Description : Header file for custom path data structure
*/

#ifndef PATH_H_
#define PATH_H_

class Path {
public:
	Path();
	Path( Path& from );
	~Path();
	Path& operator= ( Path& from );
	void insert( int item );
	void pop();
	int getSum();
	void clear();
	void print();
	void printBackwards();
private:
	typedef struct Node {
		Node* next;
		int item;
	} Node;
	Node* head;
	int sum;
	void printBackwards( Node* node );
	void copy( Node*& to, Node* from );
};

#endif // !PATH_H_
