//============Student.cpp=========
// Contains the actual code for the functions declared in Student.h
//============================================================

#include "Student.h"   
#include <iostream>    

using namespace std;

//this function belongs to the Student class
//The constructor uses an "initializer list" to set each of the four private fields
//while the object is being built.

Student::Student(const string& id, const string& name,
                 const string& email, const string& major)
    : studentId(id), name(name), email(email), major(major) {
   
}

//===========GETTERS========================
//Each one  returns the matching private field.
//const at the end promises the function won't change the Student.
//==========================================
const string& Student::getId() const    { return studentId; }
const string& Student::getName() const  { return name; }
const string& Student::getEmail() const { return email; }
const string& Student::getMajor() const { return major; }

void Student::display() const {
    cout << "ID: " << studentId << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Major: " << major << endl;
}

//====== toFileString()========

string Student::toFileString() const {
    return studentId + "|" + name + "|" + email + "|" + major;
}