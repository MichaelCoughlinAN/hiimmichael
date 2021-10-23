/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Implementation file for a pointer-based implementation of the ADT
 *  list.
 *
 *  Adapted from page 274-80 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *  @date 2013 Jan 17
 *  @version 6.0 */

#include <string>
#include <new>

using namespace std;

#include <cassert>

template <typename ItemType>
LinkedList<ItemType>::LinkedList()
   : headPtr(nullptr),
     itemCount(0) {
}

template <typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList) {

   if (aList.headPtr == nullptr) {
      headPtr = nullptr;
   }
   else {
      Node<ItemType>* aListPtr = aList.headPtr;

      try {
         headPtr = new Node<ItemType>();
         headPtr->setItem(aListPtr->getItem() );

         Node<ItemType>* thisListPtr = headPtr;

         aListPtr = aListPtr->getNext();

         while (aListPtr != nullptr) {
            ItemType nextItem = aListPtr->getItem();

            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

            thisListPtr->setNext(newNodePtr);

            thisListPtr = thisListPtr->getNext();

            aListPtr = aListPtr->getNext();
         }

         thisListPtr->setNext(nullptr);
      }
      catch (const bad_alloc&) {
         clear();
         throw;
      }
   }
}

template <typename ItemType>
LinkedList<ItemType>::~LinkedList() {

   clear();
}

template <typename ItemType>
bool LinkedList<ItemType>::isEmpty() const {

   return itemCount == 0;
}

template <typename ItemType>
int LinkedList<ItemType>::getLength() const {

   return itemCount;
}

template <typename ItemType>
bool LinkedList<ItemType>::insert(const int newPosition,
                                  const ItemType& newEntry) {

   bool ableToInsert = newPosition >= 1 &&
      newPosition <= itemCount + 1;

   if (ableToInsert) {
      try {
         Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

         if (newPosition == 1) {
            newNodePtr->setNext(headPtr);
            headPtr = newNodePtr;
         }
         else {
            Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);

            newNodePtr->setNext(prevPtr->getNext() );
            prevPtr->setNext(newNodePtr);
         }
         ++itemCount;
      }
      catch (const bad_alloc&) {
         ableToInsert = false;
      }
   }

   return ableToInsert;
}

template <typename ItemType>
bool LinkedList<ItemType>::remove(const int position) {

   bool ableToRemove = position >= 1 &&
      position <= itemCount;

   if (ableToRemove) {
      Node<ItemType>* nodeToDeletePtr = nullptr;

      if (position == 1) {
         nodeToDeletePtr = headPtr;
         headPtr = headPtr->getNext();
      }
      else {
         Node<ItemType>* prevPtr = getNodeAt(position - 1);

         nodeToDeletePtr = prevPtr->getNext();

         prevPtr->setNext(nodeToDeletePtr->getNext() );
      }

      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;

      --itemCount;
   }

   return ableToRemove;
}

template <typename ItemType>
void LinkedList<ItemType>::clear() {

   while (!isEmpty() ) {
      remove(1);
   }
}

template <typename ItemType>
ItemType LinkedList<ItemType>::getEntry(const int position) const
   throw(PrecondViolatedExcep) {

   bool ableToGet = position >= 1 &&
      position <= itemCount;

   if (ableToGet) {
      Node<ItemType>* nodePtr = getNodeAt(position);

      return nodePtr->getItem();
   }
   else {
      string message = "LinkedList::getEntry() called with an empty ";
      message += "list or an invalid position.";

      throw PrecondViolatedExcep(message);
   }
}

template <typename ItemType>
void LinkedList<ItemType>::setEntry(const int position,
                                   const ItemType& newEntry)
   throw(PrecondViolatedExcep) {

   bool ableToSet = position >= 1 &&
      position <= itemCount;

   if (ableToSet) {
      Node<ItemType>* nodePtr = getNodeAt(position);

      nodePtr->setItem(newEntry);
   }
   else {
      string message = "LinkedList::setEntry() called with an empty ";
      message += "list or an invalid poosition.";

      throw PrecondViolatedExcep(message);
   }
}

template <typename ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(const int position) const {

   assert(position >= 1 && position <= itemCount);

   Node<ItemType>* curPtr = headPtr;

   for (int skip = 1; skip < position; ++skip) {
      curPtr = curPtr->getNext();
   }

   return curPtr;
}

/* Same function template works for either General or Specific
   Template Friendship: */

// template <typename ItemType>
// ostream& operator<<(ostream& s,
//                     const LinkedList<ItemType>& aList) {

//    /* getEntry is not very efficient, making this insertion operator a
//       O(n^2) routine. We *can* do better by allowing this routine to
//       access the Node class template. */
//    for (int i = 1; i < aList.getLength(); ++i) {
//       s << aList.getEntry(i) << endl;
//    }

//    return s;
// }

/* More efficient insertion operator. This is the way it *should* be
 * implmented: */

template <typename ItemType>
ostream& operator<<(ostream& s,
                    const LinkedList<ItemType>& aList) {

   for (Node<ItemType>* curPtr = aList.headPtr;
        curPtr != nullptr;
        curPtr = curPtr->getNext() ) {

      s << curPtr->getItem()
        << endl;
   }

   return s;
}

/* Most efficient insertion operator. Requires friend access to the
 * Node itself. Notice, no method calls on Node objects; we directly
 * access the 'next' and 'item' private data members: */

// template <typename ItemType>
// ostream& operator<<(ostream& s,
//                     const LinkedList<ItemType>& aList) {

//    for (Node<ItemType>* curPtr = aList.headPtr;
//         curPtr != nullptr;
//         curPtr = curPtr->next) {
//       s << curPtr->item
//         << endl;
//    }

//    return s;
// }
