#include "nim.H"

Move StrategyInfo::getMove(GameState state) {
    // This implements the simple, mindless Nim strategy
    int pile;
    if (state->getPile1() != 0)
        pile = 1;
    else if (state->getPile2() != 0)
        pile = 2;
    else
        pile = 3;
    return new MoveInfo(1, pile);
}

