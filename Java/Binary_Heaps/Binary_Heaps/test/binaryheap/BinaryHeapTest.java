package binaryheap;

import java.util.Comparator;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author tcolburn
 */
public class BinaryHeapTest {

    /**
     * A binary heap of Integer objects
     */
    private BinaryHeap<Integer> bh;

    /**
     * Some Integer nodes for testing
     */
    private Integer n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;

    /**
     * An object for comparing Integer nodes
     */
    private Comparator<Integer> comp;


    public BinaryHeapTest() {

        comp = new Comparator<Integer>() {

            public int compare(Integer t, Integer t1) {
                return t.compareTo(t1);
            }
        };

        bh = new BinaryHeap<Integer>(10, comp);

        n1 = new Integer(1);
        n2 = new Integer(2);
        n3 = new Integer(3);
        n4 = new Integer(4);
        n5 = new Integer(5);
        n6 = new Integer(6);
        n7 = new Integer(7);
        n8 = new Integer(8);
        n9 = new Integer(9);
        n10 = new Integer(10);
    }


    @Test
    public void testAdd() {

        buildHeap();

        assertTrue(leftChild(n1) == n2);
        assertTrue(rightChild(n1) == n5);
        assertTrue(leftChild(n2) == n4);
        assertTrue(rightChild(n2) == n3);
        assertTrue(leftChild(n5) == n9);
        assertTrue(rightChild(n5) == n6);
        assertTrue(leftChild(n4) == n10);
        assertTrue(rightChild(n4) == n7);
        assertTrue(leftChild(n3) == n8);
        assertTrue(rightChild(n3) == null);
        assertTrue(leftChild(n9) == null);
        assertTrue(rightChild(n9) == null);
        assertTrue(leftChild(n6) == null);
        assertTrue(rightChild(n6) == null);

        assertTrue(parent(n10) == n4);
        assertTrue(parent(n7) == n4);
        assertTrue(parent(n8) == n3);
        assertTrue(parent(n4) == n2);
        assertTrue(parent(n3) == n2);
        assertTrue(parent(n9) == n5);
        assertTrue(parent(n6) == n5);
        assertTrue(parent(n2) == n1);
        assertTrue(parent(n5) == n1);
        assertTrue(parent(n1) == null);
    }

    /**
     * An auxiliary method that builds a heap that should look like:
     *
     *              1
     *            /   \
     *          2       5
     *         /  \    / \
     *       4     3  9   6
     *      / \   /
     *    10   7 8
     */
    private void buildHeap() {

        bh.clear();

        assertTrue(bh.isEmpty());

        bh.add(n10);
        bh.add(n9);
        bh.add(n8);
        bh.add(n7);
        bh.add(n6);
        bh.add(n5);
        bh.add(n4);
        bh.add(n3);
        bh.add(n2);
        bh.add(n1);


        
        assertTrue(bh.size() == 10);
        
        
    }

    @Test
    public void testRemove() {

        buildHeap();
        assertTrue(bh.remove() == n1);
        assertTrue(bh.remove() == n2);
        assertTrue(bh.remove() == n3);
        assertTrue(bh.remove() == n4);
        assertTrue(bh.remove() == n5);
        assertTrue(bh.remove() == n6);
        assertTrue(bh.remove() == n7);
        assertTrue(bh.remove() == n8);
        assertTrue(bh.remove() == n9);
        assertTrue(bh.remove() == n10);

        assertTrue(bh.isEmpty());

    }

    /**
     * Returns the left child of a given element in this binary heap, or null if
     * the element has no left child.
     * This method performs a search of the underlying ArrayList object
     * (using the indexOf method) and should be used for testing purposes only.
     * It is not used to implement binary heap adds or removes.
     * @param element A binary heap element
     * @return The element's left child or null
     */
    private Object leftChild(Object element) {
        int index = bh.indexOf(element)*2;
        if ( outOfRange(index) )
            return null;
        else
            return bh.get(index);
    }

    /**
     * Returns the right child of a given element in this binary heap, or null if
     * the element has no right child.
     * This method performs a search of the underlying ArrayList object
     * (using the indexOf method) and should be used for testing purposes only.
     * It is not used to implement binary heap adds or removes.
     * @param element A binary heap element
     * @return The element's right child or null
     */
    private Object rightChild(Object element) {
        int index = bh.indexOf(element)*2+1;
        if ( outOfRange(index) )
            return null;
        else
            return bh.get(index);
    }

    /**
     * Returns the parent of a given element in this binary heap, or null if
     * the element is the root.
     * This method performs a search of the underlying ArrayList object
     * (using the indexOf method) and should be used for testing purposes only.
     * It is not used to implement binary heap adds or removes.
     * @param element A binary heap element
     * @return The element's parent or null
     */
    private Object parent(Object element) {
        int index = bh.indexOf(element)/2;
        if ( outOfRange(index) )
            return null;
        else 
            return bh.get(index);
    }

    /**
     * Returns whether a given index is out of range for this binary heap.
     * Since the first element of the underlying ArrayList object is not used,
     * and index is out of range if it is less than 1 or greater than the
     * size of this binary heap.
     * @param index An index into this binary heap
     * @return Whether the index is out of range
     */
    private boolean outOfRange(int index) {
        return index < 1 || index > bh.size();
    }

}