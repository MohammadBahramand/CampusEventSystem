#include <iostream>
#include "EventSystem.h"
#include "FileManager.h"
#include "Menu.h"

using namespace std;

int main()
{
    EventSystem system;
    FileManager files;

    // Load everything saved from last time
    files.loadAll(system);

    // Run the menu until the user picks 0
    Menu menu(system);
    menu.run();

    // Save everything before closing
    if (files.saveAll(system))
    {
        cout << "Data saved." << endl;
    }
    else
    {
        cout << "Error: could not save data. Make sure the data folder exists." << endl;
    }

    return 0;
}