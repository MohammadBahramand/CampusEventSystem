#ifndef CAREEREVENT_H
#define CAREEREVENT_H

#include "Event.h"

/*******************************************************
 * CareerEvent
 * this code adds the company hosting the event and the recruiter attending. 
 * event and the recruiter attending.
 *******************************************************/
class CareerEvent : public Event
{
private:
    string companyName;     // company hosting the event
    string recruiterName;   // recruiter attending

public:
    // Constructor: creates a career event with all its info
    CareerEvent(const string& eventID, const string& name,
                const string& description, const string& date,
                const string& time, const string& location,
                int capacity, const string& companyName,
                const string& recruiterName);

    // Accessors: returns the data without changing it
    string getCompanyName() const;
    string getRecruiterName() const;

    // Displays event info plus career details
    void displayDetails() const;
};

#endif