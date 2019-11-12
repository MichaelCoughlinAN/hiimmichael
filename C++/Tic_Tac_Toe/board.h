/** @file
 *
 * @author Mike Dawson
 *
 * @author Steven J Holtz
 *
 * @note From "C++ Projects: Programming with Text-Based Games" */

#ifndef BOARD_H
#define BOARD_H 1

/** @class Board */
class Board {
private:

   /** The number of winning combinations. */
   static const int NUM_COMBOS = 8;

   /** The number of positions in a winning combination. */
   static const int NUM_IN_COMBO = 3;

   /** The winning combinations. */
   static const int WINNING_COMBOS[NUM_COMBOS][NUM_IN_COMBO];

   /** The squares on this board. */
   char* squares;

public:

   /** Default ctor */
   Board();

   /** Dtor */
   ~Board();

   /** Is this board full?
    *
    * @pre None.
    *
    * @post None.
    *
    * @return True if this board is full, else false. */
   bool isFull() const;

   /** Is the player associated with PIECE the winner?
    *
    * @pre None.
    *
    * @post None.
    *
    * @param piece The piece associated with one of the players.
    *
    * @return True if the player associated with PIECE is the winner,
    *         else false. */
   bool isWinner(char piece) const;

   /** Is MOVE a legal move?
    *
    * @pre None.
    *
    * @post None.
    *
    * @param move Is a move entered by the user.
    *
    * @return True if MOVE is on the board and that cell on the board
    *         has not already been taken, else false. */
   bool isLegalMove(int move) const;

   /** Display this board.
    *
    * @pre None.
    *
    * @post None. */
   void display() const;

   /** Reset this board to an empty state.
    *
    * @pre None.
    *
    * @post This board's squares have been returned to the EMPTY
    *       state. */
   void reset();

   /** Try to apply MOVE to the board on behalf of the player
    *  associated with PIECE.
    *
    * @pre MOVE must be a legal position on this board that has not
    *      already been taken.
    *
    * @post PIECE has been placed on this board at position MOVE.
    *
    * @param piece The character associated with the player that made
    *        this MOVE.
    *
    * @param move The position on this board to place the PIECE. */
   void receiveMove(char piece,
                    int move);

   /** The number of squares on this board. */
   static const int NUM_SQUARES = 9;

   /** The character associated with an empty square. */
   static const char EMPTY = ' ';
};

#endif
