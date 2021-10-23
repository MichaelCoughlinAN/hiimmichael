/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Implementation file for a node in the linked implementation of the
 *  ADT bag.
 *
 *  Adapted from page 136-7 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Nov 18
 *
 *  @version 6.0 */

template <typename ItemType>
Node<ItemType>::Node()
   : next(nullptr) {
}

template <typename ItemType>
Node<ItemType>::Node(const ItemType& anItem)
   : item(anItem),
     next(nullptr) {
}

template <typename ItemType>
Node<ItemType>::Node(const ItemType& anItem,
                     Node<ItemType>* nextNodePtr)
   : item(anItem),
     next(nextNodePtr) {
}

template <typename ItemType>
void Node<ItemType>::setItem(const ItemType& anItem) {

   item = anItem;
}

template <typename ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr) {

   next = nextNodePtr;
}

template <typename ItemType>
ItemType Node<ItemType>::getItem() const {

   return item;
}

template <typename ItemType>
Node<ItemType>* Node<ItemType>::getNext() const {

   return next;
}
