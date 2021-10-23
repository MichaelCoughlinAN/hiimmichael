/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Implementation file for a pointer-based implementation of the ADT
 *  stack.
 *
 *  Adapted from page 246-8 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Nov 27
 *
 *  @version 6.0 */

template <typename ItemType>
LinkedStack<ItemType>::LinkedStack()
  : topPtr(nullptr) {
}

template <typename ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack) {

  if (aStack.topPtr == nullptr) {
    topPtr = nullptr;
  }
  else {
    Node<ItemType>* origStackPtr = aStack.topPtr;

    try {
      topPtr = new Node<ItemType>();
      topPtr->setItem(origStackPtr->getItem() );

      Node<ItemType>* newChainPtr = topPtr;

      origStackPtr = origStackPtr->getNext();

      while (origStackPtr != nullptr) {
	ItemType nextItem = origStackPtr->getItem();

	Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

	newChainPtr->setNext(newNodePtr);

	newChainPtr = newChainPtr->getNext();

	origStackPtr = origStackPtr->getNext();
      }

      newChainPtr->setNext(nullptr);
    }
    catch(const bad_alloc&) {
      while (!isEmpty() ) {
	pop();
      }
      throw;
    }
  }
}

template <typename ItemType>
LinkedStack<ItemType>::~LinkedStack() {

  while (!isEmpty() ) {
    pop();
  }
}

template <typename ItemType>
bool LinkedStack<ItemType>::isEmpty() const {

  return topPtr == nullptr;
}

template <typename ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem) {

  bool result = true;

  try {
    Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);

    topPtr = newNodePtr;

    newNodePtr = nullptr;
  }
  catch(const bad_alloc&) {
    result = false;
  }

  return result;
}

template <typename ItemType>
bool LinkedStack<ItemType>::pop() {

  bool result = false;

  if (!isEmpty() ) {
    Node<ItemType>* nodeToDeletePtr = topPtr;

    topPtr = topPtr->getNext();

    nodeToDeletePtr->setNext(nullptr);
    delete nodeToDeletePtr;
    nodeToDeletePtr = nullptr;

    result = true;
  }

  return result;
}

template <typename ItemType>
ItemType LinkedStack<ItemType>::peek() const
  throw(PrecondViolatedExcep) {

  if (isEmpty() ) {
    throw PrecondViolatedExcep("LinkedStack::peek() called on an empty stack.");
  }

  return topPtr->getItem();
}
