#include <iostream>
#include <string>
#include <memory>
#include "EventSystem.h"
#include "FileManager.h"
#include "AcademicEvent.h"
#include "CareerEvent.h"
#include "ClubEvent.h"
#include "SocialEvent.h"

using namespace std;

//=================== Input helpers ===================
// Reads a whole line of text after showing a prompt.
string readLine(const string& prompt)
{
    cout << prompt;
    string text;
    getline(cin, text);
    return text;
}

// Keeps asking until the user types a whole number.
// This stops the program from breaking when someone types letters.
int readInt(const string& prompt)
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
        catch (...)
        {
        }
        cout << "Please enter a whole number." << endl;
    }
}

//=================== Menu actions ===================
void createEvent(EventSystem& system)
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
        event = make_unique<AcademicEvent>(id, name, description, date, time, location,
                                           organizerID, capacity, department, speaker);
    }
    else if (type == 2)
    {
        string company = readLine("Enter company name: ");
        string recruiter = readLine("Enter recruiter name: ");
        event = make_unique<CareerEvent>(id, name, description, date, time, location,
                                         organizerID, capacity, company, recruiter);
    }
    else if (type == 3)
    {
        string club = readLine("Enter club name: ");
        event = make_unique<ClubEvent>(id, name, description, date, time, location,
                                       organizerID, capacity, club);
    }
    else
    {
        string theme = readLine("Enter theme: ");
        string food = readLine("Is food provided? (y/n): ");
        bool foodProvided = (food == "y" || food == "Y");
        event = make_unique<SocialEvent>(id, name, description, date, time, location,
                                         organizerID, capacity, theme, foodProvided);
    }

    // addEvent prints its own error if the ID is taken or the organizer doesn't exist
    if (system.addEvent(std::move(event)))
    {
        cout << "Event created successfully." << endl;
    }
}

void searchEvents(const EventSystem& system)
{
    string search = readLine("Enter part of the event name: ");

    bool foundAny = false;
    for (const auto& event : system.getEvents())
    {
        if (event->getName().find(search) != string::npos)
        {
            cout << "-----------------" << endl;
            event->displayDetails();
            foundAny = true;
        }
    }

    if (!foundAny)
    {
        cout << "No events matched \"" << search << "\"." << endl;
    }
}

void viewOrganizerEvents(const EventSystem& system)
{
    string id = readLine("Enter organizer ID: ");
    if (system.findOrganizer(id) == nullptr)
    {
        cout << "Organizer not found." << endl;
        return;
    }

    bool foundAny = false;
    for (const auto& event : system.getEvents())
    {
        if (event->getOrganizerID() == id)
        {
            cout << "- " << event->getEventID() << ": " << event->getName() << endl;
            foundAny = true;
        }
    }

    if (!foundAny)
    {
        cout << "This organizer has no events." << endl;
    }
}

void showReports(const EventSystem& system)
{
    cout << "1. Events with available capacity" << endl;
    cout << "2. Full events" << endl;
    cout << "3. Registrations per event" << endl;
    cout << "4. Students registered for multiple events" << endl;
    int report = readInt("Enter report: ");

    switch (report)
    {
        case 1: system.reportEventsWithSpace(); break;
        case 2: system.reportFullEvents(); break;
        case 3: system.reportRegistrationsPerEvent(); break;
        case 4: system.reportStudentsInMultipleEvents(); break;
        default: cout << "Invalid report." << endl;
    }
}

//=================== Main ===================
int main()
{
    EventSystem system;
    FileManager files;

    // Load everything saved from last time (FileManager handles the load order)
    files.loadAll(system);

    int choice;

    do
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
                createEvent(system);
                break;

            case 4:
                system.displayAllEvents();
                break;

            case 5:
                searchEvents(system);
                break;

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
                system.displayStudentRegistrations(readLine("Enter student ID: "));
                break;

            case 9:
                system.displayEventAttendees(readLine("Enter event ID: "));
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
                viewOrganizerEvents(system);
                break;

            // Reports
            case 13:
                showReports(system);
                break;

            // Exit
            case 0:
                // Save everything before closing
                if (files.saveAll(system))
                {
                    cout << "Data saved." << endl;
                }
                else
                {
                    cout << "Error: could not save data. Make sure the data folder exists." << endl;
                }
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid selection." << endl;
        }

    } while (choice != 0);

    return 0;
}