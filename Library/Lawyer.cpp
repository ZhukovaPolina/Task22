#include "Lawyer.h"
#include "Case.h"
#include <string>
#include <sstream>
#include <iomanip>

Lawyer::Lawyer(const std::string& name, const std::string& specialization, double rate)
    : Person(name), specialization(specialization), isAvailable(true), hourlyRate(rate) {}

std::string Lawyer::getInfo() const {
    std::ostringstream oss;
    oss << "Адвокат " << getFullName() 
        << ", специализация: " << specialization 
        << ", ставка: " << std::fixed << std::setprecision(2) << hourlyRate << " руб/час"
        << ", дел: " << getCaseCount();
    return oss.str();
}

std::string Lawyer::getRole() const {
    return "Адвокат";
}

std::string Lawyer::getSpecialization() const {
    return specialization;
}

bool Lawyer::getIsAvailable() const {
    return isAvailable;
}

double Lawyer::getHourlyRate() const {
    return hourlyRate;
}

void Lawyer::assignCase(Case* casePtr) {
    addCase(casePtr);
    isAvailable = false;
}

void Lawyer::completeCase(Case* casePtr) {
    removeCase(casePtr);
    isAvailable = getCaseCount() == 0;
}

void Lawyer::setAvailability(bool available) {
    isAvailable = available;
}

void Lawyer::setHourlyRate(double rate) {
    hourlyRate = rate;
}
