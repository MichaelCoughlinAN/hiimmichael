package waterjug;

import framework.Console;

/**
 * This class provides a terminal console interface to the Water
 * Jug problem.
 * Note that its function is entirely provided by the <b>Console</b>
 * class which is provided by the framework.
 * You do not have to add anything to this class.
 * @author tcolburn
 */
public class WaterJugConsole {
       
    /**
     * This method launches the console.
     * @param args ignored
     */
    public static void main(String[] args) {
        Console console = new Console(new WaterJugProblem());
        console.start();
    } 
}
