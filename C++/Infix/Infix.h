#ifndef _INFIX
#define _INFIX

#include "DivideByZeroExcep.h"
#include "LinkedStack.h"
#include <string>

class Infix {
 private:
  string expStr;




 public:
  Infix();
  void setExpStr(const string& input);
  string getExpStr() const;
  int convertToInt(char input) const;
  int evaluateExp(string& infixExp);
  int execute(LinkedStack<char>& operatorStack,
              LinkedStack<int>& valueStack) const;   
  bool precedence(const char op1, const char op2) const;
  bool isOperand(const char input) const;
  bool isOperator(const char input) const; 
};


#endif
