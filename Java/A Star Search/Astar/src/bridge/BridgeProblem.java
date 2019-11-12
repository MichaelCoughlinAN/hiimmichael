package bridge;

import framework.Move;
import framework.Problem;
import java.util.ArrayList;

/**
 * This class represents the Bridge Crossing problem.
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
 * Lab Section 7
 */
public class BridgeProblem extends Problem {
    
    /**
     * Constructs a new bridge problem object.  A new bridge state object
     * should be constructed with P1, P2, P5, P10, and the flashlight all on the
     * west side of the bridge with zero time elapsed.
     * This state should be set as the current state of the problem using
     * the inherited <b>setCurrentState()</b> method.
     * The ten valid bridge moves should be created and stored on a list using
     * the inherited <b>setMoves()</b> method.
     * The appropriate introduction string for this problem should be stored
     * using the inherited <b>setIntroduction()</b>.
     */
    public BridgeProblem() {
           setCurrentState(new BridgeState(Position.WEST, Position.WEST, Position.WEST, 
                                   Position.WEST,Position.WEST,0));
       setIntroduction(
            "Welcome to the Bridge Crossing Problem.\n\n" +
            "Person Pn can cross the bridge in n minutes.\n" +
            "Only one or two persons can cross at a time because it is dark,\n" +
            "and the flashlight must be taken on every crossing.\n" +
            "When two people cross, they travel at the speed of the slowest person.\n" +
            "Devise a sequence of crossings so that all four people get across\n" +
            "the bridge in no more than 17 minutes.");
           setMoves(new ArrayList<Move>());
      setChooser(false);
        getMoves().add(new BridgeMove("P1 crosses alone"));
        getMoves().add(new BridgeMove("P2 crosses alone"));
        getMoves().add(new BridgeMove("P5 crosses alone"));
        getMoves().add(new BridgeMove("P10 crosses alone"));
        getMoves().add(new BridgeMove("P1 crosses with P2"));
        getMoves().add(new BridgeMove("P1 crosses with P5"));
        getMoves().add(new BridgeMove("P1 crosses with P10"));
        getMoves().add(new BridgeMove("P2 crosses with P5"));
        getMoves().add(new BridgeMove("P2 crosses with P10"));
        getMoves().add(new BridgeMove("P5 crosses with P10"));
    }
    
    /**
     * Returns whether the current state of this problem is a success.
     * Note that this method implements the abstract <b>success</b> method declared
     * in the parent.
     * Note also that the current state of the problem must be gotten using the
     * inherited <b>getCurrentState()</b> method.
     * Since that method returns a value of type <b>State</b>, it must be cast to
     * <b>BridgeState</b> before processing.
     * The current state is a success if P1, P2, P5, and P10 are all on the
     * east side of the bridge and the time taken to cross is less than 18 minutes.
     * @return <b>true</b> if the current state is a success, <b>false</b> otherwise
     */
    public boolean success() {
        BridgeState currentState = (BridgeState) getCurrentState();
        return currentState.getP1Position().equals(Position.EAST) &&
                currentState.getP2Position().equals(Position.EAST) &&
                currentState.getP5Position().equals(Position.EAST)&&
                currentState.getP10Position().equals(Position.EAST) &&
                currentState.getFlashlightPosition().equals(Position.EAST) &&
                currentState.getTimeSoFar() <= 17;   
    }
    
}
