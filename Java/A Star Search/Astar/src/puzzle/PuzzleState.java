package puzzle;

import framework.State;
import graph.SimpleVertex;

/**
 * This class represents states of the 8-Puzzle problem.
 * It creates new puzzle states, tests states for equality,
 * and produces string representations of them.
 * Note that this class implements the <b>State</b> interface
 * and therefore imports <b>framework.State</b>.
 * Except for the import and the class header, this class can be
 * the same as in the previous assignment.
 * @author Michael Coughlin
 * CS2511 Fall 2014
 * Lab Section 1
 */
public class PuzzleState extends SimpleVertex implements State {
    
    /**
     * Creates a new puzzle state and stores the positions
     * of the tiles
     * @param firstPosition position of first tile
     * @param secondPosition position of second tile
     * @param thirdPosition position of third tile
     * @param forthPosition position of forth tile
     * @param fifthPosition position of fifth tile
     * @param sixthPosition position of sixth tile
     * @param seventhPosition position of seventh tile
     * @param eigthPosition position of eigth tile
     * @param ninthPosition  position of ninth tile
     */
    public PuzzleState(int firstPosition, int secondPosition, int thirdPosition,
                       int forthPosition, int fifthPosition, int sixthPosition,
                       int seventhPosition, int eigthPosition, int ninthPosition) {
        
        this.firstPosition = firstPosition;
        this.secondPosition = secondPosition;
        this.thirdPosition = thirdPosition;
        this.forthPosition = forthPosition;
        this.fifthPosition = fifthPosition;
        this.sixthPosition = sixthPosition;
        this.seventhPosition = seventhPosition;
        this.eigthPosition = eigthPosition;
        this.ninthPosition = ninthPosition;
        
    }
    
    @Override
     public boolean equals(Object other) {
       PuzzleState state = (PuzzleState) other;
	 return this.getFirstPosition() == state.getFirstPosition() &&
                this.getSecondPosition() == state.getSecondPosition() &&
                this.getThirdPosition() == state.getThirdPosition() &&
                this.getForthPosition() == state.getForthPosition() &&
                this.getFifthPosition() == state.getFifthPosition() &&
                this.getSixthPosition() == state.getSixthPosition() &&
                this.getSeventhPosition() == state.getSeventhPosition() &&
                this.getEigthPosition() == state.getEigthPosition() &&
                this.getNinthPosition() == state.getNinthPosition();         
    }
    
    private final int firstPosition;
    private final int secondPosition;
    private final int thirdPosition;
    private final int forthPosition;
    private final int fifthPosition;
    private final int sixthPosition;                                       
    private final int seventhPosition;
    private final int eigthPosition;
    private final int ninthPosition;

    public int getFirstPosition() {
        return firstPosition;
    }

    public int getSecondPosition() {
        return secondPosition;
    }

    public int getThirdPosition() {
        return thirdPosition;
    }

    public int getForthPosition() {
        return forthPosition;
    }

    public int getFifthPosition() {
        return fifthPosition;
    }

    public int getSixthPosition() {
        return sixthPosition;
    }

    public int getSeventhPosition() {
        return seventhPosition;
    }

    public int getEigthPosition() {
        return eigthPosition;
    }

    public int getNinthPosition() {
        return ninthPosition;
    }

    @Override
    public int getHeuristic(State goal) {
    // return tilesOutOfPlace(goal); 
    return sumManhattan();
    }
    
