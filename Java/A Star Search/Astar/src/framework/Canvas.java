
package framework;

import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JComponent;

/**
 * An abstract class that creates a canvas used to display the current state.
 * Note, this class extends JComponent.
 * @author Michael Coughlin
 * CS 2511, Fall 2014
 * Section 1
 */
public abstract class Canvas extends JComponent {
    
    /**
     * Creates a canvas object to be used by the overriding canvas objects.
     * @param stateObject the state
     */
    public Canvas(State stateObject) {
        this.theState = stateObject; 
    }
    /**
     * A method used to evoke repaint().
     */
    public void render(){
        repaint();
    }
  
    
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2= (Graphics2D) g;
    }

    /**
     * Getter method for theState object
     * @return theState
     */
    public State getTheState() {
        return theState;
    }

    /**
     * Setter method for theState object
     * @param theState 
     */
    public void setTheState(State theState) {
        this.theState = theState;
    }
    
    /**
     * Getter method for the prevState object.
     * @return preState, the previous state.
     */
    public State getPrevState() {
        return prevState;
    }

    /**
     * Setter method for prevState object
     * @param prevState 
     */
    public void setPrevState(State prevState) {
        this.prevState = prevState;
    }
    
    /**
     * The current state object.
     */
    private State theState;
    
    /**
     * The previous state object.
     */
    private State prevState;
}
