package bridge;
import java.lang.StringBuilder;
/**
 * This class represents states of the Bridge Crossing problem.
 * It creates new bridge states, tests states for equality,
 * and produces string representations of them.
 * @author your name here
 */
public class BridgeState {
    //The time it has taken for the person(s) to cross so far.
    private int time;
    //Position of current flashlight.
    private Position flashlight;
    //Position of current person(s)
    private Position p1;
    private Position p2; 
    private Position p5; 
    private Position p10;

    /**
     * Creates a new bridge state.  
     * Besides storing the positions of the persons and flashlight, a
     * bridge state should also store the time taken so far to cross in
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
     * Tests this bridge state with another for equality.
     * Two bridge states are equal if the positions of the persons and 
     * flashlight in one state are matched by their positions in the other.
     * Note that the time taken to cross so far is not taken into account
     * when considering equality.
     * @param other the other bridge state to be tested against this one.
     * @return true if this state is equal to the other state, false otherwise
     */
    public boolean equals(BridgeState other) {
        return this.getP1Position().equals(other.getP1Position()) &&
                this.getP2Position().equals(other.getP2Position()) &&
                this.getP5Position().equals(other.getP5Position()) &&
                this.getP10Position().equals(other.getP10Position()) &&
                this.getFlashlightPosition().equals(other.getFlashlightPosition());
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

    public Position getFlashlightPosition() {
        return flashlight;
    }

    public Position getP10Position() {
        return p10;
    }

    public Position getP1Position() {
        return p1;
    }

    public Position getP2Position() {
        return p2;
    }

    public Position getP5Position() {
        return p5;
    }

    public int getTimeSoFar() {
        return time;
    }   
}
