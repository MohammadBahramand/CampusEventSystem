#include <iostream>
#include <string>
#include "EventSystem.h"

using namespace std;

int main()
{
    EventSystem system;

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
        cout << "12. System Reports" << endl;
        cout << "0. Exit" << endl;

        cout << "\nEnter selection: ";
        cin >> choice;

        switch (choice)
        {
            // Students
            case 1:
            {
                string id;
                string name;
                string email;
                string major;

                cout << "Enter student ID: ";
                cin >> id;
                cin.ignore();

                cout << "Enter name: ";
                getline(cin, name);

                cout << "Enter email: ";
                getline(cin, email);

                cout << "Enter major: ";
                getline(cin, major);

                if (system.addStudent(id, name, email, major))
                {
                    cout << "Student added successfully." << endl;
                }

                break;
            }

            case 2:
            {
                system.displayAllStudents();
                break;
            }

            // Events
            case 3:
            {
                cout << "Create Event is not connected yet." << endl;
                break;
            }

            case 4:
            {
                // system.displayAllEvents();

                cout << "View Events is not connected yet." << endl;
                break;
            }

            case 5:
            {
                cout << "Search Events is not connected yet." << endl;
                break;
            }

            // Registrations
            case 6:
            {
                cout << "Registration is not connected yet." << endl;
                break;
            }

            case 7:
            {
                cout << "Cancel Registration is not connected yet." << endl;
                break;
            }

            case 8:
            {
                cout << "Student Registrations is not connected yet." << endl;
                break;
            }

            case 9:
            {
                cout << "Event Attendees is not connected yet." << endl;
                break;
            }

            // Organizers
            case 10:
            {
                string organizerID;
                string name;
                string email;
                string department;

                cout << "Enter organizer ID: ";
                cin >> organizerID;
                cin.ignore();

                cout << "Enter name: ";
                getline(cin, name);

                cout << "Enter email: ";
                getline(cin, email);

                cout << "Enter department: ";
                getline(cin, department);

                cout << "Organizer management is not connected yet." << endl;

                break;
            }

            case 11:
            {
                cout << "View Organizers is not connected yet." << endl;
                break;
            }

            // Reports
            case 12:
            {
                cout << "Reports are not connected yet." << endl;
                break;
            }

            // Exit
            case 0:
            {
                cout << "Exiting program..." << endl;
                break;
            }

            default:
            {
                cout << "Invalid selection." << endl;
            }
        }

    } 
    
    while (choice != 0);

    return 0;
}