
#ifndef REGISTRATION_MANAGER_H
#define REGISTRATION_MANAGER_H

#include <string>
#include <vector>
#include "Registration.h"

class Student;
class Event;

enum class RegistrationResult {
    Success,
    StudentNotFound,
    EventNotFound,
    DuplicateRegistration,
    EventFull,
    InvalidDate
};

class RegistrationManager {
private:
    std::vector<Registration> registrations;

public:
    RegistrationResult registerStudent(
        const Student* student,
        const Event* event,
        const std::string& registrationDate);

    bool cancelRegistration(
        const std::string& studentId,
        const std::string& eventId);

    bool isRegistered(
        const std::string& studentId,
        const std::string& eventId) const;

    int getRegistrationCount(
        const std::string& eventId) const;

    std::vector<std::string> getEventIdsForStudent(
        const std::string& studentId) const;

    std::vector<std::string> getStudentIdsForEvent(
        const std::string& eventId) const;

    const std::vector<Registration>&
    getAllRegistrations() const;

    bool addLoadedRegistration(
        const Registration& registration);
};

#endif
