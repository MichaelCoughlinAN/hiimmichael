/** @file
 *
 * @author Mike Dawson
 *
 * @author Steven J Holtz
 *
 * @note From "C++ Projects: Programming with Text-Based Games" */

#ifndef GAME_H
#define GAME_H 1

#include "board.h"
#include "player.h"

/** @class Game */
class Game {
private:

   /** The number of players in this game. */
   static const int NUM_PLAYERS = 2;

   /** The id associated with the first player. */
   static const int FIRST = 0;

   /** The id associated with the second player. */
   static const int SECOND = 1;

   /** The game board. */
   Board* board;

   /** The players. */
   Player** players;

   /** The id of the current player. */
   int currentPlayer;
public:

   /** Default ctor */
   Game();

   /** Dtor */
   ~Game();

   /** Is this game still being played?
    *
    * @pre None.
    *
    * @post None.
    *
    * @return True if the board is not full and no player has won,
    *         else false. */
   bool isPlaying() const;

   /** Is this game a tie?
    *
    * @pre None.
    *
    * @post None.
    *
    * @return True if the board is full and no player has won, else
    *         false. */
   bool isTie() const;

   /** Display instructions for this game.
    *
    * @pre None.
    *
    * @post None. */
   void displayInstructions() const;

   /** Switch to the next player.
    *
    * @pre None.
    *
    * @post currentPlayer is switched to the next player. */
   void nextPlayer();

   /** Display the winner of this game.
    *
    * @pre One of the players has won this game.
    *
    * @post None. */
   void announceWinner() const;

   /** Play this game!
    *
    * @pre The board is empty and the players have their pieces set.
    *
    * @post This game is over and the winner has been announced. */
   void play();
};

#endif
