package bridge;

import framework.GUI;
import javax.swing.JFrame;

/**
 * A class to test your GUI class on the bridge crossing problem.
 * @author tcolburn
 */
public class BridgeGUI extends JFrame {
    
    public BridgeGUI() {
       add(new GUI(new BridgeProblem(), 
                   new BridgeCanvas(new BridgeState(Position.WEST, Position.WEST,
                                                    Position.WEST, Position.WEST,
                                                    Position.WEST, 0)), 
                   new BridgeCanvas(new BridgeState(Position.EAST, Position.EAST,
                                                    Position.EAST, Position.EAST,
                                                    Position.EAST, 0))));
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }
    
    /**
     * This method launches the gui.
     * @param args ignored
     */
    public static void main(String[] args) {
        new BridgeGUI();
    }
    
}