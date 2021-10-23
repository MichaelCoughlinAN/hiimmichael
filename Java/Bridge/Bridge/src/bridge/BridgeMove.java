package bridge;

/**
 * This class represents moves in the Bridge Crossing problem.
 * A move object stores its move name and knows how to apply itself
 * to a bridge state to create a new state representing the result
 * of the move.
 * @author your name here
 */
public class BridgeMove {
    
    //name of the current move.
    private String name;
    
    /**
     * Constructs a new bridge move object.
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
        if(moveName.equals("P1 crosses alone") || moveName.equals("P2 crosses alone") ||
            moveName.equals("P5 crosses alone") || moveName.equals("P10 crosses alone")  ||    
            moveName.equals("P1 crosses with P2") || moveName.equals("P1 crosses with P5")  ||    
            moveName.equals("P1 crosses with P10") || moveName.equals("P2 crosses with P5") ||
            moveName.equals("P2 crosses with P10") || moveName.equals("P5 crosses with P10")
        ) //if is not needed. However, I left it as it is safe.
        name = moveName;
    }

    /**
     * Getter (accessor) for this move object's move name.
     * @return this move object's move name
     */
    public String getMoveName() {
        return name;
    }
    
    /**
     * Attempts to perform this move on a given bridge state.
     * The move to perform is determined by this object's move name.
     * If the move can be performed a new bridge state object is returned that
     * reflects this move.
     * A move cannot be performed if the flashlight is not on the same side
     * as the crossing person(s), or if a pair of persons who are crossing are not
     * on the same side.
     * If the move cannot be performed <b>null</b> is returned.
     * @param state the bridge state on which this move is to be performed
     * @return a new bridge state reflecting the move, or <b>null</b> if it
     * cannot be performed
     */
    public BridgeState doMove(BridgeState state) throws NullPointerException {
       
        BridgeState newState = null; //creates a BridgeState and sets to null.
        //The following chain of if statements determines which side the 
        //person(s) and flashlight need to move to. Returns null if invalid.
        if(name.equals("P1 crosses alone")){
            if(state.getP1Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST) ) {
               newState = new BridgeState(Position.EAST, state.getP2Position(),
                                          Position.EAST, state.getP5Position(),
                                          state.getP10Position(), state.getTimeSoFar() + 1);
             }else if(state.getP1Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) )
                newState = new BridgeState(Position.WEST, state.getP2Position(),
                                           Position.WEST, state.getP5Position(),
                                           state.getP10Position(), state.getTimeSoFar() + 1);      
        }
        else if(name.equals("P2 crosses alone") ){
            if(state.getP2Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST) ) {
               newState = new BridgeState(state.getP1Position(), Position.EAST,
                                          Position.EAST, state.getP5Position(),
                                          state.getP10Position(), state.getTimeSoFar() + 2);
             }else if(state.getP2Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) )
                newState = new BridgeState(state.getP1Position(), Position.WEST,
                                           Position.WEST, state.getP5Position(),
                                           state.getP10Position(), state.getTimeSoFar() + 2);      
        }
        else if(name.equals("P5 crosses alone")){
            if(state.getP5Position().equals(Position.WEST ) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(state.getP1Position(), state.getP2Position(),
                                          Position.EAST, Position.EAST,
                                          state.getP10Position(), state.getTimeSoFar() + 5);
             }else if(state.getP5Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) ) 
                newState = new BridgeState(state.getP1Position(), state.getP2Position(),
                                           Position.WEST, Position.WEST,
                                           state.getP10Position(), state.getTimeSoFar() + 5);      
        }
            else if(name.equals("P10 crosses alone")){
            if(state.getP10Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(state.getP1Position(), state.getP2Position(),
                                          Position.EAST, state.getP5Position(),
                                          Position.EAST, state.getTimeSoFar() + 10);
             }else  if(state.getP10Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) )
                newState = new BridgeState(state.getP1Position(), state.getP2Position(),
                                           Position.WEST, state.getP5Position(),
                                           Position.WEST, state.getTimeSoFar() + 10); 
        }
        else if(name.equals("P1 crosses with P2")){
            if(state.getP1Position().equals(Position.WEST) && state.getP2Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(Position.EAST, Position.EAST, Position.EAST,
                                          state.getP5Position(), state.getP10Position(),
                                          state.getTimeSoFar() + 2);
             }else if(state.getP1Position().equals(Position.EAST) && state.getP2Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) ) 
                newState = new BridgeState(Position.WEST, Position.WEST, Position.WEST,
                                           state.getP5Position(), state.getP10Position(),
                                           state.getTimeSoFar() + 2);
        }
        else if(name.equals("P1 crosses with P5")){
            if(state.getP1Position().equals(Position.WEST) && state.getP5Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(Position.EAST, state.getP2Position(), Position.EAST,
                                          Position.EAST, state.getP10Position(),
                                          state.getTimeSoFar() + 5);
             }else  if(state.getP1Position().equals(Position.EAST) && state.getP5Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) )   
                newState = new BridgeState(Position.WEST, state.getP2Position(), Position.WEST,
                                           Position.WEST, state.getP10Position(),
                                           state.getTimeSoFar() + 5);
        }
        else if(name.equals("P1 crosses with P10")){
            if(state.getP1Position().equals(Position.WEST) && state.getP10Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(Position.EAST, state.getP2Position(), Position.EAST,
                                          state.getP5Position(), Position.EAST,
                                          state.getTimeSoFar() + 10);
             }else   if(state.getP1Position().equals(Position.EAST) && state.getP10Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) ) 
                newState = new BridgeState(Position.WEST, state.getP2Position(), Position.WEST,
                                           state.getP5Position(), Position.WEST,
                                           state.getTimeSoFar() + 10);
        }
        else if(name.equals("P2 crosses with P5")){
            if(state.getP2Position().equals(Position.WEST) && state.getP5Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(state.getP1Position(), Position.EAST, Position.EAST,
                                          Position.EAST, state.getP10Position(),
                                          state.getTimeSoFar() + 5);
             }else  if(state.getP2Position().equals(Position.EAST) && state.getP5Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) )  
                newState = new BridgeState(state.getP1Position(), Position.WEST, Position.WEST, Position.WEST,
                                           state.getP10Position(),
                                           state.getTimeSoFar() + 5);
        }
        else if(name.equals("P2 crosses with P10")){
            if(state.getP2Position().equals(Position.WEST) && state.getP10Position().equals(Position.WEST) && state.getFlashlightPosition().equals(Position.WEST)) {
               newState = new BridgeState(state.getP1Position(), Position.EAST, Position.EAST,
                                          state.getP5Position(), Position.EAST,
                                          state.getTimeSoFar() + 10);
             }else   if(state.getP2Position().equals(Position.EAST) && state.getP10Position().equals(Position.EAST) && state.getFlashlightPosition().equals(Position.EAST) ) 
                newState = new BridgeState(state.getP1Position(), Position.WEST, Position.WEST,
                          state.getP5Position(), Position.WEST,
                         state.getTimeSoFar() + 10);
        }
        else if(name.equals("P5 crosses with P10")){
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
}
    
    