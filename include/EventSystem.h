//================EventSystem.h==================
//coordinator class owns all the students
//Responsible for adding, searching, and displaying students
//================================================
#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include <vector>   
#include <memory>  
#include <string>
#include "Student.h"
#include "Organizer.h"
#include "Event.h"
#include "RegistrationManager.h"

using namespace std;

class EventSystem {
private:
    //EventSystem owns the students, so we use unique_ptr 
    //to manage memory automatically.
    vector<unique_ptr<Student>> students;

     vector<unique_ptr<Organizer>> organizers;

     vector<unique_ptr<Event>> events;
     RegistrationManager registrationManager;
public:
    //Adds a new student.
    //Returns true if added, false if that ID 
    //already exists

    bool addStudent(const string& id, const string& name,
                    const string& email, const string& major);

    //Looks up a student by ID.
    //Returns a pointer to the student,or nullptr if not found.
    //The function is const because searching 
    //doesn't change anything.
    Student* findStudent(const string& id) const;

    
    void displayStudent(const string& id) const;
    void displayAllStudents() const;

   
    const vector<unique_ptr<Student>>& getStudents() const;


    //=====Organizers========
    //Returns true if added, false if the organizer ID already exists.
    bool addOrganizer(const string& id, const string& name,
                      const string& email, const string& department);

    //Returns a pointer to the organizer, or nullptr if not found.

    Organizer* findOrganizer(const string& id) const;

    void displayOrganizer(const string& id) const;
    void displayAllOrganizers() const;

    //Read-only access to the organizers list
    const vector<unique_ptr<Organizer>>& getOrganizers() const;
    //=======Events======
    //Returns false, and adds nothing if the event ID
    //already exists or its organizer ID is not a known organizer
    bool addEvent(unique_ptr<Event> event);

    //Returns a pointer to the event, or nullptr if not found
    
    Event* findEvent(const string& id) const;
    void displayEvent(const string& id) const;
    void displayAllEvents() const;

    //Read-only access for FileManager code and reports
    const vector<unique_ptr<Event>>& getEvents() const;

    //===========Registrations=============
    //Registers a student for an event, prints the outcome and returns
    //true only if success
    bool registerStudent(const string& studentId, const string& eventId,
                         const string& date);

    //Cancels an existing registration, returns false if none exists.
    bool cancelRegistration(const string& studentId, const string& eventId);

    void displayStudentRegistrations(const string& studentId) const;
    void displayEventAttendees(const string& eventId) const;

    //active registrations for an event
    int getRegisteredCount(const string& eventId) const;

    //saving and loading registrations
    RegistrationManager& getRegistrationManager();
    const RegistrationManager& getRegistrationManager() const;

    //===========Reports==========
    //Events that still have open spots (shows registered / capacity).
    void reportEventsWithSpace() const;

    //Events that have no spots left.
    void reportFullEvents() const;

    //Every event with how many students are registered.
    void reportRegistrationsPerEvent() const;

    //Students registered for two or more events.
    void reportStudentsInMultipleEvents() const;

    //===========Search=============
    //Prints every event whose name contains the text (ignores upper and
    //lower case). Returns how many events matched.
    int searchEventsByName(const string& text) const;

};

#endif
