#include "Simulation.h"

Simulation::Simulation(){
}

Simulation::~Simulation() {
}

void Simulation::simulate() {
 cout << "\nSimulation of 1 Queue Begins\n";
  
 events.add(eventBuilder.createArrivalEvent(1)); // Create an initial arrival event, 
                                                 // put that event into the event list

 while (!events.isEmpty()) {
   currentEvent = events.peek(); //  Retrieve the next event from the event list
       
   if (currentEvent.getType() == ARRIVAL) {
     if (currentEvent.getNumber() == 0)
       break;
      else  
        processArrival();
	 }
    else {
       processDeparture();
	 }
   stats.addEvent(currentEvent); // Add the event to the statistics object
     }
 stats.reportStats(); //  Generate a statistics report 
}

void Simulation::processArrival() {
  bool lineIsEmpty = line.isEmpty(); 
  line.enqueue(currentEvent); //Put currentEvent at the end of the queue
  events.remove(); //Delete currentEvent from event list
 
     if (lineIsEmpty) {
       events.add(eventBuilder.createDepartureEvent(currentEvent.getTime(), 
                                                    currentEvent.getDuration(), 
                                                    currentEvent.getNumber() )); 
       // Insert into event list a departure event corresponding
       // to current event (customer) with currTime = currTime + transLength
     }
     Event newEvent = eventBuilder.createArrivalEvent(currentEvent.getNumber() + 1); // Create a new arrival event newEvent
				 
  if (newEvent.getNumber() != 0) {
      events.add(newEvent);
	}  
}

void Simulation::processDeparture() {
  line.dequeue();// Remove the event from front of queue. Customer leaves bank
  events.remove(); // Delete currentEvent from event list

 

    if (!line.isEmpty() ) {
     Event newEvent = line.peekFront();
     events.add(eventBuilder.createDepartureEvent(currentEvent.getTime(), 
                                                  newEvent.getDuration(),
                                                  newEvent.getNumber() ));
     // Insert into event list a departure event
     //	corresponding to event (customer) at front of queue
     // with currTime = currTime + transLength
	}

}
