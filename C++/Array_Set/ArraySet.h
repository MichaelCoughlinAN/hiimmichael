#ifndef _ARRAY_SET
#define _ARRAY_SET

#include "SetInterface.h"

/** @class ArraySet ArraySet.h "ArraySet.h"
 *
 *  Specification of an array-based ADT set. */
template <typename ItemType>
 class ArraySet : public SetInterface<ItemType> {
   private:
   /** Maximum capacity of this set. */
   static const int DEFAULT_CAPACITY = 6;

   /** Data storage. */
   ItemType items[DEFAULT_CAPACITY];
  
   /** Number of items in this set. */
   int itemCount;

   /** Maximum capacity of this set. */
   int maxItems;

   /** Gets the index of target in the array 'items' in this set.
    *
    * @param target The ItemType value to retrieve the index of.
    *
    * @return The index of the element in the array 'items' that
    *         contains 'target' or -1 if the array does not contain
    *         'target'. */
   int getIndexOf(const ItemType& target) const;

   public:
   /** Default constructor. */
   ArraySet();

   /** Gets the current number of entries in this set.
    *
    *  @return The integer number of entries currently in the set. */
   int getCurrentSize() const;

   /** Sees whether this set is empty.
    *
    *  @return True if the set is empty, or false if not. */
   bool isEmpty() const;

   /** Adds a new entry to this set.
    *
    *  @post If successful, newEntry is stored in the set and the
    *        count of items in the set has increased by 1.
    *
    *  @param newEntry The object to be added as a new entry.
    *
    *  @return True if addition was successful, or false if not. */
   bool add(const ItemType& newEntry);

   /** Removes one occurrence of a given entry from this set, if
    *  possible.
    *
    *  @post If successful, anEntry has been removed from the set and
    *        the count of items in the set has decreased by 1.
    *
    *  @param anEntry The value of the entry to be removed.
    *
    *  @return True if removal was successful, or false if not. */
   bool remove(const ItemType& anEntry);

   /** Removes all entries from this set.
    *
    *  @post This set contains no items (thus the count is 0). */
   void clear();

   /** Finds the constrasted elements amongst two sets.
    *
    * @param set The set containing values to compare.
    *
    * @return A set converted into a vector holding the entries that
    *         would be left in one bag after removing those [entries] 
    *         that also occur in the second.  */
   vector<ItemType> difference(const ArraySet<ItemType>& set) const;

   /** Counts the number of times a given entry appears in set.
    *
    *  @param anEntry The value of the entry to be counted.
    *
    *  @return The number of times anEntry appears in this set. */
   int getFrequencyOf(const ItemType& anEntry) const;

   /** Tests whether this set contains a given entry.
    *
    *  @param anEntry The value of the entry to locate.
    *
    *  @return True if this set contains anEntry, or false
    *          otherwise. */
   bool contains(const ItemType& anEntry) const;

   /** Converts this set into a vector.
    *
    *  @return A vector containing all the entries in this set. */
   vector<ItemType> toVector() const;
   };

#include "ArraySet.cpp"

#endif
