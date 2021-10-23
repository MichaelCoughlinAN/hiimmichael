package bridge;

import java.util.Scanner;
import java.io.IOException;

/**
 * This class provides a terminal console interface to the Bridge
 * Crossing problem.
 * The user attempts to solve the problem, with invalid moves rejected,
 * and the user can quit at any time.
 * If a move is valid, the new state is displayed.
 * If the solution is found, a message is given showing the number of moves
 * attempted, and processing halts.
 * @author your name here
 */
public class BridgeConsole {

    /**
       Creates a bridge problem console user interface.  An introduction
       is displayed, the move count is initialized, the initial state is
       displayed, the first move is solicited, and problem solution proceeds.
       @param problem the problem
     */
    public BridgeConsole(BridgeProblem problem) {
      //Creates an initial BridgeState object to start the problem.
      BridgeState state = new BridgeState(Position.WEST, Position.WEST, 
                                                   Position.WEST, Position.WEST, 
                                                   Position.WEST, 0);
        
      //A Second BridgeState used to store state if state != null.
      BridgeState state2 = null;
      
      //Counts the number of moves the user has made.
      int moveCount = 0;
     
      //A boolean used to stop the options menu from displaying when erroneous 
      //input is encountered.
      boolean fin = true;
      
      Scanner in = new Scanner(System.in);
      String input = "";
      
      System.out.print(problem.getIntroduction());
      System.out.print( "Here is your initial state:\n\n" +
                        " P1 |   |\n" +
                        " P2 |   |\n" +
                        "  f |===|\n" +
                        " P5 |   |\n" +
                        "P10 |   |\n" +
                     "Time elapsed so far: 0 minutes.\n");
    //loops while the user hasn't entered "0"
     while(!input.equals("0")){
     //Displays the options.
         if(fin) {
     System.out.println("\nOptions:");
     for(int i = 0; i < problem.getMoves().size(); ++i) {
        System.out.print(i + 1 + ". " + problem.getMoves().get(i).getMoveName() + "\n");            
     }
     System.out.print("\nChoose 1-10 (zero to quit): ");
     }
      //Asks the user for their choice of option.   
      input = in.nextLine();
     
      //Check's if input is a valid integer. Catches NumberFormatException.
    try{ 
    if(Integer.parseInt(input) >= 1 && Integer.parseInt(input) <= 10)
       fin = true; 
    else {
        fin = false;
        System.out.println("Option out of range. Try again.");
    }
    }catch(NumberFormatException e){
      System.out.println("Option not an integer. Try again.");
      fin = false;
   }  
    
    //if state is not null, it sets state2 to state. 
    if(state != null) {
        state2 = state;
    }
 //Checks the user's input. Catches NullPointerException if invalid.
 try {
  if (input.equals("0")) {
      System.out.println("User quit. You attempted " + Integer.toString(moveCount) + " moves.");
      System.exit(0); 
  } else if(input.equals("1")){
      // tries to do move on a null state.
         state = new BridgeMove("P1 crosses alone").doMove(state2); 
         System.out.print(state.toString());
         moveCount++;
     }
     else if(input.equals("2")){
         state = new BridgeMove("P2 crosses alone").doMove(state2);
         System.out.print(state.toString());
         moveCount++;
     }
     else if(input.equals("3")){
         state = new BridgeMove("P5 crosses alone").doMove(state2);
         System.out.print(state.toString());
         moveCount++;
     }
     else if(input.equals("4")){
         state = new BridgeMove("P10 crosses alone").doMove(state2);
         System.out.print(state.toString());
         moveCount++;
     }
     else if(input.equals("5")){
         state = new BridgeMove("P1 crosses with P2").doMove(state2);
         System.out.print(state.toString());
         moveCount++;
     }
    else if(input.equals("6")){
         state = new BridgeMove("P1 crosses with P5").doMove(state2);
         System.out.print(state.toString());
         moveCount++;
     }
    else if(input.equals("7")){
         state = new BridgeMove("P1 crosses with P10").doMove(state2);
         System.out.print(state.toString());
         moveCount++;
     }
    else if(input.equals("8")){
         state = new BridgeMove("P2 crosses with P5").doMove(state2);
         System.out.print(state.toString());
         moveCount++;
     }
    else if(input.equals("9")){
         state = new BridgeMove("P2 crosses with P10").doMove(state2);
         System.out.print(state.toString());
         moveCount++;
     }
    else if(input.equals("10")){
         state = new BridgeMove("P5 crosses with P10").doMove(state2);
         System.out.print(state.toString());
         moveCount++;
     }
   
    problem.setCurrentState(state); // sets state, needed for success();
 
   }catch(NullPointerException ex) {  
     fin = false;
    System.out.println("Invalid move. Try again.");  
}
    //Checks if problem has been solved. Catches NullPointerException.
     try{
      if(problem.success()) {
         System.out.println("\nCongratulations. You solved the problem using " 
                            + Integer.toString(moveCount) + " moves.");
         System.exit(0);
     }
    }catch(NullPointerException e){
        fin = false;
    }
    } 
    }

    /**
     * This method launches the console
     * @param args ignored
     */
    public static void main(String[] args) {
        new BridgeConsole(new BridgeProblem());
    }

}
