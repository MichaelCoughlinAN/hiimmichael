#ifndef SIMULATION_H
#define SIMULATION_H 1

#include "Event.h"
#include "EventBuilder.h"
#include "LinkedQueue.h"
#include "PriorityQueue.h"
#include "Statistics.h"
#include <iostream>

using namespace std;

class Simulation {
private:
   void processArrival();
   void processDeparture();

   Event currentEvent;
   EventBuilder eventBuilder;
   LinkedQueue<Event> line;
   PriorityQueue<Event> events;
   Statistics stats;
   // LinkedSortedList<Event> events;
public:
   Simulation();
   ~Simulation();
   void simulate();
};

#endif
