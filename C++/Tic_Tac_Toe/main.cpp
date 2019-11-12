/** @file
 *
 * @author Mike Dawson
 *
 * @author Steven J Holtz
 *
 * @note From "C++ Projects: Programming with Text-Based Games" */

#include <iostream>
#include <cstdlib>

using namespace std;

#include "game.h"

int main() {

   Game* ticTacToe = new Game;

   ticTacToe->displayInstructions();

   char playAgain;

   do {
      ticTacToe->play();
      cout << "\nPlay again (y/n)? ";
      cin >> playAgain;
   } while (playAgain != 'n');

   return EXIT_SUCCESS;
}
