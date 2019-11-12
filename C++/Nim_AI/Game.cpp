#include "nim.H"

GameInfo::GameInfo(Player player1, Player player2,
                   GameState initialState) {
    this->player1 = player1;
    this->player2 = player2;
    currentState = initialState;
    nextToPlay = player1;
}

Player GameInfo::play() {
    cout << endl << currentState->toString() << endl << endl;
    if (gameOver())
        return opponent(nextToPlay);  // nextToPlay loses
    else {
        Move move = nextToPlay->getMove(currentState);
        GameState next = currentState->nextState(move);
        if (next == NULL) {
            cout << "Illegal move.\n";
            play();
        }
        else {
            cout << nextToPlay->getName() << " takes " << move->getCoins() 
                 << " coin(s) from pile " << move->getPile() << endl;
            GameState save = currentState;
            currentState = next;
            delete save; // reclaim memory for game state object
            delete move; // reclaim memory for move object
            nextToPlay = opponent(nextToPlay);
            play();
        }
    }
}

bool GameInfo::gameOver() {
    return (currentState->getPile1() +
            currentState->getPile2() +
            currentState->getPile3()) == 0;
}

Player GameInfo::opponent(Player p) {
    return (p == player1) ? player2 : player1;
}

