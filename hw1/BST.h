/**
* Title: Binary Search Trees
* Author : Mehmet Akif Şahin
* ID: 22203673 
* Section : 3
* Homework : 1
* Description : Header file of Binary Search Tree class
*/

#ifndef BST_H_
#define BST_H_
#include "Path.h"
class BST {
public:
	BST( int keys[] = {}, int size = 0 );
	~BST();
	
	void insertKey( int key );
	void deleteKey( int key );
	void displayInorder();
	void findFullBTLevel();
	void lowestCommonAncestor( int A, int B );
	void maximumSumPath();
	void maximumWidth();
	void pathFromAtoB( int A, int B );

	void insertKey( int key, bool verbose );
	int getHeight();
private:
	typedef struct TreeNode {
		TreeNode *left, *right;
		int item;
	} TreeNode;
	typedef TreeNode*& TNPR;
	TreeNode* root;
	int size;

	void clear( TreeNode* node );
	TNPR find( int key );
	TNPR find( int key, TNPR node );
	TNPR find( int key, TNPR node, Path& path );
	TNPR findLeftmost( TNPR node );
	void displayInorder( TreeNode* node, int& displayedSoFar, int& lastTerm );
	TreeNode* lowestCommonAncestor( TreeNode* node, int A, int B, bool verbose );
	void maximumSumPath( TreeNode* node, Path& path, Path& max_path );
	int getHeight( TreeNode* node );
};
#endif // !BST_H_
