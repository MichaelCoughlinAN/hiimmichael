/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package puzzle;

import framework.Move;
import framework.State;
import org.junit.After;
import org.junit.AfterClass;
import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

/**
 *
 * @author Michael
 */
public class PuzzleMoveTest {
    
    private State start = new PuzzleState(2, 8, 3, 1, 6, 4, 7, 0, 5);  // +---+---+---+ 
                                                                       // | 2 | 8 | 3 | 
                                                                       // +---+---+---+ 
                                                                       // | 1 | 6 | 4 | 
                                                                       // +---+---+---+ 
                                                                       // | 7 |   | 5 | 
                                                                       // +---+---+---+   
    
    private Move t1 = new PuzzleMove("Slide Tile 1");
    private Move t2 = new PuzzleMove("Slide Tile 2");
    private Move t3 = new PuzzleMove("Slide Tile 3");
    private Move t4 = new PuzzleMove("Slide Tile 4");
    private Move t5 = new PuzzleMove("Slide Tile 5");
    private Move t6 = new PuzzleMove("Slide Tile 6");
    private Move t7 = new PuzzleMove("Slide Tile 7");
    private Move t8 = new PuzzleMove("Slide Tile 8");

     @Test
    /**
     * Tests the moving of tile 7 and the empty spot. First, tile one is moved and
     * the new state is tested, t1 is moved back to the original position,
     * and the new state is tested again.
     */
    public void testT7() {
        PuzzleState next = (PuzzleState) t7.doMove(start);
        assertTrue(next.equals(new PuzzleState(2,8,3,1,6,4,0,7,5)));
       
        next = (PuzzleState) t7.doMove(next); // perform same move on next state
        assertTrue(next.equals(start));       // should go back to start  
    }
    

    @Test
    /**
     * Tests situations where tiles are moved when they cannot be. 
     */
    public void testInvalidMove() {
        PuzzleState next = (PuzzleState) t1.doMove(start);
        assertTrue(next==null); // t1 was not moved
        next = (PuzzleState) t2.doMove(start);
        assertTrue(next==null); // t2 was not moved
    }
    
    @Test
    /**
     * Tests to ensure that a state object is not altered when a move is
     * performed on it.
     */
    public void testImmutability() {
        PuzzleState next = (PuzzleState) t5.doMove(start);
        assertTrue(start.equals(new PuzzleState(2, 8, 3, 1, 6, 4, 7, 0, 5)));
    }
}
