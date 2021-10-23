/* 
 * File:   IntermediateStrategy.H
 * Author: tcolburn
 *
 * Created on December 10, 2013, 4:23 PM
 */

#ifndef INTERMEDIATESTRATEGY_H
#define	INTERMEDIATESTRATEGY_H

#include "nim.H"

class IntermediateStrategyInfo: public StrategyInfo {
public:
    Move getMove(GameState state);
private:
    Move removePile(int pile, GameState state);
    Move evenPiles(GameState state);
    bool allNonEmpty(GameState state);
    bool oneNonEmpty(GameState state);
    bool allDifferent(GameState state);
    int theDifferentPile(GameState state);
};

#endif	/* INTERMEDIATESTRATEGY_H */

