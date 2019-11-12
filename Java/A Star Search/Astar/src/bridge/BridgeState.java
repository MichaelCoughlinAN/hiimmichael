package bridge;

import framework.State;
import graph.SimpleVertex;

/**
 * This class represents states of the Bridge Crossing problem.
 * It creates new bridge states, tests states for equality,
 * and produces string representations of them.
 * Note that this class implements the <b>State</b> interface
 * and therefore imports <b>framework.State</b>.
 * Except for the import and the class header, this class can be
 * the same as in the previous assignment.
 * @author Michael Coughlin
 * CS2511 Fall 2014
 * Lab Section 7
 */
public class BridgeState extends SimpleVertex implements State {

    /**
     * Creates a new bridge state.  
     * Besides storing the positions of the persons and flashlight, a
     * bridge state should also store the time taken to get to this state in
     * integer minutes.
     * @param p1Position position of the person who can cross in 1 minute
     * @param p2Position position of the person who can cross in 2 minutes
     * @param flashlightPosition position of the flashlight
     * @param p5Position position of the person who can cross in 5 minutes
     * @param p10Position  position of the person who can cross in 10 minutes
     * @param timeSoFar time taken so far
     */
    public BridgeState(Position p1Position, 
                       Position p2Position, 
                       Position flashlightPosition, 
                       Position p5Position, 
                       Position p10Position,
                       int timeSoFar) {
        
    time = time + timeSoFar;
    flashlight = flashlightPosition;
    p1 = p1Position;
    p2 = p2Position; 
    p5 = p5Position; 
    p10 = p10Position;
    }
    
    /**
     * Compares this bridge state with another for equality.
     * Note that this method overrides the <b>equals</b> method defined
     * in <b>java.lang.Object</b>.
     * Thus the argument of type <b>Object</b> must be cast to type
     * <b>BridgeState</b> before processing.
     * Two bridge states are equal if the positions of the persons and 
     * flashlight in one state are matched by their positions in the other.
     * Note that the time taken to cross so far is not taken into account
     * when considering equality.
     * @param other the other bridge state to be compared with this one.
     * @return whether this state is equal to the other state
     */
    public boolean equals(Object other) {
        BridgeState state = (BridgeState) other;
      return this.getP1Position().equals(state.getP1Position()) &&
                this.getP2Position().equals(state.getP2Position()) &&
                this.getP5Position().equals(state.getP5Position()) &&
                this.getP10Position().equals(state.getP10Position()) &&
                this.getFlashlightPosition().equals(state.getFlashlightPosition());
    }
    
    /**
     * Creates a string representation of this state for display to the user
     * trying to solve the problem.
     * Note that the time so far to cross is part of the string representation.
     * @return the string representation of this state
     */
    public String toString() {
          //Checks which side the person(s) are on and appends to an empty string
        //to produce an image of the current state.
	String result = "";
               if(p1.equals(Position.WEST))   
              result += " P1 |   |\n";
         else result += "    |   | P1\n";
               if(p2.equals(Position.WEST))   
              result += " P2 |   |\n";
         else result += "    |   | P2\n";
               if(flashlight.equals(Position.WEST))   
              result += "  f |===|\n";
         else result += "    |===| f\n";
               if(p5.equals(Position.WEST))   
              result += " P5 |   |\n";
         else result += "    |   | P5\n";
               if(p10.equals(Position.WEST))   
              result += "P10 |   |\n";
         else result += "    |   | P10\n";
       
      result += "Time elapsed so far: " + Integer.toString(time) + " minutes.\n";
               return result;
    }

    /**
     * Getter (accessor) for the position of the flashlight in this state.
     * @return the position of the flashlight
     */
    public Position getFlashlightPosition() {
            return flashlight;
    }

    /**
     * Getter (accessor) for the position of person P1 in this state.
     * @return the position of person P1
     */
    public Position getP1Position() {
        return p1;
    }

    /**
     * Getter (accessor) for the position of person P2 in this state.
     * @return the position of person P2
     */
    public Position getP2Position() {
        return p2;
    }

    /**
     * Getter (accessor) for the position of person P5 in this state.
     * @return the position of person P5
     */
    public Position getP5Position() {
        return p5;
    }

    /**
     * Getter (accessor) for the position of person P10 in this state.
     * @return the position of person P10
     */
    public Position getP10Position() {
        return p10;
    }
    /**
     * Getter (accessor) for the time taken to get to this state.
     * @return the time taken to get to this state
     */
    public int getTimeSoFar() {
        return time;
    }
    
    // Private methods and instance fields should go here
    //The time it has taken for the person(s) to cross so far.
    private int time;
    //Position of current flashlight.
    private final Position flashlight;
    //Position of current person(s)
    private final Position p1;
    private final Position p2; 
    private final Position p5; 
    private final Position p10;

    @Override
    public int getHeuristic(State goal) {
        return 0;
    }
    
}
