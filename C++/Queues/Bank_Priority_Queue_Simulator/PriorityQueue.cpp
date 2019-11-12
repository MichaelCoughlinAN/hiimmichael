/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Implementation file for a sorted list-based implementation of the
 *  ADT priority queue.
 *
 *  Adapted from page 411-2 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Jan 23
 *
 *  @version 6.0 */

template <typename ItemType>
PriorityQueue<ItemType>::PriorityQueue()
  : sListPtr(new LinkedSortedList<ItemType>() ) {
}

template <typename ItemType>
PriorityQueue<ItemType>::PriorityQueue(const PriorityQueue<ItemType>& pq)
  : sListPtr(new LinkedSortedList<ItemType>(*pq.sListPtr)) {
}

template <typename ItemType>
PriorityQueue<ItemType>::~PriorityQueue() {

  delete sListPtr;
}

template <typename ItemType>
bool PriorityQueue<ItemType>::isEmpty() const {

  return sListPtr->isEmpty();
}

template <typename ItemType>
bool PriorityQueue<ItemType>::add(const ItemType& newEntry) {

  return sListPtr->insertSorted(newEntry);
}

template <typename ItemType>
bool PriorityQueue<ItemType>::remove() {

  return sListPtr->remove(sListPtr->getLength() );
}

template <typename ItemType>
ItemType PriorityQueue<ItemType>::peek() const
  throw(PrecondViolatedExcep) {

  return sListPtr->getEntry(sListPtr->getLength() );
}
