/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a pointer-based implementation of the ADT list.
 *
 *  Adapted from page 273 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *  @date 2013 Jan 17
 *  @version 6.0 */

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "ListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

/** @class LinkedList LinkedList.h "LinkedList.h"
 *
 *  Specification of a pointer-based ADT list. */
template <typename ItemType>
class LinkedList : public ListInterface<ItemType> {
 private:
  Node<ItemType>* headPtr;

  int itemCount;

  Node<ItemType>* getNodeAt(const int position) const;

 public:
  LinkedList();

  LinkedList(const LinkedList<ItemType>& aList);

  virtual ~LinkedList();

  virtual bool isEmpty() const;

  virtual int getLength() const;

  virtual bool insert(const int newPosition,
		      const ItemType& newEntry);

  virtual bool remove(const int position);

  virtual void clear();

  virtual ItemType getEntry(const int position) const
    throw(PrecondViolatedExcep);

  virtual void setEntry(const int position,
			const ItemType& newEntry)
    throw(PrecondViolatedExcep);
};

#include "LinkedList.cpp"

#endif
