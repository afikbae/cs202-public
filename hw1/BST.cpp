/**
* Title: Binary Search Trees
* Author : Mehmet Akif Şahin
* ID: 22203673 
* Section : 3
* Homework : 1
* Description : Implementation file of Binary Search Tree class
*/

#include "BST.h"
#include "Queue.cpp"
#include <iostream>
#include <limits.h>

BST::BST( int keys[], int input_size ) {
	root = nullptr;
	size = 0;
	if ( input_size > 0 ) {
		for ( int i = 0; i < input_size; i++ ) {
			insertKey( keys[i], false );
		}
	}
	std::cout << "BST with size " << input_size << " is created." << std::endl;
}

BST::~BST() {
	clear( root );
}

void BST::clear( TreeNode* node ) {
	if ( node == nullptr ) return;
	clear( node->left );
	clear( node->right );
	delete node;
}

BST::TreeNode*& BST::find( int key ) {
	return find( key, root );
}

BST::TreeNode*& BST::find( int key, BST::TreeNode*& node ) {
	if ( node == nullptr || node->item == key ) {
		return node;
	} else if ( node->item > key ) {
		return find ( key, node->left );
	} else {
		return find ( key, node->right );
	}
}

BST::TreeNode*& BST::find( int key, BST::TreeNode*& node, Path& path ) {
	if ( node ) {
		path.insert( node->item );
	}
	if ( node == nullptr || node->item == key ) {
		return node;
	} else if ( node->item > key ) {
		return find ( key, node->left, path );
	} else {
		return find ( key, node->right, path );
	}
}

BST::TreeNode*& BST::findLeftmost( BST::TreeNode*& node ) {
	if ( node->left == nullptr ) return node;
	else return findLeftmost( node->left );
}

void BST::insertKey( int key ) {
	insertKey( key, true );
}

void BST::insertKey( int key, bool verbose ) {
	TreeNode *& ptr = find( key );
	if (ptr) {
		if ( verbose )
			std::cout << "Key " << key << " is not added. It exists!" << std::endl;
		return;
	}
	ptr = new BST::TreeNode;
	*ptr = { nullptr, nullptr, key };
	size++;
	if ( verbose )
		std::cout << "Key " << key << " is added." << std::endl;
}

void BST::deleteKey( int key ) {
	TreeNode *& ptr = find ( key );
	if ( !ptr ) {
		std::cout << "Key " << key << " is not deleted. It does not exist!" << std::endl;
		return;
	}
	size--;
	if ( ptr->left == nullptr && ptr->right == nullptr ) {
		delete ptr;
		ptr = nullptr;
		return;
	}
	if ( ptr->left == nullptr && ptr->right != nullptr ) {
		TreeNode* temp = ptr;
		ptr = ptr->right;
		delete temp;
		return;
	}
	if ( ptr->left != nullptr && ptr->right == nullptr ) {
		TreeNode* temp = ptr;
		ptr = ptr->left;
		delete temp;
		return;
	}

	TreeNode *& succ = findLeftmost( ptr->right );
	ptr->item = succ->item;
	delete succ;
	succ = nullptr;
	std::cout << "Key " << key << " is deleted." << std::endl;
}

void BST::displayInorder() {
	std::cout << "Inorder display is: ";
	int lastTerm;
	int displayed = 0;
	displayInorder( root, displayed, lastTerm);
	std::cout << lastTerm << std::endl;
}

void BST::displayInorder( TreeNode* node, int& displayedSoFar, int& lastTerm ) {
	if (node) {
		if ( displayedSoFar == size - 1 ) {
			lastTerm = node->item;
			return;
		}
		displayInorder(node->left, displayedSoFar, lastTerm);
		std::cout << node->item << ", ";
		displayedSoFar++;
		displayInorder(node->right, displayedSoFar, lastTerm);
	}
}

