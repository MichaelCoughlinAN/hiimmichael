package bridge;

import java.util.List;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 * A class to test the BridgeProblem class.
 * @author tcolburn
 */
public class BridgeProblemTest {
    
    // Some instance fields used in the test methods below
    
    private BridgeProblem problem;
    
    private List<BridgeMove> moves;

    private BridgeMove p1 = new BridgeMove("P1 crosses alone");
    private BridgeMove p2 = new BridgeMove("P2 crosses alone");
    private BridgeMove p5 = new BridgeMove("P5 crosses alone");
    private BridgeMove p10 = new BridgeMove("P10 crosses alone");
    private BridgeMove p1p2 = new BridgeMove("P1 crosses with P2");
    private BridgeMove p1p5 = new BridgeMove("P1 crosses with P5");
    private BridgeMove p1p10 = new BridgeMove("P1 crosses with P10");
    private BridgeMove p2p5 = new BridgeMove("P2 crosses with P5");
    private BridgeMove p2p10 = new BridgeMove("P2 crosses with P10");
    private BridgeMove p5p10 = new BridgeMove("P5 crosses with P10");
    
    /**
     * Creates a new bridge problem object and extracts the move list for use
     * in the test methods below.
     */
    public BridgeProblemTest() {
        problem = new BridgeProblem();
        moves = problem.getMoves();
    }
    
    @Test
    /**
     * Tests the getter (accessor) for the problem's introduction string.
     */
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
    
    /**
     * An auxiliary method used in the <b>testMoves</b> method,
     * this method searches the problem's move list for a move with the given name.
     * @param moveName the name of the move to find
     * @return the bridge move object with the given name
     */
    private BridgeMove findMove(String moveName) {
        for (BridgeMove move : moves) {
            if (move.getMoveName().equals(moveName)) {
                return move;
            }
        }
        return null;
    }
    
    @Test
    /**
     * Tests to make sure all and only the 10 correct move objects
     * are on the problem's move list.
     */
    public void testMoves() {
    
        String[] moveNames = new String[]{"P1 crosses alone",
                                          "P2 crosses alone",
                                          "P5 crosses alone",
                                          "P10 crosses alone",
                                          "P1 crosses with P2",
                                          "P1 crosses with P5",
                                          "P1 crosses with P10",
                                          "P2 crosses with P5",
                                          "P2 crosses with P10",
                                          "P5 crosses with P10"};
        
        assertTrue(moveNames.length==moves.size());
        
        for (String name : moveNames) {
            assertTrue(findMove(name) != null);
        }
    }
    
    /**
     * An auxiliary method used in the <b>testSolutionFail</b> and
     * <b>testSolutionSucceed</b> methods, this method performs a move
     * on the problem's current state and updates it.
     * @param move the bridge move to be performed
     * @param problem the bridge problem whose current state is to be updated
     */
    private void tryMove(BridgeMove move, BridgeProblem problem) {
        BridgeState state = problem.getCurrentState();
        BridgeState next = move.doMove(state);
        problem.setCurrentState(next);
    }
    
    @Test
    /**
     * Simulates a failed attempt to solve the bridge crossing problem.
     */
    public void testSolutionFail() {
                                                     // P1 |   |
                                                     // P2 |   |
                                                     //  f |===|
                                                     // P5 |   |
                                                     //P10 |   |
                                                     //time: 0
        assertFalse(problem.success());            
        tryMove(p1p10, problem);                     //    |   | P1
                                                     // P2 |   |   
                                                     //    |===| f
                                                     // P5 |   |
                                                     //    |   | P10
                                                     //time: 10
        assertFalse(problem.success());
        tryMove(p1, problem);                        // P1 |   |   
                                                     // P2 |   |   
                                                     //  f |===|
                                                     // P5 |   |
                                                     //    |   | P10
                                                     //time: 11
        assertFalse(problem.success());
        tryMove(p1p5, problem);                      //    |   | P1
                                                     // P2 |   |   
                                                     //    |===| f
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 16
        assertFalse(problem.success());
        tryMove(p1, problem);                        // P1 |   |   
                                                     // P2 |   |   
                                                     //  f |===|
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 17
        assertFalse(problem.success());
        tryMove(p1p2, problem);                      //    |   | P1
                                                     //    |   | P2
                                                     //    |===| f
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 19
        assertFalse(problem.success());
    }
    
    @Test
    /**
     * Simulates a successful attempt to solve the bridge crossing problem.
     */
    public void testSolutionSucceed() {
                                                     // P1 |   |
                                                     // P2 |   |
                                                     //  f |===|
                                                     // P5 |   |
                                                     //P10 |   |
                                                     //time: 0
        assertFalse(problem.success());            
        tryMove(p1p2, problem);                      //    |   | P1
                                                     //    |   | P2
                                                     //    |===| f
                                                     // P5 |   |
                                                     //P10 |   |
                                                     //time: 2
        assertFalse(problem.success());
        tryMove(p1, problem);                        // P1 |   |   
                                                     //    |   | P2
                                                     //  f |===|
                                                     // P5 |   |
                                                     //P10 |   |
                                                     //time: 3
        assertFalse(problem.success());
        tryMove(p5p10, problem);                     // P1 |   |   
                                                     //    |   | P2
                                                     //    |===| f
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 13
        assertFalse(problem.success());
        tryMove(p2, problem);                        // P1 |   |   
                                                     // P2 |   |   
                                                     //  f |===|
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 15
        assertFalse(problem.success());
        tryMove(p1p2, problem);                      //    |   | P1
                                                     //    |   | P2
                                                     //    |===| f
                                                     //    |   | P5
                                                     //    |   | P10
                                                     //time: 17
        assertTrue(problem.success());
    }
}
