/**
* Title: Hash Table
* Author : Mehmet Akif Şahin
* ID: 22203673 
* Section : 3
* Homework : 3
* Description : HashTable class implementation file
*/

#include "HashTable.h"

HashTable::HashTable ( int cap ) {
	size = 0;
	this->cap = cap;
	table = new Bucket[ cap ];
	for ( int i = 0; i < cap; i++ ) {
		table[i].head = nullptr;
	}
}

HashTable::HashTable ( const HashTable& from ) {
	table = nullptr;
	*this = from;
}

HashTable::~HashTable () {
	clear();
	delete[] table;
}

HashTable& HashTable::operator= ( const HashTable& from ) {
	clear();
	delete[] table;
	size = from.size;
	cap = from.cap;
	table = new Bucket[ cap ];
	for ( int i = 0; i < cap; i++ ) {
		copyBucket ( table[i], from.table[i] );
	}
	return *this;
}

void HashTable::insert ( const HashTableItem& item ) {
	int itemHash = hash(item);
	Bucket& bucket = table[itemHash];
	insertToBucket ( bucket, item );
}

void HashTable::insert ( const int hash ) {
	Bucket& bucker = table[hash];
	insertToBucket ( bucker, "" );
}

bool HashTable::contains ( const HashTableItem& item ) const {
	int itemHash = hash(item);
	Bucket& bucket = table[itemHash];
	return bucketContains( bucket, item );
}

bool HashTable::contains ( const int hash ) const {
	return table[hash].head != nullptr;
}

Bucket HashTable::get ( const int hash ) const {
	Bucket result;
	result.head = nullptr;
	copyBucket( result, table[hash] );
	return result;
}

void HashTable::clear () {
	for ( int i = 0; i < cap; i++ ) {
		clearBucket( table[i] );
	}
	size = 0;
}

int HashTable::hash ( const HashTableItem& item ) const {
	int result = 0;
	int p = 31;
	for ( int i = item.length() - 1; i >= 0; i-- ) {;
		result *= p;
		result %= cap;
		result += (item[i] | 32) - 'a' + 1;
		result %= cap;
	}
	return result;
}

void HashTable::copyBucket ( Bucket & to, Bucket & from ) const {
	clearBucket ( to );
	if ( from.head == nullptr ) {
		return;
	}
	to.head = new BucketNode;
	to.head->item = from.head->item;
	BucketNode* toNode = to.head;
	BucketNode* fromNode = from.head;
	while ( fromNode->next ) {
		toNode->next = new BucketNode;
		toNode->next->item = fromNode->next->item;
		toNode = toNode->next;
		fromNode = fromNode->next;
	}
}

void HashTable::insertToBucket ( Bucket & to, const HashTableItem& item ) {
	BucketNode * node = to.head;
	if ( node ) {
		while ( node->next ) node = node->next;
		node->next = new BucketNode;
		node = node->next;
	} else {
		to.head = new BucketNode;
		node = to.head;
	}
	node->item = item;
	node->next = nullptr;
}

bool HashTable::bucketContains ( const Bucket& bucket, const HashTableItem& item ) const {
	BucketNode * node = bucket.head;
	while ( node ) {
		if ( node->item == item ) {
			return true;
		}
		node = node->next;
	}
	return false;
}

void HashTable::clearBucket ( Bucket& bucket ) const {
	deleteNodes ( bucket.head );
	bucket.head = nullptr;
}

void HashTable::deleteNodes ( BucketNode *& node ) const {
	if ( node ) deleteNodes ( node->next );
	delete node;
}
