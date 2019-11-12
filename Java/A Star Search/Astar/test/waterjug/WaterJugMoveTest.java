package waterjug;

import framework.Move;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 * A class to test the WaterJugMove class.
 * @author Michael Coughlin
 * CS2511 Fall 2014
 * Lab Section 7
 */
public class WaterJugMoveTest {
    
    // You should use the BridgeMoveTest class as a model for setting up
    // the tests with private instance fields here.
     private WaterJugState start = new WaterJugState(0,0); //           |   |
                                                           //    |   |  |   |
                                                           //    |   |  |   |
                                                           //    |   |  |   | 
                                                           //    +---+  +---+
                                                           //      X      Y  
    
    private Move fX = new WaterJugMove("Fill Jug X");
    private Move fY = new WaterJugMove("Fill Jug Y");
    private Move eX =new WaterJugMove("Empty Jug X");
    private Move eY = new WaterJugMove("Empty Jug Y");
    private Move tXY = new WaterJugMove("Transfer Jug X to Jug Y");
    private Move tYX = new WaterJugMove("Transfer Jug Y to Jug X");
   
    
    /**
     * Tests filling jug X
     */
    @Test
    public void testFillX() {
        WaterJugState next = (WaterJugState) fX.doMove(start); 
        assertTrue(next.equals(new WaterJugState(3,0)));   //           |   |
                                                           //    |***|  |   |
                                                           //    |***|  |   |
                                                           //    |***|  |   | 
                                                           //    +---+  +---+
                                                           //      X      Y  
    
        assertTrue(next.getJugX() == 3);
     
    }

    /**
     * Tests filling jug Y
     */
    @Test
    public void testFillY() {
      WaterJugState next = (WaterJugState) fY.doMove(start); 
      assertTrue(next.equals(new WaterJugState(0,4)));     //           |***|
                                                           //    |   |  |***|
                                                           //    |   |  |***|
                                                           //    |   |  |***| 
                                                           //    +---+  +---+
                                                           //      X      Y  
    
      assertTrue(next.getJugY() == 4);
    }
    
    /**
     * Tests emptying jug X
     */
    @Test
    public void testEmptyX() {
      WaterJugState next = (WaterJugState) fX.doMove(start); // fills Jug X
      next = (WaterJugState) eX.doMove(next); // performs empty move on JugX
      assertTrue(next.equals(new WaterJugState(0,0)));     //           |   |
                                                           //    |   |  |   |
                                                           //    |   |  |   |
                                                           //    |   |  |   | 
                                                           //    +---+  +---+
                                                           //      X      Y  
    
      assertTrue(next.equals(start)); // should go back to start
    }
    
    /**
     * Tests emptying jug Y
     */
    @Test
    public void testEmptyY() {
      WaterJugState next = (WaterJugState) fY.doMove(start); // fills JugY
      next = (WaterJugState) eY.doMove(next); // performs empty move on JugY
      assertTrue(next.equals(new WaterJugState(0,0)));     //           |   |
                                                           //    |   |  |   |
                                                           //    |   |  |   |
                                                           //    |   |  |   | 
                                                           //    +---+  +---+
                                                           //      X      Y  
    
      assertTrue(next.equals(start)); // should go back to start
    
    }
    
    /**
     * Tests transferring jug X to jug Y
     */
    @Test
    public void testXToY() {
      WaterJugState next = (WaterJugState) fX.doMove(start); // fills jugX
      next = (WaterJugState) tXY.doMove(next); // performs transfer move on X to Y
      assertTrue(next.equals(new WaterJugState(0,3)));     //           |   |
                                                           //    |   |  |***|
                                                           //    |   |  |***|
                                                           //    |   |  |***| 
                                                           //    +---+  +---+
                                                           //      X      Y  
    
     assertTrue(next.getJugY() == 3); // JugY should now equal 3
    }
    
    /**
     * Tests transferring jug Y to jug X
     */
    @Test
    public void testYToX() {
      WaterJugState next = (WaterJugState) fY.doMove(start); // fills jugY
      next = (WaterJugState) tYX.doMove(next); // performs transfer move on Y to X
      assertTrue(next.equals(new WaterJugState(3,1)));     //           |   |
                                                           //    |***|  |   |
                                                           //    |***|  |   |
                                                           //    |***|  |***| 
                                                           //    +---+  +---+
                                                           //      X      Y  
    
     assertTrue(next.getJugY() == 1); // JugY should now equal 1
     assertTrue(next.getJugX() == 3); // JugX should now equal 3
    }
}
