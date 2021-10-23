/* 
 * File:   Player.H
 * Author: tcolburn
 *
 * Created on December 10, 2013, 4:07 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "nim.H"
#include <string>
using namespace std;

class PlayerInfo {
public:
    PlayerInfo(string name);
    string getName();
    virtual Move getMove(GameState state);
private:
    string name;
};

#endif	/* PLAYER_H */

