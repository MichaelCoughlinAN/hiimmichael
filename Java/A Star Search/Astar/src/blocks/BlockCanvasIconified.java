package blocks;


import framework.Canvas;
import framework.State;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.GeneralPath;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;
import java.awt.geom.RoundRectangle2D;
import java.lang.reflect.Array;
import java.util.Stack;
import javax.swing.JFrame;

/**
 * A class that overrides Canvas. Creates an ActionListener() that adjusts
 * the displayed canvas image accordingly.
 * @author Michael Coughlin
 * CS 2511, Fall 2014
 * Section 1
 */
public class BlockCanvasIconified extends Canvas {

     /**
     * Constructs a BlockCanvas, creating the ActionListener as well as
     * setting the state and creating the initial graphic.
     * @param theState, the state object
     */
    public BlockCanvasIconified(State theState) {
        super(theState);
        
         this.state = theState; 
          this.blockState = (BlockState) theState;
         
         setPreferredSize(new Dimension(137, 107));
         largeRectangle = new Rectangle2D.Double(1,1,135,105);
         rectangle  = new Rectangle2D.Double(1,1,135,105);
         square = new Rectangle2D.Double(56,270,15,15);
         square1 = new Rectangle2D.Double(56,270,15,15);
         line = new Line2D.Double(17,80,120,80); //(double x1, double y1, double x2, double y2)
     
    }
     


        @Override
    public void setTheState(State state){
        this.state = state;
        this.blockState = (BlockState) state;
}
    
    @Override
     public void paintComponent(Graphics g) {
         super.paintComponent(g);
         Graphics2D g2= (Graphics2D) g;
             g2.setColor(new Color(189,183,107));
             g2.draw(largeRectangle);
             g2.fill(largeRectangle);    
             g2.setColor(new Color(160,82,45));
             g2.setStroke(new BasicStroke(1));
             g2.draw(rectangle); 
             g2.setStroke(new BasicStroke(2)); 
             g2.draw(line);
             g2.setColor(Color.BLACK); 
             g2.setFont(new Font("Dialog", Font.BOLD, 10));
             g2.drawString("p", 36, 92);
             g2.setFont(new Font("Dialog", Font.BOLD, 10));
             g2.drawString("q", 67, 92);
             g2.setFont(new Font("Dialog", Font.BOLD, 10));
             g2.drawString("r", 98, 92);
         
             
        Stack<Character> p = (Stack<Character>) blockState.getP().clone();
        Stack<Character> q = (Stack<Character>) blockState.getQ().clone();
        Stack<Character> r = (Stack<Character>) blockState.getR().clone();
        
        char[] pArray = null;
        char[] qArray = null;
        char[] rArray = null;
      
        if(!p.isEmpty() ) {
          pArray = new char[p.size() ];
          int length = p.size();
          for (int i = 0; i < length; ++i) {
            pArray[i] = p.pop();
        }
       int y = 63;
       int end = pArray.length -1;
    for (int i = 0; i < pArray.length; ++i) {
            char temp = pArray[end];
             g2.setColor(new Color(255,127,80));
             square.setRect(31,y,15,15);
             g2.draw(square);
             g2.fill(square);
             square1.setRect(31,y,15,15);
             g2.setColor(Color.BLACK);
             g2.setStroke(new BasicStroke(2));
             g2.draw(square1);
             g2.setFont(new Font("Dialog", Font.BOLD, 10));
             g2.drawString(Character.toString(temp), 35, y+11);
             y -= 15;
             end--;
        }
        }
        if (!q.isEmpty()) {
              qArray = new char[q.size() ];
          int length = q.size();
        for (int i = 0; i < length; ++i) {
            qArray[i] = q.pop();
        }
       int y = 63;
       int end = qArray.length -1;
    for (int i = 0; i < qArray.length; ++i) {
            char temp = qArray[end];
             g2.setColor(new Color(255,127,80));
             square.setRect(62,y,15,15);
             g2.draw(square);
             g2.fill(square);
             square1.setRect(62,y,15,15);
             g2.setColor(Color.BLACK);
             g2.setStroke(new BasicStroke(2));
             g2.draw(square1);
             g2.setFont(new Font("Dialog", Font.BOLD, 10));
             g2.drawString(Character.toString(temp), 66, y+11);
             y -= 15;
             end--;
        }
        }
        if (!r.isEmpty()) {
              rArray = new char[r.size() ];
          int length = r.size();
        for (int i = 0; i < length; ++i) {
            rArray[i] = r.pop();
        }
       int y = 63;
       int end = rArray.length -1;
    for (int i = 0; i < rArray.length; ++i) {
            char temp = rArray[end];
             g2.setColor(new Color(255,127,80));
             square.setRect(93,y,15,15);
             g2.draw(square);
             g2.fill(square);
             square1.setRect(93,y,15,15);
             g2.setColor(Color.BLACK);
             g2.setStroke(new BasicStroke(2));
             g2.draw(square1);
             g2.setFont(new Font("Dialog", Font.BOLD, 10));
             g2.drawString(Character.toString(temp), 97, y+11);
             y -= 15;
             end--;
        }
        }

        
        
        
    }

     
     
       public static void main(String[] args) {
        JFrame frame = new JFrame("BlockCanvas Test");
        frame.add(new BlockCanvasIconified(new BlockState("AB", "", "" )));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }
       
       
    private State state;
    private BlockState blockState;
    private final Rectangle2D.Double largeRectangle;
    private final Rectangle2D.Double rectangle;
    private final Rectangle2D.Double square;
    private final Rectangle2D.Double square1;
    private Line2D.Double line;
 
    
}
         