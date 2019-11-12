/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Implementation file for a pointer-based implementation of the ADT
 *  binary search tree.
 *
 *  Not in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2014 Mar 19
 *
 *  @version 6.0 */

//////////////////////////////////////////////////////////////
//
//      Protected Utility Methods Section
//
//////////////////////////////////////////////////////////////

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr,
                                                                BinaryNode<ItemType>* newNodePtr) {

  BinaryNode<ItemType>* returnPtr = newNodePtr;

  if (subTreePtr != nullptr) {
    if (this->getItem(subTreePtr) > this->getItem(newNodePtr) ) {
      this->setLeftChildPtr(subTreePtr,
			    insertInorder(this->getLeftChildPtr(subTreePtr),
					  newNodePtr) );
    }
    else {
      this->setRightChildPtr(subTreePtr,
			     insertInorder(this->getRightChildPtr(subTreePtr),
					   newNodePtr) );
    }

    returnPtr = subTreePtr;
  }

  return returnPtr;
}

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr,
                                                              const ItemType target,
                                                              bool& success) {

  BinaryNode<ItemType>* returnPtr = nullptr;

  if (subTreePtr == nullptr) {
    success = false;
  }
  else if (this->getItem(subTreePtr) == target) {
    subTreePtr = removeNode(subTreePtr);
    success = true;
    returnPtr = subTreePtr;
  }
  else {
    if (this->getItem(subTreePtr) > target) {
      // Search the left subtree
      this->setLeftChildPtr(subTreePtr,
			    removeValue(this->getLeftChildPtr(subTreePtr),
					target,
					success) );
    }
    else {
      // Search the right subtree
      this->setRightChildPtr(subTreePtr,
			     removeValue(this->getRightChildPtr(subTreePtr),
					 target,
					 success) );
    }

    returnPtr = subTreePtr;
  }

  return returnPtr;
}

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType>* nodePtr) {

  BinaryNode<ItemType>* returnPtr = nullptr;

  // Case 1) Node is a leaf - it is deleted
  if (this->isLeaf(nodePtr) ) {
    delete nodePtr;
    nodePtr = nullptr;
  }
  // Case 2) Node has one child - parent adopts child
  else if (this->getLeftChildPtr(nodePtr) == nullptr) { // Has rightChild only
    BinaryNode<ItemType>* nodeToConnectPtr = this->getRightChildPtr(nodePtr);
    delete nodePtr;
    nodePtr = nullptr;
    returnPtr = nodeToConnectPtr;
  }
  else if (this->getRightChildPtr(nodePtr) == nullptr) { // Has left child only
    BinaryNode<ItemType>* nodeToConnectPtr = this->getLeftChildPtr(nodePtr);
    delete nodePtr;
    nodePtr = nullptr;
    returnPtr = nodeToConnectPtr;
  }
  // Case 3) Node has two children:
  else {
    // Traditional way to remove a value in a node with two children
    ItemType newNodeValue;

    this->setRightChildPtr(nodePtr,
			   removeLeftmostNode(this->getRightChildPtr(nodePtr),
					      newNodeValue) );
    this->setItem(nodePtr, newNodeValue);

    returnPtr = nodePtr;

    // Alernative way to remove a value in a node with two children;
    // does not require pass-by-reference.  We need to check whether
    // this right child has a left child.  This is similar to the
    // base case in "findSuccessorValue" but we need to remove the
    // special case where the right child *is* the inorder successor
    /*
      BinaryNode<ItemType>* myRightChildPtr = this->getRightChildPtr(nodePtr);
      BinaryNode<ItemType>* myLeftGrandChildPtr = this->getLeftChildPtr(myRightChildPtr);

      // Special case - right child is successor
      if (myLeftGrandChildPtr == nullptr) {
         this->setItem(nodePtr, this->getItem(myRightChildPtr) );
         this->setRightChildPtr(nodePtr, removeNode(myRightChildPtr) );
         returnPtr = nodePtr;
      }
      else {
         this->setItem(nodePtr, findSuccessorValue(this->getRightChildPtr(nodePtr)) );
         returnPtr = nodePtr;
      }
    */
  }

  return returnPtr;
}

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType& inorderSuccessor) {

  BinaryNode<ItemType>* returnPtr = nullptr;

  if (this->getLeftChildPtr(nodePtr) == nullptr) {
    inorderSuccessor = this->getItem(nodePtr);

    returnPtr = removeNode(nodePtr);
  }
  else {
    this->setLeftChildPtr(nodePtr,
			  removeLeftmostNode(this->getLeftChildPtr(nodePtr),
					     inorderSuccessor) );

    returnPtr = nodePtr;
  }

  return returnPtr;
}

/*
  template <typename ItemType>
ItemType BinarySearchTree<ItemType>::findSuccessorValue(BinaryNode<ItemType>* subTreePtr) {
   BinaryNode<ItemType>* myLeftChildPtr = this->getLeftChildPtr(subTreePtr);

   ItemType returnItem;

   if (this->getLeftChildPtr(myLeftChildPtr) == nullptr) {
      returnItem = this->getItem(myLeftChildPtr);
      this->setLeftChildPtr(subTreePtr, removeNode(myLeftChildPtr) );
   }
   else {
      returnItem = findSuccessorValue(this->getLeftChildPtr(subTreePtr) );
   }

   return returnItem;
}
*/

