package framework;

import java.util.*;

/**
 * This class has methods for interacting with a user who is trying to 
 * solve a problem through a console interface.
 * Note that this class is concrete; it is neither an interface
 * nor abstract.  It also does not depend on any particular problem domain.
 */
public class Console {

    /**
       Creates a new problem console user interface.
       @param problem the problem
     */
    public Console(Problem problem) {

        this.problem = problem;
        moves = problem.getMoves();
        options = makeOptions();
        moveCount = 0;
        scanner = new Scanner(System.in);

    }
    
    /**
     * Displays the introduction and begins to process user moves.
     */
    public void start() {
        
        display(problem.getIntroduction());
        display("\nHere is your initial state:\n");
        processMoves();
        
    }

    /**
     * Getter for the number of moves the user has tried so far.
     * @return the move count
     */
    private int getMoveCount() {
        return moveCount;
    }

    /**
     * Setter for the number of moves the user has tried so far
     * @param moveCount the new move count
     */
    private void setMoveCount(int moveCount) {
        this.moveCount = moveCount;
    }

    /**
     * Getter for the legal moves as a string of numbered options.
     * @return the string of numbered options
     */
    private String getOptions() {
        return options;
    }

    /**
     * Getter for the problem object associated with this console.
     * @return this console's problem object
     */
    private Problem getProblem() {
        return problem;
    }

    /**
       Makes a list of move options from the list of legal moves.
       @return the options string
     */
    private String makeOptions() {

        StringBuilder buffer = new StringBuilder();

        int n = 1;
        buffer.append("Options:\n");
        for (Move move : moves) {
            buffer.append("  ").append(n++).append(". ").append(move.getMoveName()).append("\n");
        }
        buffer.append("\nChoose 1-").append(moves.size()).append(" (zero to quit): ");
        return buffer.toString();
    }

    /**
     * Gets and processes moves from the user.  First displays the current
     * state and checks for success.  If success, congratulations are given
     * along with the number of moves used and the program exits.
     * Otherwise the available options are displayed and prompted for.
     * Bad input causes a message and re-prompt.  Input of zero causes a
     * message of number of moves attempted and the program exits.
     * Valid input causes the move to be attempted.  If the result is
     * <b>null</b>, the move could not be performed so a message is given
     * and the user is re-prompted.  Otherwise the result is installed as
     * the new problem current state and <b>getMove</b> is repeated.
     */
    private void processMoves() {

        display(problem.getCurrentState().toString());
        if ( problem.success() ) {
            display("Congratulations.  You solved the problem using " +
                    moveCount + " moves.\n");
            System.exit(0);
        }
        display(options);
        Move move = getOption();
        if ( move == null ) {
            display("User quit.  You attempted " + moveCount + " moves.\n");
            System.exit(0);
        }
        State newState = move.doMove(problem.getCurrentState());
        if ( newState == null ) {
            display("That move is not possible.  Try again.\n");
        }
        else {
            problem.setCurrentState(newState);
            moveCount++;
        }
        processMoves();
    }


    /**
       Prompts for a move option, re-prompting if necessary.
       @return the move associated with the (valid) option
     */
    private Move getOption() {

        if ( scanner.hasNext() )
            if ( scanner.hasNextInt() ) {
                int n = scanner.nextInt();
                if ( 1 <= n && n <= moves.size() )
                    return moves.get(n-1);
                if ( n == 0 )
                    return null;
                display("Option out of range.\n");
                display(problem.getCurrentState().toString());
                display(options);
                return getOption();
            }
            else {
                String dum = scanner.next();
                display("Option not an integer.\n");
                display(problem.getCurrentState().toString());
                display(options);
                return getOption();
            }
        else
            return null;
    }

    /**
       Displays a string to the console.
       @param string the string to be displayed
     */
    private void display(String string) {

        System.out.print("\n" + string);

    }
    
    /**
    * The puzzle problem object
    */
    private Problem problem;
    
    /**
       The legal moves for the problem.
     */
    private List<Move> moves;

    /**
       A prompt string of move options
     */
    private String options;

    /**
       Number of moves user has taken in solving the problem.
     */
    private int moveCount;
    
    /**
       A scanner for reading input
     */
    private Scanner scanner;

}
