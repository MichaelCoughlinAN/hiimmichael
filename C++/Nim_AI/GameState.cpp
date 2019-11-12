#include "nim.H"
#include <sstream>

GameStateInfo::GameStateInfo(int pile1, int pile2, int pile3) {
    this->pile1 = pile1;
    this->pile2 = pile2;
    this->pile3 = pile3;
}

int GameStateInfo::getPile1() {
    return pile1;
}

int GameStateInfo::getPile2() {
    return pile2;
}

int GameStateInfo::getPile3() {
    return pile3;
}

string GameStateInfo::toString() {

    return "    Pile 1: " + Utils::intToString(pile1) + "\n" +
           "    Pile 2: " + Utils::intToString(pile2) + "\n" +
           "    Pile 3: " + Utils::intToString(pile3);
}

GameState GameStateInfo::nextState(Move m) {
    int pile = m->getPile();
    if (pile < 1 || pile > 3)
        return NULL;
    int coins = m->getCoins();
    int availableCoins =
        (pile == 1) ? pile1 : (pile == 2) ? pile2 : pile3;
    if (coins > availableCoins)
        return NULL;
    int newCoins = availableCoins - coins;
    switch (pile) {
        case 1: pile1 = newCoins; break;
        case 2: pile2 = newCoins; break;
        case 3: pile3 = newCoins;
    }
    return new GameStateInfo(pile1, pile2, pile3);
}


