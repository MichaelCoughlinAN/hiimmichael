package framework;

/**
 * This abstract class represents a move in a problem solving domain.
 * It provides a constructor and accessor for a move's name, but extending
 * classes must provide code for actually performing moves.
 * Extending classes need not have an instance field for the move name, 
 * as it is inherited from this class.
 * Extending classes must access the move name through this class's <b>getMoveName()</b>
 * method.
 */

public abstract class Move {
    
    /**
     * Creates a problem move, storing the move name.
     * It is a precondition that the move name be valid for the
     * underlying problem.
     * Extending class constructors must call this constructor first using
     * <b>super</b>.
     * @param moveName the user command for this move.
     */
    public Move(String moveName) {
        this.moveName = moveName;
    }
    
    /**
     * Performs this move on a given state.  
     * Extending classes must override this method.
     * Note also that overriding methods should cast the <b>State</b>
     * argument to the appropriate specific class type before using it.
     * Depending on the
     * move name for this state, this method attempts to create a new state
     * that is the result of applying the move to the given state.  If the
     * move cannot be performed for whatever reason, <b>null</b> is returned.  
     * Otherwise the resulting 
     * NEW state is returned.  Note that the argument state is not altered.
     * @param state an existing state
     * @return a new state resulting from the move (might be null)
     */
    public abstract State doMove(State state);
    

    /**
     * Accessor for this move's name.
     * @return the name of this move
     */
    public String getMoveName() {
        return moveName;        
    }

    
    /**
       Instance field for this move's name.
     */
    private String moveName;  
    
}
