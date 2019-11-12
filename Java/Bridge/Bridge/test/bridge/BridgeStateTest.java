package bridge;

import org.junit.Test;
import static org.junit.Assert.*;

/**
 * A class to test the BridgeState class.
 * @author tcolburn
 */
public class BridgeStateTest {
    
    // Some instance fields used in the test methods below
    
    private BridgeState state1 = new BridgeState(Position.WEST, 
                                                 Position.WEST, 
                                                 Position.WEST, 
                                                 Position.WEST, 
                                                 Position.WEST,
                                                 0);
    
    private String state1String = " P1 |   |\n" +
                                  " P2 |   |\n" +
                                  "  f |===|\n" +
                                  " P5 |   |\n" +
                                  "P10 |   |\n" +
                                  "Time elapsed so far: 0 minutes.\n";
    
    private BridgeState state2 = new BridgeState(Position.EAST, 
                                                 Position.WEST, 
                                                 Position.EAST, 
                                                 Position.EAST, 
                                                 Position.WEST,
                                                 5);
    
    private String state2String = "    |   | P1\n" +
                                  " P2 |   |\n" +
                                  "    |===| f\n" +
                                  "    |   | P5\n" +
                                  "P10 |   |\n" +
                                  "Time elapsed so far: 5 minutes.\n";
    
    private BridgeState state1Copy = new BridgeState(Position.WEST, 
                                                     Position.WEST, 
                                                     Position.WEST, 
                                                     Position.WEST, 
                                                     Position.WEST,
                                                     10);

    @Test
    /**
     * Tests the state's getter (accessor) methods
     */
    public void testAccessors() {
        assertTrue(state2.getP1Position()==Position.EAST);         //    |   | P1
        assertTrue(state2.getP2Position()==Position.WEST);         // P2 |   |
        assertTrue(state2.getFlashlightPosition()==Position.EAST); //    |===| f
        assertTrue(state2.getP5Position()==Position.EAST);         //    |   | P5
        assertTrue(state2.getP10Position()==Position.WEST);        //P10 |   |
    }
    
    @Test
    /**
     * Tests state equality
     */
    public void testEquals() {
        assertFalse(state1.equals(state2));
        assertTrue(state1.equals(state1Copy)); // state1 and state1Copy are equal
        assertFalse(state1==state1Copy);       // but they are not identical
        
        // Some more random states and equality tests
        
        BridgeState wwwww = new BridgeState(Position.WEST, 
                                            Position.WEST, 
                                            Position.WEST, 
                                            Position.WEST, 
                                            Position.WEST,
                                            0);
        
        BridgeState wwwwe = new BridgeState(Position.WEST, 
                                            Position.WEST, 
                                            Position.WEST, 
                                            Position.WEST, 
                                            Position.EAST,
                                            0);
        
        BridgeState wewww = new BridgeState(Position.WEST, 
                                            Position.EAST, 
                                            Position.WEST, 
                                            Position.WEST, 
                                            Position.WEST,
                                            0);
        
        BridgeState eeeee = new BridgeState(Position.EAST, 
                                            Position.EAST, 
                                            Position.EAST, 
                                            Position.EAST, 
                                            Position.EAST,
                                            0);
        
        BridgeState eeewe = new BridgeState(Position.EAST, 
                                            Position.EAST, 
                                            Position.EAST, 
                                            Position.WEST, 
                                            Position.EAST,
                                            0);
        
        BridgeState weeew = new BridgeState(Position.WEST, 
                                            Position.EAST, 
                                            Position.EAST, 
                                            Position.EAST, 
                                            Position.WEST,
                                            0);
        
        assertFalse(wwwww.equals(wwwwe));
        assertFalse(wwwwe.equals(wewww));
        assertFalse(wewww.equals(eeeee));
        assertFalse(eeeee.equals(eeewe));
        assertFalse(eeewe.equals(weeew));
        assertTrue(state1Copy.equals(wwwww));
    }

    @Test
    /**
     * Tests the string representation of a state
     */
    public void testToString() {
        assertTrue(state1.toString().equals(state1String));
        assertTrue(state2.toString().equals(state2String));
    }
}
