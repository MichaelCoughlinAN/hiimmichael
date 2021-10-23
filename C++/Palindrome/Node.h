/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a node in the linked implementation of the ADT
 *  bag.
 *
 *  Adapted from page 136 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Nov 18
 *
 *  @version 6.0 */

#ifndef _NODE
#define _NODE

template <typename ItemType>
class Node {
 private:
  ItemType item;
  Node<ItemType>* next;

 public:
  Node();
  Node(const ItemType& anItem);
  Node(const ItemType& anItem,
       Node<ItemType>* nextNodePtr);

  void setItem(const ItemType& anItem);
  void setNext(Node<ItemType>* nextNodePtr);

  ItemType getItem() const;
  Node<ItemType>* getNext() const;
};

#include "Node.cpp"

#endif
