
#include "RegistrationManager.h"
#include "Student.h"
#include "Event.h"

RegistrationResult RegistrationManager::registerStudent(
    const Student* student,
    const Event* event,
    const std::string& registrationDate) {

    if (student == nullptr) {
        return RegistrationResult::StudentNotFound;
    }

    if (event == nullptr) {
        return RegistrationResult::EventNotFound;
    }

    if (registrationDate.empty()) {
        return RegistrationResult::InvalidDate;
    }

    const std::string& studentId = student->getId();
    const std::string& eventId = event->getEventID();

    if (isRegistered(studentId, eventId)) {
        return RegistrationResult::DuplicateRegistration;
    }

    if (getRegistrationCount(eventId) >= event->getCapacity()) {
        return RegistrationResult::EventFull;
    }

    for (Registration& registration : registrations) {
        if (registration.getStudentId() == studentId &&
            registration.getEventId() == eventId) {

            registration.reactivate(registrationDate);
            return RegistrationResult::Success;
        }
    }

    registrations.emplace_back(
        studentId, eventId, registrationDate);

    return RegistrationResult::Success;
}

bool RegistrationManager::cancelRegistration(
    const std::string& studentId,
    const std::string& eventId) {

    for (Registration& registration : registrations) {
        if (registration.getStudentId() == studentId &&
            registration.getEventId() == eventId &&
            registration.isActive()) {

            registration.cancel();
            return true;
        }
    }

    return false;
}

bool RegistrationManager::isRegistered(
    const std::string& studentId,
    const std::string& eventId) const {

    for (const Registration& registration : registrations) {
        if (registration.getStudentId() == studentId &&
            registration.getEventId() == eventId &&
            registration.isActive()) {

            return true;
        }
    }

    return false;
}

int RegistrationManager::getRegistrationCount(
    const std::string& eventId) const {

    int count = 0;

    for (const Registration& registration : registrations) {
        if (registration.getEventId() == eventId &&
            registration.isActive()) {

            ++count;
        }
    }

    return count;
}

std::vector<std::string>
RegistrationManager::getEventIdsForStudent(
    const std::string& studentId) const {

    std::vector<std::string> result;

    for (const Registration& registration : registrations) {
        if (registration.getStudentId() == studentId &&
            registration.isActive()) {

            result.push_back(registration.getEventId());
        }
    }

    return result;
}

std::vector<std::string>
RegistrationManager::getStudentIdsForEvent(
    const std::string& eventId) const {

    std::vector<std::string> result;

    for (const Registration& registration : registrations) {
        if (registration.getEventId() == eventId &&
            registration.isActive()) {

            result.push_back(registration.getStudentId());
        }
    }

    return result;
}

const std::vector<Registration>&
RegistrationManager::getAllRegistrations() const {
    return registrations;
}

bool RegistrationManager::addLoadedRegistration(
    const Registration& registration) {

    if (registration.getStudentId().empty() ||
        registration.getEventId().empty() ||
        registration.getRegistrationDate().empty()) {

        return false;
    }

    for (const Registration& existing : registrations) {
        if (existing.getStudentId() ==
                registration.getStudentId() &&
            existing.getEventId() ==
                registration.getEventId()) {

            return false;
        }
    }

    registrations.push_back(registration);
    return true;
}
