package waterjug;

import framework.Move;
import framework.State;

/**
 * This class represents moves in the Water Jug problem.
 * A move object stores its move name and knows how to apply itself
 * to a water jug state to create a new state representing the result
 * of the move.
 * Note that this class extends the abstract class <b>Move</b> and
 * therefore imports <b>framework.Move</b>.
 * This class inherits the <b>getMoveName()</b> method from its parent
 * and thus it should not have an instance field for the move name.
 * @author Michael Coughlin
 * CS2511 Fall 2014
 * Lab Section 7
*/
public class WaterJugMove extends Move {

    /**
     * Constructs a new water jug move object.
     * Note that the move name is passed to the parent constructor
     * using <b>super</b>.
     * @param moveName the name of this move.
     * It is an error if the name is not one of the following:
     * <ul>
     * <li> "Fill Jug X" </li>
     * <li> "Fill Jug Y" </li>
     * <li> "Empty Jug X" </li>
     * <li> "Empty Jug Y" </li>
     * <li> "Transfer Jug X to Jug Y" </li>
     * <li> "Transfer Jug X to Jug Y" </li>
     * </ul>
     */
    public WaterJugMove(String moveName) {
	super(moveName);
    }

    /**
     * Attempts to perform this move on a given water jug state.
     * Note that this method implements the abstract <b>doMove</b> method declared
     * in the parent.
     * Thus the argument of type <b>State</b> must be cast to type
     * <b>WaterJugState</b> before processing.
     * The move to perform is determined by this object's move name.
     * If the move can be performed a new water jug state object is returned that
     * reflects this move.
     * A move cannot be performed if trying to fill or transfer to an already
     * full jug, or if trying to empty or transfer from an empty jug.
     * If the move cannot be performed <b>null</b> is returned.
     * @param otherState the water jug state on which this move is to be performed
     * @return a new water jug state reflecting the move, or <b>null</b> if it
     * cannot be performed
     */
    public State doMove(State otherState) {
	WaterJugState state = (WaterJugState) otherState;
        WaterJugState newState = null; //creates a WaterJugState and sets to null.
        //Checks to see what the current move name is, then it checks to see if
        //the move is valid. If the move is valid, it performs the move and creates
        //the new state.
        if(getMoveName().equals("Fill Jug X")){
            if(state.getJugX() != 3)
                newState = new WaterJugState(3, state.getJugY() );
        }else if(getMoveName().equals("Fill Jug Y")){
            if(state.getJugY() != 4)
                newState = new WaterJugState(state.getJugX(), 4);
        }else if(getMoveName().equals("Empty Jug X")){
            if(state.getJugX() != 0)
               newState = new WaterJugState(0, state.getJugY() );
        }else if(getMoveName().equals("Empty Jug Y")){
            if(state.getJugY() != 0)
               newState = new WaterJugState(state.getJugX(), 0);
        }
       
        else if(getMoveName().equals("Transfer Jug X to Jug Y")){
           
            if(state.getJugX() != 0)
                if(state.getJugY() != 4)
                    if(state.getJugX() == 3 && state.getJugY() == 3)
                         newState = new WaterJugState(2, 4);
                    else 
               newState = new WaterJugState(0, state.getJugX() );
            
        }else if(getMoveName().equals("Transfer Jug Y to Jug X")){
            
            if(state.getJugY() != 0)
               if(state.getJugX() != 3)
                   if(state.getJugY() == 4 && state.getJugX() == 0)
                       newState =  new WaterJugState(3, 1);
                   else if(state.getJugY() == 4 && state.getJugX() == 1)
                       newState =  new WaterJugState(3, 2);
                       else
               newState = new WaterJugState(state.getJugY(), 0);
    
        }
     return newState;
    }
    
    // Private methods and instance fields should go here

}
