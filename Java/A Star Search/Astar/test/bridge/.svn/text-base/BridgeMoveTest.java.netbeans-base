package bridge;

import framework.Move;
import framework.State;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 * A class to test the BridgeMove class.
 * @author tcolburn
 */
public class BridgeMoveTest {
    
    private State start = new BridgeState(Position.WEST, // P1 |   |
                                          Position.WEST, // P2 |   |
                                          Position.WEST, //  f |===|
                                          Position.WEST, // P5 |   |
                                          Position.WEST, // P10|   |
                                          0);
    
    private Move p1 = new BridgeMove("P1 crosses alone");
    private Move p2 = new BridgeMove("P2 crosses alone");
    private Move p5 = new BridgeMove("P5 crosses alone");
    private Move p10 = new BridgeMove("P10 crosses alone");
    private Move p1p2 = new BridgeMove("P1 crosses with P2");
    private Move p1p5 = new BridgeMove("P1 crosses with P5");
    private Move p1p10 = new BridgeMove("P1 crosses with P10");
    private Move p2p5 = new BridgeMove("P2 crosses with P5");
    private Move p2p10 = new BridgeMove("P2 crosses with P10");
    private Move p5p10 = new BridgeMove("P5 crosses with P10");
    
    @Test
    /**
     * Tests the crossing of P1 alone.  P1 is crossed to the other side,
     * the new state is tested, P1 is crossed back to the original side,
     * and the new state is tested again.
     */
    public void testP1() {
        BridgeState next = (BridgeState) p1.doMove(start);
        assertTrue(next.equals(new BridgeState(Position.EAST, //    |   | P1
                                               Position.WEST, // P2 |   |
                                               Position.EAST, //    |===| f
                                               Position.WEST, // P5 |   |
                                               Position.WEST, // P10|   |
                                               1)));
        assertTrue(next.getTimeSoFar() == 1);
        next = (BridgeState) p1.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));       // should go back to start
        assertTrue(next.getTimeSoFar() == 2);
    }
    
    @Test
    /**
     * Tests the crossing of P2 alone.  P2 is crossed to the other side,
     * the new state is tested, P2 is crossed back to the original side,
     * and the new state is tested again.
     */
    public void testP2() {
        BridgeState next = (BridgeState) p2.doMove(start);
        assertTrue(next.equals(new BridgeState(Position.WEST, // P1 |   |   
                                               Position.EAST, //    |   | P2
                                               Position.EAST, //    |===| f
                                               Position.WEST, // P5 |   |
                                               Position.WEST, // P10|   |
                                               2)));
        assertTrue(next.getTimeSoFar() == 2);
        next = (BridgeState) p2.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));       // should go back to start
        assertTrue(next.getTimeSoFar() == 4);
    }
    
    @Test
    /**
     * Tests the crossing of P5 alone.  P5 is crossed to the other side,
     * the new state is tested, P5 is crossed back to the original side,
     * and the new state is tested again.
     */
    public void testP5() {
        BridgeState next = (BridgeState) p5.doMove(start);
        assertTrue(next.equals(new BridgeState(Position.WEST, // P1 |   |   
                                               Position.WEST, // P2 |   |   
                                               Position.EAST, //    |===| f
                                               Position.EAST, //    |   | P5
                                               Position.WEST, // P10|   |
                                               5)));
        assertTrue(next.getTimeSoFar() == 5);
        next = (BridgeState) p5.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));       // should go back to start
        assertTrue(next.getTimeSoFar() == 10);
    }
    
    @Test
    /**
     * Tests the crossing of P10 alone.  P10 is crossed to the other side,
     * the new state is tested, P10 is crossed back to the original side,
     * and the new state is tested again.
     */
    public void testP10() {
        BridgeState next = (BridgeState) p10.doMove(start);
        assertTrue(next.equals(new BridgeState(Position.WEST, // P1 |   |   
                                               Position.WEST, // P2 |   |   
                                               Position.EAST, //    |===| f
                                               Position.WEST, // P5 |   |   
                                               Position.EAST, //    |   | P10
                                               10)));
        assertTrue(next.getTimeSoFar() == 10);
        next = (BridgeState) p10.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));        // should go back to start
        assertTrue(next.getTimeSoFar() == 20);
    }
    
    @Test
    /**
     * Tests the crossing of P1 and P2 together.  P1 and P2 are crossed to the other side,
     * the new state is tested, P1 and P2 are crossed back to the original side,
     * and the new state is tested again.
     */
    public void testP1P2() {
        BridgeState next = (BridgeState) p1p2.doMove(start);
        assertTrue(next.equals(new BridgeState(Position.EAST, //    |   | P1
                                               Position.EAST, //    |   | P2
                                               Position.EAST, //    |===| f
                                               Position.WEST, // P5 |   |
                                               Position.WEST, // P10|   |
                                               2)));
        assertTrue(next.getTimeSoFar() == 2);
        next = (BridgeState) p1p2.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));         // should go back to start
        assertTrue(next.getTimeSoFar() == 4);
    }
    
    @Test
    /**
     * Tests the crossing of P1 and P5 together.  P1 and P5 are crossed to the other side,
     * the new state is tested, P1 and P5 are crossed back to the original side,
     * and the new state is tested again.
     */
    public void testP1P5() {
        BridgeState next = (BridgeState) p1p5.doMove(start);
        assertTrue(next.equals(new BridgeState(Position.EAST, //    |   | P1
                                               Position.WEST, // P2 |   |   
                                               Position.EAST, //    |===| f
                                               Position.EAST, //    |   | P5
                                               Position.WEST, // P10|   |
                                               5)));
        assertTrue(next.getTimeSoFar() == 5);
        next = (BridgeState) p1p5.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));         // should go back to start
        assertTrue(next.getTimeSoFar() == 10);
    }
    
    @Test
    /**
     * Tests the crossing of P1 and P10 together.  P1 and P10 are crossed to the other side,
     * the new state is tested, P1 and P10 are crossed back to the original side,
     * and the new state is tested again.
     */
    public void testP1P10() {
        BridgeState next = (BridgeState) p1p10.doMove(start);
        assertTrue(next.equals(new BridgeState(Position.EAST, //    |   | P1
                                               Position.WEST, // P2 |   |   
                                               Position.EAST, //    |===| f
                                               Position.WEST, // P5 |   |   
                                               Position.EAST, //    |   | P10
                                               10)));
        assertTrue(next.getTimeSoFar() == 10);
        next = (BridgeState) p1p10.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));          // should go back to start
        assertTrue(next.getTimeSoFar() == 20);
    }
    
    @Test
    /**
     * Tests the crossing of P2 and P5 together.  P2 and P5 are crossed to the other side,
     * the new state is tested, P2 and P5 are crossed back to the original side,
     * and the new state is tested again.
     */
    public void testP2P5() {
        BridgeState next = (BridgeState) p2p5.doMove(start);
        assertTrue(next.equals(new BridgeState(Position.WEST, // P1 |   |   
                                               Position.EAST, //    |   | P2
                                               Position.EAST, //    |===| f
                                               Position.EAST, //    |   | P5
                                               Position.WEST, // P10|   |    
                                               5)));
        assertTrue(next.getTimeSoFar() == 5);
        next = (BridgeState) p2p5.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));         // should go back to start
        assertTrue(next.getTimeSoFar() == 10);
    }
    
    @Test
    /**
     * Tests the crossing of P2 and P10 together.  P2 and P10 are crossed to the other side,
     * the new state is tested, P2 and P10 are crossed back to the original side,
     * and the new state is tested again.
     */
    public void testP2P10() {
        BridgeState next = (BridgeState) p2p10.doMove(start);
        assertTrue(next.equals(new BridgeState(Position.WEST, // P1 |   |   
                                               Position.EAST, //    |   | P2
                                               Position.EAST, //    |===| f
                                               Position.WEST, // P5 |   |   
                                               Position.EAST, //    |   | P10
                                               10)));
        assertTrue(next.getTimeSoFar() == 10);
        next = (BridgeState) p2p10.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));          // should go back to start
        assertTrue(next.getTimeSoFar() == 20);
    }
    
    @Test
    /**
     * Tests the crossing of P5 and P10 together.  P5 and P10 are crossed to the other side,
     * the new state is tested, P5 and P10 are crossed back to the original side,
     * and the new state is tested again.
     */
    public void testP5P10() {
        BridgeState next = (BridgeState) p5p10.doMove(start);
        assertTrue(next.equals(new BridgeState(Position.WEST, // P1 |   |   
                                               Position.WEST, // P2 |   |   
                                               Position.EAST, //    |===| f
                                               Position.EAST, //    |   | P5
                                               Position.EAST, //    |   | P10
                                               10)));
        assertTrue(next.getTimeSoFar() == 10);
        next = (BridgeState) p5p10.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));          // should go back to start
        assertTrue(next.getTimeSoFar() == 20);
    }
    
    private BridgeState state = new BridgeState(Position.WEST, // P1 |   |   
                                                Position.WEST, // P2 |   |   
                                                Position.EAST, //    |===| f
                                                Position.EAST, //    |   | P5
                                                Position.EAST, //    |   | P10
                                                10);
    
    @Test
    /**
     * Tests situations where two crossing persons are not on the same side, 
     * and where the flashlight is on the wrong side.
     */
    public void testInvalidMove() {
        BridgeState next = (BridgeState) p1p5.doMove(state);
        assertTrue(next==null); // P1 and P5 not on same side
        next = (BridgeState) p1p2.doMove(state);
        assertTrue(next==null); // P1 and P2 not on same side as flashlight
    }
    
    @Test
    /**
     * Tests to ensure that a state object is not altered when a move is
     * performed on it.
     */
    public void testImmutability() {
        BridgeState next = (BridgeState) p5p10.doMove(start);
        assertTrue(start.equals(new BridgeState(Position.WEST, // P1 |   |
                                                Position.WEST, // P2 |   |
                                                Position.WEST, //  f |===|
                                                Position.WEST, // P5 |   |
                                                Position.WEST, // P10|   |
                                                0)));
    }
}
