
#include "Registration.h"

Registration::Registration(
    const std::string& studentId,
    const std::string& eventId,
    const std::string& registrationDate,
    bool active)
    : studentId(studentId),
      eventId(eventId),
      registrationDate(registrationDate),
      active(active) {
}

const std::string& Registration::getStudentId() const {
    return studentId;
}

const std::string& Registration::getEventId() const {
    return eventId;
}

const std::string& Registration::getRegistrationDate() const {
    return registrationDate;
}

bool Registration::isActive() const {
    return active;
}

void Registration::cancel() {
    active = false;
}

void Registration::reactivate(const std::string& newDate) {
    registrationDate = newDate;
    active = true;
}
