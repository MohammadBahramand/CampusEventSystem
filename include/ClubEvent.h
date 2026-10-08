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
    ClubEvent(const string& id,
          const string& eventName,
          const string& eventDescription,
          const string& eventDate,
          const string& eventTime,
          const string& eventLocation,
          int eventCapacity,
          const string& club);

    string getClubName() const;

    void displayDetails() const override;
};

#endif
