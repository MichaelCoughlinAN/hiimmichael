package blocks;

import framework.State;
import graph.SimpleVertex;
import java.util.Arrays;
import java.util.Stack;

/**
 * This class represents a state of the Blocks World.
 * @author tcolburn
 */
public class BlockState extends SimpleVertex implements State {
    
    /**
     * A block state is represented by three stacks of characters, with the
     * top block on the stack top.
     * @param p the stack at place p
     * @param q the stack at place q
     * @param r  the stack at place r
     */
    public BlockState(Stack<Character> p, Stack<Character> q, Stack<Character> r) {

        this.p = p;
	this.q = q;
	this.r = r;
    }

    /**
     * A convenience constructor that allows stacks of blocks to be presented
     * as strings that are then converted to stacks of characters.
     * The first character of the string represents the top block of the stack.
     * @param p string representing place p
     * @param q string representing place q
     * @param r  string representing place r
     */
    public BlockState(String p, String q, String r) {
        this.p = stringToStack(p);
        this.q = stringToStack(q);
        this.r = stringToStack(r);
    }

    /**
     * A block state constructor that takes a state, a source place, 
     * and a target place, and creates a new state in which the block 
     * on top of the source is moved to the top of the target.
     * Precondition: the source place cannot be empty.
     * Note the use of clone() to copy the stacks.
     * @param state
     * @param source
     * @param target 
     */
    public BlockState(BlockState state, char source, char target) {
        p = (Stack<Character>)state.p.clone();
	q = (Stack<Character>)state.q.clone();
	r = (Stack<Character>)state.r.clone();
        Character block = source == 'p' ? p.pop() :
                          source == 'q' ? q.pop() : r.pop();
        Stack<Character> stack = target == 'p' ? p :
                                 target == 'q' ? q : r;
        stack.push(block);
    }

    /**
     * Indicates whether a place is empty in this state.
     * Precondition: the place must be either 'p', 'q', or 'r'.
     * @param place either 'p', 'q', or 'r'
     * @return true if the place is empty, false otherwise.
     */
    public boolean placeEmpty(char place) {

        if ( place == 'p' )
            if ( p.empty() )
                return true;
            else
                return false;
        else if ( place == 'q' )
            if ( q.empty() )
                return true;
            else
                return false;
        else  // place must be 'r'
            if ( r.empty() )
                return true;
            else
                return false;
    }

    /**
     * Getter for the stack at place p. 
     * Provided primarily for the BlockCanvas class
     * @return the stack at place p
     */
    public Stack<Character> getP() {
        return p;
    }

    /**
     * Getter for the stack at place q. 
     * Provided primarily for the BlockCanvas class
     * @return the stack at place q
     */
    public Stack<Character> getQ() {
        return q;
    }

    /**
     * Getter for the stack at place r. 
     * Provided primarily for the BlockCanvas class
     * @return the stack at place r
     */
    public Stack<Character> getR() {
        return r;
    }
    
    /**
     * Checks for equality between this block state and another object.
     * @param other the other object
     * @return true if all corresponding stacks are equal, false otherwise
     */
    public boolean equals(Object other) {
	if (this == other) return true;
	if (other == null) return false;
	if (getClass() != other.getClass()) return false;
	BlockState state = (BlockState) other;
	return (p.equals(state.p) &&
		q.equals(state.q) &&
		r.equals(state.r));
    }

    /**
     * Creates and returns a string representation of this block state.
     * @return a string representation of this block state
     */
    public String toString() {

        StringBuffer buf = new StringBuffer();

        int maxSize = Math.max(Math.max(p.size(), q.size()), r.size());

	for (int i = maxSize-1; i >= 0; i--) {
	    Character pBlock = getBlock(p,i);
	    Character qBlock = getBlock(q,i);
	    Character rBlock = getBlock(r,i);
            buf.append(" " + pBlock + " " + qBlock + " " + rBlock + " \n");
	}

        buf.append(" ----- \n p q r ");
        return buf.toString();
    }

    private static Character getBlock(Stack<Character> s, int index) {
	Character block = ' ';
	try {
	    block = ((Character)s.elementAt(index));
	}
	catch(ArrayIndexOutOfBoundsException ex) { }
	return block;
    }

    /**
     * Computes and returns a heuristic estimate of the number of moves from 
     * this state to the goal state.
     * @param goal the goal state for the problem currently being solved
     * @return the heuristic estimate of the number of moves to the goal
     */
    public int getHeuristic(State goal) {
        return sumManhattan(goal);
    }
    
