
package waterjug;


import bridge.BridgeState;
import bridge.Position;
import framework.Canvas;
import framework.State;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;
import java.awt.geom.RoundRectangle2D;
import javax.swing.JFrame;
import javax.swing.Timer;


/**
 * A class that overrides Canvas. Creates an ActionListener() that adjusts
 * the displayed canvas image accordingly.
 * @author Michael Coughlin
 * CS 2511, Fall 2014
 * Section 1
 */
public final class WaterJugCanvas extends Canvas {
    
    /**
     * Constructs a WaterJugCanvas, creating the ActionListener as well as
     * setting the state and creating the initial graphic.
     * @param theState, the state object
     */
    public WaterJugCanvas(State theState) {
        super(theState);
        this.state = theState;
        this.newState = (WaterJugState)state;
        setPreferredSize(new Dimension(300, 300));
        rectangle = new RoundRectangle2D.Double(2, 2, 295, 297, 40, 40 );
        
        xWater = new Rectangle2D.Double(30,220,95 ,0);
        yWater = new Rectangle2D.Double(177,220,95 ,0);
      
        setNewState((WaterJugState)state);
        xHeight = 0;
        yHeight = 0;
        final int DELAY = 10;

        // The following code determines the action to be done on the water jugs.
        t = new Timer(DELAY, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {   
              setNewState((WaterJugState)state);
              
               if (newState.getJugY() == 4 && newState.getJugX() == 2) {
                 if (yWater.getHeight() < newState.getJugY() + 191 ) {
                    yHeight += 1;
                    yWater.setRect(177, 220 - yHeight, 95, yHeight);
                }
               if (xWater.getHeight() > newState.getJugX() + 100 ) {
                    xHeight -= 1;
                    xWater.setRect(30, 220 - xHeight, 95, xHeight);
                }
              }
              if (newState.getJugX() == 1){
               if (xWater.getHeight() < newState.getJugX() + 50 ) {
                    xHeight += 1;
                    xWater.setRect(30, 220 - xHeight, 95, xHeight);
                }
              }
              if (newState.getJugX() == 2){
               if (xWater.getHeight() < newState.getJugX() + 100 ) {
                    xHeight += 1;
                    xWater.setRect(30, 220 - xHeight, 95, xHeight);
                }
             }
             if (newState.getJugX() == 3){
               if (xWater.getHeight() < newState.getJugX() + 147 ) {
                    xHeight += 1;
                    xWater.setRect(30, 220 - xHeight, 95, xHeight);
                }
               } else if (newState.getJugX() == 0){
                if (xWater.getHeight() > 0) {
                    xHeight -= 1;
                    xWater.setRect(30, 220 - xHeight, 95, xHeight);
                }
               } 
             if (newState.getJugY() == 4){
                 if (yWater.getHeight() < newState.getJugY() + 191 ) {
                    yHeight += 1;
                    yWater.setRect(177, 220 - yHeight, 95, yHeight);
                }
               } else if (newState.getJugY() == 0){
                if (yWater.getHeight() > 0) {
                    yHeight -= 1;
                    yWater.setRect(177, 220 - yHeight, 95, yHeight);
                }
               }
                if (newState.getJugY() == 1 && newState.getJugX() == 3) {
                 if (xWater.getHeight() < newState.getJugX() + 147 ) {
                    xHeight += 1;
                    xWater.setRect(30, 220 - xHeight, 95, xHeight); 
                    yHeight -= 1.9;
                    yWater.setRect(177, 220 - yHeight, 95, yHeight);
                }
               } 
               if (newState.getJugY() == 1){
                 if (yWater.getHeight() < newState.getJugY() + 50 ) {
                    yHeight += 1;
                    yWater.setRect(177, 220 - yHeight, 95, yHeight);
                }
               }
                if (newState.getJugY() == 2){
                 if (yWater.getHeight() < newState.getJugY() + 100 ) {
                    yHeight += 1;
                    yWater.setRect(177, 220 - yHeight, 95, yHeight);
                }
               }
                if(newState.getJugY() == 3 && newState.getJugX() == 0){
                   if (yWater.getHeight() < newState.getJugY() + 147 ) {
                    yHeight += 1;
                    yWater.setRect(177, 220 - yHeight, 95, yHeight);
                    xHeight -= 1;
                    xWater.setRect(30, 220 - xHeight, 95, xHeight);
                   }
                }
                  if(newState.getJugY() == 2 && newState.getJugX() == 3){
              if (yWater.getHeight() > newState.getJugY() + 100 ) {
                    yHeight -= 1;
                    yWater.setRect(177, 220 - yHeight, 95, yHeight);
                }              
                }         
               repaint();  // repaint the current state
            }           
        });
       t.start();   
    }
 
    @Override
    public void render() {
        repaint();
    }
 
    @Override
     public void paintComponent(Graphics g) {
         super.paintComponent(g);
         Graphics2D g2= (Graphics2D) g;  
  
        g2.setColor(new Color(205,175,149)); // create background rectangle
        g2.draw(rectangle);
        g2.fill(rectangle);

        g2.setColor(Color.BLUE); //create the water in the jugs
        g2.draw(xWater);
        g2.fill(xWater);
        g2.draw(yWater);
        g2.fill(yWater);
    
        g2.setStroke(new BasicStroke(5) ); //create the outline of the jugs
        g2.setColor(Color.BLACK);
        line = new Line2D.Double(270,220,270,25);
        g2.draw(line);
        line.setLine(30, 220, 30, 70);
        g2.draw(line);
        line.setLine(128, 220, 128, 70);
        g2.draw(line);
        line.setLine(176, 220, 176, 25);
        g2.draw(line);
        line.setLine(32, 220, 128, 220);
        g2.draw(line);
        line.setLine(180, 220, 270, 220);
        g2.draw(line);
 
        g2.setColor(new Color(139,69,19)); // display state of jugs
        g2.setFont(new Font("Dialog", Font.BOLD, 24));
        g2.drawString("X (" + Integer.toString(newState.getJugX() ) + ")", 56, 255);
        g2.drawString("Y (" + Integer.toString(newState.getJugY() ) + ")", 196, 255);  
    }
    
    public static void main(String[] args) {
        JFrame frame = new JFrame("BridgeCanvas Test");
        frame.add(new WaterJugCanvas(new BridgeState(Position.WEST,
                                                   Position.WEST,
                                                   Position.WEST,
                                                   Position.WEST,
                                                   Position.WEST,
                                                   0)));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    } 

 // Private methods and instance variables 
  
    @Override
    public void setTheState(State theState) {
        this.state = theState;
    }
    
    public void setNewState(WaterJugState newState) {
        this.newState = newState;
    }
    
    private State state;
    
    /**
     * RoundRectangle2D used throughout the code.
     */
    private final RoundRectangle2D rectangle;
    
    /**
     * Rectangle2D used as the water graphic for JugX.
     */
    private final Rectangle2D xWater;
    
    /**
     * Rectangle2D used as the water graphic for JugY.
     */
    private final Rectangle2D yWater;
    
    /**
     * Line used to draw both jugs.
     */
    private Line2D line;
    
    /**
     * The WaterJugState.
     */
    private WaterJugState newState;
    
    /**
     * Timer used in ActionLister so set delay on animation.
     */
    private final  Timer t;
    
    /**
     *  The height of jugX.
     */
    private int xHeight;
    
    /**
     * The height of jugY.
     */
    private double yHeight;
     
   
    public State getState() {
        return state;   
    }

    
    
}
