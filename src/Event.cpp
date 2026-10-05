#include "Event.h"
#include <iostream>
using namespace std;

Event::Event(string id, string eventName, string eventDescription, string eventDate, string eventTime, string eventLocation, int eventCapacity)
{
  eventID = id;
  name = eventName;
  description = eventDescription;
  date = eventDate;
  location = eventLocation;
  time = eventTime;
  capacity = eventCapacity;
}
