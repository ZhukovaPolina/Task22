#include "Lawyer.h"
#include "Case.h"
#include <string>

Lawyer::Lawyer(const std::string& name, const std::string& specialization, double rate)
    : Person(name), specialization(specialization), isAvailable(true), hourlyRate(rate) {}

std::string Lawyer::getInfo() const {
    return "Адвокат " + getFullName() + ", специализация: " + specialization +
        ", ставка: " + std::to_string(hourlyRate) + " руб/час";
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

int Lawyer::getCaseCount() const {
    return cases.size();
}

void Lawyer::assignCase(Case* casePtr) {
    cases.push_back(casePtr);
    isAvailable = false;
}

void Lawyer::removeCase(Case* casePtr) {
    auto it = std::find(cases.begin(), cases.end(), casePtr);
    if (it != cases.end()) {
        cases.erase(it);
    }
    isAvailable = cases.empty();
}

void Lawyer::setAvailability(bool available) {
    isAvailable = available;
}

void Lawyer::setHourlyRate(double rate) {
    hourlyRate = rate;
}