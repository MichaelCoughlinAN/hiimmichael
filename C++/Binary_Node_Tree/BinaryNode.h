/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a node in the pointer-based implementation of the
 *  ADT binary tree.
 *
 *  Adapted from page 458 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Feb 07
 *
 *  @version 6.0 */

#ifndef _BINARY_NODE
#define _BINARY_NODE

/** @class BinaryNode BinaryNode.h "BinaryNode.h"
 *
 *  Specification of a node for a link-based ADT binary tree. */
template <typename ItemType>
class BinaryNode {
 private:
  ItemType item;

  BinaryNode<ItemType>* leftChildPtr;
  BinaryNode<ItemType>* rightChildPtr;

  BinaryNode();
  BinaryNode(const ItemType& anItem,
	     BinaryNode<ItemType>* leftPtr = nullptr,
	     BinaryNode<ItemType>* rightPtr = nullptr);

   template <typename FriendItemType>
     friend class BinaryNodeTree;

};

#include "BinaryNode.cpp"

#endif
