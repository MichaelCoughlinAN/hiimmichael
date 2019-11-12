
package bridge;

import static bridge.Position.WEST;
import framework.Canvas;
import framework.State;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.GeneralPath;
import java.awt.geom.Rectangle2D;
import java.awt.geom.RoundRectangle2D;
import javax.swing.JFrame;

/**
 * A class that overrides Canvas. Creates an ActionListener() that adjusts
 * the displayed canvas image accordingly.
 * @author Michael Coughlin
 * CS 2511, Fall 2014
 * Section 1
 */
public class BridgeCanvas extends Canvas {
    
     /**
     * Constructs a BridgeCanvas, creating the ActionListener as well as
     * setting the state and creating the initial graphic.
     * @param theState, the state object
     */
    public BridgeCanvas(State theState) {
        super(theState);
        
         this.state = theState;

          setPreferredSize(new Dimension(280, 300));
          path = new GeneralPath();
          rectangle = new RoundRectangle2D.Double(5, 5, 270, 293, 40, 40 ); //create the background
         
       path.moveTo(110, 5);     //create the river
       path.quadTo(80, 60, 120, 150);
       path.lineTo(190, 150);
       path.quadTo(150, 70, 178, 5);
       path.closePath();
          
       path2 = new GeneralPath();
       path2.moveTo(115, 150);     
       path2.quadTo(85, 250, 110, 300);
       path2.lineTo(178, 300);
       path2.quadTo(148, 220, 185, 150);
       path2.closePath();
                
          //creates the bridge
         bridgeRectangle =  new Rectangle2D.Double(90, 126, 105, 45);  
         bridgePath = new GeneralPath();
         bridgePath.moveTo(86, 117);  
         bridgePath.lineTo(86, 178);  
         bridgePath.lineTo(134, 150);
         bridgePath.closePath();
         bridgePath2 = new GeneralPath();
         bridgePath.moveTo(205, 117);  
         bridgePath.lineTo(205, 178);  
         bridgePath.lineTo(160, 150);   
         bridgePath.closePath();       
    }

    @Override
     public void paintComponent(Graphics g) {
         super.paintComponent(g);
         Graphics2D g2= (Graphics2D) g;
         
     
        g2.setStroke(new BasicStroke(5) );
        g2.setColor(new Color(34,139,34)); //forest green
        g2.draw(rectangle);
        g2.fill(rectangle);
        
        g2.setColor(new Color(0,0,255));
        g2.draw(path);
        g2.fill(path);
        g2.draw(path2);
        g2.fill(path2);
        
        g2.setColor(new Color(139,69,19));
        g2.draw(bridgeRectangle);
        g2.fill(bridgeRectangle);
        g2.draw(bridgePath);
        g2.fill(bridgePath);
        g2.draw(bridgePath2);
        g2.fill(bridgePath2);
        
        g2.setColor(Color.WHITE);
        g2.setFont(new Font("Dialog", Font.BOLD, 24));

        updateState(); //set state
    
        // The following determines the state of the bridge and creates the graphic
        // accordingly.
        BridgeState newState = (BridgeState)state;
        g2.drawString(Integer.toString(time) + " min", 114, 161);
        g2.setColor(Color.BLACK);
        g2.setFont(new Font("Dialog", Font.ITALIC, 30));
        
        if(newState.getP1Position().equals(WEST)){
        g2.drawString("P1", 31, 65);
       } else g2.drawString("P1", 215, 65);
         
        if(newState.getP2Position().equals(WEST)){
        g2.drawString("P2", 31, 115);
       } else g2.drawString("P2", 215, 115);
        
          if(newState.getFlashlightPosition().equals(WEST)){
        g2.drawString("f", 31, 165);
       } else g2.drawString("f", 230, 165);
        
        if(newState.getP5Position().equals(WEST)){
        g2.drawString("P5", 31, 215);
       } else g2.drawString("P5", 215, 215);
        
        if(newState.getP10Position().equals(WEST)){
        g2.drawString("P10", 31, 265);
       } else g2.drawString("P10", 215, 265);
    }
     
     /**
      * Updates the state and sets the time taken so far.
      */
  public void updateState() {
    BridgeState newState = (BridgeState)state;
    time = newState.getTimeSoFar();  
}

       public static void main(String[] args) {
        JFrame frame = new JFrame("BridgeCanvas Test");
        frame.add(new BridgeCanvas(new BridgeState(Position.WEST,
                                                   Position.WEST,
                                                   Position.WEST,
                                                   Position.WEST,
                                                   Position.WEST,
                                                   0)));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }
            
     public State getState() {
        return state;
    }

    @Override
    public void setTheState(State theState) {
        this.state = theState;
    }
    
    @Override
    public State getPrevState() {
        return prevState;
    }

    @Override
    public void setPrevState(State prevState) {
        this.prevState = prevState;
    }
    
  // Private instance variables
    private State prevState;
    
    /**
     * Path used to create bridge graphic.
     */
    private final GeneralPath path; 
    
    /**
     * Path used to create bridge graphic.
     */
    private final GeneralPath path2; 
    
    /**
     * Path used to create bridge graphic.
     */
    private final GeneralPath bridgePath;
    
    /**
     * Path used to create bridge graphic.
     */
    private final GeneralPath bridgePath2; 
    
    /**
     * Rectangle2D used to create bridge graphic.
     */
    private final RoundRectangle2D rectangle;
    
    /**
     * Rectangle2D used to create bridge graphic.
     */
    private final Rectangle2D bridgeRectangle;
    
    /**
     * The current state.
     */
    private State state;
    
    /**
     * The current time.
     */
    private int time;
     
       
       
       
}
