/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package puzzle;

import framework.Move;
import framework.State;

/**
 * This class represents moves in the 8-Puzzle problem.
 * A move object stores its move name and knows how to apply itself
 * to a bridge state to create a new state representing the result
 * of the move.
 * Note that this class extends the abstract class <b>Move</b> and
 * therefore imports <b>framework.Move</b>.
 * This class inherits the <b>getMoveName()</b> method from its parent
 * and thus it should not have an instance field for the move name.
 * @author Michael Coughlin
 * CS2511 Fall 2014
 * Lab Section 7
 */
public class PuzzleMove extends Move {

      /**
     * Constructs a new Puzzle move object.
     * Note that the move name is passed to the parent constructor
     * using <b>super</b>.
     * @param moveName the name of this move.
     * It is an error if the name is not one of the following:
     * <ul>
     * <li> "Slide Tile 1" </li>
     * <li> "Slide Tile 2" </li>
     * <li> "Slide Tile 3" </li>
     * <li> "Slide Tile 4" </li>
     * <li> "Slide Tile 5" </li>
     * <li> "Slide Tile 6" </li>
     * <li> "Slide Tile 7" </li>
     * <li> "Slide Tile 8" </li>
     * </ul>
     */
    public PuzzleMove(String moveName) {
        super(moveName);
    }

