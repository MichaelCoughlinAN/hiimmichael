/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package puzzle;

import framework.Canvas;
import framework.Move;
import framework.Problem;
import framework.State;
import java.awt.Component;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JFrame;

/**
 * This class represents the 8-Puzzle problem.
 * It provides an introductory message describing the problem,
 * stores the problem's possible moves and current state, and
 * checks for whether the problem has been successfully solved.
 * Note that this class extends the abstract class <b>Problem</b> and
 * therefore imports <b>framework.Problem</b>.
 * This class inherits the <b>setIntroduction(), setCurrentState()</b>, and
 * <b>setMoves()</b> methods from its parent
 * and thus it should not have any instance fields for these attributes.
 * @author Michael Coughlin
 * CS2511 Fall 2014
 * Lab Section 1
 */
public class PuzzleProblem extends Problem {

     /**
     * Constructs a new puzzle problem object. Eight new puzzle state object
     * should be constructed. This state should be set as the current state of 
     * the problem using the inherited <b>setCurrentState()</b> method.
     * The eight valid moves should be created and stored on a list using
     * the inherited <b>setMoves()</b> method.
     * The appropriate introduction string for this problem should be stored
     * using the inherited <b>setIntroduction()</b>.
     */
    public PuzzleProblem() {
       setCurrentState(new PuzzleState(2, 8, 3, 1, 6, 4, 7, 0, 5));
       setFinalState(new PuzzleState(1, 2, 3, 8, 0, 4, 7, 6, 5));
       setIntroduction(
            "Welcome to the 8-Puzzle Problem.\n\n" +
            "You are given a 3x3 board in which 8 numbered tiles can slide around.\n" +
            "There is one blank space that holds no tile. A legal move consists\n" +
            "of sliding a tile into the blank space if the tile is adjacent to it.\n" +
            "The goal is to move tiles around until the board looks like the final\n" +
            "state below." 
       );
                     setMoves(new ArrayList<Move>());
      setChooser(true);
        getMoves().add(new PuzzleMove("Slide Tile 1"));
        getMoves().add(new PuzzleMove("Slide Tile 2"));
        getMoves().add(new PuzzleMove("Slide Tile 3"));
        getMoves().add(new PuzzleMove("Slide Tile 4"));
        getMoves().add(new PuzzleMove("Slide Tile 5"));
        getMoves().add(new PuzzleMove("Slide Tile 6"));
        getMoves().add(new PuzzleMove("Slide Tile 7"));
        getMoves().add(new PuzzleMove("Slide Tile 8"));

        PuzzleState start1 =
                new PuzzleState(2, 8, 3, 1, 6, 4, 7, 0, 5); // 5 moves

        PuzzleState start2 =
                new PuzzleState(3, 6, 4, 1, 0, 2, 8, 7, 5); // 10 moves

        PuzzleState start3 =
                new PuzzleState(3, 0, 4, 1, 6, 5, 8, 2, 7); // 13 moves

        PuzzleState start4 =
                new PuzzleState(2, 1, 3, 8, 0, 4, 6, 7, 5); // 18 moves

        PuzzleState start5 =
                new PuzzleState(4, 2, 0, 8, 3, 6, 7, 5, 1); // 20 moves

        PuzzleState start6 =
                new PuzzleState(1, 6, 3, 4, 0, 8, 7, 2, 5); // 24 moves

        PuzzleState start7 =
                new PuzzleState(5, 2, 7, 8, 0, 4, 3, 6, 1); // 30 moves

        PuzzleState start8 =
                new PuzzleState(5, 6, 7, 4, 0, 8, 3, 2, 1); // 30 moves

        PuzzleState finalState =
                new PuzzleState(1, 2, 3, 8, 0, 4, 7, 6, 5);

        List<State> initialStates = new ArrayList<State>();
        List<State> finalStates = new ArrayList<State>();
        List<Integer> moveCounts = new ArrayList<Integer>();
        List<Canvas> initialCanvases = new ArrayList<Canvas>();
        List<Canvas> finalCanvases = new ArrayList<Canvas>();

        initialStates.add(start1);    finalStates.add(finalState); moveCounts.add(5);
        initialStates.add(start2);    finalStates.add(finalState); moveCounts.add(10);
        initialStates.add(start3);    finalStates.add(finalState); moveCounts.add(13);
        initialStates.add(start4);    finalStates.add(finalState); moveCounts.add(18);
        initialStates.add(start5);    finalStates.add(finalState); moveCounts.add(20);
        initialStates.add(start6);    finalStates.add(finalState); moveCounts.add(24);
        initialStates.add(start7);    finalStates.add(finalState); moveCounts.add(30);
        initialStates.add(start8);    finalStates.add(finalState); moveCounts.add(30);


        initialCanvases.add(new PuzzleCanvasIconified(start1));
        initialCanvases.add(new PuzzleCanvasIconified(start2));
        initialCanvases.add(new PuzzleCanvasIconified(start3));
        initialCanvases.add(new PuzzleCanvasIconified(start4));
        initialCanvases.add(new PuzzleCanvasIconified(start5));
        initialCanvases.add(new PuzzleCanvasIconified(start6));
        initialCanvases.add(new PuzzleCanvasIconified(start7));
        initialCanvases.add(new PuzzleCanvasIconified(start8));

        finalCanvases.add(new PuzzleCanvasIconified(finalState));
        finalCanvases.add(new PuzzleCanvasIconified(finalState));
        finalCanvases.add(new PuzzleCanvasIconified(finalState));
        finalCanvases.add(new PuzzleCanvasIconified(finalState));
        finalCanvases.add(new PuzzleCanvasIconified(finalState));
        finalCanvases.add(new PuzzleCanvasIconified(finalState));
        finalCanvases.add(new PuzzleCanvasIconified(finalState));
        finalCanvases.add(new PuzzleCanvasIconified(finalState));

        setInitialCanvases(initialCanvases);
        setFinalCanvases(finalCanvases);
        setInitialStates(initialStates);
        setFinalStates(finalStates);
        setMoveCounts(moveCounts);
    
    }

     /**
     * Returns whether the current state of this problem is a success.
     * Note that this method implements the abstract <b>success</b> method declared
     * in the parent.
     * Note also that the current state of the problem must be gotten using the
     * inherited <b>getCurrentState()</b> method.
     * Since that method returns a value of type <b>State</b>, it must be cast to
     * <b>PuzzleState</b> before processing.
     * @return <b>true</b> if the current state is a success, <b>false</b> otherwise
     */
    @Override
    public boolean success() {
        PuzzleState cur = (PuzzleState)getCurrentState();
        return cur.getFirstPosition() == 1 && cur.getSecondPosition() == 2 &&
               cur.getThirdPosition() == 3 && cur.getForthPosition() == 8 &&
               cur.getFifthPosition() == 0 && cur.getSixthPosition() == 4 &&
               cur.getSeventhPosition() == 7 && cur.getEigthPosition() == 6 &&
               cur.getNinthPosition() == 5;
    }

  

}

