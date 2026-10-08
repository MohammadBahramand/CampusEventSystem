#include "Event.h"
#include <iostream>
using namespace std;

Event::Event(const string& id,
             const string& eventName,
             const string& eventDescription,
             const string& eventDate,
             const string& eventTime,
             const string& eventLocation,
             int eventCapacity)
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
const string& Event::getEventID() const
{
    return eventID;
}
//======================================
const string& Event::getName() const
{
    return name;
}
//======================================
const string& Event::getDescription() const
{
    return description;
}
//======================================
const string& Event::getDate() const
{
    return date;
}
//======================================
const string& Event::getTime() const
{
    return time;
}
//======================================
const string& Event::getLocation() const
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
