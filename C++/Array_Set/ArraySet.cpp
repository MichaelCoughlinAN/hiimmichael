template <typename ItemType>
ArraySet<ItemType>::ArraySet()
  : itemCount(0),
    maxItems(DEFAULT_CAPACITY) {
    }

template <typename ItemType>
int ArraySet<ItemType>::getCurrentSize() const {

  return itemCount;
}

template <typename ItemType>
bool ArraySet<ItemType>::isEmpty() const {

  return itemCount == 0;
}

template <typename ItemType>
bool ArraySet<ItemType>::add(const ItemType& newEntry) {

  bool hasRoomToAdd = itemCount < maxItems;

  if((hasRoomToAdd) && !contains(newEntry)) {
    items[itemCount] = newEntry;
    ++itemCount;
  }

  return hasRoomToAdd;
}

template <typename ItemType>
bool ArraySet<ItemType>::remove(const ItemType& anEntry) {

  int locatedIndex = getIndexOf(anEntry);
  bool canRemoveItem = !isEmpty() && locatedIndex > -1;

  if (canRemoveItem) {
    --itemCount;
    items[locatedIndex] = items[itemCount];
  }

  return canRemoveItem;
}

template <typename ItemType>
void ArraySet<ItemType>::clear() {

  itemCount = 0;
}

template <typename ItemType>
bool ArraySet<ItemType>::contains(const ItemType& anEntry) const {

  bool found = false;
  int curIndex = 0;

  while (!found && curIndex < itemCount) {
    if (anEntry == items[curIndex]) {
      found = true;
    }
    ++curIndex;
  }

  return found;
}

template <typename ItemType>
int ArraySet<ItemType>::getFrequencyOf(const ItemType& anEntry) const {

  int frequency = 0;
  int curIndex = 0;

  while (curIndex < itemCount) {
    if (items[curIndex] == anEntry) {
      ++frequency;
    }
    ++curIndex;
  }
  return frequency;
}

template <typename ItemType>
vector<ItemType> ArraySet<ItemType>::toVector() const{ 
  vector<ItemType> setContents;
 for(int i = 0; i < itemCount; ++i) {
   setContents.push_back(items[i]);
 }
 return setContents;
}


template <typename ItemType>
int ArraySet<ItemType>::getIndexOf(const ItemType& target) const {

  bool found = false;
  int result = -1;
  int searchIndex = 0;

  while (!found && searchIndex < itemCount) {
    if (items[searchIndex] == target) {
      found = true;
      result = searchIndex;
    }
    else {
      ++searchIndex;
    }
  }

  return result;
}

template <typename ItemType>
vector<ItemType> ArraySet<ItemType>::difference(const ArraySet<ItemType>& set) const {

  ArraySet<ItemType> temp;

  for(int i = 0; i < itemCount; ++i){ 
    if(!set.contains(items[i]))
  temp.add(items[i]);
  }
  return temp.toVector();
}
 
