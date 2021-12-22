#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <iostream>
#include "Stack.h"

using namespace std;

class BinaryTree
{
 public:
  //Constructor
  BinaryTree();
  //Copy Constructor - TODO in .cpp file
  BinaryTree(const BinaryTree&);
  //Destructor
  ~BinaryTree();
  
  // Insertion method
  void insert(int);
  
  BinaryTree & BinaryTree::operator += (int const & rhs);
  BinaryTree & BinaryTree::operator += (BinaryTree const & rhs);
  BinaryTree & BinaryTree::operator = (BinaryTree const & rhs);
  bool BinaryTree::operator == (BinaryTree const & rhs) const;
  bool BinaryTree::operator != (BinaryTree const & rhs) const;



private:
  //The root of the tree
  TreeNode* root;
  friend ostream& operator<<(ostream& os, const BinaryTree & tree);
  friend BinaryTree operator + (BinaryTree const & rhs, int const & lhs);
  friend class Iterator;
  void deleteNode(TreeNode* & node);
};

ostream& operator<<(ostream& os, const BinaryTree & tree);
ostream& outstream_helper(ostream& os, const TreeNode* tempNode);
BinaryTree  operator + (BinaryTree const & rhs, int const & lhs);
BinaryTree  operator + (int const & rhs, BinaryTree const & lhs);
BinaryTree operator + (BinaryTree const & rhs, BinaryTree const & lhs);
//BinaryTree operator + (BinaryTree const & rhs, BinaryTree const & lhs);


class Iterator{
public:
  //Constructor
  Iterator();
  ~Iterator();

  void Init(const BinaryTree& );
  bool hasNext();
  TreeNode* Next();
  int getSize();

private:
  TreeNode* myCurrent;
  Stack* stack;
  int treeSize;
  void Iterator::InitHelper(TreeNode* tempNode);

};

#endif
