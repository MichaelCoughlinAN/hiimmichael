/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a pointer-based implementation of the ADT queue.
 *
 *  Adapted from page 401-2 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Jan 23
 *
 *  @version 6.0 */

#ifndef _LINKED_QUEUE
#define _LINKED_QUEUE

#include "QueueInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

/** @class LinkedQueue LinkedQueue.h "LinkedQueue.h"
 *
 *  Specification of a pointer-based ADT queue. */
template <typename ItemType>
class LinkedQueue : public QueueInterface<ItemType> {
 private:
  Node<ItemType>* backPtr;
  Node<ItemType>* frontPtr;

 public:
  LinkedQueue();

  LinkedQueue(const LinkedQueue<ItemType>& aQueue);

  virtual ~LinkedQueue();

  virtual bool isEmpty() const;

  virtual bool enqueue(const ItemType& newEntry);

  virtual bool dequeue();

  virtual ItemType peekFront() const
    throw(PrecondViolatedExcep);
};

#include "LinkedQueue.cpp"

#endif
