
#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <string>

class Registration {
private:
    std::string studentId;
    std::string eventId;
    std::string registrationDate;
    bool active;

public:
    Registration(const std::string& studentId,
                 const std::string& eventId,
                 const std::string& registrationDate,
                 bool active = true);

    const std::string& getStudentId() const;
    const std::string& getEventId() const;
    const std::string& getRegistrationDate() const;

    bool isActive() const;

    void cancel();
    void reactivate(const std::string& newDate);
};

#endif
