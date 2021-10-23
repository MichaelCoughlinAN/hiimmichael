#include "DivideByZeroExcep.h"

DivideByZeroExcep::DivideByZeroExcep(const string& message)
  : overflow_error(message.c_str()){
}

DivideByZeroExcep::~DivideByZeroExcep()
  throw(){
}
