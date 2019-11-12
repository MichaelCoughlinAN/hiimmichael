package bridge;

import org.junit.Test;
import static org.junit.Assert.*;

/**
 * A class to test the BridgeState class.
 * @author tcolburn
 */
public class BridgeStateTest {
    
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

    /**
     * This method tests the accessors (getters) for <b>BridgeState</b> objects.
     */
    @Test
    public void testAccessors() {
        assertTrue(state2.getP1Position()==Position.EAST);
        assertTrue(state2.getP2Position()==Position.WEST);
        assertTrue(state2.getFlashlightPosition()==Position.EAST);
        assertTrue(state2.getP5Position()==Position.EAST);
        assertTrue(state2.getP10Position()==Position.WEST);
        assertTrue(state2.getTimeSoFar()==5);
    }
    
    /**
     * This method tests the <b>equals</b> method for <b>BridgeState</b> objects.
     * Note that the time taken to get to a state is not taken into account.
     */
    @Test
    public void testEquals() {
        assertFalse(state1.equals(state2));
        assertTrue(state1.equals(state1Copy));
        assertFalse(state1==state1Copy);
    }

    /**
     * This method tests the <b>toString</b> method for <b>BridgeState</b> objects.
     * Look at the definitions of <b>state1String</b> and <b>state2String</b> to see
     * how <b>toString</b> should format a state's string representation.
     */
    @Test
    public void testToString() {
        assertTrue(state1.toString().equals(state1String));
        assertTrue(state2.toString().equals(state2String));
    }
}
