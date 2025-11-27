#include "Lawyer.h"
#include "Case.h"

Lawyer::Lawyer(const std::string& lawyerName, const std::string& lawyerSpecialization)
    : name(lawyerName), specialization(lawyerSpecialization), isAvailable(true) {}

std::string Lawyer::getName() const {
    return name;
}

std::string Lawyer::getSpecialization() const {
    return specialization;
}

bool Lawyer::getIsAvailable() const {
    return isAvailable;
}

void Lawyer::assignCase(Case* casePtr) {
    assignedCases.push_back(casePtr);
    isAvailable = false;
}

void Lawyer::removeCase(Case* casePtr) {
    for (auto it = assignedCases.begin(); it != assignedCases.end(); ++it) {
        if (*it == casePtr) {
            assignedCases.erase(it);
            break;
        }
    }
    isAvailable = assignedCases.empty();
}

void Lawyer::setAvailability(bool available) {
    isAvailable = available;
}

int Lawyer::getCaseCount() const {
    return assignedCases.size();
}