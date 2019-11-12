template <typename KeyType, typename ItemType>
Entry<KeyType, ItemType>::Entry() {
}

template <typename KeyType, typename ItemType>
void Entry<KeyType, ItemType>::setKey(const KeyType& key) {
  searchKey = key;
}

template <typename KeyType, typename ItemType>
void Entry<KeyType, ItemType>::setEthnic(const string& eth) {
  ethnic = eth;
}

template <typename KeyType, typename ItemType>
void Entry<KeyType, ItemType>::setAge(const string& ag) {
  age = ag;
}

template <typename KeyType, typename ItemType>
Entry<KeyType, ItemType>::Entry(ItemType newEntry, KeyType search) {
  item = newEntry;
  searchKey = search;
}

template <typename KeyType, typename ItemType>
Entry<KeyType, ItemType>::~Entry() {
}

template <typename KeyType, typename ItemType>
ItemType Entry<KeyType, ItemType>::getItem() const {
  return item;
}

template <typename KeyType, typename ItemType>
KeyType Entry<KeyType, ItemType>::getKey() const {
  return searchKey;
}

template <typename KeyType, typename ItemType>
string Entry<KeyType, ItemType>::getEthnic() const {
  return ethnic;
}

template <typename KeyType, typename ItemType>
string Entry<KeyType, ItemType>::getAge() const {
  return age;
}

template <typename KeyType, typename ItemType>
void Entry<KeyType, ItemType>::setItem(const ItemType& newEntry) {
  item = newEntry;
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator==(const Entry<KeyType, ItemType>& rhs) const {
  return searchKey == rhs.searchKey;
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator>(const Entry<KeyType, ItemType>& rhs) const {
    return searchKey > rhs.searchKey;
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator<(const Entry<KeyType, ItemType>& rhs) const {
    return searchKey < rhs.searchKey;
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator!=(const Entry<KeyType, ItemType>& rhs) const {
    return searchKey != rhs.searchKey;
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator>=(const Entry<KeyType, ItemType>& rhs) const {
    return searchKey >= rhs.searchKey;
}

template <typename KeyType, typename ItemType>
bool Entry<KeyType, ItemType>::operator<=(const Entry<KeyType, ItemType>& rhs) const {
    return searchKey <= rhs.searchKey;
}
