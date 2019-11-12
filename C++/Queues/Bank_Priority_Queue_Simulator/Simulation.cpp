#include "Simulation.h"

Simulation::Simulation(){
}

Simulation::~Simulation() {
}

void Simulation::simulate() {
 cout << "\nSimulation of 3 Queue Begins\n";
 eventList.add(eventBuilder.createArrivalEvent(1, 1)); // Create an initial arrival event, put that event into the event list

 while (!eventList.isEmpty() ) {
   currentEvent = eventList.peek(); //  Retrieve the next event from the event list
   if (currentEvent.getType() == ARRIVAL) {
     if (currentEvent.getNumber() == 0) { 
         break;
   }
        else {  
        processArrival();
	}
   }
     else {
       processDeparture();
	 }   
   stats.addEvent(currentEvent); 
     }
 stats.reportStats(); 
}

void Simulation::processArrival() {
  Event newEvent;
  bool line1IsEmpty = line1.isEmpty();
  bool line2IsEmpty = line2.isEmpty();
  bool line3IsEmpty = line3.isEmpty();
  int line1Length = line1.getLength();
  int line2Length = line2.getLength();
  int line3Length = line3.getLength();

  eventList.remove(); 
 
 if(line1Length <= line2Length && line1Length <= line3Length) {
   currentEvent.setLine(1);   
 line1.enqueue(currentEvent);	  
    }
    else if(line2Length <= line1Length && line2Length <= line3Length) {	   
      currentEvent.setLine(2);   
 line2.enqueue(currentEvent);
    }
    else if(line3Length <= line1Length && line3Length <= line2Length) {	  
      currentEvent.setLine(3);   
 line3.enqueue(currentEvent);
    }  


  if (line1IsEmpty) { 
       eventList.add(eventBuilder.createDepartureEvent(currentEvent.getTime(), 
                                                       currentEvent.getDuration(), 
						       currentEvent.getNumber(), 
                                                       currentEvent.getLine() )); 
       
 }
  else if (line2IsEmpty) { 
       eventList.add(eventBuilder.createDepartureEvent(currentEvent.getTime(), 
                                                       currentEvent.getDuration(), 
						       currentEvent.getNumber(), 
                                                       currentEvent.getLine() ));
        }
  else if (line3IsEmpty) { 
       eventList.add(eventBuilder.createDepartureEvent(currentEvent.getTime(), 
                                                       currentEvent.getDuration(), 
						       currentEvent.getNumber(), 
                                                       currentEvent.getLine() ));
  } 

   line1Length = line1.getLength();
   line2Length = line2.getLength();
   line3Length = line3.getLength();

 if(line1Length <= line2Length && line1Length <= line3Length) { 
    newEvent = eventBuilder.createArrivalEvent(currentEvent.getNumber() + 1, 1); 
 }
  else if(line2Length <= line1Length && line2Length <= line3Length) {	   
    newEvent = eventBuilder.createArrivalEvent(currentEvent.getNumber() + 1, 2);
 }
  else if(line3Length <= line1Length && line3Length <= line2Length) {	  
    newEvent = eventBuilder.createArrivalEvent(currentEvent.getNumber() + 1, 3);   
 }
    
  if (newEvent.getNumber() != 0) {
      eventList.add(newEvent);
	}  
  }

void Simulation::processDeparture() {
  Event newEvent; 
  eventList.remove(); // Delete currentEvent from event list

  if(currentEvent.getLine() == 1) {
    line1.dequeue();
    if (!line1.isEmpty() ) {
      newEvent = line1.peekFront();
      eventList.add(eventBuilder.createDepartureEvent(currentEvent.getTime(), 
                                                      newEvent.getDuration(),
                                                      newEvent.getNumber(), 
						      newEvent.getLine() ));
       } 
  }
  else if(currentEvent.getLine() == 2) {
   line2.dequeue();
    if (!line2.isEmpty() ) {
      newEvent = line2.peekFront();
      eventList.add(eventBuilder.createDepartureEvent(currentEvent.getTime(), 
                                                      newEvent.getDuration(),
                                                      newEvent.getNumber(), 
						      newEvent.getLine() ));
	}
  }
  else if(currentEvent.getLine() == 3) { 
   line3.dequeue();
    if (!line3.isEmpty() ) {
      newEvent = line3.peekFront();
      eventList.add(eventBuilder.createDepartureEvent(currentEvent.getTime(), 
                                                      newEvent.getDuration(),
                                                      newEvent.getNumber(), 
						      newEvent.getLine() ));
	}
  }
}