      private int sumManhattan() {
          int value = 0;
          if (getFirstPosition() == 1) {
          } else if (getSecondPosition() == 1)
              value++;
          else if (getThirdPosition() == 1)
              value = value + 2;
          else if (getForthPosition() == 1)
              value++;
          else if (getFifthPosition() == 1)
              value = value + 2;
          else if (getSixthPosition() == 1)
              value = value + 3;
          else if (getSeventhPosition() == 1)
              value = value + 2; // might be 4
          else if (getEigthPosition() == 1)
              value = value + 3;
          else if (getNinthPosition() == 1)
              value = value + 4;
          
            if (getSecondPosition() == 2) {
               
          } else if (getFirstPosition() == 2)
              value++;
          else if (getThirdPosition() == 2)
              value++;
          else if (getForthPosition() == 2)
              value = value + 2;
          else if (getFifthPosition() == 2)
              value++;
          else if (getSixthPosition() == 2)
              value = value + 2;
          else if (getSeventhPosition() == 2)
              value = value + 3; 
          else if (getEigthPosition() == 2)
              value = value + 2;
          else if (getNinthPosition() == 2)
              value = value + 3;
            
              if (getThirdPosition() == 3) {
          } else if (getSecondPosition() == 3)
              value++;
          else if (getFirstPosition() == 3)
              value = value + 2;
          else if (getForthPosition() == 3)
              value = value + 3;
          else if (getFifthPosition() == 3)
              value = value + 2;
          else if (getSixthPosition() == 3)
              value = value + 1;
          else if (getSeventhPosition() == 3)
              value = value + 4; 
          else if (getEigthPosition() == 3)
              value = value + 3;
          else if (getNinthPosition() == 3)
              value = value + 2;
              
                if (getForthPosition() == 8) {
          } else if (getFirstPosition() == 8)
              value++;
          else if (getSecondPosition() == 8)
              value = value + 2;
          else if (getThirdPosition() == 8)
              value = value + 3;
          else if (getFifthPosition() == 8)
              value++;
          else if (getSixthPosition() == 8)
              value = value + 2;
          else if (getSeventhPosition() == 8)
              value++; 
          else if (getEigthPosition() == 8)
              value = value + 2;
          else if (getNinthPosition() == 8)
              value = value + 3;
                
             
                
                  if (getSixthPosition() == 4) {
          } else if (getFirstPosition() == 4)
              value = value + 3;
          else if (getSecondPosition() == 4)
              value = value + 2;
          else if (getThirdPosition() == 4)
              value++;
          else if (getForthPosition() == 4)
              value = value + 2;
          else if (getFifthPosition() == 4)
              value++;
          else if (getSeventhPosition() == 4)
              value = value + 3; 
          else if (getEigthPosition() == 4)
              value = value + 2;
          else if (getNinthPosition() == 4)
              value++;
                  
                    if (getSeventhPosition() == 7) {
          } else if (getFirstPosition() == 7)
              value = value + 2;
          else if (getSecondPosition() == 7)
              value = value + 3;
          else if (getThirdPosition() == 7)
              value = value + 4;
          else if (getForthPosition() == 7)
              value++;
          else if (getFifthPosition() == 7)
              value = value + 2;
          else if (getSixthPosition() == 7)
              value = value + 3;
          else if (getEigthPosition() == 7)
              value++;
          else if (getNinthPosition() == 7)
              value = value + 2;
                    
                      if (getEigthPosition() == 6) {
          } else if (getFirstPosition() == 6)
              value = value + 3;
          else if (getSecondPosition() == 6)
              value = value + 2;
          else if (getThirdPosition() == 6)
              value = value + 3;
          else if (getForthPosition() == 6)
              value = value + 2;
          else if (getFifthPosition() == 6)
              value++;
          else if (getSixthPosition() == 6)
              value = value + 2; // might be 4
          else if (getSeventhPosition() == 6)
              value++;
          else if (getNinthPosition() == 6)
              value++;
                      
                        if (getNinthPosition() == 5) {
          } else if (getFirstPosition() == 5)
              value = value + 4;
          else if (getSecondPosition() == 5)
              value = value + 3;
          else if (getThirdPosition() == 5)
              value = value + 2;
          else if (getForthPosition() == 5)
              value = value + 3;
          else if (getFifthPosition() == 5)
              value = value + 2;
          else if (getSixthPosition() == 5)
              value++;// might be 4
          else if (getSeventhPosition() == 5)
              value = value + 2;
          else if (getEigthPosition() == 5)
              value++;
                        
           
          
       return value;
    }
      
 private int tilesOutOfPlace(State goal) {
       PuzzleState puzzleState = (PuzzleState)goal;
      int value = 0;
     
      if(getFirstPosition() != 1 && getFirstPosition() != 0) {
          value++;
      }
      if(getSecondPosition() != 2 && getSecondPosition() != 0) {
          value++;
      }
      if(getThirdPosition() != 3 && getThirdPosition() != 0) {
          value++;
      }
      if(getForthPosition() != 8 && getForthPosition() != 0) {
          value++;
      }
      if(getFifthPosition() != 0) {
          value++;
      }
      if(getSixthPosition() != 4 && getSixthPosition() != 0) {
          value++;
      }
      if(getSeventhPosition() != 7 && getSeventhPosition() != 0) {
          value++;
      }
      if(getEigthPosition() != 6 && getEigthPosition() != 0) {
          value++;
      }
      if(getNinthPosition() != 5 && getNinthPosition() != 0) {
          value++;
      }
       
      return value;
    }

  

}