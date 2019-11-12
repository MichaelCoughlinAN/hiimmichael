/** @file
 *
 *  @course CS1521
 *  @section 9
 *
 *  Header file for an entry object in a dictionary.
 *
 *  Adapted from page 533 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *  @author Michael Coughlin
 *
 *  @date 2014 Mar 20
 *
 *  @version 6.0 */

#ifndef _ENTRY
#define _ENTRY

/** @class Entry Entry.h "Entry.h"
 *
 *  Specification for an immutable object for ADT dictionary. */
template <typename KeyType, typename ItemType>
  class Entry {
 private:
  ItemType item;
  KeyType searchKey;
  string ethnic;
  string age;

 protected:
  void setKey(const KeyType& searchKey);

 public:
  Entry();

  Entry(ItemType newEntry,
	KeyType searchKey);

  void setEthnic(const string& eth);

  void setAge(const string& ag);

  virtual ~Entry();

  ItemType getItem() const;

  KeyType getKey() const;

  string getEthnic() const;

  string getAge() const;

  void setItem(const ItemType& newEntry);

  bool operator==(const Entry<KeyType, ItemType>& rhs) const;

  bool operator>(const Entry<KeyType, ItemType>& rhs) const;

  bool operator!=(const Entry<KeyType, ItemType>& rhs) const;

  bool operator<=(const Entry<KeyType, ItemType>& rhs) const;

  bool operator>=(const Entry<KeyType, ItemType>& rhs) const;

  bool operator<(const Entry<KeyType, ItemType>& rhs) const;
};

#include "Entry.cpp"

#endif
