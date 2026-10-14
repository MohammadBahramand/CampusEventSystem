//============= EventSystem.cpp=======
//=====================================

#include "EventSystem.h"
#include <iostream>

using namespace std;

//======================addStudent=======================
//Adds a new student, but only if the ID is not already used.
//=======================================================
bool EventSystem::addStudent(const string& id, const string& name,
                             const string& email, const string& major) {
    //refuse duplicates before creating anything.
    //findStudent returns nullptr when the ID is not in the list,
    //!= nullptr means "a student with this ID already exists"
    if (findStudent(id) != nullptr) {
        cout << "Error: a student with ID " << id << " already exists." << endl;
        return false;   // nothing was added
    }

    //creates the Student and store it.
    students.push_back(make_unique<Student>(id, name, email, major));
    return true;        
}

//===========findStudent=================
// Searches the list one student at a time
// ------------------------------------------------------------
Student* EventSystem::findStudent(const string& id) const {
   
    for (const auto& s : students) {
        if (s->getId() == id) {   //reaches the Student through the pointer
            return s.get();       //gives the plain pointer WITHOUT
                                  //giving up ownership
        }
    }
    return nullptr;               
}

//==============displayStudent====================
//
//================================================
void EventSystem::displayStudent(const string& id) const {
    Student* s = findStudent(id);

   //checks for nullptr so the user isn't shown a blank screen.
    if (s == nullptr) {
        cout << "Student not found." << endl;
        return;
    }

    s->display();
}

//===============displayAllStudents===================
// 
//=====================================================
void EventSystem::displayAllStudents() const {
    //handle the empty list so the user isn't shown a blank screen.
    if (students.empty()) {
        cout << "No students in the system." << endl;
        return;
    }

    int count = 1;   //numbering for the output
    for (const auto& s : students) {
        cout << "--- Student " << count << " ---" << endl;
        s->display();
        count++;
    }
}

//===========getStudents=======================
//Returns the list so the FileManager can read it when saving.
//=============================================
const vector<unique_ptr<Student>>& EventSystem::getStudents() const {
    return students;
}
// ==================== ORGANIZERS=========================
// ============================================================

//============addOrganizer==================
//Adds a new organizer, but only if the ID is not already used.
//=========================================
bool EventSystem::addOrganizer(const string& id, const string& name,
                               const string& email, const string& department) {
    //search first, create second.
    if (findOrganizer(id) != nullptr) {
        cout << "Error: an organizer with ID " << id << " already exists." << endl;
 return false;
    }

    //make_unique builds the Organizer on the heap and wraps it in a
    //unique_ptr. push_back moves ownership into the vector.
    organizers.push_back(make_unique<Organizer>(id, name, email, department));
    return true;
}

//=============findOrganizer=====================
//Linear search by ID, returns nullptr when nobody matches.
//===============================================
Organizer* EventSystem::findOrganizer(const string& id) const {
    for (const auto& o : organizers) {
        //organizer names its ID getter getOrganizerID(),
        //while Student uses getId(). Same idea, different name.
        if (o->getOrganizerID() == id) {
            return o.get();   // plain pointer, ownership stays here
        }
    }
    return nullptr;
}

//=================displayOrganizer===================
//
//=================================================
void EventSystem::displayOrganizer(const string& id) const {
    Organizer* o = findOrganizer(id);
    if (o == nullptr) {       // always check before using a pointer
        cout << "Organizer not found." << endl;
        return;
    }
    o->display();
}

//================displayAllOrganizers==============
//Prints every organizer numbered.
//=================================================
void EventSystem::displayAllOrganizers() const {
    if (organizers.empty()) {
        cout << "No organizers in the system." << endl;
        return;
    }
    int count = 1;
    for (const auto& o : organizers) {
        cout << "--- Organizer " << count << " ---" << endl;
        o->display();
        count++;
    }
}

//==============getOrganizers======================
// Read-only access for the FileManager code (saving to a file).
//============================================
const vector<unique_ptr<Organizer>>& EventSystem::getOrganizers() const {
    return organizers;
}

//====================EVENTS=========================
// ============================================================

//===============addEvent=========================
//Takes ownership of an event that the caller already built.
//Rejects it if the ID is taken or the organizer does not exist.
//================================================
bool EventSystem::addEvent(unique_ptr<Event> event) {
    if (event == nullptr) {
        cout << "Error: no event was provided." << endl;
        return false;
    }

 //Duplicate ID check
    if (findEvent(event->getEventID()) != nullptr) {
        cout << "Error: an event with ID " << event->getEventID() << " already exists." << endl;
        return false;
    }

    //we check here that this organizer really exists.
    if (findOrganizer(event->getOrganizerID()) == nullptr) {
        cout << "Error: organizer " << event->getOrganizerID() << " does not exist." << endl;
        return false;
    }

    // std::move hands ownership of the event into the vector. The
    // parameter is empty afterward, which is what unique_ptr requires.
    events.push_back(std::move(event));
    return true;
}

