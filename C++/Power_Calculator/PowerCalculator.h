#ifndef POWERCALCULATOR_H
#define POWERCALCULATOR_H

using namespace std;

typedef unsigned char Exponent;
typedef signed char Base;
typedef unsigned int Counter;
typedef signed long ReturnType;

class PowerCalculator{
 public:
  Counter getRecurse() const;
  Counter getMult() const;
  void  multiplications();
  void  recursiveCalls();
  ReturnType power1(Base, Exponent);
  ReturnType power2(Base, Exponent);
  ReturnType power3(Base, Exponent);
  void calculator();
  void setValues();
 
private:
  Counter totalMult;
  Counter totalRecurse;
  ReturnType value;
  ReturnType base1;
  ReturnType power;
  char input;
  bool fin; 
};

#endif 
