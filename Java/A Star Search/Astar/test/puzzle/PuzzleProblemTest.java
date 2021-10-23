/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package puzzle;

import framework.Move;
import framework.Problem;
import framework.State;
import java.util.List;
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
public class PuzzleProblemTest {
    
     
    private Problem problem = new PuzzleProblem();
    
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

    private Move t1;
    private Move t2;
    private Move t3;
    private Move t4;
    private Move t5;
    private Move t6;
    private Move t7;
    private Move t8;
    
    /**
     * Initializes the move objects.
     */
    private void initializeMoves() {
        t1 = findMove("Slide Tile 1");
        t2 = findMove("Slide Tile 2");
        t3 = findMove("Slide Tile 3");
        t4 = findMove("Slide Tile 4");
        t5 = findMove("Slide Tile 5");
        t6 = findMove("Slide Tile 6");
        t7 = findMove("Slide Tile 7");
        t8 = findMove("Slide Tile 8");
     
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
        assertTrue(t1 != null);
        assertTrue(t2 != null);
        assertTrue(t3 != null);
        assertTrue(t4 != null);
        assertTrue(t5 != null);
        assertTrue(t6 != null);
        assertTrue(t7 != null);
        assertTrue(t8 != null);
    }
    
    /**
     * Tests a failed attempt to solve the 8-Puzzle Problem.
     */
    @Test
    public void testSolutionFail() {
        initializeMoves();
                                                     // +---+---+---+ 
                                                     // | 2 | 8 | 3 | 
                                                     // +---+---+---+ 
                                                     // | 1 | 6 | 4 | 
                                                     // +---+---+---+ 
                                                     // | 7 |   | 5 | 
                                                     // +---+---+---+   
        assertFalse(problem.success());            
        tryMove(t7);                            
                                                     // +---+---+---+ 
                                                     // | 2 | 8 | 3 | 
                                                     // +---+---+---+ 
                                                     // | 1 | 6 | 4 | 
                                                     // +---+---+---+ 
                                                     // |   | 7 | 5 | 
                                                     // +---+---+---+           
        
        assertFalse(problem.success());
        tryMove(t1);              
                                                     // +---+---+---+ 
                                                     // | 2 | 8 | 3 | 
                                                     // +---+---+---+ 
                                                     // |   | 6 | 4 | 
                                                     // +---+---+---+ 
                                                     // | 1 | 7 | 5 | 
                                                     // +---+---+---+   
        assertFalse(problem.success());            
        tryMove(t2);    
                                                     // +---+---+---+ 
                                                     // |   | 8 | 3 | 
                                                     // +---+---+---+ 
                                                     // | 2 | 6 | 4 | 
                                                     // +---+---+---+ 
                                                     // | 1 | 7 | 5 | 
                                                     // +---+---+---+   
        assertFalse(problem.success());            
        tryMove(t8);     
                                                     // +---+---+---+ 
                                                     // | 8 |   | 3 | 
                                                     // +---+---+---+ 
                                                     // | 2 | 6 | 4 | 
                                                     // +---+---+---+ 
                                                     // | 1 | 7 | 5 | 
                                                     // +---+---+---+   
        assertFalse(problem.success());            
     
    }
    
    /**
     * Tests a successful attempt to solve the bridge crossing problem.
     */
    @Test
    public void testSolutionSucceed() {
         initializeMoves();
                                                     // +---+---+---+ 
                                                     // | 2 | 8 | 3 | 
                                                     // +---+---+---+ 
                                                     // | 1 | 6 | 4 | 
                                                     // +---+---+---+ 
                                                     // | 7 |   | 5 | 
                                                     // +---+---+---+   
        assertFalse(problem.success());            
        tryMove(t6);                            
                                                     // +---+---+---+ 
                                                     // | 2 | 8 | 3 | 
                                                     // +---+---+---+ 
                                                     // | 1 |   | 4 | 
                                                     // +---+---+---+ 
                                                     // | 7 | 6 | 5 | 
                                                     // +---+---+---+           
        
        assertFalse(problem.success());
        tryMove(t8);              
                                                     // +---+---+---+ 
                                                     // | 2 |   | 3 | 
                                                     // +---+---+---+ 
                                                     // | 1 | 8 | 4 | 
                                                     // +---+---+---+ 
                                                     // | 7 | 6 | 5 | 
                                                     // +---+---+---+   
        assertFalse(problem.success());            
        tryMove(t2);    
                                                     // +---+---+---+ 
                                                     // |   | 2 | 3 | 
                                                     // +---+---+---+ 
                                                     // | 1 | 8 | 4 | 
                                                     // +---+---+---+ 
                                                     // | 7 | 6 | 5 | 
                                                     // +---+---+---+   
        assertFalse(problem.success());            
        tryMove(t1);     
                                                     // +---+---+---+ 
                                                     // | 1 | 2 | 3 | 
                                                     // +---+---+---+ 
                                                     // |   | 8 | 4 | 
                                                     // +---+---+---+ 
                                                     // | 7 | 6 | 5 | 
                                                     // +---+---+---+   
        assertFalse(problem.success());            
        tryMove(t8);     
                                                     // +---+---+---+ 
                                                     // | 1 | 2 | 3 | 
                                                     // +---+---+---+ 
                                                     // | 8 |   | 4 | 
                                                     // +---+---+---+ 
                                                     // | 7 | 6 | 5 | 
                                                     // +---+---+---+   
        assertTrue(problem.success());            
    }
    
    
}
