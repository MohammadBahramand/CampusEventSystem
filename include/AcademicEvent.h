#ifndef ACADEMICEVENT_H
#define ACADEMICEVENT_H

#include "Event.h"
#include <string>
using namespace std;

class AcademicEvent : public Event
{
private: 
  string department;
  string speaker;
public:
  AcademicEvent(const string& id,
                const string& eventName;
                const string& eventDescription,
                const string& eventDate,
                const string& eventTime,
                const string& eventLocation,
                int eventCapacity,
                const string& eventDepartment,
                const string& eventSpeaker);

  const string& getDepartment() const;
  const string& getSpeaker() const;

  void displayDetails() const override;
};

#endif
