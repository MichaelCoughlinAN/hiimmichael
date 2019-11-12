#include "Event.h"

Event::Event() {
}

int Event::getLine() const {
  return line;
}

Time Event::getTime() const {
  return time;
}

EventType Event::getType() const {
  return type;
}

int Event::getNumber() const {
  return number;
}

Time Event::getDuration() const {
  return length;
}

void Event::setType(EventType ty) {
  type = ty;
}

void Event::setNumber(int num) {
  number = num;
}

void Event::setDuration(Time dur) {
  length = dur;
}

void Event::setTime(Time tim) {
  time = tim;
}


void Event::setLine(int lin) {
  line = lin;
}
