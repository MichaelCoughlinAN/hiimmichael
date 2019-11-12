/** @file
 *
 * @author Mike Dawson
 *
 * @author Steven J Holtz
 *
 * @note From "C++ Projects: Programming with Text-Based Games" */

#ifndef PLAYER_H
#define PLAYER_H 1

/** Forward declaration of the Board class. */
class Board;

/** @class Player */
class Player {
private:

   /** Number of players in the game (distinct pieces). */
   static const int NUM_PIECES = 2;

   /** The pieces associated with each player. */
   static const char PIECES[NUM_PIECES];

   /** The number of the current player being constructed. */
   static int current;

   /** The piece associated with this player. */
   char piece;
public:

   /** Default ctor */
   Player();

   /** Dtor */
   ~Player();

   /** Get this player's piece.
    *
    * @pre This player's piece has been set.
    *
    * @post None.
    *
    * @return This player's piece. */
   char getPiece() const;

   /** Get a move from the user associated with this player and place
    *  this move on the BOARD.
    *
    * @pre The BOARD exists.
    *
    * @post This player's move has been placed on the BOARD.
    *
    * @param board Is the game board. */
   void makeMove(Board* board) const;
};

#endif
