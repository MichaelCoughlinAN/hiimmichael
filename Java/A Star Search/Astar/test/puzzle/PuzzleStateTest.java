/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package puzzle;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author Michael
 */
public class PuzzleStateTest {
    
    private PuzzleState state1 = new PuzzleState(1,2,3,8,0,4,7,6,5);
   
    private PuzzleState state2 = new PuzzleState(2,1,8,3,0,4,7,6,5);
    
    private PuzzleState state1Copy = new PuzzleState(1,2,3,8,0,4,7,6,5);
    
  
    /**
     * This method tests the accessors (getters) for <b>PuzzleState</b> objects.
     */
    @Test
    public void testAccessors() {
        assertTrue(state1.getFirstPosition() == 1);
        assertTrue(state1.getSecondPosition() == 2);
        assertTrue(state1.getThirdPosition() == 3);
        assertTrue(state1.getForthPosition() == 8);
        assertTrue(state1.getFifthPosition()== 0);
        assertTrue(state1.getSixthPosition()== 4);
        assertTrue(state1.getSeventhPosition()== 7);
        assertTrue(state1.getEigthPosition()== 6);
   
    }
    
    /**
     * This method tests the <b>equals</b> method for <b>PuzzleState</b> objects.
     * Note that the time taken to get to a state is not taken into account.
     */
    @Test
    public void testEquals() {
        assertFalse(state1.equals(state2));
        assertTrue(state1.equals(state1Copy));

    }

  
    
}
