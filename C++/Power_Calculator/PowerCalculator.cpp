#include "PowerCalculator.h"
#include <cmath>
#include <iostream>

using namespace std;

Counter PowerCalculator::getMult() const{
  return totalMult;
}
Counter PowerCalculator::getRecurse() const{
  return totalRecurse;
}
void PowerCalculator::setValues(){
  totalMult = 0;
  totalRecurse = 0;
}
void PowerCalculator::multiplications(){
  totalMult++;
}
void PowerCalculator::recursiveCalls(){
  totalRecurse++;
}
ReturnType PowerCalculator::power1(Base x, Exponent n){
  value = 1;
  for(int y = 1; y <= n; y++){
    multiplications();
    value = value * x;
  }
  return value;
}
ReturnType PowerCalculator::power2(Base x, Exponent n){
  if(n == 0)
    return 1;
    else{
      multiplications();
      recursiveCalls();
      return x * power2(x, (n - 1));
    }
}
ReturnType PowerCalculator::power3(Base x, Exponent n){
 if(n == 0)
    return 1;
  else if (n == 1)
    return x;
  else if ((n % 2) == 0){
    multiplications();
    recursiveCalls();
    return power3(x, (n / 2)) * power3(x, (n / 2));
  }else{
    multiplications();
    multiplications();
    recursiveCalls();
    recursiveCalls();
    return x * ((power3(x, (n / 2))) * ((power3(x, (n / 2)))));
  }
}
void PowerCalculator::calculator(){
  fin = false; 
 cout << "Please enter a base number: ";
  cin >> base1;
  cout << "Now enter a power: ";
  cin >> power;
  cout << base1 << " raised by a power of " << power << " is equal to: "
       << power3(base1, power) << endl;
 cout << "Would you like to continue? (y/n): ";
  cin >> input;
  while(fin == false){
    if(input == 'Y' || input == 'y'){
      calculator();
      fin = true;
    }
    else if (input == 'N' || input == 'n'){
    fin = true;
    cout << "Goodbye, have a nice day!\n";
      }
  else{ cout << "Incorrect input. Would you like to continue? (y/n): \n";
    cin >> input;  
}
  }
  }


