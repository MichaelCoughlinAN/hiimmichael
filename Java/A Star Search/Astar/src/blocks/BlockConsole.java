package blocks;

import framework.Console;

/**
 * This class provides a terminal console interface to the Blocks World
 * problem.
 * @author tcolburn
 */
public class BlockConsole {
    
    /**
     * This method launches the console.
     * @param args ignored
     */
    public static void main(String[] args) {
        Console console = new Console(new BlockProblem());
        console.start();
    }
    
}
