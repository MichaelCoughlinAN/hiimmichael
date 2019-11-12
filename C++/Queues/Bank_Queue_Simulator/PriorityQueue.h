/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a sorted list-based implementation of the ADT
 *  priority queue.
 *
 *  Adapted from page 411 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Jan 23
 *
 *  @version 6.0 */

#ifndef _PRIORITY_QUEUE
#define _PRIORITY_QUEUE

#include "PriorityQueueInterface.h"
#include "LinkedSortedList.h"
#include "PrecondViolatedExcep.h"

/** @class PriorityQueue PriorityQueue.h "PriorityQueue.h"
 *
 *  Specification of a sorted list-based ADT priority queue. */
template <typename ItemType>
class PriorityQueue : public PriorityQueueInterface<ItemType> {
 private:
  LinkedSortedList<ItemType>* sListPtr;

 public:
  PriorityQueue();

  PriorityQueue(const PriorityQueue<ItemType>& pq);

  virtual ~PriorityQueue();

  virtual bool isEmpty() const;

  virtual bool add(const ItemType& newEntry);

  virtual bool remove();

  virtual ItemType peek() const
    throw(PrecondViolatedExcep);
};

#include "PriorityQueue.cpp"

#endif
