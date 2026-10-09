#include "ClubEvent.h"
#include <iostream>
using namespace std;

ClubEvent::ClubEvent(const string& id,
                     const string& eventName,
                     const string& eventDescription,
                     const string& eventDate,
                     const string& eventTime,
                     const string& eventLocation,
                     int eventCapacity,
                     const string& club)
    : Event(id, eventName, eventDescription,
            eventDate, eventTime,
            eventLocation, eventCapacity)
{
    clubName = club;
}
const string& ClubEvent::getClubName() const
{
    return clubName;
}

void ClubEvent::displayDetails() const
{
    Event::displayDetails();

    cout << "Club Name: " << clubName << endl;
}
