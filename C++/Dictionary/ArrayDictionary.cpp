template<typename KeyType, typename ItemType>
ArrayDictionary<KeyType, ItemType>::ArrayDictionary() {
  itemCount = 0;
  maxItems = DEFAULT_CAPACITY;
}

template<typename KeyType, typename ItemType>
ArrayDictionary<KeyType, ItemType>::~ArrayDictionary() {
}

template<typename KeyType, typename ItemType>
bool ArrayDictionary<KeyType, ItemType>::isEmpty() const {
  return itemCount == 0;
}

template<typename KeyType, typename ItemType>
void ArrayDictionary<KeyType, ItemType>::clear() {
  itemCount = 0;
}

template<typename KeyType, typename ItemType>
int ArrayDictionary<KeyType, ItemType>::getNumberOfItems() const {
  return itemCount;
}

template<typename KeyType, typename ItemType>
bool ArrayDictionary<KeyType, ItemType>::add(const KeyType& searchKey, 
					     const ItemType& newItem, 
					     const string& item, 
                                             const string& item1) {
  bool ableToAdd = itemCount < maxItems;

  if(ableToAdd) {
    entryPtr = new Entry<KeyType, ItemType>(searchKey, newItem);
    entryPtr->setEthnic(item);
    entryPtr->setAge(item1);
    items[itemCount] = entryPtr;   
    itemTree.add(newItem);
    keyTree.add(searchKey);
    ++itemCount;
  }

  return ableToAdd;
}

template<typename KeyType, typename ItemType>
bool ArrayDictionary<KeyType, ItemType>::remove(int position) {
  bool ableToRemove = position <= itemCount;
   if (ableToRemove) {
     entryPtr = items[position];
     itemTree.remove(entryPtr->getKey() );
     keyTree.remove(entryPtr->getItem() ); 
    }

  return ableToRemove;
}

template<typename KeyType, typename ItemType>
void ArrayDictionary<KeyType, ItemType>::traverse(void visit(const ItemType&) ) {
       itemTree.preorderTraverse(visit); 
}

template<typename KeyType, typename ItemType>
void ArrayDictionary<KeyType, ItemType>::traverseKey(void visit(const KeyType&) ) {
       keyTree.preorderTraverse(visit); 
}

template<typename KeyType, typename ItemType>
void ArrayDictionary<KeyType, ItemType>::displayEntry(int position) {
  entryPtr = items[position];
  cout << endl
       << "Name: " << entryPtr->getItem()
       << endl
       << "SSN: " << entryPtr->getKey()
       << endl
       << "Age: " << entryPtr->getAge()
       << endl
       << "Ethnicity: " << entryPtr->getEthnic()
       << endl;
}

template<typename KeyType, typename ItemType>
int ArrayDictionary<KeyType, ItemType>::getPosition(string& item) {
  int pos = 0;

  while (pos < itemCount) {
    entryPtr = items[pos];
    if(item != entryPtr->getKey())
      ++pos;
    else break;
  }
 
 return pos;
}

template<typename KeyType, typename ItemType>
int ArrayDictionary<KeyType, ItemType>::getPositionKey(string& item) {
  int pos = 0;

  while (pos < itemCount) {
    entryPtr = items[pos];
    if(item != entryPtr->getItem() )
      ++pos;
    else break;
  } 

 return pos;
}

