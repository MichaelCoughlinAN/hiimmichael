/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a pointer-based implementation of the ADT binary
 *  tree.
 *
 *  Adapted from page 460 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2014 Mar 19
 *
 *  @version 6.0 */

#ifndef _BINARY_NODE_TREE
#define _BINARY_NODE_TREE

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcep.h"
#include "NotFoundException.h"

#include <climits>
#include <limits>

/** @class BinaryNodeTree BinaryNodeTree.h "BinaryNodeTree.h"
 *
 *  Specification of a link-based ADT binary tree. */
template <typename ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType> {
 private:
  BinaryNode<ItemType>* rootPtr;

 protected:
  //------------------------------------------------------------
  // Protected Utility Methods Section:
  // Recursive helper methods for the public methods.
  //------------------------------------------------------------

  int getHeightHelper(BinaryNode<ItemType>* subTreePtr) const;

  int getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const;

  // Recursively deletes all nodes from the tree.
  void destroyTree(BinaryNode<ItemType>* subTreePtr);

  // Recursively adds a new node to the tree in a left/right fashion to
  // keep the tree balanced.
  BinaryNode<ItemType>* balancedAdd(BinaryNode<ItemType>* subTreePtr,
				    BinaryNode<ItemType>* newNodePtr);

  // Removes the target value from the tree by calling moveValuesUpTree
  // to overwrite value with value from child.
  BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr,
				    const ItemType target,
				    bool& success);

  // Copies values up the tree to overwrite value in current node until
  // a leaf is reached; the leaf is then removed, since its value is
  // stored in the parent.
  BinaryNode<ItemType>* moveValuesUpTree(BinaryNode<ItemType>* subTreePtr);

  // Recursively searches for target value in the tree by using a
  // preorder traversal.
  BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr,
				 const ItemType& target,
				 bool& success) const;

  // Copies the tree rooted at treePtr and returns a pointer to
  // the copy.
  BinaryNode<ItemType>* copyTree(BinaryNode<ItemType>* treePtr) const;

  // Recursive traversal helper methods:
  void preorder(void visit(ItemType&),
		BinaryNode<ItemType>* treePtr);
  void inorder(void visit(ItemType&),
	       BinaryNode<ItemType>* treePtr);
  void postorder(void visit(ItemType&),
		 BinaryNode<ItemType>* treePtr);

  // Tools for manipulating BinaryNodes:

  void setItem(BinaryNode<ItemType>* nodePtr,
	       const ItemType& anItem);

  ItemType getItem(const BinaryNode<ItemType>* nodePtr) const;

  bool isLeaf(const BinaryNode<ItemType>* nodePtr) const;

  BinaryNode<ItemType>* getLeftChildPtr(const BinaryNode<ItemType>* nodePtr) const;
  BinaryNode<ItemType>* getRightChildPtr(const BinaryNode<ItemType>* nodePtr) const;

  void setLeftChildPtr(BinaryNode<ItemType>* nodePtr,
		       BinaryNode<ItemType>* leftPtr);
  void setRightChildPtr(BinaryNode<ItemType>* nodePtr,
			BinaryNode<ItemType>* rightPtr);

  BinaryNode<ItemType>* getRootPtr() const;
  void setRootPtr(BinaryNode<ItemType>* newRootPtr);

  BinaryNode<ItemType>* createNewNode(const ItemType& anItem,
				      BinaryNode<ItemType>* leftPtr = nullptr,
				      BinaryNode<ItemType>* rightPtr = nullptr) const;
 
  void flipTree(BinaryNode<ItemType>* nodePtr);
  bool isBinTreeHelper(BinaryNode<ItemType>* nodePtr, int min, int max);
  ItemType minHelper(BinaryNode<ItemType>* nodePtr)
    throw(PrecondViolatedExcep);
  ItemType maxHelper(BinaryNode<ItemType>* nodePtr)
    throw(PrecondViolatedExcep);
  void printRootToLeafPathsHelper(BinaryNode<ItemType>* nodePtr,
				  ItemType pathArray[],
				  int count);
  void printArray(ItemType pathArray[], int count);
  bool addArray(int pathArray[], int count, int sum);
  void doesSomePathHaveSum(BinaryNode<ItemType>* nodePtr, int pathArray[], int count, int sum);
 public:
  //------------------------------------------------------------
  // Constructor and Destructor Section.
  //------------------------------------------------------------
  BinaryNodeTree();
  BinaryNodeTree(const ItemType& rootItem);
  BinaryNodeTree(const ItemType& rootItem,
		 const BinaryNodeTree<ItemType>* leftTreePtr,
		 const BinaryNodeTree<ItemType>* rightTreePtr);
  BinaryNodeTree(const BinaryNodeTree<ItemType>& tree);

  virtual ~BinaryNodeTree();

  //------------------------------------------------------------
  // Public BinaryTreeInterface Methods Section.
  //------------------------------------------------------------
  virtual bool isEmpty() const;

  virtual int getHeight() const;

  virtual int getNumberOfNodes() const;

  virtual ItemType getRootData() const
    throw(PrecondViolatedExcep);

  virtual void setRootData(const ItemType& newData);

  virtual bool add(const ItemType& newData);

  virtual bool remove(const ItemType& data);

  virtual void clear();

  virtual ItemType getEntry(const ItemType& anEntry) const
    throw(NotFoundException);

  virtual bool contains(const ItemType& anEntry) const;

  //------------------------------------------------------------
  // Public Traversals Section.
  //------------------------------------------------------------
  virtual void preorderTraverse(void visit(ItemType&) );
  virtual void inorderTraverse(void visit(ItemType&) );
  virtual void postorderTraverse(void visit(ItemType&) );
  
  void flip();
  bool isBinTree();
  ItemType minValue();
  ItemType maxValue();
  void printPaths();
  void pathSum(int sum);
  //------------------------------------------------------------
  // Overloaded Operator Section.
  //------------------------------------------------------------
  BinaryNodeTree& operator=(const BinaryNodeTree& rhs);
};

#include "BinaryNodeTree.cpp"

#endif