//================findEvent=====================
// Linear search by ID. Returns nullptr when nothing matches.
// ----------------------------------------
Event* EventSystem::findEvent(const string& id) const {
    for (const auto& e : events) {
        if (e->getEventID() == id) {
            return e.get();   // plain pointer, ownership stays here
        }
    }
    return nullptr;
}

//=====================displayEvent=====================
//Prints one event. displayDetails() is virtual, so the right
//subclass version runs even though we only hold an Event pointer.
//============================================
void EventSystem::displayEvent(const string& id) const {
    Event* e = findEvent(id);
    if (e == nullptr) {
        cout << "Event not found." << endl;
        return;
    }
    e->displayDetails();
}

//===========displayAllEvents===================
// Prints every event, numbered (polymorphism again).
//=========================================
void EventSystem::displayAllEvents() const {
    if (events.empty()) {
        cout << "No events in the system." << endl;
        return;
    }
    int count = 1;
    for (const auto& e : events) {
        cout << "--- Event " << count << " ---" << endl;
        e->displayDetails();
        count++;
    }
}

//================getEvents===================
// Read-only access for saving to a file and for reports.
//============================================
const vector<unique_ptr<Event>>& EventSystem::getEvents() const {
    return events;
}

//==================== REGISTRATIONS=========================
// ============================================================

//=============registerStudent=====================
//Looks up the student and the event, hands them to the
//RegistrationManager (which enforces the rules), and turns the
//result into a message. The manager prints nothing itself.
//=========================================
bool EventSystem::registerStudent(const string& studentId, const string& eventId,
                                  const string& date) {
    Student* student = findStudent(studentId);   // nullptr if not found
    Event* event = findEvent(eventId);           // nullptr if not found

    //manager handles nullptr, duplicates, capacity and a blank date.
    RegistrationResult result = registrationManager.registerStudent(student, event, date);

    switch (result) {
        case RegistrationResult::Success:
            cout << "Registration successful!" << endl;
            cout << "Student: " << student->getName() << endl;
            cout << "Event: " << event->getName() << endl;
            return true;
        case RegistrationResult::StudentNotFound:
            cout << "Error: student not found." << endl;
            break;
        case RegistrationResult::EventNotFound:
            cout << "Error: event not found." << endl;
            break;
        case RegistrationResult::DuplicateRegistration:
            cout << "Error: this student is already registered for this event." << endl;
            break;
        case RegistrationResult::EventFull:
            cout << "Error: this event is full." << endl;
            break;
        case RegistrationResult::InvalidDate:
            cout << "Error: a registration date is required." << endl;
            break;
    }
    return false;
}

//================cancelRegistration=================
// Delegates to the manager and reports the outcome.
//====================================================
bool EventSystem::cancelRegistration(const string& studentId, const string& eventId) {
    if (registrationManager.cancelRegistration(studentId, eventId)) {
        cout << "Registration canceled." << endl;
        return true;
    }
    cout << "Error: no active registration found for that student and event." << endl;
    return false;
}

//===========displayStudentRegistrations===================
// The manager returns event IDs; we look each one up for its name.
//=========================================
void EventSystem::displayStudentRegistrations(const string& studentId) const {
    Student* student = findStudent(studentId);
    if (student == nullptr) {
        cout << "Student not found." << endl;
        return;
    }

    vector<string> eventIds = registrationManager.getEventIdsForStudent(studentId);
    cout << "Student: " << student->getName() << endl;
    if (eventIds.empty()) {
        cout << "No registered events." << endl;
        return;
    }

    cout << "Registered Events:" << endl;
    int count = 1;
    for (const string& id : eventIds) {
        Event* event = findEvent(id);
        cout << count << ". " << (event != nullptr ? event->getName() : id) << endl;
        count++;
    }
}

// ==============displayEventAttendees==============
// The manager returns student IDs; we look each one up for a name.
//===================================================
void EventSystem::displayEventAttendees(const string& eventId) const {
    Event* event = findEvent(eventId);
    if (event == nullptr) {
        cout << "Event not found." << endl;
        return;
    }

    vector<string> studentIds = registrationManager.getStudentIdsForEvent(eventId);
    cout << "Event: " << event->getName() << endl;
    if (studentIds.empty()) {
        cout << "No registered students." << endl;
        return;
    }

    cout << "Registered Students:" << endl;
    int count = 1;
    for (const string& id : studentIds) {
        Student* student = findStudent(id);
        cout << count << ". " << (student != nullptr ? student->getName() : id) << endl;
        count++;
    }
}

//==========getRegisteredCount / getRegistrationManager=====
//=========================================
int EventSystem::getRegisteredCount(const string& eventId) const {
    return registrationManager.getRegistrationCount(eventId);
}

RegistrationManager& EventSystem::getRegistrationManager() {
    return registrationManager;
}

const RegistrationManager& EventSystem::getRegistrationManager() const {
    return registrationManager;
}
