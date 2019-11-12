#include "isFloatingPoint.h"
#include <string>

using namespace std;

bool isFloatingPoint::isDigit(const char& input) {
  if (isdigit(input))
       return true;
  else if (input == '.')
      return false;
  else return false;
}

int isFloatingPoint::endInt(const string& strExp, int first){
  endIndex = -1;
  length = strExp.length();
  currentChar = strExp.at(first);
  last = strExp.length() - 1;
 
  if (first + 1 < length)
      nextChar = strExp.at(first + 1);

  if (isDigit(currentChar) && length == 1)    
      return first;

  if (isDigit(currentChar) && nextChar == '.' && last > first)
      endIndex = first;
  else if (isDigit(currentChar) && first + 1 > last)
      endIndex = first;
  else if (isDigit(currentChar) && first < last) { 
      nextIndex = endInt(strExp, (first + 1)); 
   
  if (nextIndex < 0)  
      endIndex = first;  
   else 
     endIndex = nextIndex; 
  }
  return endIndex;
}

bool isFloatingPoint::isFloatingPointValue(const string& strExp) {
  first = 0;
  length = strExp.length();
  last = strExp.length() - 1;

  index = endInt(strExp, first); 

  if (last == index) 
      return true;

  if (first + 1 < length)
      nextChar = strExp.at(index + 1);

  if (last == index) 
      return true;
  else if (index < 0)
    return false;

  if (index >= 0 && length > 2 && nextChar == '.')
      index = endInt(strExp, index + 2);

  if (last == index) 
      return true;
        
  return false; 
}
