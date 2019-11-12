package framework;

import blocks.BlockState;
import graph.DequeAdder;
import graph.Vertex;
import static java.lang.Integer.max;
import java.util.Comparator;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import javax.swing.JOptionPane;

/**
 * This abstract class represents a problem in a problem solving domain.
 * Note that this class does not provide a constructor.
 * It provides getters and setters for the current state
 * of the problem, the list of moves for the problem, and the problem's
 * introduction string.
 * Extending classes need not have instance fields for these attributes, 
 * as they are inherited from this class.
 * Extending classes must set these values in their constructors using 
 * the setters (mutators) provided in this class.
 * Extending classes must also override the abstract <b>success</b> method.
 */
public abstract class Problem {
    
    /**
     * Searches the Vertex for the end state, solution, of the current problem.
     * @param start the starting Vertex, state, of the problem
     * @param end
     * @return Vertex, the end state, NULL if state is not found
     */
    public Vertex search(Vertex start, final Vertex end) { 
        queueOps = 0;
        queueSize = 0;
        maxQueueSize = 0;
        minimalMoves = 0;
      
        PriorityQueue<Vertex> queue = new PriorityQueue<Vertex>(new Comparator<Vertex>() {
            @Override
            public int compare(Vertex v1, Vertex v2) {
                int h1 = ((State) v1).getHeuristic((State) end);
                int d1 = v1.getDistance();
                int h2 = ((State) v2).getHeuristic((State) end);
                int d2 = v2.getDistance();
                return (h1 + d1) - (h2 + d2);
            }
        });
        
        start.setDistance(0);
        start.setPredecessor(null); 
        queue.add(start); 
        queueOps++;
        queueSize++;
   
        while (!queue.isEmpty() ) {
             Vertex vertex = queue.remove(); // removes from the head
             currentState = (State)vertex;
          queueOps++;
          queueSize--;
       
         if (success()) { 
             stack = new LinkedList<State>();
             stack.push(currentState);
            minimalMoves++;
             Vertex link = vertex;
             boolean valid = true;  
             while(valid ) {
                 link = link.getPredecessor();
                if (!link.equals(start)) {  
                     stack.push((State)link);
                      minimalMoves++;
                }
                 if (link.equals(start))
                     valid = false;            
             }
           
             return vertex;
         }
         else  {
                 List<Vertex> x = this.expand(vertex);
               
             for (Vertex successor : x ) { 
                    successor.setPredecessor(vertex);
                    queue.add(successor);                  
                    queueOps++;
                    queueSize++;
                    maxQueueSize = max(queueSize, maxQueueSize);
          
                 
             }
         }
        }
          JOptionPane.showMessageDialog(null, "No Solution Found!"); 
          return null;
    }

    
    
    public boolean getChooser() {
        return chooser;
    }
   
    public void setChooser(boolean y) {
        this.chooser = y;
    }

    
    /**
     * Determines whether the current state of this problem is a success.
     * Extending classes need to override this method.
     * @return whether the current state is a success
     */
    public abstract boolean success();
   /**
     * Checks to see if a vertex appears on the predecessor path
     * of an ancestor vertex.
     * @param v the vertex to check
     * @param ancestor the ancestor of v
     * @return true if v equals ancestor or any ancestor of ancestor
     */
    public boolean occursOnPath(Vertex v, Vertex ancestor) {
    
       while(ancestor != null) {
         if ( v.equals(ancestor) ) {
             return true;
         }
             else ancestor = ancestor.getPredecessor();           
       }
        return false;
    }

    /**
     * Expands a vertex v in a state space search tree by creating a list
     * (its children) of all vertices adjacent to it in the state space.
     * The list may not include any vertex on the predecessor path 
     * leading to v.
     * Each child on the list has its predecessor set to v and its distance
     * from the root (its depth in the search tree) set to one more than v's 
     * distance.
     * @param v the vertex being expanded
     * @return a list of the children
     */
    public List<Vertex> expand(Vertex v) {
        LinkedList<Vertex> children = new LinkedList<Vertex>();
        List<Move> moveList = getMoves();
        
         for(Move theMove : moveList) {
             State child = theMove.doMove((State)v);
         
           if (child != null && !occursOnPath((Vertex)child, v) ) {
                 ((Vertex)child).setPredecessor(v); 
                 ((Vertex)child).setDistance(v.getDistance() + 1); 
                  children.add((Vertex)child);  
                  
        } 
         } 
     return children;
         }

    /**
     * Gets the current state of the problem.
     * @return the current state
     */
    public State getCurrentState() {
        return currentState;
    }

    /**
     * Sets the current state of the problem.
     * @param currentState the current state
     */
    public void setCurrentState(State currentState) {
        this.currentState = currentState;
    }

    /**
     * Gets an explanatory introduction string for the problem.
     * @return the introduction string
     */
    public String getIntroduction() {
        return introduction;
    }

    /**
     * Sets the introduction string for this problem.
     * @param introduction the introduction string
     */
    public void setIntroduction(String introduction) {
        this.introduction = introduction;
    }

    /**
     * Gets the list of moves for this problem.
     * @return the list of moves
     */
    public List<Move> getMoves() {
        return moves;
    }

    /**
     * Sets the list of moves for this problem.
     * @param moves the list of moves
     */
    public void setMoves(List<Move> moves) {
        this.moves = moves;
    }
    
    /**
     * The current state of this problem
     */
    private State currentState;

    /**
     * The explanatory string for this problem.
     */
    private String introduction;

    /**
     * The list of moves for this problem.
     */
    private List<Move> moves;
    
   private LinkedList<State> stack;
   private int queueOps;
   private int queueSize;
   private int maxQueueSize;
   private int minimalMoves;
   private List<State> startStates;
   private List<State> finalStates;
   private List<Integer> moveCounts;
   public State finalState; 
   public List<State> initialStates;
   private State initialState;
   private boolean chooser;

    public State getInitialState() {
        return initialState;
    }

    public int getMinimalMoves() {
        return minimalMoves;
    }

    public LinkedList<State> getStack() {
        return stack;
    }

    public int getQueueOps() {
        return queueOps;
    }

    public int getQueueSize() {
        return queueSize;
    }

    public int getMaxQueueSize() {
        return maxQueueSize;
    }
    
    public List<State> getInitialStates() {
        return initialStates;
    }

    public void setInitialStates(List<State> initialStates) {
        this.initialStates = initialStates;
    }
 
    public List<State> getStartStates() {
        return startStates;
    }

    public void setStartStates(List<State> startStates) {
        this.startStates = startStates;
    }

    public List<State> getFinalStates() {
        return finalStates;
    }

    public void setFinalStates(List<State> finalStates) {
        this.finalStates = finalStates;
    }

    public List<Integer> getMoveCounts() {
        return moveCounts;
    }

    public void setMoveCounts(List<Integer> moveCounts) {
        this.moveCounts = moveCounts;
    }

    public State getFinalState() {
        return finalState;
    }

    public void setFinalState(State finalState) {
        this.finalState = finalState;
    }
   
    public void setInitialCanvases(List<Canvas> initialCanvases) {
      this.initialCanvases = initialCanvases;
    }

    public void setFinalCanvases(List<Canvas> finalCanvases) {
       this.finalCanvases = finalCanvases;
    }

    public List<Canvas> getInitialCanvases() {
        return initialCanvases;
    }

    public List<Canvas> getFinalCanvases() {
        return finalCanvases;
    }
  
    private List<Canvas> initialCanvases;
    private List<Canvas> finalCanvases;

    
}
