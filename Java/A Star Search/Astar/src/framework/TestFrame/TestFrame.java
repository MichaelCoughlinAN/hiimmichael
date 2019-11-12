package framework.TestFrame;

import blocks.BlockCanvas;
import blocks.BlockProblem;
import blocks.BlockState;
import bridge.BridgeCanvas;
import bridge.BridgeProblem;
import bridge.BridgeState;
import bridge.Position;
import framework.Canvas;
import framework.GUI;
import framework.ProblemPane;
import java.awt.Dimension;
import javax.swing.JFrame;
import puzzle.PuzzleCanvas;
import puzzle.PuzzleProblem;
import puzzle.PuzzleState;
import waterjug.WaterJugCanvas;
import waterjug.WaterJugProblem;
import waterjug.WaterJugState;

/**
 * A class to display the bridge crossing and water jug problems in a tabbed pane
 * within an application frame.
 * @author tcolburn
 */
public class TestFrame extends JFrame {
    
    public TestFrame() {
        super("Testing Problems");
        ProblemPane problemPane = new ProblemPane();
      
        problemPane.add("Bridge", new GUI(new BridgeProblem(), 
                        new BridgeCanvas(new BridgeState(Position.WEST, Position.WEST,
                                                    Position.WEST, Position.WEST,
                                                    Position.WEST, 0)), 
                        new BridgeCanvas(new BridgeState(Position.EAST, Position.EAST,
                                                    Position.EAST, Position.EAST,
                                                    Position.EAST, 0))));
        problemPane.add("Water Jug", new GUI(new WaterJugProblem(), new WaterJugCanvas(new WaterJugState(0,0)),
                                                                    new WaterJugCanvas(new WaterJugState(2,2))));
        
        problemPane.add("8 Puzzle", new GUI(new PuzzleProblem(), new PuzzleCanvas(new PuzzleState(2, 8, 3, 1, 6, 4, 7, 0, 5)),
                                                                 new PuzzleCanvas(new PuzzleState(1, 2, 3, 8, 0, 4, 7, 6, 5))));
        problemPane.add("Blocks", new GUI(new BlockProblem(), new BlockCanvas(new BlockState("AB", "","")), 
                                                              new BlockCanvas(new BlockState("", "AB",""))));
        add(problemPane);
      
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setVisible(true);
        setLocationRelativeTo(null);
    }
    
    public static void main(String[] args) {
        new TestFrame();
    }
}