template <typename ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* subTreePtr,
                                                           const ItemType& target) const {

  BinaryNode<ItemType>* returnPtr = nullptr;

  if (subTreePtr != nullptr) {
    if (this->getItem(subTreePtr) == target) {
      returnPtr = subTreePtr;
    }
    else if (this->getItem(subTreePtr) > target) {
      returnPtr = findNode(this->getLeftChildPtr(subTreePtr), target);
    }
    else {
      returnPtr = findNode(this->getRightChildPtr(subTreePtr), target);
    }
  }

  return returnPtr;
}

template <typename ItemType>
void BinarySearchTree<ItemType>::preorder(void visit(const ItemType&),
                                          const BinaryNode<ItemType>* const treePtr) const {

  if (treePtr != nullptr) {
    visit(this->getItem(treePtr) );
    preorder(visit, this->getLeftChildPtr(treePtr) );
    preorder(visit, this->getRightChildPtr(treePtr) );
  }
}

template <typename ItemType>
void BinarySearchTree<ItemType>::inorder(void visit(const ItemType&),
                                         const BinaryNode<ItemType>* const treePtr) const {

  if (treePtr != nullptr) {
    inorder(visit, this->getLeftChildPtr(treePtr) );
    visit(this->getItem(treePtr) );
    inorder(visit, this->getRightChildPtr(treePtr) );
  }
}

template <typename ItemType>
void BinarySearchTree<ItemType>::postorder(void visit(const ItemType&),
                                           const BinaryNode<ItemType>* const treePtr) const {

  if (treePtr != nullptr) {
    postorder(visit, this->getLeftChildPtr(treePtr) );
    postorder(visit, this->getRightChildPtr(treePtr) );
    visit(this->getItem(treePtr) );
  }
}

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
  : BinaryNodeTree<ItemType>() {
}

template <typename ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
  : BinaryNodeTree<ItemType>(rootItem) {
}

template <typename ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& rhs) {

  try {
    this->setRootPtr(this->copyTree(rhs.getRootPtr()) );
  }
  catch (const bad_alloc&) {
    clear();
    throw;
  }
}

template <typename ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() {

  clear();
}

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const {

  return BinaryNodeTree<ItemType>::isEmpty();
}

template <typename ItemType>
int BinarySearchTree<ItemType>::getHeight() const {

  return this->getHeightHelper(this->getRootPtr() );
}

template <typename ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const {

  return this->getNumberOfNodesHelper(this->getRootPtr() );
}

template <typename ItemType>
void BinarySearchTree<ItemType>::clear() {

  this->destroyTree(this->getRootPtr() );
  this->setRootPtr(nullptr);
}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const
  throw(PrecondViolatedExcep) {

  if (isEmpty() ) {
    throw PrecondViolatedExcep("getRootData() called with empty tree.");
   }

   return this->getItem(this->getRootPtr() );
}

// Must override setRootData to disable its affect:
// IMPOSSIBLE - base version can still be called - this indicates
// that PUBLIC INHERITANCE SHOULD NOT BE USED.

// Must not implement in derived class - private inheritance makes it
// private here, so clients cannot destroy the ordering of the search
// tree.

// template <typename ItemType>
// void BinarySearchTree<ItemType>::setRootData(const ItemType& newItem) const
//    throw(PrecondViolatedExcep) {

//    throw PrecondViolatedExcep("Cannot change root value in a BST!");
// }

template <typename ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData) {

   bool canAdd = true;

   try {
      this->setRootPtr(insertInorder(this->getRootPtr(),
                                     this->createNewNode(newData)) );
   }
   catch (const bad_alloc&) {
      canAdd = false;
   }

   return canAdd;
}

template <typename ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target) {

   bool isSuccessful = false;

   this->setRootPtr(removeValue(this->getRootPtr(),
                                target,
                                isSuccessful) );

   return isSuccessful;
}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const
   throw(NotFoundException) {

   BinaryNode<ItemType>* nodeWithEntry = findNode(this->getRootPtr(),
                                                  anEntry);

   if (nodeWithEntry == nullptr) {
      throw NotFoundException("Entry not found in tree.");
   }
   else {
      return this->getItem(nodeWithEntry);
   }
}

template <typename ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const {

   return findNode(this->getRootPtr(), anEntry);
}

//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template <typename ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(const ItemType&) ) const {

   this->preorder(visit, this->getRootPtr() );
}

template <typename ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(const ItemType&) ) const {

   this->inorder(visit, this->getRootPtr() );
}

template <typename ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(const ItemType&) ) const {

   this->postorder(visit, this->getRootPtr() );
}

//////////////////////////////////////////////////////////////
//      Overloaded Operator
//////////////////////////////////////////////////////////////

template <typename ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>:: operator=(const BinarySearchTree<ItemType>& rhs) {

   if (!isEmpty() ) {
      clear();
   }

   this->setRootPtr(this->copyTree(rhs.getRootPtr()) );

   return *this;
}
