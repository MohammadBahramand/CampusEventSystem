#ifndef CLUBEVENT_H
#define CLUBEVENT_H

#include "Event.h"
#include <string>
using namespace std;

class ClubEvent : public Event
{
private:
    string clubName;

public:
    ClubEvent(string id, string eventName, string eventDescription,
              string eventDate, string eventTime,
              string eventLocation, int eventCapacity,
              string club);

    string getClubName() const;

    void displayDetails() const override;
};

#endif
