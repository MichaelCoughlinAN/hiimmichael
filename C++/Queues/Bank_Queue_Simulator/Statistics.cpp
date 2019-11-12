#include <iostream>

using namespace std;

#include "Statistics.h"

Statistics::Statistics()
   : count(0),
     waitTime(0) {
}

Statistics::~Statistics() {
}

void Statistics::addEvent(const Event& event) {

   if (event.getType() == ARRIVAL) {
#ifdef TESTING
      cout << "Processing arrival event "
           << event.getNumber()
           << " at time: "
           << event.getTime()
           << endl;
#endif
      arrivalEvents.enqueue(event);
      ++count;
   }
   else { // event is a departure event
#ifdef TESTING
      cout << "Processing departure event "
           << event.getNumber()
           << " at time: "
           << event.getTime();
#endif
      if (!arrivalEvents.isEmpty() ) {
         Event arrivalEvent;

         arrivalEvent = arrivalEvents.peekFront();
         arrivalEvents.dequeue();
         waitTime += event.getTime() - (arrivalEvent.getTime() + arrivalEvent.getDuration() );
#ifdef TESTING
         cout << " event "
              << arrivalEvent.getNumber()
              << " waited: "
              << event.getTime() - (arrivalEvent.getTime() + arrivalEvent.getDuration() );
#endif
      }
#ifdef TESTING
      else {
         cout << " no events waiting.";
      }
      cout << endl;
#endif
   }
}

void Statistics::reportStats() const {
  cout << "Simulation Ends\n" << endl;

   cout << "Final Statistics:"
        << endl
        << "  Total number of people processed: "
        << count
        << endl
        << "  Total wait time: "
        << waitTime
        << endl
        << "  Average amount of time spent waiting: ";
   if (count != 0) {
      cout << (double)waitTime / (double)count;
   }
   else {
      cout << 0.0;
   }
   cout << endl;
}
