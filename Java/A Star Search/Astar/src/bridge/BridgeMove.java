package bridge;

import framework.Move;
import framework.State;

/**
 * This class represents moves in the Bridge Crossing problem.
 * A move object stores its move name and knows how to apply itself
 * to a bridge state to create a new state representing the result
 * of the move.
 * Note that this class extends the abstract class <b>Move</b> and
 * therefore imports <b>framework.Move</b>.
 * This class inherits the <b>getMoveName()</b> method from its parent
 * and thus it should not have an instance field for the move name.
 * Other than that, it can be essentially the same as in the previous
 * assignment.
 * @author Michael Coughlin
 * CS2511 Fall 2014
 * Lab Section 7
 */
public class BridgeMove extends Move {

    /**
     * Constructs a new bridge move object.
     * Note that the move name is passed to the parent constructor
     * using <b>super</b>.
     * @param moveName the name of this move.
     * It is an error if the name is not one of the following:
     * <ul>
     * <li> "P1 crosses alone" </li>
     * <li> "P2 crosses alone" </li>
     * <li> "P5 crosses alone" </li>
     * <li> "P10 crosses alone" </li>
     * <li> "P1 crosses with P2" </li>
     * <li> "P1 crosses with P5" </li>
     * <li> "P1 crosses with P10" </li>
     * <li> "P2 crosses with P5" </li>
     * <li> "P2 crosses with P10" </li>
     * <li> "P5 crosses with P10" </li>
     * </ul>
     */
    public BridgeMove(String moveName) {
        super(moveName);
    }
    
