#include <iostream>
#include <string>
#include <memory>

#include "Menu.h"
#include "AcademicEvent.h"
#include "CareerEvent.h"
#include "ClubEvent.h"
#include "SocialEvent.h"

using namespace std;

// Constructor 
Menu::Menu(EventSystem& system) : system(system) {}

//Input helpers 
string Menu::readLine(const string& prompt) const
{
    string text;

    cout << prompt;
    getline(cin, text);

    return text;
}

// Keeps asking until the user types a whole number.
int Menu::readInt(const string& prompt) const
{
    while (true)
    {
        string text = readLine(prompt);

        try
        {
            size_t used = 0;
            int value = stoi(text, &used);

            if (used == text.size())
            {
                return value;
            }
        }
        catch (...) {}

        cout << "Please enter a whole number." << endl;
    }
}

// Menu display 
void Menu::showMenu() const
{
    cout << "\n====================================" << endl;
    cout << " CAMPUS EVENT MANAGEMENT SYSTEM" << endl;
    cout << "====================================" << endl;

    cout << "1. Add Student" << endl;
    cout << "2. View Students" << endl;
    cout << "3. Create Event" << endl;
    cout << "4. View Events" << endl;
    cout << "5. Search Events" << endl;
    cout << "6. Register Student for Event" << endl;
    cout << "7. Cancel Registration" << endl;
    cout << "8. View Student Registrations" << endl;
    cout << "9. View Event Attendees" << endl;
    cout << "10. Add Organizer" << endl;
    cout << "11. View Organizers" << endl;
    cout << "12. View Events by Organizer" << endl;
    cout << "13. System Reports" << endl;
    cout << "0. Exit" << endl;
}

// Menu actions 
void Menu::createEvent()
{
    cout << "Event type:" << endl;
    cout << "1. Academic" << endl;
    cout << "2. Career" << endl;
    cout << "3. Club" << endl;
    cout << "4. Social" << endl;

    int type = readInt("Enter type: ");

    if (type < 1 || type > 4)
    {
        cout << "Invalid event type." << endl;
        return;
    }

    string id = readLine("Enter event ID: ");
    string name = readLine("Enter name: ");
    string description = readLine("Enter description: ");
    string date = readLine("Enter date (YYYY-MM-DD): ");
    string time = readLine("Enter time (HH:MM): ");
    string location = readLine("Enter location: ");
    string organizerID = readLine("Enter organizer ID: ");

    int capacity = readInt("Enter capacity: ");

    if (capacity <= 0)
    {
        cout << "Capacity must be greater than 0." << endl;
        return;
    }

    unique_ptr<Event> event;

    if (type == 1)
    {
        string department = readLine("Enter department: ");
        string speaker = readLine("Enter speaker: ");

        event = make_unique<AcademicEvent>
        (
            id, name, description, date, time, location,
            organizerID, capacity, department, speaker
        );
    }
    else if (type == 2)
    {
        string company = readLine("Enter company name: ");
        string recruiter = readLine("Enter recruiter name: ");

        event = make_unique<CareerEvent>
        (
            id, name, description, date, time, location,
            organizerID, capacity, company, recruiter
        );
    }
    else if (type == 3)
    {
        string club = readLine("Enter club name: ");

        event = make_unique<ClubEvent>
        (
            id, name, description, date, time, location,
            organizerID, capacity, club
        );
    }
    else
    {
        string theme = readLine("Enter theme: ");
        string food = readLine("Is food provided? (y/n): ");

        bool foodProvided = (food == "y" || food == "Y");

        event = make_unique<SocialEvent>
        (
            id, name, description, date, time, location,
            organizerID, capacity, theme, foodProvided
        );
    }

    // addEvent prints its own error if the ID is taken or the organizer doesn't exist
    if (system.addEvent(move(event)))
    {
        cout << "Event created successfully." << endl;
    }
}

void Menu::showReports() const
{
    cout << "1. Events with available capacity" << endl;
    cout << "2. Full events" << endl;
    cout << "3. Registrations per event" << endl;
    cout << "4. Students registered for multiple events" << endl;

    int report = readInt("Enter report: ");

    switch (report)
    {
        case 1:
            system.reportEventsWithSpace();
            break;

        case 2:
            system.reportFullEvents();
            break;

        case 3:
            system.reportRegistrationsPerEvent();
            break;

        case 4:
            system.reportStudentsInMultipleEvents();
            break;

        default:
            cout << "Invalid report." << endl;
    }
}

// Shows the menu and runs until they pick 0
void Menu::run()
{
    int choice;

    do
    {
        showMenu();
        choice = readInt("\nEnter selection: ");

        switch (choice)
        {
            // Students
            case 1:
            {
                string id = readLine("Enter student ID: ");
                string name = readLine("Enter name: ");
                string email = readLine("Enter email: ");
                string major = readLine("Enter major: ");

                if (system.addStudent(id, name, email, major))
                {
                    cout << "Student added successfully." << endl;
                }

                break;
            }

            case 2:
                system.displayAllStudents();
                break;

            // Events
            case 3:
                createEvent();
                break;

            case 4:
                system.displayAllEvents();
                break;

            case 5:
            {
                string search = readLine("Enter part of the event name: ");
                system.searchEventsByName(search);
                break;
            }

            // Registrations
            case 6:
            {
                string studentId = readLine("Enter student ID: ");
                string eventId = readLine("Enter event ID: ");
                string date = readLine("Enter registration date (YYYY-MM-DD): ");

                system.registerStudent(studentId, eventId, date);

                break;
            }

            case 7:
            {
                string studentId = readLine("Enter student ID: ");
                string eventId = readLine("Enter event ID: ");

                system.cancelRegistration(studentId, eventId);

                break;
            }

            case 8:
                system.displayStudentRegistrations(
                    readLine("Enter student ID: ")
                );
                break;

            case 9:
                system.displayEventAttendees(
                    readLine("Enter event ID: ")
                );
                break;

            // Organizers
            case 10:
            {
                string id = readLine("Enter organizer ID: ");
                string name = readLine("Enter name: ");
                string email = readLine("Enter email: ");
                string department = readLine("Enter department: ");

                if (system.addOrganizer(id, name, email, department))
                {
                    cout << "Organizer added successfully." << endl;
                }

                break;
            }

            case 11:
                system.displayAllOrganizers();
                break;

            case 12:
            {
                string organizerId = readLine("Enter organizer ID: ");
                system.displayEventsByOrganizer(organizerId);
                break;
            }

            // Reports
            case 13:
                showReports();
                break;

            // Exit 
            case 0:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid selection." << endl;
        }

    } while (choice != 0);
}