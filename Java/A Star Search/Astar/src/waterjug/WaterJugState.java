package waterjug;

import framework.State;
import graph.SimpleVertex;

/**
 * This class represents states of the Water Jug problem.
 * It creates new water jug states, tests states for equality,
 * and produces string representations of them.
 * Note that this class implements the <b>State</b> interface
 * and therefore imports <b>framework.State</b>.
 * @author Michael Coughlin
 * CS2511 Fall 2014
 * Lab Section 7
 */
public class WaterJugState extends SimpleVertex implements State {

    public WaterJugState(int jugX, int jugY){
               this.jugX = jugX;
               this.jugY = jugY;
    }

    /**
       Tests for equality between this state and the argument state.
       Two states are equal if the X jugs have the same amount of water
       and the Y jugs have the same amount of water.
       @param other the state to test against this state
       @return whether the states are equal
    */
    public boolean equals(Object other) {
       WaterJugState state = (WaterJugState) other;
	 return this.getJugX() == state.getJugX()  &&
                this.getJugY() == state.getJugY(); 
               
    }

    /**
       Creates a primitive, non-GUI representation of this WaterJugState object.
       @return the string representation of this water jug state
     */
    public String toString() {
	String result = "";
      int tempJugY = jugY;
      int tempJugX = jugX;
       //Checks for top of jugY.
      if(tempJugY == 4){
             result += "       |***|\n";
             --tempJugY;          
      }
        else result += "       |   |\n";
       //Checks whether jugX or jugY contains 3 gallons. 
         if(tempJugX == 3 && tempJugY == 3){
             result += "|***|  |***|\n";
             --tempJugY; 
             --tempJugX;
      }else if(tempJugX != 3 && tempJugY == 3){
          result += "|   |  |***|\n";
          --tempJugY;
      }
      else if(tempJugX == 3 && tempJugY != 3){
          result += "|***|  |   |\n";
          --tempJugX;
      }
     else result += "|   |  |   |\n";
         //Checks whether jugX or jugY contains 2 gallons. 
         if(tempJugX == 2 && tempJugY == 2){
             result += "|***|  |***|\n";
             --tempJugY; 
             --tempJugX;
      }else if(tempJugX != 2 && tempJugY == 2){
          result += "|   |  |***|\n";
          --tempJugY;
      }
      else if(tempJugX == 2 && tempJugY != 2){
          result += "|***|  |   |\n";
          --tempJugX;
      }
     else result += "|   |  |   |\n";
         //Checks whether jugX or jugY contains 1 gallons. 
         if(tempJugX == 1 && tempJugY == 1){
             result += "|***|  |***|\n";
             --tempJugY; 
             --tempJugX;
      }else if(tempJugX != 1 && tempJugY == 1){
          result += "|   |  |***|\n";
          --tempJugY;
      }
      else if(tempJugX == 1 && tempJugY != 1){
          result += "|***|  |   |\n";
          --tempJugX;
      }
     else result += "|   |  |   |\n";
         
                     
            result += "+---+  +---+\n" +
                      "  X      Y  \n";;

               return result; //the string representation of the state.
    }

    public int getJugX() {
        return jugX;
    }

    public int getJugY() {
        return jugY;
    }
    
    
    // Private methods and instance fields should go here
private int jugX;
private int jugY;

    @Override
    public int getHeuristic(State goal) {
       return 0;
    }
}
