package binaryheap;

import java.util.ArrayList;
import java.util.Comparator;

/**
 * This class implements a binary heap data structure by extending the
 * ArrayList class.
 * @author tcolburn
 * @author Michael Coughlin
 * CS 2511, Fall 2014
 * Section 1
 */
public class BinaryHeap<E> extends ArrayList<E> {

    /**
     * Creates an empty binary heap with a given capacity and comparator.
     * @param capacity The initial size of the underlying ArrayList object.
     * @param comp A comparator object for comparing keys of binary heap elements.
     */
    public BinaryHeap(int capacity, Comparator<E> comp) {
        super(capacity+1);
        init();
        this.comp = comp;
    }

    /**
     * Initializes the underlying ArrayList object for use as a binary heap.
     * A null object is added to location 0, which is not used by the heap.
     */
    private void init() {
        add(0, null);
    }

    /**
     * Clears this binary heap by clearing and initializing the underlying
     * ArrayList object.
     */
    public void clear() {
        super.clear();
        init();
    }

    /**
     * Returns the current size of this binary heap.  Since the first location 
     * (index 0) of the underlying ArrayList object is not used, the size of the 
     * binary heap is one less than the size of the ArrayList object.
     * @return The binary heap's current size. 
     */
    public int size() {
        return super.size()-1;
    }

    /**
     * Returns true if this binary heap is empty, that is, its size is zero.
     * @return Whether this binary heap is empty.
     */
    public boolean isEmpty() {
        return size() == 0;
    }

    /**
     * Adds a new element to this binary heap.  At the end of the add,
     * the heap has one more element and the heap property is maintained.
     * @param element The element to add
     * @return true.  In accordance with the Collection interface, returns
     * true since duplicate elements are allowed.
     */
    public boolean add(E element) {
         add(size() + 1, element);
         int i = size();
         
        if (size() == 1 ) {
         return true;
       } else {
            while (comp.compare(this.get(i), this.get(i/2) ) < 0) {
          
            E temp = this.get(i/2);
            set(i/2, element);
            set(i, temp);
            i = i/2;
            
             if (i == 1)
               return true; 
            }  
        }       
        return false;
    }
      

    /**
     * Removes an element from the root of this binary heap.  After removal,
     * the heap has one less element and the heap property is restored.
     * This method does not override any method in the ArrayList class 
     * (note absence of an index parameter).
     * @return The removed element
     */
    public E remove() {
     
        if (isEmpty() )
       throw new ArrayIndexOutOfBoundsException("Heap is empty");

    	E root = get(1);
        set(1, get(size() ));
        remove(size() );
        
        int index = 1;
        while (index * 2 <= size()) {
    
            int lesserChild = index*2;

            if (index * 2 + 1 <= size() && comp.compare(get(index*2), get(index * 2 + 1)) > 0) {
                lesserChild = index * 2 + 1;
            } 
            if (comp.compare(get(index), get(lesserChild)) > 0) {
                E tmp = get(index);
                set(index, get(lesserChild) );
                set(lesserChild, tmp); 
            } 
            else break;
     
            index = lesserChild;
        }        	
    	return root;
    }


    
    
    


    /**
     * A Comparator object used to compare binary heap elements during its
     * add and remove operations.
     */
    private Comparator<E> comp;

}
