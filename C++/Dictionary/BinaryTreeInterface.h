/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  BinaryTreeInterface class template definition.
 *
 *  Adapted from page 441-2 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Jan 30
 *
 *  @version 6.0 */

#ifndef _BINARY_TREE_INTERFACE
#define _BINARY_TREE_INTERFACE

#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"

/** @class BinaryTreeInterface BinaryTreeInterface.h "BinaryTreeInterface.h"
 *
 *  Definition of BinaryTreeInterface class template. */
template <typename ItemType>
class BinaryTreeInterface {
 public:

  /** Sees whether this binary tree is empty.
   *
   *  @return True if this binary tree is empty, or false if not. */
  virtual bool isEmpty() const = 0;

  /** Gets the height of this binary tree.
   *
   *  @return The height of this binary tree. */
  virtual int getHeight() const = 0;

  /** Gets the number of nodes in this binary tree.
   *
   *  @return The number of nodes in this binary tree. */
  virtual int getNumberOfNodes() const = 0;

  /** Gets the data stored in the root of this binary tree.
   *
   *  @pre This binary tree is not empty.
   *
   *  @post None.
   *
   *  @return The data stored in the root of this binary tree.
   *
   *  @throw PrecondViolatedExcep If the precondition is violated. */
  virtual ItemType getRootData() const
    throw(PrecondViolatedExcep) = 0;

  /** Replaces the data stored in the root of this binary tree with
   *  the given data, if this binary tree is not empty. However, if
   *  this binary tree is empty, then insert a new node containing
   *  the given data into the root of this binary tree.
   *
   *  @pre None.
   *
   *  @post The data in the root of this binary tree is the given
   *        data.
   *
   *  @param newData The given data. */
  virtual void setRootData(const ItemType& newData) = 0;

  /** Inserts a new node containingthe given data into this binary
   *  tree.
   *
   *  @pre None.
   *
   *  @post This binary tree contains a new node containing the given
   *        data.
   *
   *  @param newData The data for the new node.
   *
   *  @return True if insertion was successful, or false if not. */
  virtual bool add(const ItemType& newData) = 0;

  /** Removes the node containing data from this binary tree.
   *
   *  @pre None.
   *
   *  @post A node containing data is no longer in this binary tree.
   *
   *  @param data The data value to remove from this binary tree.
   *
   *  @return True if removal was successful, or false if not. */
  virtual bool remove(const ItemType& data) = 0;

  /** Removes all nodes from this binary tree.
   *
   *  @post This binary tree contains no nodes;
   *        getNumberOfNodes() == 0. */
  virtual void clear() = 0;

  /** Retrieves a specific entry in this binary tree.
   *
   *  @pre None.
   *
   *  @post None.
   *
   *  @param anEntry The value of the desired entry to retrieve.
   *
   *  @return The entry in this binary tree that matches the given
    *          entry.
    *
    *  @throw NotFoundException If the given entry was not found in
    *         this binary tree. */
  virtual ItemType getEntry(const ItemType& anEntry) const
    throw(NotFoundException) = 0;

  /** Tests whether the given entry occurs in this binary tree.
   *
   *  @pre None.
   *
   *  @post None.
   *
   *  @param anEntry The entry to find.
   *
   *  @return True if the given entry occurs in this binary tree. */
  virtual bool contains(const ItemType& anEntry) const = 0;

  /** Traverses this binary tree in preorder (inorder, postorder) and
   *  calls the function visit once for each node.
   *
   *  @pre None.
   *
   *  @post The function visit has been called once per node. This
   *        call can alter the data stored in this binary tree.
   *
   *  @param visit A client-defined function that will perform some
   *               operation of the data in a node. */
  virtual void preorderTraverse(void visit(ItemType&) ) = 0;
  virtual void inorderTraverse(void visit(ItemType&) ) = 0;
  virtual void postorderTraverse(void visit(ItemType&) ) = 0;
};

#endif
