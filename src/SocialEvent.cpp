#include "SocialEvent.h"
#include <iostream>
using namespace std;

// SocialEvent is a type of Event that also has
// a theme and whether there's food.

//======================================
// Constructor
// Sends the basic event info to Event, then saves
// the theme and food info here.
//======================================
SocialEvent::SocialEvent(const string& eventID, const string& name,
                         const string& description, const string& date,
                         const string& time, const string& location,
                         int capacity, const string& theme,
                         bool foodProvided)
    : Event(eventID, name, description, date, time, location, capacity)
{
    this->theme = theme;
    this->foodProvided = foodProvided;
}

//======================================
// Gets the theme
//======================================
string SocialEvent::getTheme() const
{
    return theme;
}

//======================================
// Tells you if there's food
//======================================
bool SocialEvent::isFoodProvided() const
{
    return foodProvided;
}

//======================================
// Shows the normal event info, then the
// theme and whether there's food
//======================================
void SocialEvent::displayDetails() const
{
    Event::displayDetails();

    cout << "Theme: " << theme << endl;
    if (foodProvided)
        cout << "Food Provided: Yes" << endl;
    else
        cout << "Food Provided: No" << endl;
}
