#ifndef _SIMULATION
#define _SIMULATION

#include "Event.h"
#include "EventBuilder.h"
#include "LinkedQueue.h"
#include "PriorityQueue.h"
#include "Statistics.h"

class Simulation {
private:
   void processArrival();
   void processDeparture();

   Event currentEvent;
   EventBuilder eventBuilder;
   LinkedQueue<Event> line1;
   LinkedQueue<Event> line2;
   LinkedQueue<Event> line3;
   PriorityQueue<Event> eventList;
   Statistics stats;

public:
   Simulation();
   ~Simulation();
   void simulate();
};

#endif
