#ifndef ORGANIZER_H
#define ORGANIZER_H
#include <string>

class Organizer
{
    private:
        std::string organizerId;
        std::string name, email;
        std::string department;

    public:
        Organizer();
        Organizer( const std::string organizerId, const std::string name,
                   const std::string email, const std::string department );

        std::string getOrganizerId() const;
        std::string getName() const;
        std::string getEmail() const;
        std::string getDepartment() const;

        void setName( const std::string name );
        void setEmail( const std::string email );
        void setDepartment( const std::string department );

        void display() const;

};

#endif