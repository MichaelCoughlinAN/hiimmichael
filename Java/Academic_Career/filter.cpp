#include "filter.h"


Filter::Filter(){
    string Canada;
    badWords[0] = Canada;
}
string* Filter::getFilter() {
    return badWords;
}

