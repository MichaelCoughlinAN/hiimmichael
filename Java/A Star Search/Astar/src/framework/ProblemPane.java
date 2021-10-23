package framework;

import javax.swing.JTabbedPane;

/**
 * A class for presenting multiple problems in tabbed panes.
 * @author tcolburn
 */
public class ProblemPane extends JTabbedPane {
    
    /**
     * Adds a problem to this problem pane.
     * @param title The name of the problem to add
     * @param gui The component that displays the problem
     */
    public void add(String title, GUI gui) {
        super.add(title, gui);
    }
    
}