/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a pointer-based implementation of the ADT stack.
 *
 *  Adapted from page 246 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Nov 27
 *
 *  @version 6.0 */

#ifndef _LINKED_STACK
#define _LINKED_STACK

#include "StackInterface.h"
#include "Node.h"

/** @class LinkedStack LinkedStack.h "LinkedStack.h"
 *
 *  Specification of a pointer-based ADT stack. */
template <typename ItemType>
class LinkedStack : public StackInterface<ItemType> {
 private:
  Node<ItemType>* topPtr;

 public:
  LinkedStack();

  LinkedStack(const LinkedStack<ItemType>& aStack);

  virtual ~LinkedStack();

  virtual bool isEmpty() const;

  virtual bool push(const ItemType& newEntry);

  virtual bool pop();

  virtual ItemType peek() const;
};

#include "LinkedStack.cpp"

#endif
