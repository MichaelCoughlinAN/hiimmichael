/* 
 * File:   Game.H
 * Author: tcolburn
 *
 * Created on December 10, 2013, 4:32 PM
 */

#ifndef GAME_H
#define	GAME_H

#include "nim.H"

class GameInfo {
public:
    GameInfo(Player player1, Player player2,
             GameState initialState);
    Player play();

private:
    Player opponent(Player p);
    bool gameOver();

    Player player1;
    Player player2;
    Player nextToPlay;
    GameState currentState;
};

#endif	/* GAME_H */

