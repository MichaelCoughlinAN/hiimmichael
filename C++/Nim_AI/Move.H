/* 
 * File:   Move.H
 * Author: tcolburn
 *
 * Created on December 10, 2013, 3:45 PM
 */

#ifndef MOVE_H
#define	MOVE_H

class MoveInfo {
public:
  MoveInfo(int coins, int pile);
  int getCoins();
  int getPile();
private:
  int coins;
  int pile;
};

#endif	/* MOVE_H */

