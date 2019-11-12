#ifndef _NOT_FOUND_EXCEP
#define _NOT_FOUND_EXCEP

#include <stdexcept>
#include <string>

using namespace std;

/** @class NotFoundException NotFoundException.h "NotFoundException.h"
 *
 *  Specification for an object thrown on violation of not found. */
class NotFoundException : public logic_error {
 public:

  explicit NotFoundException(const string& message = "");

  virtual ~NotFoundException() throw();
};

#endif
