#include <iostream>

using namespace std;

#include "Statistics.h"

Statistics::Statistics()
   : countTotal(0),
     count1(0),
     count2(0),
     count3(0),
     waitTimeTotal(0),
     waitTime1(0),
     waitTime2(0),
     waitTime3(0) {
}

Statistics::~Statistics() {
}

void Statistics::addEvent(const Event& event) {

   // Use arrivals to count the total number of customers and tally
   // the numbers of customers that enter each line.
   if (event.getType() == ARRIVAL) {
#ifdef TESTING
      cout << "Processing arrival event "
           << event.getNumber()
           << " in queue "
           << event.getLine()
           << " at time "
           << event.getTime()
           << endl;
#endif
      ++countTotal;

      if (event.getLine() == 1) {
         arrivalEvents1.enqueue(event);
         ++count1;
      }
      else if (event.getLine() == 2) {
         arrivalEvents2.enqueue(event);
         ++count2;
      }
      else {
         arrivalEvents3.enqueue(event);
         ++count3;
      }
   }

   // Use departures to calculate total wait time and cumulative wait
   // time for each line.
   else {
#ifdef TESTING
      cout << "Processing departure event "
           << event.getNumber()
           << " at time: "
           << event.getTime()
           << " in line number "
           << event.getLine();
#endif
      Event arrivalEvent;
      bool eventWaiting = false;

      if (event.getLine() == 1 && !arrivalEvents1.isEmpty() ) {
         arrivalEvent = arrivalEvents1.peekFront();
         arrivalEvents1.dequeue();
         waitTime1 += event.getTime() - (arrivalEvent.getTime() + arrivalEvent.getDuration() );
         eventWaiting = true;
      }
      else if (event.getLine() == 2 && !arrivalEvents2.isEmpty() ) {
         arrivalEvent = arrivalEvents2.peekFront();
         arrivalEvents2.dequeue();
         waitTime2 += event.getTime() - (arrivalEvent.getTime() + arrivalEvent.getDuration() );
         eventWaiting = true;
      }
      else if (event.getLine() == 3 && !arrivalEvents3.isEmpty() ) {
         arrivalEvent = arrivalEvents3.peekFront();
         arrivalEvents3.dequeue();
         waitTime3 += event.getTime() - (arrivalEvent.getTime() + arrivalEvent.getDuration() );
         eventWaiting = true;
      }

      if (eventWaiting) {
#ifdef TESTING
         cout << " event "
              << arrivalEvent.getNumber()
              << " waited: "
              << event.getTime() - (arrivalEvent.getTime() + arrivalEvent.getDuration() );
#endif
         waitTimeTotal += event.getTime() - (arrivalEvent.getTime() + arrivalEvent.getDuration() );
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

   cout << "\nFinal Statistics:"
        << endl
        << "  Total number of people processed: "
        << countTotal
        << endl
        << "  Total wait time: "
        << waitTimeTotal
        << endl
        << "  Average amount of time spent waiting: ";
   if (countTotal != 0) {
      cout << (double)waitTimeTotal / (double)countTotal;
   }
   else {
      cout << 0.0;
   }
   cout << endl
        << "\n  Totals for Teller 1:"
        << endl
        << "    People processed: "
        << count1
        << endl
        << "    Wait time: "
        << waitTime1
        << endl
        << "    Average wait time: ";
   if (count1 != 0) {
      cout << (double)waitTime1 / (double)count1;
   }
   else {
      cout << 0.0;
   }
   cout << endl
        << "\n  Totals for Teller 2:"
        << endl
        << "    People processed: "
        << count2
        << endl
        << "    Wait time: "
        << waitTime2
        << endl
        << "    Average wait time: ";
   if (count2 != 0) {
      cout << (double)waitTime2 / (double)count2;
   }
   else {
      cout << 0.0;
   }
   cout << endl
        << "\n  Totals for Teller 3:"
        << endl
        << "    People processed: "
        << count3
        << endl
        << "    Wait time: "
        << waitTime3
        << endl
        << "    Average wait time: ";
   if (count3 != 0) {
      cout << (double)waitTime3 / (double)count3;
   }
   else {
      cout << 0.0;
   }
   cout << endl;
}
