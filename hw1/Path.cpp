/**
* Title: Binary Search Trees
* Author : Mehmet Akif Şahin
* ID: 22203673
* Section : 3
* Homework : 1
* Description : Implementation file for custom path data structure
*/

#include "Path.h"
#include <stdexcept>
#include <iostream>

Path::Path() {
	sum = 0;
	head = nullptr;
}

Path::Path( Path& from ) {
	clear();
	copy( head, from.head );
	sum = from.sum;
}

Path::~Path() {
	clear();
}

Path& Path::operator= ( Path& from ) {
	clear();
	copy( head, from.head );
	sum = from.sum;
	return *this;
}

void Path::insert( int item ) {
	head = new Node{ head, item };
	sum += item;
}

void Path::pop() {
	if ( head == nullptr ) {
		throw std::runtime_error("pop on empty path");
	}
	auto temp = head;
	head = head->next;
	sum -= temp->item;
	delete temp;
}

int Path::getSum() {
	return sum;
}

void Path::clear() {
	while (head) {
		auto temp = head;
		head = head->next;
		delete temp;
	}
	sum = 0;
}

void Path::print() {
	auto temp = head;
	while ( temp ) {
		std::cout << temp->item << ", ";
		temp = temp->next;
	}
}

void Path::printBackwards() {
	if ( head ) {
		printBackwards( head->next );
		std::cout << head->item << std::endl;
	}
}

void Path::printBackwards( Node* node ) {
	if (node) {
		printBackwards( node->next );
		std::cout << node->item << ", ";
	}
}

void Path::copy( Node*& to, Node* from ) {
	if ( from == nullptr ) {
		return;
	}
	to = new Node{ nullptr, from->item };
	copy( to->next, from->next );
}
