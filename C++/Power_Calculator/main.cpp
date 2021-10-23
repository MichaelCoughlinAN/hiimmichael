#include "PowerCalculator.h"
#include <cmath>
#include <iostream>

using namespace std;

int main(){

  PowerCalculator calc;
  
  cout << "RUNNING TESTS\n" << endl;
  calc.setValues();
  if(calc.power1(3, 32) == ((ReturnType) pow((ReturnType) 3, 32))){
    cout << "power1(3, 32) = " << calc.power1(3, 32)
	 << " has been correctly solved!\n"
	 << "This took " << calc.getMult() << " multiplications and "
	 << calc.getRecurse() << " recursive calls to solve.\n" << endl;
  }else cout << "power1(3, 32) generated an incorrect value.\n";
  calc.setValues();

 if(calc.power2(3, 32) == ((ReturnType) pow((ReturnType) 3, 32))){
    cout << "power2(3, 32) = " << calc.power2(3, 32)
	 << " has been correctly solved!\n"
	 << "This took " << calc.getMult() << " multiplications and "
	 << calc.getRecurse() << " recursive calls to solve.\n" << endl;
  }else cout << "power2(3, 32) generated an incorrect value.\n";
  calc.setValues();

 if(calc.power3(3, 32) == ((ReturnType) pow((ReturnType) 3, 32))){
    cout << "power3(3, 32) = " << calc.power3(3, 32)
	 << " has been correctly solved!\n"
	 << "This took " << calc.getMult() << " multiplications and "
	 << calc.getRecurse() << " recursive calls to solve.\n" << endl;
  }else cout << "power3(3, 32) generated an incorrect value.\n";
  calc.setValues();

  if(calc.power1(3, 19) == ((ReturnType) pow((ReturnType) 3, 19))){
    cout << "power1(3, 19) = " << calc.power1(3, 19)
	 << " has been correctly solved!\n"
	 << "This took " << calc.getMult() << " multiplications and "
	 << calc.getRecurse() << " recursive calls to solve.\n" << endl;
  }else cout << "power1(3, 19) generated an incorrect value.\n";
  calc.setValues();

 if(calc.power2(3, 19) == ((ReturnType) pow((ReturnType) 3, 19))){
    cout << "power2(3, 19) = " << calc.power2(3, 19)
	 << " has been correctly solved!\n"
	 << "This took " << calc.getMult() << " multiplications and "
	 << calc.getRecurse() << " recursive calls to solve.\n" << endl;
  }else cout << "power2(3, 19) generated an incorrect value.\n";
  calc.setValues();

 if(calc.power3(3, 19) == ((ReturnType) pow((ReturnType) 3, 19))){
    cout << "power3(3, 19) = " << calc.power3(3, 19)
	 << " has been correctly solved!\n"
	 << "This took " << calc.getMult() << " multiplications and "
	 << calc.getRecurse() << " recursive calls to solve.\n" << endl;
  }else cout << "power3(3, 19) generated an incorrect value.\n";
  calc.setValues();

  cout << "TESTS SUCCESSFULL\n" << endl;
  cout << "Welcome to the Power Calculator!\n" << endl;
  calc.calculator();

  return 0;

}
