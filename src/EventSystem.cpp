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