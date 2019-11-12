/* 
 * File: ScoreKeeper.H
 * Author: tcolburn
 * Student: Michael Coughlin
 * Created on December 10, 2013, 4:37 PM
 */

#ifndef SCOREKEEPER_H
#define	SCOREKEEPER_H

#include "nim.H"

class ScoreKeeperInfo {
public:
    void start();
private:
    void welcome();
    void flipCoin();
    void playRepeatedly();
    void makeRandomStartState();
    int playerScore(int score1);
    int computerScore(int score2);
    Player player1;
    Player player2;
    Player firstToPlay;
    Player setToPlay;
    Player temp;
    string yesOrNo;
    string name;
    string headsOrTails;
    int score1;
    int score2;
    int random;
    int choice; 
    int A;
    int B;
    int C;
    Game game;
    GameState initialState; 
    bool finished;
    bool end;
    
    
};

#endif	/* SCOREKEEPER_H */