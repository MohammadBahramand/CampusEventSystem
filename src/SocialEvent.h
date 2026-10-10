#ifndef SOCIALEVENT_H
#define SOCIALEVENT_H

#include "Event.h"

// SocialEvent is a type of Event that also has
// a theme and whether there's food.
class SocialEvent : public Event
{
private:
    string theme;        // like "Halloween" or "Movie Night"
    bool foodProvided;   // true if there's food

public:
    // Constructor: makes a social event with all its info
    SocialEvent(const string& eventID, const string& name,
                const string& description, const string& date,
                const string& time, const string& location,
                int capacity, const string& theme,
                bool foodProvided);

    // Getters
    string getTheme() const;
    bool isFoodProvided() const;

    // Shows the normal event info, then the theme and food
    void displayDetails() const;
};

#endif
