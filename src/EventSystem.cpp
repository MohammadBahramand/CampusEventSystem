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
// ============================================================
// ORGANIZERS
// ============================================================

// ------------------------------------------------------------
// addOrganizer
// Adds a new organizer, but only if the ID is not already used.
// ------------------------------------------------------------
bool EventSystem::addOrganizer(const string& id, const string& name,
                               const string& email, const string& department) {
    // Same duplicate rule as students: search first, create second.
    if (findOrganizer(id) != nullptr) {
        cout << "Error: an organizer with ID " << id << " already exists." << endl;
        return false;   // nothing was added
    }

    // make_unique builds the Organizer on the heap and wraps it in a
    // unique_ptr. push_back moves ownership into the vector.
    organizers.push_back(make_unique<Organizer>(id, name, email, department));
    return true;
}

// ------------------------------------------------------------
// findOrganizer
// Linear search by ID. Returns nullptr when nobody matches.
// ------------------------------------------------------------
Organizer* EventSystem::findOrganizer(const string& id) const {
    for (const auto& o : organizers) {
        // NOTE: Organizer names its ID getter getOrganizerID(),
        // while Student uses getId(). Same idea, different name.
        if (o->getOrganizerID() == id) {
            return o.get();   // plain pointer, ownership stays here
        }
    }
    return nullptr;
}

// ------------------------------------------------------------
// displayOrganizer
// Prints one organizer, or a message if the ID doesn't exist.
// ------------------------------------------------------------
void EventSystem::displayOrganizer(const string& id) const {
    Organizer* o = findOrganizer(id);
    if (o == nullptr) {       // always check before using a pointer
        cout << "Organizer not found." << endl;
        return;
    }
    o->display();
}

// ------------------------------------------------------------
// displayAllOrganizers
// Prints every organizer, numbered.
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// getOrganizers
// Read-only access for the FileManager code (saving to a file).
// ------------------------------------------------------------
const vector<unique_ptr<Organizer>>& EventSystem::getOrganizers() const {
    return organizers;
}
