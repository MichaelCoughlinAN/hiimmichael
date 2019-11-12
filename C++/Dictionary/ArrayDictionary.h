/** @file
 *
 *  @course CS1521
 *  @section 9
 *
 *  Header file for an array-based ADT dictionary.
 *
 *  Adapted from page 535 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *  @author Michael Coughlin
 *
 *  @date 2014 Mar 20
 *
 *  @version 6.0 */

#ifndef _ARRAY_DICTIONARY
#define _ARRAY_DICTIONARY

#include "DictionaryInterface.h"
#include "Entry.h"
#include "NotFoundException.h"
#include "BinarySearchTree.h"

#include <iostream>
#include <fstream>

/** @class ArrayDictionary ArrayDictionary.h "ArrayDictionary.h"
 *
 * An array-based implementation of the ADT dictionary that organizes
 * its data items in sorted search-key order.  Search keys in the
 * dictionary must be unique. */
template <typename KeyType, typename ItemType>
  class ArrayDictionary : public DictionaryInterface<KeyType, ItemType> {
 private:
  static const int DEFAULT_CAPACITY = 21;

  ifstream inFile;

  int itemCount;

  int maxItems;

  Entry<KeyType, ItemType>* entryPtr;

  Entry<KeyType, ItemType>* items[DEFAULT_CAPACITY];

  BinarySearchTree<ItemType> itemTree;

  BinarySearchTree<KeyType> keyTree;

 public:
  ArrayDictionary();
  
  virtual ~ArrayDictionary();

  virtual bool isEmpty() const;

  virtual int getNumberOfItems() const;
 
  virtual bool add(const KeyType& search, 
                   const ItemType& newItem, 
                   const string& item, 
                   const string& item1);

  virtual bool remove(int position);

  virtual void clear();

  int getPosition(string&);

  int getPositionKey(string&);

  void displayEntry(int positon);

  virtual void traverse(void visit(const ItemType&) );

  void traverseKey(void visit(const KeyType&) );
};

#include "ArrayDictionary.cpp"

#endif