    /**
     * Attempts to perform this move on a given puzzel state.
     * Note that this method implements the abstract <b>doMove</b> method declared
     * in the parent.
     * Thus the argument of type <b>State</b> must be cast to type
     * <b>PuzzleState</b> before processing.
     * The move to perform is determined by this object's move name.
     * If the move can be performed a new bridge state object is returned that
     * reflects this move.
     * A move cannot be performed if the flashlight is not on the same side
     * as the crossing person(s), or if a pair of persons who are crossing are not
     * on the same side.
     * If the move cannot be performed <b>null</b> is returned.
     * @param otherState the bridge state on which this move is to be performed
     * @return a new puzzle state reflecting the move, or <b>null</b> if it
     * cannot be performed
     */
    @Override
    public State doMove(State state) {
        PuzzleState puzzleState = (PuzzleState) state;
        PuzzleState newState = null;

        if (getMoveName().equals("Slide Tile 1")) {
           if (puzzleState.getFirstPosition() == 1) {
               if (puzzleState.getSecondPosition() == 0)
                   newState = new PuzzleState(0, 1, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getForthPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 1, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
           }
          else if (puzzleState.getSecondPosition() == 1) {
               if (puzzleState.getFirstPosition() == 0)
                   newState = new PuzzleState(1, 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, 1, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
                   
               else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 1,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          } 
          else if (puzzleState.getThirdPosition() == 1) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), 1, 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              1, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getForthPosition() == 1) {
              if (puzzleState.getFirstPosition() == 0)
                  newState = new PuzzleState(puzzleState.getForthPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSeventhPosition() == 0)
               newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getFifthPosition() == 1) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getFifthPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFifthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                             puzzleState.getFifthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getSixthPosition() == 1) {
              if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(),  puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() ); 
              else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(),  puzzleState.getSixthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getNinthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(),  puzzleState.getSixthPosition() );
          }
          else if (puzzleState.getSeventhPosition() == 1) {
              if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );

              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getSeventhPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getEigthPosition() == 1) {
            if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getNinthPosition() );   
             else if (puzzleState.getSeventhPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getEigthPosition(), 0, puzzleState.getNinthPosition() );
             else if (puzzleState.getNinthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getEigthPosition() ); 
          }
          else if (puzzleState.getNinthPosition() == 1) {
              if (puzzleState.getSixthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getNinthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), 0);    
              else if (puzzleState.getEigthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getNinthPosition(), 0 );
          }
   
        } else if (getMoveName().equals("Slide Tile 2")) {
                 if (puzzleState.getFirstPosition() == 2) {
               if (puzzleState.getSecondPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getForthPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFirstPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
           }
          else if (puzzleState.getSecondPosition() == 2) {
               if (puzzleState.getFirstPosition() == 0)
                   newState = new PuzzleState(puzzleState.getSecondPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getSecondPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
                   
               else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getSecondPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          } 
          else if (puzzleState.getThirdPosition() == 2) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getForthPosition() == 2) {
              if (puzzleState.getFirstPosition() == 0)
                  newState = new PuzzleState(puzzleState.getForthPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSeventhPosition() == 0)
               newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getFifthPosition() == 2) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getFifthPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFifthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                             puzzleState.getFifthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getSixthPosition() == 2) {
              if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(),  puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() ); 
              else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(),  puzzleState.getSixthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getNinthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(),  puzzleState.getSixthPosition() );
          }
          else if (puzzleState.getSeventhPosition() == 2) {
              if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );

              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getSeventhPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getEigthPosition() == 2) {
            if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getNinthPosition() );   
             else if (puzzleState.getSeventhPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getEigthPosition(), 0, puzzleState.getNinthPosition() );
             else if (puzzleState.getNinthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getEigthPosition() ); 
          }
          else if (puzzleState.getNinthPosition() == 2) {
              if (puzzleState.getSixthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getNinthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), 0);    
              else if (puzzleState.getEigthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getNinthPosition(), 0 );
          }
        } else if (getMoveName().equals("Slide Tile 3")) {
               if (puzzleState.getFirstPosition() == 3) {
               if (puzzleState.getSecondPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getForthPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFirstPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
           }
          else if (puzzleState.getSecondPosition() == 3) {
               if (puzzleState.getFirstPosition() == 0)
                   newState = new PuzzleState(puzzleState.getSecondPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getSecondPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
                   
               else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getSecondPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          } 
          else if (puzzleState.getThirdPosition() == 3) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getForthPosition() == 3) {
              if (puzzleState.getFirstPosition() == 0)
                  newState = new PuzzleState(puzzleState.getForthPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSeventhPosition() == 0)
               newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getFifthPosition() == 3) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getFifthPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFifthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                             puzzleState.getFifthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getSixthPosition() == 3) {
              if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(),  puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() ); 
              else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(),  puzzleState.getSixthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getNinthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(),  puzzleState.getSixthPosition() );
          }
          else if (puzzleState.getSeventhPosition() == 3) {
              if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );

              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getSeventhPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getEigthPosition() == 3) {
            if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getNinthPosition() );   
             else if (puzzleState.getSeventhPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getEigthPosition(), 0, puzzleState.getNinthPosition() );
             else if (puzzleState.getNinthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getEigthPosition() ); 
          }
          else if (puzzleState.getNinthPosition() == 3) {
              if (puzzleState.getSixthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getNinthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), 0);    
              else if (puzzleState.getEigthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getNinthPosition(), 0 );
          }
        } else if (getMoveName().equals("Slide Tile 4")) { 
                 if (puzzleState.getFirstPosition() == 4) {
               if (puzzleState.getSecondPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getForthPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFirstPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
           }
          else if (puzzleState.getSecondPosition() == 4) {
               if (puzzleState.getFirstPosition() == 0)
                   newState = new PuzzleState(puzzleState.getSecondPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getSecondPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
                   
               else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getSecondPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          } 
          else if (puzzleState.getThirdPosition() == 4) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getForthPosition() == 4) {
              if (puzzleState.getFirstPosition() == 0)
                  newState = new PuzzleState(puzzleState.getForthPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSeventhPosition() == 0)
               newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getFifthPosition() == 4) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getFifthPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFifthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                             puzzleState.getFifthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getSixthPosition() == 4) {
              if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(),  puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() ); 
              else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(),  puzzleState.getSixthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getNinthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(),  puzzleState.getSixthPosition() );
          }
          else if (puzzleState.getSeventhPosition() == 4) {
              if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );

              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getSeventhPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getEigthPosition() == 4) {
            if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getNinthPosition() );   
             else if (puzzleState.getSeventhPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getEigthPosition(), 0, puzzleState.getNinthPosition() );
             else if (puzzleState.getNinthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getEigthPosition() ); 
          }
          else if (puzzleState.getNinthPosition() == 4) {
              if (puzzleState.getSixthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getNinthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), 0);    
              else if (puzzleState.getEigthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getNinthPosition(), 0 );
          }
   
        } else if (getMoveName().equals("Slide Tile 5")) { 
                if (puzzleState.getFirstPosition() == 5) {
               if (puzzleState.getSecondPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getForthPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFirstPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
           }
          else if (puzzleState.getSecondPosition() == 5) {
               if (puzzleState.getFirstPosition() == 0)
                   newState = new PuzzleState(puzzleState.getSecondPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getSecondPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
                   
               else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getSecondPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          } 
          else if (puzzleState.getThirdPosition() == 5) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getForthPosition() == 5) {
              if (puzzleState.getFirstPosition() == 0)
                  newState = new PuzzleState(puzzleState.getForthPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSeventhPosition() == 0)
               newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getFifthPosition() == 5) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getFifthPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFifthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                             puzzleState.getFifthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getSixthPosition() == 5) {
              if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(),  puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() ); 
              else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(),  puzzleState.getSixthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getNinthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(),  puzzleState.getSixthPosition() );
          }
          else if (puzzleState.getSeventhPosition() == 5) {
              if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );

              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getSeventhPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getEigthPosition() == 5) {
            if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getNinthPosition() );   
             else if (puzzleState.getSeventhPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getEigthPosition(), 0, puzzleState.getNinthPosition() );
             else if (puzzleState.getNinthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getEigthPosition() ); 
          }
          else if (puzzleState.getNinthPosition() == 5) {
              if (puzzleState.getSixthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getNinthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), 0);    
              else if (puzzleState.getEigthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getNinthPosition(), 0 );
          }
   
        } else if (getMoveName().equals("Slide Tile 6")) {
                 if (puzzleState.getFirstPosition() == 6) {
               if (puzzleState.getSecondPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getForthPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFirstPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
           }
          else if (puzzleState.getSecondPosition() == 6) {
               if (puzzleState.getFirstPosition() == 0)
                   newState = new PuzzleState(puzzleState.getSecondPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getSecondPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
                   
               else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getSecondPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          } 
          else if (puzzleState.getThirdPosition() == 6) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getForthPosition() == 6) {
              if (puzzleState.getFirstPosition() == 0)
                  newState = new PuzzleState(puzzleState.getForthPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSeventhPosition() == 0)
               newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getFifthPosition() == 6) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getFifthPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFifthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                             puzzleState.getFifthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 6, puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getSixthPosition() == 6) {
              if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(),  puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() ); 
              else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(),  puzzleState.getSixthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getNinthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(),  puzzleState.getSixthPosition() );
          }
          else if (puzzleState.getSeventhPosition() == 6) {
              if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );

              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getSeventhPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getEigthPosition() == 6) {
             if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getNinthPosition() );    
             else if (puzzleState.getSeventhPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getEigthPosition(), 0, puzzleState.getNinthPosition() );
             else if (puzzleState.getNinthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getEigthPosition() ); 
          }
          else if (puzzleState.getNinthPosition() == 6) {
              if (puzzleState.getSixthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getNinthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), 0);    
              else if (puzzleState.getEigthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getNinthPosition(), 0 );
          }
   
        } else if (getMoveName().equals("Slide Tile 7")) {
                if (puzzleState.getFirstPosition() == 7) {
               if (puzzleState.getSecondPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getForthPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFirstPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
           }
          else if (puzzleState.getSecondPosition() == 7) {
               if (puzzleState.getFirstPosition() == 0)
                   newState = new PuzzleState(puzzleState.getSecondPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getSecondPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
                   
               else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getSecondPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          } 
          else if (puzzleState.getThirdPosition() == 7) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getForthPosition() == 7) {
              if (puzzleState.getFirstPosition() == 0)
                  newState = new PuzzleState(puzzleState.getForthPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSeventhPosition() == 0)
               newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getFifthPosition() == 7) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getFifthPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFifthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                             puzzleState.getFifthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getSixthPosition() == 7) {
              if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(),  puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() ); 
              else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(),  puzzleState.getSixthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getNinthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(),  puzzleState.getSixthPosition() );
          }
          else if (puzzleState.getSeventhPosition() == 7) {
              if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );

              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getSeventhPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getEigthPosition() == 7) {
             if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getNinthPosition() );   
             else if (puzzleState.getSeventhPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getEigthPosition(), 0, puzzleState.getNinthPosition() );
             else if (puzzleState.getNinthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getEigthPosition() ); 
          }
          else if (puzzleState.getNinthPosition() == 7) {
              if (puzzleState.getSixthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getNinthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), 0);    
              else if (puzzleState.getEigthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getNinthPosition(), 0 );
          }
   
        } else if (getMoveName().equals("Slide Tile 8")) {
                  if (puzzleState.getFirstPosition() == 8) {
               if (puzzleState.getSecondPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getForthPosition() == 0)
                   newState = new PuzzleState(0, puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFirstPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
           }
          else if (puzzleState.getSecondPosition() == 8) {
               if (puzzleState.getFirstPosition() == 0)
                   newState = new PuzzleState(puzzleState.getSecondPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
               else if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getSecondPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
                   
               else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), 0, puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getSecondPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          } 
          else if (puzzleState.getThirdPosition() == 8) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), 0, puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getForthPosition() == 8) {
              if (puzzleState.getFirstPosition() == 0)
                  newState = new PuzzleState(puzzleState.getForthPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getForthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSeventhPosition() == 0)
               newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), 0, puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getFifthPosition() == 8) {
              if (puzzleState.getSecondPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getFifthPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getFifthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getSixthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                             puzzleState.getFifthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), 0,
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getSixthPosition() == 8) {
              if (puzzleState.getThirdPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(),  puzzleState.getSixthPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() ); 
              else if (puzzleState.getFifthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(),  puzzleState.getSixthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );
              else if (puzzleState.getNinthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                             0, puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(),  puzzleState.getSixthPosition() );
          }
          else if (puzzleState.getSeventhPosition() == 8) {
              if (puzzleState.getForthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getSeventhPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getEigthPosition(), puzzleState.getNinthPosition() );

              else if (puzzleState.getEigthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), 0, puzzleState.getSeventhPosition(), puzzleState.getNinthPosition() );
          }
          else if (puzzleState.getEigthPosition() == 8) {
            if (puzzleState.getFifthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getEigthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getNinthPosition() );   
             else if (puzzleState.getSeventhPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getEigthPosition(), 0, puzzleState.getNinthPosition() );
             else if (puzzleState.getNinthPosition() == 0)
                  newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), 0, puzzleState.getEigthPosition() ); 
          }
          else if (puzzleState.getNinthPosition() == 8) {
              if (puzzleState.getSixthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getNinthPosition(), puzzleState.getSeventhPosition(), puzzleState.getEigthPosition(), 0);    
              else if (puzzleState.getEigthPosition() == 0)
                   newState = new PuzzleState(puzzleState.getFirstPosition(), puzzleState.getSecondPosition(), puzzleState.getThirdPosition(), puzzleState.getForthPosition(), puzzleState.getFifthPosition(),
                                              puzzleState.getSixthPosition(), puzzleState.getSeventhPosition(), puzzleState.getNinthPosition(), 0 );
          }
   
        } 
 
        return newState;
    }
    
    
    
}
