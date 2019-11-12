#include <iostream>
#include <string>
#include <cctype>

#include "Infix.h"

using namespace std;

Infix::Infix() {
}

string Infix::getExpStr() const {
  return expStr;
}

void Infix::setExpStr(const string& input){
  expStr = input;

}

int Infix::evaluateExp(string& infixExp){
  LinkedStack<char> operatorStack;
  LinkedStack<int> valueStack;

  for (string::size_type i = 0; i < infixExp.size(); ++i) { 
    char ch = infixExp.at(i);
    if (isOperand(ch) ) {
      valueStack.push(convertToInt(ch) ); 
	}
    else if (ch == '(' ) {
      operatorStack.push(ch);
	}
    else if (isOperator(ch) ) {
      if (operatorStack.isEmpty() || precedence(ch, operatorStack.peek() )) { 
	 operatorStack.push(ch);
      }
      else {
	while (!operatorStack.isEmpty() && !precedence(ch, operatorStack.peek() )) { 
	  valueStack.push(execute(operatorStack, valueStack));
	      }
	operatorStack.push(ch);
	   }
    }
    else if (ch == ')' ) {
      while (operatorStack.peek() != '(' ) {
	valueStack.push(execute(operatorStack, valueStack));
      }
      operatorStack.pop(); 
	}
  }
  while (!operatorStack.isEmpty() ) {
   valueStack.push(execute(operatorStack, valueStack));
     }
  return valueStack.peek();  
}

bool Infix::precedence(const char op1, const char op2) const {
  if((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
    return true;
 if((op1 == '*' || op1 == '/') && (op2 == '(' || op2 == ')'))
    return true; 
 if((op1 == '+' || op1 == '-') && (op2 == '(' || op2 == ')'))
    return true; 
  else if ((op1 == '*' || op1 == '/') && (op2 == '*' || op2 == '/'))
    return false;
  else return false; 
}

bool Infix::isOperand(const char input) const {
  if (isdigit(input) )
    return true;
       else return false;
}

bool Infix::isOperator(const char input) const {
    switch (input) {
    case '+':
      return true;
      break;
    case '-':
      return true;
      break;
    case '/':
      return true;
      break;
    case '*':
      return true;
      break;
    }
    return false;
  }


int Infix::convertToInt(char input) const {
  int result; 
 result = input - '0';
 return result;
}

 int Infix::execute(LinkedStack<char>& operatorStack, LinkedStack<int>& valueStack) const { 
   int operand2 = valueStack.peek();
   valueStack.pop();
   int operand1 = valueStack.peek();
   valueStack.pop();
   char operatorSign = operatorStack.peek();
   operatorStack.pop();
 
 switch (operatorSign) {
    case '+':
      return operand1 + operand2; 
      break;
    case '-':
      return operand1 - operand2;
      break;
    case '/':
      if (operand2 == 0) {
          throw DivideByZeroExcep("Infinite result - Cannot handle division-by-zero.");
         }
      else return operand1 / operand2;
      break;
    case '*':
      return operand1 * operand2;
      break; 
 }
 return 0;
 }
 

