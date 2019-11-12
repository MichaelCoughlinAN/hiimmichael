#include "nim.H"

AutomatedPlayerInfo::AutomatedPlayerInfo(string name, Strategy strategy) :
    PlayerInfo(name) {
    this->strategy = strategy;
}

Move AutomatedPlayerInfo::getMove(GameState state) {
    return strategy->getMove(state);
}

