package framework;

import graph.Vertex;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Comparator;
import java.util.List;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextArea;
import javax.swing.Timer;
import javax.swing.border.TitledBorder;


/**
 * A class that creates GUI components for solving search problems.
 * @author Michael Coughlin
 * CS 2511, Fall 2014
 * Section 1
 */
public class GUI extends JComponent {
    
    public GUI(final Problem problem, final Canvas canvas, Canvas finalCanvas) {
        this.problem = problem;
        this.canvas = canvas;
        this.moveCount = 0;     
        final int DELAY = 1000;
        resetState = problem.getCurrentState();
        breadthActive = true;
        depthActive = false;
        clicked = false;
//        regular = true;
        this.finalCanvas = finalCanvas;
        makeComponentsAndContainers(); // creates and initializes components 
                                       // and containers
      
        setLayoutAndDimensions();     // sets the layouts and dimensions
        
        introText.setFont(new Font("Monospaced", Font.BOLD, 14));
        introText.setText(problem.getIntroduction());
        introText.setEditable(false);       
        introPanel.add(introText);
        add(introPanel);    
        statePanel.setBorder(new TitledBorder("Current State"));
        canvas.setTheState(problem.getCurrentState() );
        statePanel.add(canvas); 
        mainPanel.add(statePanel); 
        moves = problem.getMoves();
        length = problem.getMoves().size();   
        movesPanel.setBorder(new TitledBorder("Possible Moves") );
       
        makeOptions();                 // creats move buttons and adds them to movesPanel
      
        mainPanel.add(movesPanel);
        finalStatePanel.setBorder(new TitledBorder("Final State"));
        finalStatePanel.add(finalCanvas);
        mainPanel.add(finalStatePanel);
        add(mainPanel);
//        buttonPanel.add(regularA);
//        buttonPanel.add(enhancedA); 
        FlowLayout theLayout = new FlowLayout(FlowLayout.CENTER);
        theLayout.setHgap(28);
        bottomPanel.setLayout(theLayout);  
        bottomPanel.add(solveButton);
       // bottomPanel.add(buttonPanel);
        solutionPanel.add(solutionLength);
        solutionPanel.add(numD);
        solutionPanel.add(maxSize);
        solutionPanel.setBorder(new TitledBorder("Solution Statistics") );   
        bottomPanel.add(solutionPanel);  
        solutionButtonPanel.add(nextMoves);
        solutionButtonPanel.add(allMoves);
        bottomPanel.add(solutionButtonPanel);
        
        resetButton(); 
        
        bottomPanel.add(solutionBackPanel);  
        add(bottomPanel);
        allMoves.setEnabled(false);
        nextMoves.setEnabled(false);
        solveButton.setToolTipText("Finds the solution of your current problem!");    
        
        solveButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event){ 
                 allMoves.setEnabled(true);
                 nextMoves.setEnabled(true);
                 
                 Component[] components = movesPanel.getComponents();
                 for (int i = 0; i < length; ++i) {
                    Component component = null;
                    component = components[i];
                    component.setEnabled(false);
            }        
                 
           
                  problem.search((Vertex)problem.getCurrentState(), (Vertex)problem.getFinalState());
 
            if (problem.getMinimalMoves() != 0 && problem.getQueueOps() != 0 && problem.getMaxQueueSize() != 0) {
                 solutionLength.setText("Solution Length: " + Integer.toString(problem.getMinimalMoves() )); 
                 numD.setText("Num of PQ Ops: " + Integer.toString(problem.getQueueOps() ));
                 maxSize.setText("Max PQ size: " + Integer.toString(problem.getMaxQueueSize() ));           
            }
                solveButton.setEnabled(false);
            }
        });
     
          nextMoves.addActionListener(new ActionListener() {
              @Override
              public void actionPerformed(ActionEvent event) {
                if (!clicked) {
                  newState = (problem.getStack()).remove();
                   if (newState != null) {     // checks to see if the move was valid
                    moveCount++;
                    problem.setCurrentState(newState);
                    canvas.setTheState(newState); 
                    canvas.render();
                    repaint();
       
                    if (problem.success() ) {   // checks to see if the game is over  
                      clicked = true;
                  }
                  } 
              }   
              }
          });
           
       timer = new Timer(DELAY, new ActionListener() {
            @Override  
            public void actionPerformed(ActionEvent event) {   
                if (!problem.getStack().isEmpty() )
                 newState = (problem.getStack()).remove();

                   if (newState != null) {     // checks to see if the move was valid
                    moveCount++;
                    problem.setCurrentState(newState);
                    canvas.setTheState(newState); 
                    canvas.render();
                    repaint();
       
                    if (problem.success() ) {                // checks to see if the game is over  
                     ((Timer)event.getSource()).stop();
                     clicked = true;
                  }
                   }
            }
        });
           allMoves.addActionListener(new ActionListener() {
              @Override
              public void actionPerformed(ActionEvent event) {
              if(!clicked) 
                timer.start();
              }
          });
