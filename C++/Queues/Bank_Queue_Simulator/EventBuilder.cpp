#include "EventBuilder.h"

EventBuilder::EventBuilder() {
  string filename;
  cout << "Enter a filename: ";
  cin >> filename;

  inFile.open(filename.c_str() );

  while (!inFile) {
    cerr << "File "
	 << filename
	 << " failed to open for input."
	 << endl;
    cout << "Enter a filename: ";
    cin >> filename;
    inFile.open(filename.c_str() );
  }
}

Event EventBuilder::createArrivalEvent(const int number) {
  //number is the customer number, should start at 1.
  Event event; 
  int arrTime, durTime;
  event.setType(ARRIVAL);

  if( inFile >> arrTime >> durTime ) { 
   event.setDuration(durTime);
   event.setNumber(number);
   event.setTime(arrTime);

  }
   else event.setNumber(0);
  //in the Simulation class, you should test the event.number field for zero.

  return event;
}

Event EventBuilder::createDepartureEvent(const Time& currentEventTime, 
                                         const Time& transactionLength, 
                                         const int number) {
  Event departureEvent;
 
  departureEvent.setType(DEPARTURE);
  departureEvent.setTime(currentEventTime + transactionLength);
  departureEvent.setNumber(number);

  return departureEvent;
} 
