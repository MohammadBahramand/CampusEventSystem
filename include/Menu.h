#ifndef MENU_H
#define MENU_H

#include <string>
#include "EventSystem.h"

using namespace std;
class Menu
{
private:
    EventSystem& system;

    // Input helpers
    string readLine(const string& prompt) const;
    int readInt(const string& prompt) const;

    void showMenu() const;
    void createEvent();
    void showReports() const;

public:
    // Gets the EventSystem that main created
    Menu(EventSystem& system);

    // Shows the menu over and over until the user picks 0
    void run();
};

#endif