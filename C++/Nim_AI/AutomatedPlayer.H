/* 
 * File:   AutomatedPlayer.H
 * Author: tcolburn
 *
 * Created on December 10, 2013, 4:27 PM
 */

#ifndef AUTOMATEDPLAYER_H
#define	AUTOMATEDPLAYER_H

#include "nim.H"
#include <string>
using namespace std;

class AutomatedPlayerInfo: public PlayerInfo {
public:
    AutomatedPlayerInfo(string name, Strategy strategy);
    Move getMove(GameState state);
private:
    Strategy strategy;
};


#endif	/* AUTOMATEDPLAYER_H */

