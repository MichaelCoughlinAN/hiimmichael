#include "nim.H"

Move IntermediateStrategyInfo::getMove(GameState state) {
    // This strategy attempts to leave a state with two nonempty
    // piles that are the same size
    if (allNonEmpty(state))
        if (allDifferent(state))
            return StrategyInfo::getMove(state); // Default to simple strategy
        else {
            return removePile(theDifferentPile(state), state);
        }
    else if (oneNonEmpty(state)) {
        return removePile(theDifferentPile(state), state);
    }
    else {   // Two must be nonempty
        if (allDifferent(state)) {
            return evenPiles(state);
        }
        else { // Two equal piles so you've lost
            return StrategyInfo::getMove(state); // Default to simple strategy
        }
    }}

Move IntermediateStrategyInfo::removePile(int pile, GameState state) {
    int coins = (pile == 1) ? state->getPile1() :
                (pile == 2) ? state->getPile2() : state->getPile3();
    return new MoveInfo(coins, pile);
}

Move IntermediateStrategyInfo::evenPiles(GameState state) { // There are two unequal piles left
    int pile1 = state->getPile1();
    int pile2 = state->getPile2();
    int pile3 = state->getPile3();
    if (pile1 == 0)
        if (pile2 < pile3)
            return new MoveInfo(pile3 - pile2, 3);
        else
            return new MoveInfo(pile2 - pile3, 2);
    else if (pile2 == 0)
        if (pile1 < pile3)
            return new MoveInfo(pile3 - pile1, 3);
        else
            return new MoveInfo(pile1 - pile3, 1);
    else   // pile 3 must be empty
        if (pile1 < pile2)
            return new MoveInfo(pile2 - pile1, 2);
        else
            return new MoveInfo(pile1 - pile2, 1);
}

bool IntermediateStrategyInfo::allNonEmpty(GameState state) {
    return state->getPile1() != 0 &&
            state->getPile2() != 0 &&
            state->getPile3() != 0;
}

bool IntermediateStrategyInfo::oneNonEmpty(GameState state) {
    return (state->getPile1() != 0 && state->getPile2() == 0 && state->getPile3() == 0) ||
            (state->getPile1() == 0 && state->getPile2() != 0 && state->getPile3() == 0) ||
            (state->getPile1() == 0 && state->getPile2() == 0 && state->getPile3() != 0);
}

bool IntermediateStrategyInfo::allDifferent(GameState state) {
    return state->getPile1() != state->getPile2() &&
            state->getPile2() != state->getPile3() &&
            state->getPile3() != state->getPile1();
}

int IntermediateStrategyInfo::theDifferentPile(GameState state) {          // Assumes one pile is
    if (state->getPile1() == state->getPile2())  // different than the others
        return 3;
    else if (state->getPile2() == state->getPile3())
        return 1;
    else
        return 2;
}

