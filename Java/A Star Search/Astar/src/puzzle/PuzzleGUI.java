/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package puzzle;

import framework.GUI;
import javax.swing.JFrame;

/**
 * A class to test your GUI class on the puzzle crossing problem.
 * @author Michael
 */
public class PuzzleGUI  extends JFrame {
    
    public PuzzleGUI() {
       add(new GUI(new PuzzleProblem(), 
                   new PuzzleCanvas(new PuzzleState(2, 8, 3, 1, 6, 4, 7, 0, 5)),
                   new PuzzleCanvas(new PuzzleState(1, 2, 3, 8, 0, 4, 7, 6, 5))));
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }
    
    /**
     * This method launches the gui.
     * @param args ignored
     */
    public static void main(String[] args) {
        new PuzzleGUI();
    }
    
}
