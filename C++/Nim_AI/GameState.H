/* 
 * File:   GameState.H
 * Author: tcolburn
 *
 * Created on December 10, 2013, 3:53 PM
 */

#ifndef GAMESTATE_H
#define	GAMESTATE_H

#include "nim.H"
#include <string>
using namespace std;

class GameStateInfo {
public:
  GameStateInfo(int pile1, int pile2, int pile3);
  int getPile1();
  int getPile2();
  int getPile3();
  int totalSize();
  string toString();
  GameState nextState(Move m);

private:
  int pile1;
  int pile2;
  int pile3;
};

#endif	/* GAMESTATE_H */

