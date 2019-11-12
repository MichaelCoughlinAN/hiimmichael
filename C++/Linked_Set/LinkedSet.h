/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for a linked implementation of the ADT set.
 *
 *  Adapted from page 138-9 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Nov 18
 *
 *  @version 6.0 */

#ifndef _LINKED_SET
#define _LINKED_SET

#include "SetInterface.h"
#include "Node.h"

/** @class LinkedSet LinkedSet.h "LinkedSet.h"
 *
 *  Specification of a pointer-based ADT set. */
template <typename ItemType>
class LinkedSet : public SetInterface<ItemType> {
 private:
  /** Pointer to first node. */
  Node<ItemType>* headPtr;

  /** Number of items in this set. */
  int itemCount;

  /** Gets a pointer to the node containing the target in this set.
   *
   * @pre None.
   *
   * @post None.
   *
   * @param target The ItemType value to find.
   *
   * @return A pointer to the node that contains the given target or
   *         nullptr if the set does not contain the target. */
  Node<ItemType>* getPointerTo(const ItemType& target) const;

 public:
  /** Default constructor. */
  LinkedSet();

  /** Copy constructor. */
  LinkedSet(const LinkedSet<ItemType>& aSet);

  virtual ~LinkedSet();

  int getCurrentSize() const;

  bool isEmpty() const;
 
 /** Removes any extraneous characters associated with word.
   *
   *  @post If successful, any extraneous characters associated
   *        at the beginning or end of word will be removed.
   *
   *  @param word The object to be cleaned.
   *
   *  @return String containing newly cleaned word. */
  string clean(ItemType& word) const;
 
 /** Converts a word to lowercase.
   *
   *  @post If successful, word is converted entirely to lowercase.
   *        
   *  @param word The object to be converted to lowercase.
   *
   *  @return String containing the newly lowercased word. */
  string toLower(ItemType& wordToChange) const;
 
 /** Creates a new set containing the difference..
   *
   *  @post If successful, a new set will be created storing the
   *        difference between the given sets.
   *
   *  @param set The object to find the difference of.
   *
   *  @return A set converted to a vector containing the difference. */
  vector<ItemType> difference(const LinkedSet<ItemType>& set) const;

  virtual bool add(const ItemType& newEntry);

  virtual bool remove(const ItemType& anEntry);

  virtual void clear();

  virtual int getFrequencyOf(const ItemType& anEntry) const;

  virtual bool contains(const ItemType& anEntry) const;

  virtual vector<ItemType> toVector() const;
};

#include "LinkedSet.cpp"

#endif
