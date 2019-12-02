#ifndef _SET_INTERFACE
#define _SET_INTERFACE

using namespace std;
#include <vector>
/** @class SetInterface SetInterface.h "SetInterface.h"
 *
 *  Definition of SetInterface class template. */

template <typename ItemType>
class SetInterface {
 public:

  /** Gets the current number of entries in this set.
   *
   *  @return The integer number of entries currently in this set. */
  virtual int getCurrentSize() const = 0;

  /** Checks to see whether this set is empty.
   *
   *  @return True if the set is empty, or false if not. */
  virtual bool isEmpty() const = 0;

  /** Adds a new entry to this set.
   *
   *  @post If successful, newEntry is stored in the set and the
   *        count of items in the set has increased by 1.
   *
   *  @param newEntry The object to be added as a new entry.
   *
   *  @return True if addition was successful, or false if not. */
  virtual bool add(const ItemType& newEntry) = 0;

  /** Removes the given entry from this set, if possible.
   *
   *  @post If successful, anEntry has been removed from the set and
   *        the count of items in the set has decreased by 1.
   *
   *  @param anEntry The value of the entry to be removed.
   *
   *  @return True if removal was successful, or false if not. */
  virtual bool remove(const ItemType& anEntry) = 0;

  /** Removes all entries from this set.
   *
   *  @post This set contains no items (thus the count is 0). */
  virtual void clear() = 0;
 
 //DO WE NEED?
  /** Counts the number of times a given entry appears in set.
   *
   *  @param anEntry The value of the entry to be counted.
   *
   *  @return The number of times anEntry appears in this set. */
  virtual int getFrequencyOf(const ItemType& anEntry) const = 0;

  /** Tests whether this set contains a given entry.
   *
   *  @param anEntry The value of the entry to locate.
   *
   *  @return True if this set contains anEntry, or false
   *          otherwise. */
  virtual bool contains(const ItemType& anEntry) const = 0;

  /** Converts this set into an array.
   *
   *  @return An array containing all the entries in this set. */
  virtual vector<ItemType> toVector()const  = 0;

};

#endif

