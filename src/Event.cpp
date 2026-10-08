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
//======================================
string Event::getEventID() const
{
    return eventID;
}
//======================================
string Event::getName() const
{
    return name;
}
//======================================
string Event::getDescription() const
{
    return description;
}
//======================================
string Event::getDate() const
{
    return date;
}
//======================================
string Event::getTime() const
{
    return time;
}
//======================================
string Event::getLocation() const
{
    return location;
}
//======================================
int Event::getCapacity() const
{
    return capacity;
}
//======================================
void Event::displayDetails() const
{
    cout << "Event ID: " << eventID << endl;
    cout << "Name: " << name << endl;
    cout << "Description: " << description << endl;
    cout << "Date: " << date << endl;
    cout << "Time: " << time << endl;
    cout << "Location: " << location << endl;
    cout << "Capacity: " << capacity << endl;
}
//======================================
