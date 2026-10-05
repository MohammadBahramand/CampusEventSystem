#include <iostream>
#include <string>
#include "Organizer.h"
using namespace std;

Organizer::Organizer()
{
    organizerId = "";
    name = "";
    email = "";
    department = "";
}

Organizer::Organizer( const std::string& organizerId, const std::string& name,
                      const std::string& email, const std::string& department )
{
    this->organizerId= organizerId;
    this->name = name;
    this->email = email;
    this->department = department;
}


string Organizer::getOrganizerId() const
{
    return organizerId;
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


void Organizer::setName( const string& name )
{
        this->name= name;
}

void Organizer::setEmail( const string& email )
{
      this->email = email;
}

void Organizer::setDepartment( const string& department )
{    
    this->department = department;
}


void Organizer::display() const 
{
    cout << "Organizer ID: " << organizerId << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Department: " << department << endl;
}