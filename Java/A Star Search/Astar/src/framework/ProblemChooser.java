package framework;

import java.awt.Color;
import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Iterator;
import java.util.List;
import javax.swing.JComponent;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.border.TitledBorder;

/**
 * @author tcolburn
 */
public class ProblemChooser {
    private Object state;

    /**
     * Creates a new problem chooser.  The three list parameters must match in
     * size and order.  The <b>nth</b> element of <b>startStates</b> must be the starting
     * state of a problem whose final state is the <b>nth</b> element of <b>finalStates</b>,
     * and the <b>nth</b> element of <b>moveCounts</b> must be the minimum number of moves
     * required to solve the <b>nth</b> problem.  A dialog is issued that displays the
     * problems and allows the user to select one.
     * @param startStates the list of start states
     * @param goalStates the list of final states
     * @param moveCounts the list of minimum move counts
     */
    public ProblemChooser(List<State> startStates, List<State> goalStates,
                          List<Integer> moveCounts) {
        this.startStates = startStates;
        this.goalStates = goalStates;

        assert(startStates.size() == goalStates.size() &&
               startStates.size() == moveCounts.size());

        makeProblemGrid(startStates, goalStates, moveCounts);
    }

    /**
     * Creates a new problem chooser.  The five list parameters must match in
     * size and order.  The <b>nth</b> element of <b>startStates</b> must be the starting
     * state of a problem whose final state is the <b>nth</b> element of <b>finalStates</b>,
     * and the <b>nth</b> element of <b>moveCounts</b> must be the minimum number of moves
     * required to solve the <b>nth</b> problem.  A dialog is issued that graphically displays the
     * problems using the provided canvas objects and allows the user to select one.
     * @param startStates the list of start states
     * @param goalStates the list of final states
     * @param moveCounts the list of minimum move counts
     * @param startCanvases the list of start canvases
     * @param goalCanvases the list of goal canvases
     */
    public ProblemChooser(List<State> startStates, List<State> goalStates,
                          List<Integer> moveCounts, List<Canvas> startCanvases, List<Canvas> goalCanvases) {
        this.startStates = startStates;
        this.goalStates = goalStates;

        assert(startStates.size() == goalStates.size() &&
               startStates.size() == moveCounts.size() &&
               startStates.size() == startCanvases.size() &&
               startStates.size() == goalCanvases.size());

        makeProblemGrid(startCanvases, goalCanvases, moveCounts);
    }

    /**
     * Returns the final state of the selected problem.
     * @return the final state of the selected problem
     */
    public State getFinal() {
        return goal;
    }

    /**
     * Returns the start state of the selected problem.
     * @return the start state of the selected problem
     */
    public State getStart() {
        return start;
    }
    
    private void makeProblemGrid(List startObjects, List goalObjects, List moveCounts) {
        Iterator startIter = startObjects.iterator();
        Iterator goalIter = goalObjects.iterator();
        Iterator moveCountIter = moveCounts.iterator();
        
        problemGrid = new JPanel();
        
        int numberOfProblems = startObjects.size();

        int cols = 3;
        int rows = numberOfProblems/cols;
        rows = rows * cols == numberOfProblems ? rows : rows + 1;

        problemGrid.setLayout(new GridLayout(rows, cols, 10, 10));

        problemNumber = 1;
        while ( startIter.hasNext() ) {
            problemGrid.add(makeProblemPanel(problemNumber++, startIter.next(), 
                                                              goalIter.next(),
                                                              (Integer)moveCountIter.next()));
        }
        problemNumber = 1;
        
        resetBackgrounds();
        
        elicitProblem();
    }
    
    private void elicitProblem() {
        JOptionPane.showMessageDialog(null, problemGrid, "Choose a Problem and Click OK",
                JOptionPane.QUESTION_MESSAGE);

        start = startStates.get(problemNumber-1);
        goal = goalStates.get(problemNumber-1);
    }

    private JPanel makeProblemPanel(final int pnum, final Object start, Object goal, Integer moveCount) {
        final JPanel panel = new JPanel();
        ((FlowLayout)panel.getLayout()).setHgap(20);

        panel.setBorder(new TitledBorder("Problem " + pnum + ": " + moveCount + " moves"));
        panel.add(makeStateComponent(start, "Initial", pnum));
        panel.add(makeStateComponent(goal, "Final", pnum));
        panel.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                problemNumber = pnum;
           
                resetBackgrounds();
                panel.setBackground(Color.red);
            }

           
            
        });
        return panel;
    }

 
    private JComponent makeStateComponent(Object state, String title, final int pnum) {
        final JComponent stateComponent = 
                state instanceof State ? makeStateArea(state) : makeStateCanvas(state);
        stateComponent.setBorder(new TitledBorder(title));
        stateComponent.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                problemNumber = pnum;
                resetBackgrounds();
                ((JComponent)stateComponent.getParent()).setBackground(Color.red);
            }
        });
        return stateComponent;
    }
    
    private JComponent makeStateArea(Object state) {
        JComponent jtArea = new JTextArea(state.toString());
        ((JTextArea)jtArea).setEditable(false);
        jtArea.setFont(new Font(Font.MONOSPACED, Font.BOLD, 12));
        return jtArea;
    }
    
    private JComponent makeStateCanvas(Object canvas) {
        JComponent panel = new JPanel();
        panel.add((Canvas)canvas);
        return panel;
    }
    
    private void resetBackgrounds() {
        Component[] probs = problemGrid.getComponents();
        for (int i = 0; i < probs.length; i++) {
            ((JComponent)probs[i]).setBackground(Color.white);
        }
    }
    
    private List<State> startStates;
    private List<State> goalStates;
    
    private JPanel problemGrid;
    
    private int problemNumber;
    
    private State start;
    private State goal;
}
