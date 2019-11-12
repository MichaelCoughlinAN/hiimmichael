/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  ListInterface class template definition.
 *
 *  Adapted from page 261-2 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *  @date 2013 Jan 15
 *  @version 6.0 */

#ifndef _LIST_INTERFACE
#define _LIST_INTERFACE

#include "PrecondViolatedExcep.h"

/** @class ListInterface ListInterface.h "ListInterface.h"
 *
 *  Definition of ListInterface class template. */
template <typename ItemType>
class ListInterface {
public:

   /** Sees whether this list is empty.
    *
    *  @return True if this list is empty, or false if not. */
   virtual bool isEmpty() const = 0;

   /** Gets the current number of entries in this list.
    *
    *  @return The integer number of entries in this list. */
   virtual int getLength() const = 0;

   /** Inserts a new entry into this list at a given position.
    *
    *  @pre None.
    *
    *  @post If 1 <= newPosition <= getLength() + 1 and the insertion
    *        is successful, newEntry is stored at the given position
    *        in this list, other entries are renumbered accordingly.
    *
    *  @param newPosition The list position at which to insert
    *         newEntry.
    *
    *  @param newEntry The object to be added as a new entry.
    *
    *  @return True if insertion was successful, or false if not. */
   virtual bool insert(const int newPosition,
                       const ItemType& newEntry) = 0;

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
    *  @return The entry at the desired position in this list.
    *
    *  @throw PrecondViolatedExcep If position < 1 or position >
    *         getLength(). */
   virtual ItemType getEntry(const int position) const
      throw(PrecondViolatedExcep) = 0;

   /** Replaces the entry at the given position in this list.
    *
    *  @pre 1 <= position <= getLength().
    *
    *  @post The entry at the given position is newEntry.
    *
    *  @param position The list position of the entry to replace.
    *
    *  @param newEntry The replacement entry.
    *
    *  @throw PrecondViolatedExcep If position < 1 or position >
    *         getLength(). */
   virtual void setEntry(const int position,
                         const ItemType& newEntry)
      throw(PrecondViolatedExcep) = 0;
};

#endif
