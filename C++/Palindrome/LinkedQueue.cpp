/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Implementation file for a pointer-based implementation of the ADT
 *  queue.
 *
 *  Adapted from page 402-4 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Jan 23
 *
 *  @version 6.0 */

#include <new>

using namespace std;

template <typename ItemType>
LinkedQueue<ItemType>::LinkedQueue()
  : backPtr(nullptr),
    frontPtr(nullptr) {
    }

template <typename ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue<ItemType>& aQueue) {

  if (aQueue.frontPtr == nullptr) {
    frontPtr = nullptr;
    backPtr = nullptr;
  }
  else {
    Node<ItemType>* aQueuePtr = aQueue.frontPtr;

    try {
      frontPtr = new Node<ItemType>();
      frontPtr->setItem(aQueuePtr->getItem() );

      Node<ItemType>* thisQueuePtr = frontPtr;

      aQueuePtr = aQueuePtr->getNext();

      while (aQueuePtr != nullptr) {
	ItemType nextItem = aQueuePtr->getItem();

	Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

	thisQueuePtr->setNext(newNodePtr);

	thisQueuePtr = thisQueuePtr->getNext();

	aQueuePtr = aQueuePtr->getNext();
      }

      thisQueuePtr->setNext(nullptr);
    }
    catch (const bad_alloc&) {
      while (!isEmpty() ) {
	dequeue();
      }
      throw;
    }
  }
}

template <typename ItemType>
LinkedQueue<ItemType>::~LinkedQueue() {

  while (!isEmpty() ) {
    dequeue();
  }
}

template <typename ItemType>
bool LinkedQueue<ItemType>::isEmpty() const {

  return frontPtr == nullptr;
}

template <typename ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry) {

  bool ableToEnqueue = true;

  try {
    Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

    if (isEmpty() ) {
      frontPtr = newNodePtr;
    }
    else {
      backPtr->setNext(newNodePtr);
    }

    backPtr = newNodePtr;
  }
  catch (const bad_alloc&) {
    ableToEnqueue = false;
  }

  return ableToEnqueue;
}

template <typename ItemType>
bool LinkedQueue<ItemType>::dequeue() {

  bool result = false;

  if (!isEmpty() ) {
    Node<ItemType>* nodeToDeletePtr = frontPtr;

    if (frontPtr == backPtr) {
      frontPtr = nullptr;
      backPtr = nullptr;
    }
    else {
      frontPtr = frontPtr->getNext();
    }

    nodeToDeletePtr->setNext(nullptr);
    delete nodeToDeletePtr;
    nodeToDeletePtr = nullptr;

    result = true;
  }

  return result;
}

template <typename ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const
  throw(PrecondViolatedExcep) {

  if (isEmpty() ) {
    throw PrecondViolatedExcep("peekFront() called on an empty queue.");
  }

  return frontPtr->getItem();
}
