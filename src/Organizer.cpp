#include <iostream>
#include <string>
#include "Organizer.h"
using namespace std;


// Constructors
Organizer::Organizer()
{
    organizerID = "";
    name = "";
    email = "";
    department = "";
}

Organizer::Organizer( const std::string& organizerID, const std::string& name,
                      const std::string& email, const std::string& department )
{
    this->organizerID = organizerID;
    this->name = name;
    this->email = email;
    this->department = department;
}

// Getters
string Organizer::getOrganizerID() const
{
    return organizerID;
}

string Organizer::getName() const
{
    return name;
}

string Organizer::getEmail() const
{
    return email;
}

string Organizer::getDepartment() const
{
    return department;
}

// Setters
void Organizer::setName( const string& name )
{
        this->name = name;
}

void Organizer::setEmail( const string& email )
{
      this->email = email;
}

void Organizer::setDepartment( const string& department )
{    
    this->department = department;
}

// Displays organizer info
void Organizer::display() const 
{
    cout << "Organizer ID: " << organizerID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Department: " << department << endl;
}