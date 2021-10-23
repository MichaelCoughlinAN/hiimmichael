/* 
 * File:   nim.H
 * Author: tcolburn
 *
 * Created on December 10, 2013, 3:28 PM
 */

#ifndef NIM_H
#define	NIM_H

typedef class MoveInfo* Move;
typedef class GameStateInfo* GameState;
typedef class PlayerInfo* Player;
typedef class AutomatedPlayerInfo* AutomatedPlayer;
typedef class StrategyInfo* Strategy;
typedef class IntermediateStrategyInfo* IntermediateStrategy;
typedef class GameInfo* Game;
typedef class ScoreKeeperInfo* ScoreKeeper;

#include "Move.H"
#include "Utils.H"
#include "GameState.H"
#include "Player.H"
#include "AutomatedPlayer.H"
#include "Strategy.H"
#include "IntermediateStrategy.H"
#include "Game.H"
#include "ScoreKeeper.H"

#include <iostream>

#endif	/* NIM_H */

