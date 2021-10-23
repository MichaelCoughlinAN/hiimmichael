
package puzzle;

import framework.Canvas;
import framework.State;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import javax.swing.JFrame;

/**
 * A class that overrides Canvas and adjusts the displayed canvas
 * image accordingly.
 * @author Michael Coughlin
 * CS 2511, Fall 2014
 * Section 1
 */
public class PuzzleCanvasIconified extends Canvas {

    /**
     * Constructs a PuzzleCanvas, setting the state and creating 
     * the initial graphic.
     * @param theState, the state object
     */
    public PuzzleCanvasIconified(State theState) {
        super(theState);
        
         this.state = theState;
         this.puzzleState = (PuzzleState) theState;
         
         setPreferredSize(new Dimension(105, 105));
      
         largeSquare = new Rectangle2D.Double(1,1,103,103);
         square1 = new Rectangle2D.Double(5,5,25, 25);
         square2 = new Rectangle2D.Double(40,5,25,25);
         square3 = new Rectangle2D.Double(75,5,25,25);
         
         square4 = new Rectangle2D.Double(5,40,25,25);
         square5 = new Rectangle2D.Double(40,40,25,25);
         square6 = new Rectangle2D.Double(75,40,25,25);
         
         square7 = new Rectangle2D.Double(5,75,25,25);
         square8 = new Rectangle2D.Double(40,75,25,25);
         square9 = new Rectangle2D.Double(75,75,25,25);
    }
    
    @Override
    public void setTheState(State state){
        this.state = state;
        this.puzzleState = (PuzzleState) state;
}
    

    @Override
     public void paintComponent(Graphics g) {
         super.paintComponent(g);
         Graphics2D g2= (Graphics2D) g;  

         g2.setStroke(new BasicStroke(7) );
     
         if (puzzleState.getFirstPosition() != 0) {
             g2.setColor(Color.BLACK);
             g2.draw(square1);
             g2.setColor(Color.BLUE); 
             g2.fill(square1);
             g2.setColor(Color.WHITE);
             g2.setFont(new Font("Dialog", Font.BOLD, 29));
             g2.drawString(Integer.toString(puzzleState.getFirstPosition() ), 10, 28);        
         }
         if (puzzleState.getSecondPosition() != 0) {
             g2.setColor(Color.BLACK);
             g2.draw(square2);
             g2.setColor(Color.BLUE); 
             g2.fill(square2);
             g2.setColor(Color.WHITE);
             g2.setFont(new Font("Dialog", Font.BOLD, 29));
             g2.drawString(Integer.toString(puzzleState.getSecondPosition() ), 45, 28);  
         }
         if (puzzleState.getThirdPosition() != 0) {
             g2.setColor(Color.BLACK);
             g2.draw(square3);
             g2.setColor(Color.BLUE); 
             g2.fill(square3);
             g2.setColor(Color.WHITE);
             g2.setFont(new Font("Dialog", Font.BOLD, 29));
             g2.drawString(Integer.toString(puzzleState.getThirdPosition() ), 79, 28);  
        }
         if (puzzleState.getForthPosition() != 0) {
             g2.setColor(Color.BLACK);
             g2.draw(square4);
             g2.setColor(Color.BLUE); 
             g2.fill(square4);
             g2.setColor(Color.WHITE);
             g2.setFont(new Font("Dialog", Font.BOLD, 29));
             g2.drawString(Integer.toString(puzzleState.getForthPosition() ), 10, 63);  
        }
         if (puzzleState.getFifthPosition() != 0) {
             g2.setColor(Color.BLACK);
             g2.draw(square5);
             g2.setColor(Color.BLUE); 
             g2.fill(square5);
             g2.setColor(Color.WHITE);
             g2.setFont(new Font("Dialog", Font.BOLD, 29));
             g2.drawString(Integer.toString(puzzleState.getFifthPosition() ), 45, 63);  
        }
         if (puzzleState.getSixthPosition() != 0) {
             g2.setColor(Color.BLACK);
             g2.draw(square6);
             g2.setColor(Color.BLUE); 
             g2.fill(square6);
             g2.setColor(Color.WHITE);
             g2.setFont(new Font("Dialog", Font.BOLD, 29));
             g2.drawString(Integer.toString(puzzleState.getSixthPosition() ), 79, 63);  
        }
         if (puzzleState.getSeventhPosition() != 0) {
             g2.setColor(Color.BLACK);
             g2.draw(square7);
             g2.setColor(Color.BLUE); 
             g2.fill(square7);
             g2.setColor(Color.WHITE);
             g2.setFont(new Font("Dialog", Font.BOLD, 29));
             g2.drawString(Integer.toString(puzzleState.getSeventhPosition() ), 10, 98);  
        } 
         if (puzzleState.getEigthPosition() != 0) {
            g2.setColor(Color.BLACK);
            g2.draw(square8);
            g2.setColor(Color.BLUE); 
            g2.fill(square8);
            g2.setColor(Color.WHITE);
            g2.setFont(new Font("Dialog", Font.BOLD, 29));
            g2.drawString(Integer.toString(puzzleState.getEigthPosition() ), 45, 98);  
        }
         if (puzzleState.getNinthPosition() != 0) {
            g2.setColor(Color.BLACK);
            g2.draw(square9);
            g2.setColor(Color.BLUE); 
            g2.fill(square9);
            g2.setColor(Color.WHITE);
            g2.setFont(new Font("Dialog", Font.BOLD, 29));
            g2.drawString(Integer.toString(puzzleState.getNinthPosition() ), 79, 98);  
        }    
         g2.setColor(Color.DARK_GRAY);
         g2.setStroke(new BasicStroke(1) );
         g2.draw(largeSquare);
         
    }
       public static void main(String[] args) {
        JFrame frame = new JFrame("PuzzleCanvas Test");
        frame.add(new PuzzleCanvasIconified(new PuzzleState(2, 8 ,3 ,1 ,6 ,4, 7, 0, 5)));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    } 
    
    // Instance variables used to create the graphic.
        private final Rectangle2D largeSquare;
        private final Rectangle2D square1;
        private final Rectangle2D square2;
        private final Rectangle2D square3;
        private final Rectangle2D square4;
        private final Rectangle2D square5;
        private final Rectangle2D square6;
        private final Rectangle2D square7;
        private final Rectangle2D square8;
        private final Rectangle2D square9;
        private PuzzleState puzzleState;
        private State state;
}