      private int sumManhattan(State goal) {        
      BlockState finalState = (BlockState)goal;
      int value = 0;
      //<editor-fold defaultstate="collapsed" desc="expand code">
      Stack<Character> pStack = (Stack<Character>) getP().clone();
      Stack<Character> qStack = (Stack<Character>) getQ().clone();
      Stack<Character> rStack = (Stack<Character>) getR().clone();
      Stack<Character> finalP = (Stack<Character>) finalState.getP().clone();
      Stack<Character> finalQ = (Stack<Character>) finalState.getQ().clone();
      Stack<Character> finalR = (Stack<Character>) finalState.getR().clone();
      char[] pArray = null;
      char[] qArray = null;
      char[] rArray = null;
      char[] finalPArray = null;
      char[] finalQArray = null;
      char[] finalRArray = null;
      
      if (!pStack.isEmpty() ) {
          pArray = new char[pStack.size() ];
          int length = pStack.size();
          for (int i = 0; i < length; ++i)
              pArray[i] = pStack.pop();
      }
      if (!qStack.isEmpty() ) {
          qArray = new char[qStack.size() ];
          int length = qStack.size();
          for (int i = 0; i < length; ++i)
              qArray[i] = qStack.pop();
      }
      if (!rStack.isEmpty() ) {
          rArray = new char[rStack.size() ];
          int length = rStack.size();
          for (int i = 0; i < length; ++i)
              rArray[i] = rStack.pop();
      }
      if (!finalP.isEmpty() ) {
          finalPArray = new char[finalP.size() ];
          int length = finalP.size();
          for (int i = 0; i < length; ++i)
              finalPArray[i] = finalP.pop();
      }
      if (!finalQ.isEmpty() ) {
          finalQArray = new char[finalQ.size() ];
          int length = finalQ.size();
          for (int i = 0; i < length; ++i)
              finalQArray[i] = finalQ.pop();
      }
      if (!finalR.isEmpty() ) {
          finalRArray = new char[finalR.size() ];
          int length = finalR.size();
          for (int i = 0; i < length; ++i)
              finalRArray[i] = finalR.pop();
      }
//</editor-fold>
   
          if (pArray == null && finalPArray != null)
              value = value + finalPArray.length;
          if (qArray == null && finalQArray != null)
              value = value + finalQArray.length;
          if (rArray == null && finalRArray != null)
              value = value + finalRArray.length;
          if (pArray != null && finalPArray == null)
              value = value + pArray.length;
          if (qArray != null && finalQArray == null)
              value = value + qArray.length;
          if (rArray != null && finalRArray == null)
              value = value + rArray.length;
     
          if (pArray != null && finalPArray != null) {
              if (pArray[pArray.length-1] != finalPArray[finalPArray.length-1]) {
                 value = pArray.length + finalPArray.length;
          } else if (pArray[pArray.length-1] == finalPArray[finalPArray.length-1]) {
                      value = value + finalPArray.length-1;
                  }
          }
           if (qArray != null && finalQArray != null) {
             if (qArray[qArray.length-1] != finalQArray[finalQArray.length-1]) {
                 value = qArray.length + finalQArray.length;
          } else if (qArray[qArray.length-1] == finalQArray[finalQArray.length-1]) {
                      value = value + finalQArray.length-1;
                  }
          }
             if (rArray != null && finalRArray != null) {
               if (rArray[rArray.length-1] != finalRArray[finalRArray.length-1]) {
                 value = rArray.length + finalRArray.length;
          } else if (rArray[rArray.length-1] == finalRArray[finalRArray.length-1]) {
                      value = value + finalRArray.length-1;
                  }
          }
           // compensating for overcounting:
               char topValue;
             if (pArray != null){
                topValue = pArray[0];
                if (finalQArray != null)
                    if(finalQArray[finalQArray.length-1] == topValue)
                        if(qArray == null)
                            value--;
                    else if(finalQArray[finalQArray.length-1] == qArray[qArray.length-1])
                        value--;
                    
                 if (finalRArray != null)
                    if(finalRArray[finalRArray.length-1] == topValue)
                        if(rArray == null)
                            value--;
                  else if(finalRArray[finalRArray.length-1] == rArray[rArray.length-1])
                        value--;
             }
              if (qArray != null){
                topValue = qArray[0];
                if (finalPArray != null)
                    if(finalPArray[finalPArray.length-1] == topValue)
                        if(pArray == null)
                            value--;
                 else if(finalPArray[finalPArray.length-1] == pArray[pArray.length-1])
                        value--;
                 if (finalRArray != null)
                    if(finalRArray[finalRArray.length-1] == topValue)
                        if(rArray == null)
                            value--;
                  else if(finalRArray[finalRArray.length-1] == rArray[rArray.length-1])
                        value--;
             }
               if (rArray != null){
                topValue = rArray[0];
                if (finalQArray != null)
                    if(finalQArray[finalQArray.length-1] == topValue)
                        if(qArray == null)
                            value--;
                 else if(finalQArray[finalQArray.length-1] == qArray[qArray.length-1])
                        value--;
                 if (finalPArray != null)
                    if(finalPArray[finalPArray.length-1] == topValue)
                        if(pArray == null)
                            value--;
                  else if(finalPArray[finalPArray.length-1] == pArray[pArray.length-1])
                        value--;
             }
             
               
             
        return value;
    }

      
    @Override
    public int hashCode() {
        // You must write for extra credit
        return 0;
    }

    /**
     * Helper method that converts a string to a stack of characters.
     * @param string a string representing a stack of blocks on a place
     * @return a stack of characters with the top character corresponding
     * to the first character in the string
     */
    private static Stack<Character> stringToStack(String string) {
        Stack<Character> stack = new Stack<Character>();
        for(int i = string.length()-1; i >= 0; i--) {
            stack.push(string.charAt(i));
        }
        return stack;
    }

    private Stack<Character> p;
    private Stack<Character> q;
    private Stack<Character> r;

  
}
