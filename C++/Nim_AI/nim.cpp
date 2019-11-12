/* 
 * File:   nim.cpp
 * Author: tcolburn
 *
 * Created on December 10, 2013, 3:29 PM
 */

#include "nim.H"
#include <assert.h>
#include <cstdlib>

using namespace std;

void testMove() {
    Move move = new MoveInfo(5, 3);
    assert(move->getCoins() == 5 && move->getPile() == 3);

    cout << "testMove succeeded.\n";
}

void testGameState() {
    GameState state = new GameStateInfo(3, 4, 5);

    string stateDisplay = state->toString();
    cout << stateDisplay << endl;
    string output = "    Pile 1: 3\n    Pile 2: 4\n    Pile 3: 5";
    assert(stateDisplay == output);

    Move move = new MoveInfo(5, 3);
    GameState newState = state->nextState(move);
    assert(newState->getPile1() == 3 && newState->getPile2() == 4 &&
            newState->getPile3() == 0);

    cout << "testGameState succeeded.\n";
}

void testPlayer() {
    Player player = new PlayerInfo("Fred");
    assert( player->getName() == "Fred");
    GameState state = new GameStateInfo(3, 4, 5);
    cout << "*** Please remove 4 coins from pile 3 ***\n";
    Move move = player->getMove(state);
    assert(move->getCoins() == 4 && move->getPile() == 3);

    cout << "testPlayer succeeded.\n";
}

void testStrategy() {
    Strategy strategy = new StrategyInfo;  // Uses simple, mindless strategy
    GameState state = new GameStateInfo(0, 4, 5);
    Move move = strategy->getMove(state);  
    assert(move->getCoins() == 1 && move->getPile() == 2);

    cout << "testStrategy succeeded.\n";
}

void testIntermediateStrategy() {
    Strategy strategy = new IntermediateStrategyInfo;

    Move move = strategy->getMove(new GameStateInfo(1, 2, 3));
    assert(move->getCoins() == 1 && move->getPile() == 1); // Default to simple strategy

    move = strategy->getMove(new GameStateInfo(0, 4, 4));
    assert(move->getCoins() == 1 && move->getPile() == 2); // Default to simple strategy

    move = strategy->getMove(new GameStateInfo(0, 9, 0));  // Remove pile 2
    assert(move->getCoins() == 9 && move->getPile() == 2);

    move = strategy->getMove(new GameStateInfo(3, 3, 10));  // Remove pile 3
    assert(move->getCoins() == 10 && move->getPile() == 3);

    move = strategy->getMove(new GameStateInfo(0, 5, 8));  // Even piles 2 and 3
    assert(move->getCoins() == 3 && move->getPile() == 3);

    cout << "testIntermediateStrategy succeeded.\n";
}

void testAutomatedPlayer() {
    Strategy strategy = new IntermediateStrategyInfo;
    AutomatedPlayer computer = new AutomatedPlayerInfo("HAL 9000", strategy);
    assert(computer->getName() == "HAL 9000");
    GameState state = new GameStateInfo(0, 5, 8);
    Move move = computer->getMove(state);
    assert(move->getCoins() == 3 && move->getPile() == 3);

    cout << "testAutomatedPlayer succeeded.\n";
}

void testGame() {
    cout << "Welcome to the Game of Nim.\n\nWhat is your name? ";
    string name = "                    ";
    cin >> name;
    Player player1 = new PlayerInfo(name);
    Player player2 = new AutomatedPlayerInfo("HAL 9000", new IntermediateStrategyInfo);
    GameState initialState = new GameStateInfo(5, 8, 6);
    Game game = new GameInfo(player1, player2, initialState);
    Player winner = game->play();
    cout << winner->getName() << " wins.\n";
}

void testScoreKeeper() {
    srand(time(NULL));
    ScoreKeeper scoreKeeper = new ScoreKeeperInfo;
    scoreKeeper->start();
}

/*
 * 
 */
int main(int argc, char** argv) {

//    testMove();
//    testGameState();
//    testPlayer();
//    testStrategy();
//    testIntermediateStrategy();
//    testAutomatedPlayer();
//    testGame();
    testScoreKeeper();
    
    cout << "All tests succeeded.\n";
    
    return 0;
}

