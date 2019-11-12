/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a pointer-based implementation of the ADT binary
 *  search tree.
 *
 *  Adapted from page 482 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2014 Mar 19
 *
 *  @version 6.0 */

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"

template <typename ItemType>
class BinarySearchTree : private BinaryNodeTree<ItemType> {
 protected:
  //------------------------------------------------------------
  // Protected Utility Methods Section:
  // Recursive helper methods for the public methods.
  //------------------------------------------------------------
  // Recursively finds where the given node should be placed and
  // inserts it in a leaf at that point.
  BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr,
				      BinaryNode<ItemType>* newNode);

  // Removes the given target value from the tree while maintaining a
  // binary search tree.
  BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr,
				    const ItemType target,
				    bool& success);

  // Removes a given node from a tree while maintaining a
  // binary search tree.
  BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>* nodePtr);

  // Removes the leftmost node in the left subtree of the node
  // pointed to by nodePtr.
  // Sets inorderSuccessor to the value in this node.
  // Returns a pointer to the revised subtree.
  BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* subTreePtr,
					   ItemType& inorderSuccessor);

  // Returns a pointer to the node containing the given value,
  // or nullptr if not found.
  BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr,
				 const ItemType& target) const;

  // Required with alternate removeNode implementation:
  // ItemType findSuccessorValue(BinaryNode<ItemType>* subTreePtr);

  // Recursive traversal helper methods:
  void preorder(void visit(const ItemType&),
		const BinaryNode<ItemType>* const treePtr) const;
  void inorder(void visit(const ItemType&),
	       const BinaryNode<ItemType>* const treePtr) const;
  void postorder(void visit(const ItemType&),
		 const BinaryNode<ItemType>* const treePtr) const;

 public:
  //------------------------------------------------------------
  // Constructor and Destructor Section.
  //------------------------------------------------------------
  BinarySearchTree();
  BinarySearchTree(const ItemType& rootItem);
  BinarySearchTree(const BinarySearchTree<ItemType>& tree);

  virtual ~BinarySearchTree();

  //------------------------------------------------------------
  // Public Methods Section.
  //------------------------------------------------------------
  virtual bool isEmpty() const;

  virtual int getHeight() const;

  virtual int getNumberOfNodes() const;

  virtual ItemType getRootData() const
    throw(PrecondViolatedExcep);

  // Remove setRootData so that it is privately inherited.
  // virtual void setRootData(const ItemType& newData) const
  //    throw(PrecondViolatedExcep);

  virtual bool add(const ItemType& newEntry);

  virtual bool remove(const ItemType& anEntry);

  virtual void clear();

  virtual ItemType getEntry(const ItemType& anEntry) const
    throw(NotFoundException);

  virtual bool contains(const ItemType& anEntry) const;

  //------------------------------------------------------------
  // Public Traversals Section.
  //------------------------------------------------------------
  void preorderTraverse(void visit(const ItemType&) ) const;
  void inorderTraverse(void visit(const ItemType&) ) const;
  void postorderTraverse(void visit(const ItemType&) ) const;

  //------------------------------------------------------------
  // Overloaded Operator Section.
  //------------------------------------------------------------
  BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rhs);
 
  template <typename KeyType, typename FriendItemType>
  friend class ArrayDictionary;

};

#include "BinarySearchTree.cpp"

#endif
