/** @file
 *
 *  @course CS1521
 *  @section 9
 *
 *  DictionaryInterface class template definition.
 *
 *  Adapted from pages 530-531 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *  @author Michael Coughlin
 *
 *  @date 2014 Mar 20
 *
 *  @version 6.0 */

#ifndef _DICTIONARY_INTERFACE
#define _DICTIONARY_INTERFACE

#include "NotFoundException.h"

/** @class DictionaryInterface DictionaryInterface.h "DictionaryInterface.h"
 *
 *  Specification for an interface for ADT dictionary. */
template <typename KeyType, typename ItemType>
  class DictionaryInterface {
 public:
  /** Sees whether this dictionary is empty.
   *
   *  @return True if this dictionary is empty;
   *          otherwise returns false. */
  virtual bool isEmpty() const = 0;

  /** Gets the number of items in this dictionary.
   *
   *  @return The number of items in this dictionary. */
  virtual int getNumberOfItems() const = 0;

  /** Inserts an item into this dictionary according to the item's
   *  search key.
   *
   * @pre The search key of the new item differs from all search keys
   *      presently in this dictionary.
   *
   * @post If the insertion is successful, newItem is in its proper
   *       position within this dictionary.
   *
   * @param searchKey The search key associated with the item to be
   *                  inserted.
   *
   * @param newItem The item to add to this dictionary.
   *
   * @return True if item was successfully added, or false if not. */
  virtual bool add(const KeyType& searchKey,
		   const ItemType& newItem,
		   const string& item,
		   const string& item1) = 0;

  /** Removes an item with the given search key from this dictionary.
   *
   * @post If the item whose search key equals searchKey existed in
   *       this dictionary, the item was removed.
   *
   * @param searchKey The search key of the item to be removed.
   *
   * @return True if the item was successfully removed, or false if
   *         not. */
  virtual bool remove(int position) = 0;

  /** Removes all entries from this dictionary. */
  virtual void clear() = 0;

  /** Traverses this dictionary and calls a given client function
   *  once for each item.
   *
   * @post The given function's action occurs once for each item in
   *       this dictionary and possibly alters the item.
    *
    * @param visit A client function. */
  virtual void traverse(void visit(const ItemType&) ) = 0;
};

#endif
