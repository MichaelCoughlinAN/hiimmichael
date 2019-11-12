/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Implementation file for the class LinkedSet.
 *
 *  Adapted from pages 139-148 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Nov 18
 *
 *  @version 6.0 */

template <typename ItemType>
LinkedSet<ItemType>::LinkedSet()
  : headPtr(nullptr),
    itemCount(0) {
}

template <typename ItemType>
LinkedSet<ItemType>::LinkedSet(const LinkedSet<ItemType>& aSet) {

  itemCount = aSet.itemCount;

  if (aSet.headPtr == nullptr) {
    headPtr = nullptr;
  }
  else {
    Node<ItemType>* origChainPtr = aSet.headPtr;

    headPtr = new Node<ItemType>();
    headPtr->setItem(origChainPtr->getItem() );

    Node<ItemType>* newChainPtr = headPtr;

    origChainPtr = origChainPtr->getNext();

    while (origChainPtr != nullptr) {
      ItemType nextItem = origChainPtr->getItem();

      Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

      newChainPtr->setNext(newNodePtr);
      newChainPtr = newChainPtr->getNext();
      origChainPtr = origChainPtr->getNext();
    }
    newChainPtr->setNext(nullptr);
  }
}

template <typename ItemType>
LinkedSet<ItemType>::~LinkedSet() {

  clear();
}

template <typename ItemType>
int LinkedSet<ItemType>::getCurrentSize() const {

  return itemCount;
}

template <typename ItemType>
bool LinkedSet<ItemType>::isEmpty() const {

  return itemCount == 0;
}

template <typename ItemType>
bool LinkedSet<ItemType>::add(const ItemType& newEntry) {
  Node<ItemType>* newNodePtr = new Node<ItemType>();
  if(!contains(newEntry)){ 
  newNodePtr->setItem(newEntry);
  newNodePtr->setNext(headPtr);
  headPtr = newNodePtr;
  ++itemCount;
 
 return true;
  }else return false;
}

template <typename ItemType>
bool LinkedSet<ItemType>::remove(const ItemType& anEntry) {
  bool canRemoveItem = !isEmpty();

  if (canRemoveItem) {
    Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
    canRemoveItem = entryNodePtr != nullptr;

    if (canRemoveItem) {
      entryNodePtr->setItem(headPtr->getItem() );

      Node<ItemType>* nodeToDeletePtr = headPtr;

      headPtr = headPtr->getNext();
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;
      --itemCount;
    }
  }
  return canRemoveItem;
}

template <typename ItemType>
void LinkedSet<ItemType>::clear() {
  Node<ItemType>* nodeToDeletePtr = headPtr;

  while (headPtr != nullptr) {
    headPtr = headPtr->getNext();
    nodeToDeletePtr->setNext(nullptr);
    delete nodeToDeletePtr;
    nodeToDeletePtr = headPtr;
  }
  itemCount = 0;
}

template <typename ItemType>
bool LinkedSet<ItemType>::contains(const ItemType& anEntry) const {

  return getPointerTo(anEntry) != nullptr;
}

template <typename ItemType>
int LinkedSet<ItemType>::getFrequencyOf(const ItemType& anEntry) const {

  int frequency = 0;

  Node<ItemType>* curPtr = headPtr;

  while (curPtr != nullptr) {
    if (curPtr->getItem() == anEntry) {
      ++frequency;
    }
    curPtr = curPtr->getNext();
  }
  return frequency;
}

template <typename ItemType>
vector<ItemType> LinkedSet<ItemType>::toVector() const {

  vector<ItemType> setContents;

  Node<ItemType>* curPtr = headPtr;

  while (curPtr != nullptr) {
    setContents.push_back(curPtr->getItem() );
    curPtr = curPtr->getNext();
  }
  return setContents;
}

template <typename ItemType>
Node<ItemType>* LinkedSet<ItemType>::getPointerTo(const ItemType& target) const {
  bool found = false;
  Node<ItemType>* curPtr = headPtr;

  while (!found && curPtr != nullptr) {
    if (curPtr->getItem() == target) {
      found = true;
    }
    else {
      curPtr = curPtr->getNext();
    }
  }
  return curPtr;
}


template <typename ItemType>
string LinkedSet<ItemType>::clean(ItemType& word) const{

string compare = "!@#$%^&*()_-+={}[]:;\"\'`<>,.?/|\\";
 string alphabet = "abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
 
  while(word.find_first_of(compare) < word.find_first_of(alphabet)) {
     int position = word.find_first_of(compare);
     word = word.substr(++position);
   }
  string::size_type p = word.find_last_not_of(compare);
  if(p != string::npos){
      word = word.substr(0, ++p);
  }
   return word;
 }
   
template <typename ItemType>
vector<ItemType> LinkedSet<ItemType>::difference(const LinkedSet<ItemType>& set) const{

  LinkedSet<ItemType> temp;
  Node<ItemType>* curPtr = headPtr;
  
   for(int i = 0; i < itemCount; ++i){
   if(!set.contains(curPtr->getItem())){
     temp.add(curPtr->getItem());
   }
   curPtr = curPtr->getNext();
  } return temp.toVector();
}

template <typename ItemType>
string LinkedSet<ItemType>::toLower(ItemType& wordToChange) const{
  string newWord = "";
  for(unsigned i = 0; i < wordToChange.length(); i++) {
    newWord += tolower(wordToChange.at(i));
    }
  return newWord;
}
