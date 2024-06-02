/**
* Title: Hash Table
* Author : Mehmet Akif Şahin
* ID: 22203673 
* Section : 3
* Homework : 3
* Description : HashTable class header file
*/

#include <string>

typedef std::string HashTableItem;

typedef struct BucketNode {
	HashTableItem item;
	BucketNode* next;
} BucketNode;

typedef struct Bucket {
	BucketNode* head;
} Bucket;

class HashTable {
public:
	HashTable ( int cap ); 
	HashTable ( const HashTable& );
	~HashTable ();
	HashTable& operator= ( const HashTable& );
	void insert ( const HashTableItem& item );
	void insert ( const int hash );
	bool contains ( const HashTableItem& item ) const;
	bool contains ( const int hash ) const;
	Bucket get ( const int hash ) const;
	void clear ();
private:
	int size;
	int cap;
	Bucket* table;
	int hash ( const HashTableItem& item ) const ;
	void copyBucket ( Bucket & to, Bucket & from ) const ;
	void insertToBucket ( Bucket & to, const HashTableItem& item );
	bool bucketContains ( const Bucket& bucket, const HashTableItem& item ) const ;
	void clearBucket ( Bucket& bucket ) const ;
	void deleteNodes ( BucketNode*& node ) const ;
};
