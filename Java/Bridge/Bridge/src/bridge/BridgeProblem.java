package bridge;

import java.util.List;
import java.util.ArrayList;

/**
 * This class represents the Bridge Crossing problem.
 * It provides an introductory message describing the problem,
 * stores the problem's possible moves and current state, and
 * tests for whether the problem has been successfully solved.
 * @author your name here
 */
public class BridgeProblem {
    //A constant string used to display the problem instructions.
    final private String problemIntro = 
            "Welcome to the Bridge Crossing Problem.\n\n" +
            "Person Pn can cross the bridge in n minutes.\n" +
            "Only one or two persons can cross at a time because it is dark,\n" +
            "and the flashlight must be taken on every crossing.\n" +
            "When two people cross, they travel at the speed of the slowest person.\n" +
            "Devise a sequence of crossings so that all four people get across\n" +
            "the bridge in no more than 17 minutes.\n\n";
   //BridgeState object used to represent the problem's current state.
    private BridgeState theState;
    //An ArrayList of BridgeMoves.
    private ArrayList<BridgeMove> moves; 
    

    /**
     * The bridge problem constructor should create the initial bridge state
     * object and store it as the problem's current state.
     * It should also create the 10 valid bridge move objects and store them
     * on an accessible list.
     */
    public BridgeProblem() {
        theState = new BridgeState(Position.WEST, Position.WEST, Position.WEST, 
                                   Position.WEST,Position.WEST,0);
        moves = new ArrayList<BridgeMove>();
      
        moves.add(new BridgeMove("P1 crosses alone"));
        moves.add(new BridgeMove("P2 crosses alone"));
        moves.add(new BridgeMove("P5 crosses alone"));
        moves.add(new BridgeMove("P10 crosses alone"));
        moves.add(new BridgeMove("P1 crosses with P2"));
        moves.add(new BridgeMove("P1 crosses with P5"));
        moves.add(new BridgeMove("P1 crosses with P10"));
        moves.add(new BridgeMove("P2 crosses with P5"));
        moves.add(new BridgeMove("P2 crosses with P10"));
        moves.add(new BridgeMove("P5 crosses with P10"));      
    }
    
    /**
     * Getter (accessor) for this problem's introduction string.
     * @return the introduction string
     */
    public String getIntroduction() {
        return problemIntro; 
    }

    /**
     * Getter (accessor) for this problem's list of valid bridge move objects.
     * @return the list of bridge moves
     */
    public List<BridgeMove> getMoves() {
        return moves;
    }
    
    /**
     * Tests for whether the current state of this problem indicates that the
     * problem has been successfully solved.
     * @return true if the problem has been solved, false otherwise
     */
    public boolean success() {
         return theState.getP1Position().equals(Position.EAST) &&
                theState.getP2Position().equals(Position.EAST) &&
                theState.getP5Position().equals(Position.EAST)&&
                theState.getP10Position().equals(Position.EAST) &&
                theState.getFlashlightPosition().equals(Position.EAST) &&
                theState.getTimeSoFar() <= 17;         
    }

    /**
     * Getter (accessor) for this problem's current bridge state.
     * @return the current state
     */
    public BridgeState getCurrentState() {
        return theState;
    }

    /**
     * Setter (mutator) for this problem's current bridge state.
     * @param currentState the state to be made this problem's current state
     */
    public void setCurrentState(BridgeState currentState) {
        theState = currentState;
    }    
}
