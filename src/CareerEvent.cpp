#include "CareerEvent.h"
#include <iostream>
using namespace std;

// CareerEvent is a type of Event that also has
// a company and a recruiter.

//======================================
// Constructor
// Sends the basic event info to Event, then saves
// the company and recruiter here.
//======================================
CareerEvent::CareerEvent(const string& eventID, const string& name,
                         const string& description, const string& date,
                         const string& time, const string& location,
                         int capacity, const string& companyName,
                         const string& recruiterName)
    : Event(eventID, name, description, date, time, location, capacity)
{
    this->companyName = companyName;
    this->recruiterName = recruiterName;
}

//======================================
// Gets the company name
//======================================
string CareerEvent::getCompanyName() const
{
    return companyName;
}

//======================================
// Gets the recruiter name
//======================================
string CareerEvent::getRecruiterName() const
{
    return recruiterName;
}

//======================================
// Shows the normal event info, then the
// company and recruiter
//======================================
void CareerEvent::displayDetails() const
{
    Event::displayDetails();

    cout << "Company: " << companyName << endl;
    cout << "Recruiter: " << recruiterName << endl;
}
