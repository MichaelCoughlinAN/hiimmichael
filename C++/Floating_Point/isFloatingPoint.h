#ifndef _ISFLOATINGPOINT
#define _ISFLOATINGPOINT

#include <string>
using namespace std;

class isFloatingPoint{
private:
  int endIndex;
  int nextIndex;
  int length;
  int last;
  int first;
  int index;
  char currentChar;
  char nextChar;

public: 
 bool isFloatingPointValue(const string& strExp);
 bool isDigit(const char& input);
 int endInt(const string& strExp, int first);
};

#endif
