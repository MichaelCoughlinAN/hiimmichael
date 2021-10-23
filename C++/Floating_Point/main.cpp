#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

#include "isFloatingPoint.h"

int main() {
  isFloatingPoint number;
   string exp;

    while (cin >> exp) {
      if (number.isFloatingPointValue(exp)) {
         cout << exp
              << " is a floating-point number."
              << endl;
      }
      else {
         cout << "ILLEGAL floating-point number: "
              << exp
              << endl;
      }
       }

   return EXIT_SUCCESS;
}
