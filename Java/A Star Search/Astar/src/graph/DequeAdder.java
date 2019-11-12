package graph;

import java.util.Deque;

/**
 * This interface represents an object that adds a vertex to a double-ended
 * queue of vertices.
 * Different implementations can add vertices to different parts of the
 * queue, at the head or the tail, for example, in order to implement
 * different kinds of graph search.
 * @author tcolburn
 */
public interface DequeAdder {

    /**
     * Adds a vertex to a double-ended queue of vertices
     * @param vertex A graph vertex
     * @param deque A double-ended queue of vertices
     */
    void add(Vertex vertex, Deque<Vertex> deque);

}
