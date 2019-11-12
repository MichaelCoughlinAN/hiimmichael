/** @file
 *
 *  @course CS1521
 *  @section 1
 *
 *  Implementation file for an object thrown on violation of
 *  precondition.
 *
 *  Adapted from page 250 in Carrano 6e.
 *
 *  @author Frank M. Carrano
 *  @author Timothy Henry
 *  @author Steve Holtz
 *
 *  @date 2013 Nov 27
 *
 *  @version 6.0 */

#include "PrecondViolatedExcep.h"

PrecondViolatedExcep::PrecondViolatedExcep(const string& message)
  : logic_error(message.c_str() ) {
}

PrecondViolatedExcep::~PrecondViolatedExcep()
  throw() {
}