//           regularA.setSelected(true);
//           regularA.addActionListener(new ActionListener() {
//              @Override
//              public void actionPerformed(ActionEvent event) {
//                      regular = true;
//                       enhancedA.setSelected(false); 
//              }    
//          });
//            enhancedA.addActionListener(new ActionListener() {
//              @Override
//              public void actionPerformed(ActionEvent event) {
//                          regular = false;
//                          regularA.setSelected(false); 
//              }     
//          }); 
    }
    
    // private methods and instance fields go here

    /**
     * Creates the move buttons and adds them to the movePanel. As well as,
     * setting an action listener for each button to perform the desired move.
     * If the move is valid, a new state is created and displayed. If the game 
     * is over, an option pane is created that states the number of moves need.
     * If an invalid move is selected, an option pane is displayed that states
     * an illegal move was performed.
     */
    private void makeOptions() {                     // creates the move buttons
        for (int i = 0; i < length; ++i) {
          final String name = moves.get(i).getMoveName();  
          button = new JButton(name);    
          button.addActionListener(new ActionListener() {
    
              @Override
               public void actionPerformed(ActionEvent e) {   
                   for (int i = 0; i < length; ++i) {                // finds the correct move object
                      if (name.equals(moves.get(i).getMoveName() ))
                         move = moves.get(i);      
              }            
                  newState = move.doMove(problem.getCurrentState());
 
                  if (newState != null) {     // checks to see if the move was valid
                    moveCount++;
                    problem.setCurrentState(newState);
                    canvas.setTheState(newState); 
                    canvas.render();
                    repaint();
       
                    if (problem.success() ) {                // checks to see if the game is over  
                      JOptionPane.showMessageDialog(null, "Congratulations! You"
                               + " solved the problem in " + moveCount + " moves.");
                  }
                  } else {
                     JOptionPane.showMessageDialog(null, "Illegal Move");
                  }
               }   
           });
              movesPanel.add(button);
        }    
    }
    
    /**
     * Adds a JButton that calls the reset method.
     */
    private void resetButton() {
         JButton resButton = new JButton("RESET");           
          resButton.addActionListener(new ActionListener() {  
              @Override
               public void actionPerformed(ActionEvent e) {   
                     Component[] components = movesPanel.getComponents();
       
        for (int i = 0; i < length; ++i) {
          Component component = components[i];
          component.setEnabled(true);
            }
                reset();
               }
           });
          bottomPanel.add(resButton);   
    }
    
    /**
     * Resets the current state of the game to resetState, as well as setting
     * the moveCount to 0 and stateText to the beginning state.
     */
      private void reset() {  
          
       if(problem.getChooser()) {
           ProblemChooser problemChooser = new ProblemChooser(problem.getInitialStates(),
                   problem.getFinalStates(),
                   problem.getMoveCounts(),
                   problem.getInitialCanvases(),
                   problem.getFinalCanvases());
           problem.setCurrentState(problemChooser.getStart());
           problem.setFinalState(problemChooser.getFinal());
           canvas.setTheState(problemChooser.getStart());
           canvas.repaint();
           finalCanvas.setTheState(problemChooser.getFinal());
           finalCanvas.repaint();
           
        
       } else {
          problem.setCurrentState(resetState);
          canvas.setTheState(resetState);
          canvas.repaint();
       }
          allMoves.setEnabled(false);
          nextMoves.setEnabled(false);
          solveButton.setEnabled(true);
          timer.stop();
          if (clicked ) {
          problem.getStack().clear();
            clicked = false;
          }
          solutionLength.setText("Solution Length: " ); 
          numD.setText("Num of PQ Ops: " );
          maxSize.setText("Max PQ size: " );
          moveCount = 0;
      }

      /**
       * Initializes all of the Java Components and Containers.
       */
      private void makeComponentsAndContainers() {
            stateText = new JTextArea();
            introText = new JTextArea();
            introPanel = new JPanel(); 
            mainPanel = new JPanel();  
            statePanel = new JPanel();
            finalStatePanel = new JPanel();
            movesPanel = new JPanel();
            buttonPanel = new JPanel();
            searchTypeBackPanel = new JPanel();
            bottomPanel = new JPanel();
            solutionButtonPanel = new JPanel();
//            regularA = new JRadioButton("Regular A*");
//            enhancedA = new JRadioButton("Enhanced A*");
            solveButton = new JButton("SOLVE");
            solutionPanel = new JPanel();
            solutionBackPanel = new JPanel();
            nextMoves = new JButton("SHOW NEXT MOVE");  
            allMoves = new JButton("SHOW ALL MOVES"); 
            solutionLength = new JLabel("Solution Length: ");
            numD = new JLabel("Num of PQ Ops: ");
            maxSize = new JLabel("Max PQ size: ");
      }
    
      private void setLayoutAndDimensions() {
             setLayout(new BoxLayout(this, BoxLayout.Y_AXIS) );
             movesPanel.setLayout(new GridLayout(length, 1, 0, 5) );
             buttonPanel.setLayout(new GridLayout(2,1,0,0) );
             searchTypeBackPanel.setLayout(new GridLayout(2, 1, 0, 10) );
             solutionPanel.setLayout(new GridLayout(3, 1));
             solutionButtonPanel.setLayout(new GridLayout(2, 1, 0, 7));
             solveButton.setPreferredSize(new Dimension(100, 50));
             solutionPanel.setPreferredSize(new Dimension(205, 80) );
      }
    
    /**
       The length of the of the moves list.
     */
    private final int length;
    
    /**
       The list of move objects.
     */
    private final List<Move> moves;
    
    /**
       The JTextArea containing the string representation of the current state.
     */
    private JTextArea stateText;

    /**
       The JPanel containing the available moves.
     */
    private JPanel movesPanel;
 
     /**
       The JPanel containing the stateText.
     */
    private JPanel statePanel ;
    
     /**
       The JPanel containing movesPanel and statePanel.
     */
    private JPanel mainPanel;  
    
    /**
       The problem passed to the GUI class constructor.
     */
    private final Problem problem;
    
    /**
       The beginning state of the problem.
     */
    private final State resetState;
    
    /**
       The current move to be performed on.
     */
    private Move move;
    
    /**
       The amount of turns the user has taken to solve the problem.
     */
    private int moveCount;
    
    /**
     * The canvas taken as parameter by constructor.
     */
    private final Canvas canvas;
    
    /**
     * The JPanel containing JRadioButton(s).
     */
    private JPanel buttonPanel;
    
    /**
     * The JRadioButton used to select the depth-first search.
     */
    private JRadioButton regularA;
    
    /**
     * The JRadioButton used to select the breadth-first search.
     */
    private JRadioButton enhancedA;
    
    /**
     * The JPanel containing the JLabels used to display statistics 
     * of the search.
     */
    private JPanel solutionPanel;
    
    /**
     * The JPanel that contains the solutionPanel and nextMoves 
     * and AllMoves buttons.
     */
    private JPanel solutionBackPanel;
    
    /**
     * The JPanel containing all components on the bottom of the frame.
     */
    private JPanel bottomPanel;
    
    /**
     * The JButton used to create the move buttons.
     */
    private JButton button;
    
    /**
     * The JButton that when clicked, solves the current problem
     */
    private JButton solveButton;
    
    /**
     * The JButton that when clicked, pops the next start from the stack and 
     * updates current state.
     */
    private JButton nextMoves;
    
    /**
     * The JButton that starts a timer that pops the stack, updates the current
     * state, and repaints it to the canvas.
     */
    private JButton allMoves;
    
    /**
     * The State created by doMove(State state).
     */
    private State newState;
    
    /**
     * The boolean used to indicate what search is being computed.
     */
    private boolean depthActive;
    
    /**
     * The boolean used to indicate what search is being computed.
     */
    private boolean breadthActive;
    
    /**
     * The current length of the solution.
     */
    private JLabel solutionLength;
    
    /**
     * The JLabel used to display the number of DEQUE operations.
     */
    private JLabel numD;
    
    /**
     * The JLabel used to display the max DEQUE size.
     */
    private JLabel maxSize;
    
    /**
     * The boolean that determines whether or not allMoves or nextMoves 
     * has been clicked.
     */
    private boolean clicked;
    
    /**
     * The JPanel that contains the introText.
     */
    private JPanel introPanel;
    
    /**
     * The JTextArea that contains the introduction string of the current 
     * problem.
     */
    private JTextArea introText;
    
    /**
     * The JPanel that acts as a glue to the solveButton and searchTypePanel.
     */
    private JPanel searchTypeBackPanel;
    
    /**
     * The JPanel that contains the nextMoves and allMoves JButtons.
     */
    private JPanel solutionButtonPanel;
   
    /**
     * Timer used to pop the stack when allMoves is pressed.
     */
    private Timer timer;
    
    private JPanel finalStatePanel;
    private Canvas finalCanvas;
    private boolean regular;
  }

    
