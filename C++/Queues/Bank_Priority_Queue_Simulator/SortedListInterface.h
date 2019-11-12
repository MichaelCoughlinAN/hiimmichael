/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  SortedListInterface class template definition.
 *
 *  Adapted from page 350-1 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Jan 19
 *
 *  @version 6.0 */

#ifndef _SORTED_LIST_INTERFACE
#define _SORTED_LIST_INTERFACE

#include "PrecondViolatedExcep.h"

/** @class SortedListInterface SortedListInterface.h "SortedListInterface.h"
 *
 *  Definition of SortedListInterface class template. */
template <typename ItemType>
class SortedListInterface {
 public:

  /** Sees whether this list is empty.
   *
   *  @return True if this list is empty, or false if not. */
  virtual bool isEmpty() const = 0;

  /** Gets the current number of entries in this list.
   *
   *  @return The integer number of entries in this list. */
  virtual int getLength() const = 0;

  /** Insert an entry into this sorted list in its proper order so
   *  that this sorted list remains sorted.
   *
   *  @pre None.
   *
   *  @post newEntry is stored this sorted list, and this sorted
   *        list remains sorted.
   *
   *  @param newEntry The object to be inserted in this sorted
   *                  list.
   *
   *  @return True if the insertion is successful, else false. */
  virtual bool insertSorted(const ItemType& newEntry) = 0;

  /** Removes the first or only occurrance of the given entry from
   *  this sorted list.
   *
   *  @pre None.
   *
   *  @post If the removal is successful, the first occurrance of
   *        the given entry is no longer in this sorted list.
   *
   *  @param anEntry The entry to remove.
   *
   *  @return True if removal was successful, or false if not. */
  virtual bool removeSorted(const ItemType& anEntry) = 0;

  /** Removes the entry at the given position from this list.
   *
   *  @pre None.
   *
   *  @post If 1 <= position <= getLength() and the removal is
   *        successful, the entry at the given position in this list
   *        is removed, other entries are renumbered accordingly.
   *
   *  @param position The list position of the entry to remove.
   *
   *  @return True if removal was successful, or false if not. */
  virtual bool remove(const int position) = 0;

  /** Removes all entries from this list.
   *
   *  @post List conntains no entries; getLength() == 0. */
  virtual void clear() = 0;

  /** Retrieves the entry at the given position in this list.
   *
   *  @pre 1 <= position <= getLength().
   *
   *  @post None.
   *
   *  @param position The position of the desired entry to
   *         retrieve.
   *
   *  @throw PrecondViolatedExcep If the precondition is violated.
   *
   *  @return The entry at the desired position in this list. */
  virtual ItemType getEntry(const int position) const
    throw(PrecondViolatedExcep) = 0;

  /** Gets the position of the first or only occurrance of the given
   *  entry in this sorted list. In the case the entry is not in this
   *  sorted list, it determines the position where the entry should
    *  be located if it were in this sorted list.
    *
    *  @pre None.
    *
    *  @post None.
    *
    *  @param anEntry The entry to locate.
    *
    *  @return Either the position of the first or only occurrance of
			  *          the given entry if its is in this sorted list, or the
							      *          position where the entry would occur, but as a negative
    *          integer. */
  virtual int getPosition(const ItemType& anEntry) const = 0;
};

#endif
