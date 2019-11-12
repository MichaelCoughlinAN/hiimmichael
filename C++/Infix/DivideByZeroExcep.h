#ifndef _DIVIDE_BY_ZERO_EXCEP
#define _DIVIDE_BY_ZERO_EXCEP

#include <stdexcept>
#include <string>

using namespace std;

class DivideByZeroExcep : public overflow_error {
 public:

  explicit DivideByZeroExcep(const string& message = "");

  virtual ~DivideByZeroExcep() throw();
};

#endif
