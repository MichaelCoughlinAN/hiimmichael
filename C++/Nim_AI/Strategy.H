/* 
 * File:   Strategy.H
 * Author: tcolburn
 *
 * Created on December 10, 2013, 4:17 PM
 */

#ifndef STRATEGY_H
#define	STRATEGY_H

#include "nim.H"

class StrategyInfo {
public:
    virtual Move getMove(GameState state);
private:
};

#endif	/* STRATEGY_H */

