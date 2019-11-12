#ifndef _EVENT_BUILDER
#define _EVENT_BUILDER

#include <fstream>

using namespace std;
#include <iostream>
#include "Event.h"

class EventBuilder {
private:
   ifstream inFile;

public:
   /** Three things must happen to create an EventBuilder:
    *  1) Prompt the user for the name of an input file
    *  2) Attempt to open this file on the 'inputFile' data member
    *  3) If the file doesn't open, repeat steps 1 and 2 */
   EventBuilder();

   /** Create and return an event with members:
    *  type == ARRIVAL
    *  number == 'number'
    *  line == 'lineNumber'
    *  time == time read from 'inputFile'
    *  length == transaction length read from 'inputFile'
    *
    *  If 'inputFile' has been completely read, then set the return
    *  event.number field to zero (as no event will be numbered zero).
    *  This can then be used to tell when the external file is either
    *  empty or EOF has been reached. */
   Event createArrivalEvent(const int number,
                            const int lineNumber);

   /** Create and return an event with members:
    *  type == DEPATURE
    *  number == 'number'
    *  line == 'lineNumber'
    *  time == 'currentEventTime' + 'transactionLength' */
   Event createDepartureEvent(const Time& currentEventTime,
                              const Time& transactionLength,
                              const int number,
                              const int lineNumber);
};

#endif