    /**
     * Attempts to perform this move on a given bridge state.
     * Note that this method implements the abstract <b>doMove</b> method declared
     * in the parent.
     * Thus the argument of type <b>State</b> must be cast to type
     * <b>BridgeState</b> before processing.
     * The move to perform is determined by this object's move name.
     * If the move can be performed a new bridge state object is returned that
     * reflects this move.
     * A move cannot be performed if the flashlight is not on the same side
     * as the crossing person(s), or if a pair of persons who are crossing are not
     * on the same side.
     * If the move cannot be performed <b>null</b> is returned.
     * @param otherState the bridge state on which this move is to be performed
     * @return a new bridge state reflecting the move, or <b>null</b> if it
     * cannot be performed
     */
    public State doMove(State otherState) {
        BridgeState state = (BridgeState) otherState;
        BridgeState newState = null; //creates a BridgeState and sets to null.
        //The following chain of if statements determines which side the 
        //person(s) and flashlight need to move to. Returns null if invalid.
        if(getMoveName().equals("P1 crosses alone")){
            if(state.getP1Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST) ) {
               newState = new BridgeState(Position.EAST, state.getP2Position(),
                                          Position.EAST, state.getP5Position(),
                                          state.getP10Position(), state.getTimeSoFar() + 1);
             }else if(state.getP1Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) )
                newState = new BridgeState(Position.WEST, state.getP2Position(),
                                           Position.WEST, state.getP5Position(),
                                           state.getP10Position(), state.getTimeSoFar() + 1);      
        }
        else if(getMoveName().equals("P2 crosses alone") ){
            if(state.getP2Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST) ) {
               newState = new BridgeState(state.getP1Position(), Position.EAST,
                                          Position.EAST, state.getP5Position(),
                                          state.getP10Position(), state.getTimeSoFar() + 2);
             }else if(state.getP2Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) )
                newState = new BridgeState(state.getP1Position(), Position.WEST,
                                           Position.WEST, state.getP5Position(),
                                           state.getP10Position(), state.getTimeSoFar() + 2);      
        }
        else if(getMoveName().equals("P5 crosses alone")){
            if(state.getP5Position().equals(Position.WEST ) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(state.getP1Position(), state.getP2Position(),
                                          Position.EAST, Position.EAST,
                                          state.getP10Position(), state.getTimeSoFar() + 5);
             }else if(state.getP5Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) ) 
                newState = new BridgeState(state.getP1Position(), state.getP2Position(),
                                           Position.WEST, Position.WEST,
                                           state.getP10Position(), state.getTimeSoFar() + 5);      
        }
            else if(getMoveName().equals("P10 crosses alone")){
            if(state.getP10Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(state.getP1Position(), state.getP2Position(),
                                          Position.EAST, state.getP5Position(),
                                          Position.EAST, state.getTimeSoFar() + 10);
             }else  if(state.getP10Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) )
                newState = new BridgeState(state.getP1Position(), state.getP2Position(),
                                           Position.WEST, state.getP5Position(),
                                           Position.WEST, state.getTimeSoFar() + 10); 
        }
        else if(getMoveName().equals("P1 crosses with P2")){
            if(state.getP1Position().equals(Position.WEST) && state.getP2Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(Position.EAST, Position.EAST, Position.EAST,
                                          state.getP5Position(), state.getP10Position(),
                                          state.getTimeSoFar() + 2);
             }else if(state.getP1Position().equals(Position.EAST) && state.getP2Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) ) 
                newState = new BridgeState(Position.WEST, Position.WEST, Position.WEST,
                                           state.getP5Position(), state.getP10Position(),
                                           state.getTimeSoFar() + 2);
        }
        else if(getMoveName().equals("P1 crosses with P5")){
            if(state.getP1Position().equals(Position.WEST) && state.getP5Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(Position.EAST, state.getP2Position(), Position.EAST,
                                          Position.EAST, state.getP10Position(),
                                          state.getTimeSoFar() + 5);
             }else  if(state.getP1Position().equals(Position.EAST) && state.getP5Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) )   
                newState = new BridgeState(Position.WEST, state.getP2Position(), Position.WEST,
                                           Position.WEST, state.getP10Position(),
                                           state.getTimeSoFar() + 5);
        }
        else if(getMoveName().equals("P1 crosses with P10")){
            if(state.getP1Position().equals(Position.WEST) && state.getP10Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(Position.EAST, state.getP2Position(), Position.EAST,
                                          state.getP5Position(), Position.EAST,
                                          state.getTimeSoFar() + 10);
             }else   if(state.getP1Position().equals(Position.EAST) && state.getP10Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) ) 
                newState = new BridgeState(Position.WEST, state.getP2Position(), Position.WEST,
                                           state.getP5Position(), Position.WEST,
                                           state.getTimeSoFar() + 10);
        }
        else if(getMoveName().equals("P2 crosses with P5")){
            if(state.getP2Position().equals(Position.WEST) && state.getP5Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(state.getP1Position(), Position.EAST, Position.EAST,
                                          Position.EAST, state.getP10Position(),
                                          state.getTimeSoFar() + 5);
             }else  if(state.getP2Position().equals(Position.EAST) && state.getP5Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) )  
                newState = new BridgeState(state.getP1Position(), Position.WEST, Position.WEST, Position.WEST,
                                           state.getP10Position(),
                                           state.getTimeSoFar() + 5);
        }
        else if(getMoveName().equals("P2 crosses with P10")){
            if(state.getP2Position().equals(Position.WEST) && state.getP10Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(state.getP1Position(), Position.EAST, Position.EAST,
                                          state.getP5Position(), Position.EAST,
                                          state.getTimeSoFar() + 10);
             }else   if(state.getP2Position().equals(Position.EAST) && state.getP10Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) ) 
                newState = new BridgeState(state.getP1Position(), Position.WEST, Position.WEST,
                          state.getP5Position(), Position.WEST,
                         state.getTimeSoFar() + 10);
        }
        else if(getMoveName().equals("P5 crosses with P10")){
            if(state.getP5Position().equals(Position.WEST) && state.getP10Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(state.getP1Position(), state.getP2Position(), Position.EAST,
                                          Position.EAST, Position.EAST,
                                          state.getTimeSoFar() + 10);
             }else   if(state.getP5Position().equals(Position.EAST) && state.getP10Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) ) 
                newState = new BridgeState(state.getP1Position(), state.getP2Position(), Position.WEST,
                                           Position.WEST, Position.WEST,
                                           state.getTimeSoFar() + 10);
            
        } 

       return newState;  
       
    }      

    
    
    // Private methods and instance fields should go here
}
