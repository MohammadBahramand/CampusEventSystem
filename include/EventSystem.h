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

using namespace std;

class EventSystem {
private:
    //EventSystem owns the students, so we use unique_ptr 
    //to manage memory automatically.
    vector<unique_ptr<Student>> students;

     vector<unique_ptr<Organizer>> organizers;
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

};

#endif
