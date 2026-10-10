#include "AcademicEvent.h:
#include <iostream>

using namespace std;
//==============================================
AcademicEvent::AcademicEvent(const string& id,
                             const string& eventName,
                             const string& eventDescription,
                             const string& eventDate,
                             const string& eventTime,
                             const string& eventLocation,
                             int eventCapacity,
                             const string& eventDepartment,
                             const string& eventSpeaker)
    : Event(id, eventName, eventDescription,
            eventDate, eventTime,
            eventLocation, eventCapacity)
{
  department = eventDepartment;
  speaker = eventSpeaker;
}
//==============================================
const string& AcademicEvent::getDepartment() const
{
    return department;
}
//==============================================
const string& AcademicEvent::getSpeaker() const
{
    return speaker;
}
//==============================================
void AcademicEvent::displayDetails() const
{
    Event::displayDetails();

    cout << "Department: " << department << endl;
    cout << "Speaker: " << speaker << endl;
}
//==============================================
