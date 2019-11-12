/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Header file for an object thrown on violation of precondition.
 *
 *  Adapted from page 249 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Nov 27
 *
 *  @version 6.0 */

#ifndef _PRECOND_VIOLATED_EXCEP
#define _PRECOND_VIOLATED_EXCEP

#include <stdexcept>
#include <string>

using namespace std;

/** @class PrecondViolatedExcep PrecondViolatedExcep.h "PrecondViolatedExcep.h"
 *
 *  Specification for an object thrown on violation of precondition. */
class PrecondViolatedExcep : public logic_error {
public:

   explicit PrecondViolatedExcep(const string& message = "");

   virtual ~PrecondViolatedExcep() throw();
};

#endif
