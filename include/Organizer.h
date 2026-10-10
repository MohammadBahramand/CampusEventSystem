#ifndef ORGANIZER_H
#define ORGANIZER_H
#include <string>
using namespace std;

class Organizer
{
   
    private:
        string organizerID;
        string name;
        string email;
        string department;

    public:

        // Constructors
        Organizer();
        Organizer( const string& organizerID, const string& name,
                   const string& email, const string& department );

        // Getters
        string getOrganizerID() const;
        string getName() const;
        string getEmail() const;
        string getDepartment() const;

        // Setters
        void setName( const string& name );
        void setEmail( const string& email );
        void setDepartment( const string& department );
        
        // Displays organizer info
        void display() const;

};

#endif