package bridge;

import framework.Problem;
import framework.State;
import framework.Move;
import java.util.List;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 * A class to test the BridgeProblem class.
 * @author tcolburn
 */
public class BridgeProblemTest {
    
    private Problem problem = new BridgeProblem();
    
    private List<Move> moves = problem.getMoves();
    
    /**
     * Searches the problem's move list for a move with the given name
     * @param moveName the name of the desired move
     * @return the move with the given name or null if not found
     */
    private Move findMove(String moveName) {
        for (Move move : moves) {
            if (move.getMoveName().equals(moveName)) {
                return move;
            }
        }
        return null;
    }

    private Move p1;
    private Move p2;
    private Move p5;
    private Move p10;
    private Move p1p2;
    private Move p1p5;
    private Move p1p10;
    private Move p2p5;
    private Move p2p10;
    private Move p5p10;
    
    /**
     * Initializes the move objects.
     */
    private void initializeMoves() {
        p1 = findMove("P1 crosses alone");
        p2 = findMove("P2 crosses alone");
        p5 = findMove("P5 crosses alone");
        p10 = findMove("P10 crosses alone");
        p1p2 = findMove("P1 crosses with P2");
        p1p5 = findMove("P1 crosses with P5");
        p1p10 = findMove("P1 crosses with P10");
        p2p5 = findMove("P2 crosses with P5");
        p2p10 = findMove("P2 crosses with P10");
        p5p10 = findMove("P5 crosses with P10");
    }
    
    /**
     * Tries to perform a move on the current state of the problem.
     * The problem's current state is updated to the next state, which 
     * could be null.
     * @param move the move to try
     */
    private void tryMove(Move move) {
        State state = problem.getCurrentState();
        State next = move.doMove(state);
        problem.setCurrentState(next);
    }
    
    /**
     * Tests to be sure the problem represents all the moves.
     */
    @Test
    public void testMoves() {
        initializeMoves();
        assertTrue(p1 != null);
        assertTrue(p2 != null);
        assertTrue(p5 != null);
        assertTrue(p10 != null);
        assertTrue(p1p2 != null);
        assertTrue(p1p5 != null);
        assertTrue(p1p10 != null);
        assertTrue(p2p5 != null);
        assertTrue(p2p10 != null);
        assertTrue(p5p10 != null);
    }
    
    /**
     * Tests a failed attempt to solve the bridge crossing problem.
     */
    @Test
    public void testSolutionFail() {
        initializeMoves();
                                                     // P1 |   |
                                                     // P2 |   |
                                                     //  f |===|
                                                     // P5 |   |
                                                     //P10 |   |
                                                     //time: 0
        assertFalse(problem.success());            
        tryMove(p1p10);                              //    |   | P1
                                                     // P2 |   |   
                                                     //    |===| f
                                                     // P5 |   |
                                                     //    |   | P10
                                                     //time: 10
        assertFalse(problem.success());
        tryMove(p1);                                 // P1 |   |   
                                                     // P2 |   |   
                                                     //  f |===|
                                                     // P5 |   |
                                                     //    |   | P10
                                                     //time: 11
        assertFalse(problem.success());
        tryMove(p1p5);                               //    |   | P1
                                                     // P2 |   |   
                                                     //    |===| f
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 16
        assertFalse(problem.success());
        tryMove(p1);                                 // P1 |   |   
                                                     // P2 |   |   
                                                     //  f |===|
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 17
        assertFalse(problem.success());
        tryMove(p1p2);                               //    |   | P1
                                                     //    |   | P2
                                                     //    |===| f
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 19
        assertFalse(problem.success());
    }
    
    /**
     * Tests a successful attempt to solve the bridge crossing problem.
     */
    @Test
    public void testSolutionSucceed() {
        initializeMoves();
                                                     // P1 |   |
                                                     // P2 |   |
                                                     //  f |===|
                                                     // P5 |   |
                                                     //P10 |   |
                                                     //time: 0
        assertFalse(problem.success());            
        tryMove(p1p2);                               //    |   | P1
                                                     //    |   | P2
                                                     //    |===| f
                                                     // P5 |   |
                                                     //P10 |   |
                                                     //time: 2
        assertFalse(problem.success());
        tryMove(p1);                                 // P1 |   |   
                                                     //    |   | P2
                                                     //  f |===|
                                                     // P5 |   |
                                                     //P10 |   |
                                                     //time: 3
        assertFalse(problem.success());
        tryMove(p5p10);                              // P1 |   |   
                                                     //    |   | P2
                                                     //    |===| f
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 13
        assertFalse(problem.success());
        tryMove(p2);                                 // P1 |   |   
                                                     // P2 |   |   
                                                     //  f |===|
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 15
        assertFalse(problem.success());
        tryMove(p1p2);                               //    |   | P1
                                                     //    |   | P2
                                                     //    |===| f
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 17
        assertTrue(problem.success());
    }
    
    /**
     * Tests the problem's introduction string.
     */
    @Test
    public void testIntro() {
        assertTrue(problem.getIntroduction().equals(
                "Welcome to the Bridge Crossing Problem.\n\n" +
                "Person Pn can cross the bridge in n minutes.\n" +
                "Only one or two persons can cross at a time because it is dark,\n" +
                "and the flashlight must be taken on every crossing.\n" +
                "When two people cross, they travel at the speed of the slowest person.\n" +
                "Devise a sequence of crossings so that all four people get across\n" +
                "the bridge in no more than 17 minutes.\n\n"));
    }
}
