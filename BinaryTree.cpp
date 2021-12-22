#include "BinaryTree.h"
#include <iostream>
#include <memory>

using namespace std;

//Constructor
BinaryTree::BinaryTree():root(nullptr){
}

//Copy Constructor
BinaryTree::BinaryTree(const BinaryTree& rhs): root(nullptr){
	// Traverse every value of rhs with an iterator and copy them to this Binary Tree
	Iterator i;
	i.Init(rhs);
	while (i.hasNext()){
		insert(i.Next()->value);		
	}
}

//Destructor
// Deletes all nodes recursively
BinaryTree::~BinaryTree(){
	deleteNode(root);

}

// Helps destructor to delete all nodes recursively.
void BinaryTree::deleteNode(TreeNode* & node){
	if(node){
		deleteNode(node->left);
		deleteNode(node->right);
		delete node;
		node = nullptr;
	}
}



void BinaryTree::insert(int num) {
	TreeNode* newNode = nullptr;		       
	TreeNode* tempPtr = nullptr;	
		
	newNode = new TreeNode;	
	newNode->value = num;
	
	if (!root){
		// If Binary tree is empty create root.
		root = newNode;
	}
	else{
		tempPtr = root;
		// while tempPtr is not nullptr
		while (tempPtr){
			if (num > tempPtr->value){
				// Go right 				
				if (tempPtr->right)					
					tempPtr = tempPtr->right;				
				else{					
					tempPtr->right = newNode;					
					break;				
				}			
			}
			else if (num < tempPtr->value){
				// Go left
				if (tempPtr->left){
					tempPtr = tempPtr->left;
				}
				else{
					tempPtr->left = newNode;
					break;
				}
			}
			else{
				cout << "Duplicate value found in tree." << endl;				
				break;			
			}		
		}			
	}
}	


//Operators
//Give the implementations of operators in here either as free function or member function

ostream& operator<<(ostream& os, const BinaryTree & tree){
	TreeNode* tempNode;
	tempNode = tree.root;

	return outstream_helper(os, tempNode) << endl;
}

// "operator << " function calls this function to read the value
ostream& outstream_helper(ostream& os, const TreeNode* tempNode){
	if (tempNode){
		outstream_helper(os, tempNode->left);		
		os << tempNode->value << " ";		
		outstream_helper(os, tempNode->right);	
	}
	return os;
}

BinaryTree & BinaryTree::operator += (int const & rhs){
	// Insert the rhs integer to the lefthand side binary tree
	this->insert(rhs);
	return *this;
}

BinaryTree & BinaryTree::operator += (BinaryTree const & rhs){
	// Copy every element of rhs binary tree to the lefthand side binary tree
	Iterator i;
	i.Init(rhs);
	while (i.hasNext()){
		this->insert(i.Next()->value);
	}
	return *this;
}


BinaryTree & BinaryTree::operator = (BinaryTree const & rhs){
	// if not the same tree
	if(this != &rhs){
		deleteNode(root);
		root = nullptr;
		Iterator i;
		i.Init(rhs);
		// Copy every element of rhs binary tree to the lefthand side binary tree
		while (i.hasNext()){
			this->insert(i.Next()->value);
		}
	}
	return *this;
}

// Returns true if the lhs and rhs tree have the same elements
bool BinaryTree::operator == (BinaryTree const & rhs) const {
	// Create an iterator for lhs and rhs
	Iterator leftIter;
	leftIter.Init(*this);
	Iterator rightIter;
	rightIter.Init(rhs);
	// return false if the size or any corresponding elements is different
	if(leftIter.getSize() != rightIter.getSize()){
		return false;
	}else{
		while(leftIter.hasNext()){
			if(leftIter.Next()->value != rightIter.Next()->value){
				return false;
			}
		}
		return true;
	}
}

bool BinaryTree::operator != (BinaryTree const & rhs) const{
	return !(*this == rhs);
}


BinaryTree operator + (BinaryTree const & rhs, int const & lhs){
	BinaryTree temp(rhs);
	temp.insert(lhs);
	return temp;
}

BinaryTree  operator + (int const & rhs, BinaryTree const & lhs){
	return lhs + rhs;
}





BinaryTree operator + (BinaryTree const & rhs, BinaryTree const & lhs){
	BinaryTree temp(rhs);
	
	temp += lhs;
	return temp;
}



/*
 *  ITERATOR CLASS
 */

//Constructor
Iterator::Iterator(): myCurrent(nullptr), stack(nullptr), treeSize(0){
}

Iterator::~Iterator(){
	delete stack;
	myCurrent = nullptr;
}

void Iterator::Init(const BinaryTree &tree){
	myCurrent = tree.root;
	stack = new Stack();
	InitHelper(myCurrent);
}

void Iterator::InitHelper(TreeNode* tempNode){
	if (tempNode){
		InitHelper(tempNode->right);		
		stack->push(tempNode);
		treeSize++;		
		InitHelper(tempNode->left);		
	}

}

//Returns true if tree has more nodes to explore
bool Iterator::hasNext(){
	return !(stack->isEmpty());
}

//Next node to explore
TreeNode* Iterator::Next(){
	//Note that it returns the next element
	return stack->pop();
}

//Returns size of the tree to simplify comparison
int Iterator::getSize(){
	return treeSize;
}

