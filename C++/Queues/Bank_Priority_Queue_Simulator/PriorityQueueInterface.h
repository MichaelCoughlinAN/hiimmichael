/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  PriorityQueueInterface class template definition.
 *
 *  Not in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Jan 22
 *
 *  @version 6.0 */

#ifndef _PRIORITY_QUEUE_INTERFACE
#define _PRIORITY_QUEUE_INTERFACE

#include "PrecondViolatedExcep.h"

/** @class PriorityQueueInterface PriorityQueueInterface.h "PriorityQueueInterface.h"
 *
 *  Definition of PriorityQueueInterface class template. */
template <typename ItemType>
class PriorityQueueInterface {
 public:

  /** Virtual destructor . */
  virtual ~PriorityQueueInterface() {}

  /** Sees whether this queue is empty.
   *
   *  @return True if the queue is empty, or false if not. */
  virtual bool isEmpty() const = 0;

  /** Adds a new entry to this priority queue.
   *
   *  @pre The template parameter type, ItemType, *must* implement a
   *       full range of relational operator overloads: <, >, <=,
   *       >=, ==, and !=.
   *
   *  @post If successful, newEntry is stored at its correct
   *        position in this priority queue.
   *
   *  @param newEntry The object to be added as a new entry.
   *
   *  @return True if addition was successful, or false if not. */
  virtual bool add(const ItemType& newEntry) = 0;

  /** Removes the front of this priority queue.
   *
   *  @post If successful, the front of this priority queue has been
   *        removed.
   *
   *  @return True if removal was successful, or false if not. */
  virtual bool remove() = 0;

  /** Retrieves the front of this priority queue.
   *
   *  @pre This priority queue is not empty.
   *
   *  @post None.
   *
   *  @return The front entry in this priority queue. */
  virtual ItemType peek() const
    throw(PrecondViolatedExcep) = 0;
};

#endif
