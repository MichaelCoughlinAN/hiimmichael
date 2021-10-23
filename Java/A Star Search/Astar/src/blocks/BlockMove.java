package blocks;

import framework.Move;
import framework.State;
import java.util.Arrays;
import java.util.List;

/**
 * This class represents moves in the Blocks World.
 * @author tcolburn
 */
public class BlockMove extends Move {
    
    /**
     * Constructs a new block move object.
     * @param moveName the name of this move.
     * It is an error if the name is not one of the following:
     * <ul>
     * <li> "Move block from p to q" </li>
     * <li> "Move block from p to r" </li>
     * <li> "Move block from q to p" </li>
     * <li> "Move block from q to r" </li>
     * <li> "Move block from r to p" </li>
     * <li> "Move block from r to q" </li>
     * </ul>
     */
    public BlockMove(String moveName) {
	super(moveName);
        if (!moveNames.contains(moveName)) {
            throw new RuntimeException("Bad move name: " + moveName);
        }
    }

    /**
     * Attempts to perform this move on a given block state.
     * The move to perform is determined by this object's move name.
     * A move is from a source place to a target place.
     * If the move can be performed a new block state object is returned that
     * reflects this move.
     * If the move cannot be performed <b>null</b> is returned.
     * A move cannot be performed if the source place is empty.
     * @param state the block state on which this move is to be performed
     * @return a new block state reflecting the move, or <b>null</b> if it
     * cannot be performed
     */
    public State doMove(State state) {
        BlockState s = (BlockState) state;
        if ( getMoveName().equals(PQ) )
            if ( s.placeEmpty('p') )
                return null;
            else
                return new BlockState(s,'p','q');
        else if ( getMoveName().equals(PR) )
            if ( s.placeEmpty('p') )
                return null;
            else
                return new BlockState(s,'p','r');
        else if ( getMoveName().equals(QP) )
            if ( s.placeEmpty('q') )
                return null;
            else
                return new BlockState(s,'q','p');
        else if ( getMoveName().equals(QR) )
            if ( s.placeEmpty('q') )
                return null;
            else
                return new BlockState(s,'q','r');
        else if ( getMoveName().equals(RP) )
            if ( s.placeEmpty('r') )
                return null;
            else
                return new BlockState(s,'r','p');
        else // Move must be RQ
            if ( s.placeEmpty('r') )
                return null;
            else
                return new BlockState(s,'r','q');
    }

    private static final String PQ = "Move block from p to q";
    private static final String PR = "Move block from p to r";
    private static final String QP = "Move block from q to p";
    private static final String QR = "Move block from q to r";
    private static final String RP = "Move block from r to p";
    private static final String RQ = "Move block from r to q";
    
    private static final List<String> moveNames = 
            Arrays.asList(new String[]{PQ, PR, QP, QR, RP, RQ});

}
