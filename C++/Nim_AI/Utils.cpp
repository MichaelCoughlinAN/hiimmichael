#include "Utils.H"
#include <sstream>

string Utils::intToString(int i) {
    stringstream out;
    out << i;
    return out.str();
}

int Utils::generateRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