void BST::findFullBTLevel() {
	Queue< TreeNode* > level;
	Queue< TreeNode* > nextLevel;
	level.push( root );
	int fullBTLevel = 1;
	bool isFull = true;
	while ( level.size() > 0 ) {
		TreeNode* node = level.peek();
		level.pop();
		if ( node->left != nullptr ) nextLevel.push( node->left );
		else isFull = false;
		if ( node->right != nullptr ) nextLevel.push( node->right );
		else isFull = false;
		if ( level.size() == 0 && isFull ) {
			fullBTLevel++;
			level = nextLevel;
			nextLevel.clear();
		}
	}
	std::cout << "Full binary tree level is: " << fullBTLevel << std::endl;
}

void BST::lowestCommonAncestor( int A, int B ) {
	lowestCommonAncestor( root, A, B, true );
}

BST::TreeNode* BST::lowestCommonAncestor( BST::TreeNode* node, int A, int B, bool verbose) {
	if ( node == nullptr ) return nullptr;
	if ( node->item > A && node->item > B ) {
		return lowestCommonAncestor( node->left, A, B, verbose );
	} else if ( node->item < A && node->item < B ) {
		return lowestCommonAncestor( node->right, A, B, verbose );
	} else {
		if ( verbose )
			std::cout << "Lowest common ancestor of " << A << " and " << B << " is: " << node->item << std::endl;
		return node;
	}
}

void BST::maximumSumPath() {
	Path path, max_path;
	maximumSumPath( root, path, max_path );
	std::cout << "Maximum sum path is: ";
	max_path.printBackwards();
}

void BST::maximumSumPath( TreeNode* node, Path& path, Path& max_path ) {
	if ( node == nullptr ) {
		if ( path.getSum() > max_path.getSum() ) {
			max_path.clear();
			max_path = path;
		}
		return;
	}
	path.insert( node->item );
	maximumSumPath( node->left, path, max_path );
	maximumSumPath( node->right, path, max_path );
	path.pop();
}

void BST::maximumWidth() {
	Queue< TreeNode* > levelQ;
	Queue< TreeNode* > nextLevel;
	levelQ.push( root );
	Queue< TreeNode* > maxLevel;
	while ( levelQ.size() > 0 ) {
		auto node = levelQ.peek();
		levelQ.pop();
		if ( node->left ) nextLevel.push( node->left );
		if ( node->right ) nextLevel.push( node->right );
		if ( levelQ.size() == 0 ) {
			if ( nextLevel.size() > maxLevel.size() ) {
				maxLevel.clear();
				maxLevel = nextLevel;
			}
			levelQ = nextLevel;
			nextLevel.clear();
		}
	}
	std::cout << "Maximum level is: ";
	while ( maxLevel.size() > 1 ) {
		std::cout << maxLevel.peek()->item << ", ";
		maxLevel.pop();
	}
	std::cout << maxLevel.peek()->item << std::endl;
	maxLevel.clear();
}

void BST::pathFromAtoB( int A, int B ) {
	TreeNode* lca = lowestCommonAncestor( root, A, B, false );
	Path pathToA;
	Path pathToB;
	find( A, lca->item > A ? lca->left : lca->right, pathToA );
	find( B, lca->item > B ? lca->left : lca->right, pathToB );
	std::cout << "Path from " << A << " to " << B << " is: ";
	pathToA.print();
	std::cout << lca->item << ", ";
	pathToB.printBackwards();
}

int BST::getHeight() {
	return getHeight( root );
}

int BST::getHeight( TreeNode* node ) {
	if ( !node ) return 0;
	return std::max( getHeight( node->left ), getHeight( node->right ) ) + 1;
}

//int main () {
//	int keys[] = { 10, 7, 20, 5, 6, 15, 21, 2, 12, 18, 24, 3, 19 };
//	int size = 13;
//	BST bst ( keys, size );
//	bst.findFullBTLevel();
//	bst.lowestCommonAncestor( 3, 9 );
//	bst.lowestCommonAncestor( 12, 15 );
//	bst.maximumSumPath();
//	bst.maximumWidth();
//	bst.pathFromAtoB( 2, 21 );
//	bst.insertKey( 8 );
//	bst.insertKey( 7 );
//	bst.deleteKey( 10 );
//	bst.deleteKey( 11 );
//	bst.displayInorder();
//
//	return 0;
//}
