/** @file
 *
 * @author Mike Dawson
 *
 * @author Steven J Holtz
 *
 * @note From "C++ Projects: Programming with Text-Based Games" */

#include <iostream>

using namespace std;

#include "board.h"

const int Board::WINNING_COMBOS[NUM_COMBOS][NUM_IN_COMBO] =
{ {0, 1, 2},
  {3, 4, 5},
  {6, 7, 8},
  {0, 3, 6},
  {1, 4, 7},
  {2, 5, 8},
  {0, 4, 8},
  {2, 4, 6} };

Board::Board() {

   squares = new char[NUM_SQUARES];

   reset();
}

Board::~Board() {

   delete [] squares;
}

bool Board::isFull() const {

   bool full = true;
   int i = 0;

   while (full && i < NUM_SQUARES) {
      if (squares[i] == EMPTY) {
         full = false;
         break;
      }
      ++i;
   }

   return full;
}

bool Board::isLegalMove(int move) const {

   return move >= 0 &&
      move < NUM_SQUARES &&
      squares[move] == EMPTY;
}

bool Board::isWinner(char piece) const {

   bool winner = false;
   int winningCombosRow = 0;

   while (!winner &&
          winningCombosRow < NUM_COMBOS) {
      int piecesInCombo = 0;

      for (int winningCombosColumn = 0;
           winningCombosColumn < NUM_IN_COMBO;
           ++winningCombosColumn) {
         if (squares[WINNING_COMBOS[winningCombosRow][winningCombosColumn]] == piece) {
            ++piecesInCombo;
         }
      }

      if (piecesInCombo == NUM_IN_COMBO) {
         winner = true;
      }

      ++winningCombosRow;
   }

   return winner;
}

void Board::display() const {

   cout << "\n\t"
        << squares[0]
        << " | "
        << squares[1]
        << " | "
        << squares[2]
        << "\n\t--+---+--\n\t"
        << squares[3]
        << " | "
        << squares[4]
        << " | "
        << squares[5]
        << "\n\t--+---+--\n\t"
        << squares[6]
        << " | "
        << squares[7]
        << " | "
        << squares[8]
        << endl << endl;
}

void Board::reset() {

   for (int i = 0; i < NUM_SQUARES; ++i) {
      squares[i] = EMPTY;
   }
}

void Board::receiveMove(char piece,
                        int move) {

   squares[move] = piece;
}
