#include <iostream>
#include <string>
#include <cstdlib>

#include "LinkedStack.h"
#include "Infix.h"

using namespace std;

int main() {
  string exp;
  Infix eval;
 

  cout << "\nWelcome to the Infix Calculator!\n" 
       << endl
       << "If a file was not redirected, please enter an infix expression "
       << "(you may use parentheses).\n"
       << "Otherwise, type \"done\" to exit.\n"
       << endl; 

  while (getline(cin,  exp))  {          
    if (exp == "DONE" || exp == "done" || exp == "Done") {
      cout << "Thank you and have a nice day!\n";
      break;
  }   
 eval.setExpStr(exp);
     try {
	  cout << eval.getExpStr() << " = "
	       << eval.evaluateExp(exp)
	       << endl;
	 	}
	catch (const overflow_error& e) {
	  cout << exp << " = ";
       	  cerr << e.what()
	       << endl;
	 }
}
  cout << endl
       << "EXIT SUCCESS\n";

 return EXIT_SUCCESS;
}
