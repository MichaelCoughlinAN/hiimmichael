#include "nim.H"

MoveInfo::MoveInfo(int coins, int pile) {
  this->coins = coins;
  this->pile = pile;
};

int MoveInfo::getCoins() {
  return coins;
}

int MoveInfo::getPile() {
  return pile;
}

