package waterjug;

import org.junit.Test;
import static org.junit.Assert.*;

/**
 * A class to test the WaterJugState class
 * @author Michael Coughlin
 * CS2511 Fall 2014
 * Lab Section 7
 */
public class WaterJugStateTest {
    
    private String state1String = "       |   |\n" +
                                  "|   |  |   |\n" +
                                  "|   |  |   |\n" +
                                  "|   |  |   |\n" +
                                  "+---+  +---+\n" +
                                  "  X      Y  \n";
                                 
    
    private String state2String = "       |***|\n" +
                                  "|***|  |***|\n" +
                                  "|***|  |***|\n" +
                                  "|***|  |***|\n" +
                                  "+---+  +---+\n" +
                                  "  X      Y  \n";
    
    // states used in the test methods
    private WaterJugState state1 = new WaterJugState(0,0);
    private WaterJugState state2 = new WaterJugState(3,4);
    private WaterJugState state3 = new WaterJugState(3,2);
    private WaterJugState state4 = new WaterJugState(2,3);
    private WaterJugState state1Copy = new WaterJugState(0,0);

    /**
     * This method tests the accessors (getters) for <b>WaterJugState</b> objects.
     */
    @Test
    public void testAccessors() {
        assertTrue(state1.getJugX() == 0);
        assertTrue(state1.getJugY() == 0);
        assertTrue(state2.getJugX() == 3);
        assertTrue(state2.getJugY() == 4);
        assertTrue(state3.getJugX() == 3);
        assertTrue(state3.getJugY() == 2);
        assertTrue(state4.getJugX() == 2);
        assertTrue(state4.getJugY() == 3);
   
    }

    /**
     * This method tests the <b>equals</b> method for <b>WaterJugState</b> objects.
     */
    @Test
    public void testEquals() {
        assertFalse(state1.equals(state2));
        assertTrue(state1.equals(state1Copy));
        assertFalse(state3.equals(state4));  
    }

    /**
     * This method tests the <b>toString</b> method for <b>WaterJugState</b> objects.
     * Look at the definitions of <b>state1String</b> and <b>state2String</b> to see
     * how <b>toString</b> should format a state's string representation.
     */
    @Test
    public void testToString() {
        assertTrue(state1.toString().equals(state1String));
        assertTrue(state2.toString().equals(state2String));
    }
}
