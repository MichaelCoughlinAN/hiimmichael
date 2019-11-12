#ifndef _EVENT
#define _EVENT

#include "Time.h"
#include "EventType.h"

using namespace std;

class Event {
 private:
  EventType type;
  Time time;
  Time length;
  int number;
 
 public:
  Event();
  EventType getType() const;

  int getNumber() const;
  Time getTime() const;
  Time getDuration() const;

  void setType(EventType ty);
  void setNumber(int num);
  void setTime(Time tim);
  void setDuration(Time dur);

  bool operator<(const Event& rhs) const {
    return time < rhs.time;
  }

 bool operator>(const Event& rhs) const {
    return time > rhs.time;
  }

 bool operator<=(const Event& rhs) const {
    return time <= rhs.time;
  }

 bool operator>=(const Event& rhs) const {
    return time >= rhs.time;
  }

 bool operator==(const Event& rhs) const {
    return time == rhs.time;
  }

 bool operator!=(const Event& rhs) const {
    return time != rhs.time;
  }
 
};

#endif
