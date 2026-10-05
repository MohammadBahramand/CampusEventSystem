#ifndef EVENT_H
#define EVENT_H

#include  <string>
using namespace std;

class Event
{
private:
  string eventID;
  string name;
  string description;
  string date;
  string time;
  string location;
  int capacity;
public:
  Event(string id, string eventName, string eventDescription, string eventDate, string eventTime, string eventLocation, int eventCapacity);
  string getEventID() const;
  string getName() const;
  string getDescription() const;
  string getDate() const;
  string getTime() const;
  string getLocation() const;
  int getCapacity() const;
  void displayDetails() const;
};
#endif
