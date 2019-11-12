package framework;

import graph.DequeAdder;
import java.util.Deque;
import bridge.BridgeProblem;
import bridge.BridgeState;
import bridge.Position;
import graph.Vertex;
import java.util.List;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 * This class tests your implementation of the <b>expand</b> and <b>search</b> 
 * algorithms used in depth-first and breadth-first state space search.
 * It depends on your bridge crossing application being correctly implemented.
 * @author tcolburn
 */
public class ProblemTest {
    
    public ProblemTest() {
        
        problem = new BridgeProblem();
        
        start = 
                new BridgeState(Position.WEST, 
                                Position.WEST, 
                                Position.WEST, 
                                Position.WEST, 
                                Position.WEST,
                                0);
        
        goal = 
                new BridgeState(Position.EAST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.EAST,
                                17);
        
        /**
         * The following states are used in testExpand1 and testSearch2
         */
        p1East = 
                new BridgeState(Position.EAST, 
                                Position.WEST, 
                                Position.EAST, 
                                Position.WEST, 
                                Position.WEST,
                                0);
        
        p2East = 
                new BridgeState(Position.WEST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.WEST, 
                                Position.WEST,
                                0);
        
        p5East = 
                new BridgeState(Position.WEST, 
                                Position.WEST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.WEST,
                                0);
        
        p10East = 
                new BridgeState(Position.WEST, 
                                Position.WEST, 
                                Position.EAST, 
                                Position.WEST, 
                                Position.EAST,
                                0);
        
        p1p2East = 
                new BridgeState(Position.EAST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.WEST, 
                                Position.WEST,
                                0);
        
        p1p5East = 
                new BridgeState(Position.EAST, 
                                Position.WEST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.WEST,
                                0);
        
        p1p10East = 
                new BridgeState(Position.EAST, 
                                Position.WEST, 
                                Position.EAST, 
                                Position.WEST, 
                                Position.EAST,
                                0);
        
        p2p5East = 
                new BridgeState(Position.WEST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.WEST,
                                0);
        
        p2p10East = 
                new BridgeState(Position.WEST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.WEST, 
                                Position.EAST,
                                0);
        
        p5p10East = 
                new BridgeState(Position.WEST, 
                                Position.WEST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.EAST,
                                0);
        
        /**
         * The following states are used in testExpand2
         */
        p1p5p10West = 
                new BridgeState(Position.WEST, 
                                Position.EAST, 
                                Position.WEST, 
                                Position.WEST, 
                                Position.WEST,
                                0);
        
        p2p5p10West = 
                new BridgeState(Position.EAST, 
                                Position.WEST, 
                                Position.WEST, 
                                Position.WEST, 
                                Position.WEST,
                                0);
        
        p1p2p5p10West = 
                new BridgeState(Position.WEST, 
                                Position.WEST, 
                                Position.WEST, 
                                Position.WEST, 
                                Position.WEST,
                                0);
        
        
        /**
         * The following state is used in testSearch1
         */
        p1p2West = 
                new BridgeState(Position.WEST, 
                                Position.WEST, 
                                Position.WEST, 
                                Position.EAST, 
                                Position.EAST,
                                15);
        
        /**
         * The following states are used in testSearch2
         */
        p2p5p10East = 
                new BridgeState(Position.WEST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.EAST,
                                13);
        
        p1p5p10East = 
                new BridgeState(Position.EAST, 
                                Position.WEST, 
                                Position.EAST, 
                                Position.EAST, 
                                Position.EAST,
                                14);

        /**
         * This DequeAdder is used to perform breadth-first search in
         * testSearch1 and testSearch2
         */
        tailAdder = new DequeAdder() {
            public void add(Vertex vertex, Deque<Vertex> deque) {
                deque.addLast(vertex);
            }
        };
        
    }
    
    /**
     * This test expands the start state, checks to make sure there are
     * ten children, and they are the correct children
     */
    @Test
    public void testExpand1() {
        List<Vertex> children = problem.expand(start);
        assertTrue( children.size() == 10 );
        
        nextStates = new Vertex[] {p1East,   p2East,    p5East,   p10East,   p1p2East,
                                   p1p5East, p1p10East, p2p5East, p2p10East, p5p10East};
        
        for (Vertex next: nextStates) {
            assertTrue( children.contains(next));
        }
    }
    
    /**
     * This test expands the state where P1, P2, and the flashlight are on the
     * east side, checks to make sure there are three children, and they are the
     * correct children.
     */
//    @Test
//    public void testExpand2() {
//        List<Vertex> children = problem.expand(p1p2East);
//        assertTrue( children.size() == 3 );
//        
//        nextStates = new Vertex[] {p1p5p10West, p2p5p10West, p1p2p5p10West};
//        
//        for (Vertex next: nextStates) {
//            assertTrue( children.contains(next));
//        }
//    }
//    
//    /**
//     * This test performs a breadth-first search on a state that is one
//     * step from the goal state.  It checks to make sure that the goal 
//     * state is found, and that the goal's predecessor was correctly set.
//     * It also displays the solution in the console.
//     */
//    @Test
//    public void testSearch1() {
//        Vertex found = problem.search(p1p2West, tailAdder);
//        assertTrue( ((BridgeState) found).equals(goal) );
//        assertTrue( found.getPredecessor().equals(p1p2West) );
//        displaySolution(found);
//    }
//    
//    /**
//     * This test performs a breadth-first search on the normal start state.
//     * It checks to make sure that the goal state is found, and that the 
//     * predecessors of all the goal's ancestors were correctly set.
//     * It also displays the solution in the console.
//     */
//    @Test
//    public void testSearch2() {
//        Vertex found = problem.search(start, tailAdder);
//        assertTrue( ((BridgeState) found).equals(goal) );
//        Vertex ancestor = found.getPredecessor();
//        assertTrue( ancestor.equals(p1p2West) );
//        ancestor = ancestor.getPredecessor();
//        assertTrue( ancestor.equals(p2p5p10East) || ancestor.equals(p1p5p10East) );
//        ancestor = ancestor.getPredecessor();
//        assertTrue( ancestor.equals(p1p5p10West) || ancestor.equals(p2p5p10West));
//        ancestor = ancestor.getPredecessor();
//        assertTrue( ancestor.equals(p1p2East) );
//        ancestor = ancestor.getPredecessor();
//        assertTrue( ancestor.equals(start) );
//        displaySolution(found);
//    }
//    
    /**
     * Displays the solution to the console by recursing to the start state
     * and then individually displaying states as the recursion is unwound.
     * @param state the terminating state in the solution path
     */
    private void displaySolution(Vertex state) {
        if ( state != null ) {
            displaySolution(state.getPredecessor());
            System.out.println(state.toString());
        }
    }
    
    private Problem problem;
    
    private Vertex start;
    private Vertex goal;
    
    private Vertex p1East;
    private Vertex p2East;
    private Vertex p5East;
    private Vertex p10East;
    private Vertex p1p2East;
    private Vertex p1p5East;
    private Vertex p1p10East;
    private Vertex p2p5East;
    private Vertex p2p10East;
    private Vertex p5p10East;
    
    private Vertex p1p5p10West;
    private Vertex p2p5p10West;
    private Vertex p1p2p5p10West;
    
    private Vertex p1p2West;
    
    private Vertex p1p5p10East;
    private Vertex p2p5p10East;
    
    /**
     * The following array is used in testExpand1 and testExpand2
     */
    private Vertex[] nextStates;
    
    private DequeAdder tailAdder;
}