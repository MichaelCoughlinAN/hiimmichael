/** @file
 *
 * @author Mike Dawson
 *
 * @author Steven J Holtz
 *
 * @note From "C++ Projects: Programming with Text-Based Games" */

#include <iostream>

using namespace std;

#include "game.h"

Game::Game()
   : currentPlayer(FIRST) {

   // Allocate a Board from the heap.
   board = new Board;

   // Allocate an array of pointers to Players.
   players = new Player*[NUM_PLAYERS];

   // Allocate each element in the players array to a new Player.
   players[FIRST] = new Player;
   players[SECOND] = new Player;
}

Game::~Game() {

   delete board;
   delete players[FIRST];
   delete players[SECOND];
   delete [] players;
}

bool Game::isPlaying() const {

   return !board->isFull() &&
      !board->isWinner(players[FIRST]->getPiece() ) &&
      !board->isWinner(players[SECOND]->getPiece() );
}

bool Game::isTie() const {

   return board->isFull() &&
      !board->isWinner(players[FIRST]->getPiece() ) &&
      !board->isWinner(players[SECOND]->getPiece() );
}

void Game::displayInstructions() const {

   cout << "\n\tWelcome to Tic-Tac-Toe!!!\n\n"
        << "Make your move by entering 0-8.  The number\n"
        << "corresponds to a board position:\n\n"
        << "\t0 | 1 | 2\n"
        << "\t--+---+--\n"
        << "\t3 | 4 | 5\n"
        << "\t--+---+--\n"
        << "\t6 | 7 | 8\n\n"
        << "Prepare for battle!!!\n"
        << endl;
}

void Game::nextPlayer() {

   // currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;
   ++currentPlayer %= NUM_PLAYERS;
}

void Game::announceWinner() const {

   cout << "The battle has come to an end."
        << endl;

   if (isTie() ) {
      cout << "Sadly, there is no victor." << endl;
   }
   else {
      cout << "The winner is Player ";
      if (board->isWinner(players[FIRST]->getPiece()) ) {
         cout << players[FIRST]->getPiece();
      }
      else {
         cout << players[SECOND]->getPiece();
      }
      cout << "!"
           << endl;
   }
}

void Game::play() {

   currentPlayer = FIRST;

   board->reset();

   while (isPlaying() ) {
      board->display();
      players[currentPlayer]->makeMove(board);
      nextPlayer();
   }

   board->display();

   announceWinner();
}
