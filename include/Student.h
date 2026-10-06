// ================Student.h=======================
// Declares the Student class:1 student's information.
//The actual function code goes in Student.cpp.
// ============================================================


#ifndef STUDENT_H
#define STUDENT_H

#include <string>   

using namespace std;   

class Student {
private:
    //only functions inside this class can touch these.
    //outside code can't change a student's
    //data directly, it must go through our public functions
    string studentId;   
    string name;        
    string email;       
    string major;       

public:
    //contrusctor runs when a Student object is created and fills
    // in all four fields.
    //pass by reference
    Student(const string& id, const string& name,
            const string& email, const string& major);

    //getters that let other classes read the private data.
    //const after the parentheses so  this function doesnt
    //change the Student 
    const string& getId() const;
    const string& getName() const;
    const string& getEmail() const;
    const string& getMajor() const;

    
    void display() const;

    //Converts the student into one line of text for the save file.
    //FileManager teammate calls this when saving students.txt.
    string toFileString() const;
};

#endif