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
  Event(const string& id,
          const string& eventName,
          const string& eventDescription,
          const string& eventDate,
          const string& eventTime,
          const string& eventLocation,
          int eventCapacity);
  const string& getEventID() const;
  const string& getName() const;
  const string& getDescription() const;
  const string& getDate() const;
  const string& getTime() const;
  const string& getLocation() const;
  int getCapacity() const;
  virtual void displayDetails() const;
};
#endif
