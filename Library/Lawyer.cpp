#include "Lawyer.h"
#include "Case.h"
#include <algorithm>
#include <sstream>
#include <iostream>

Lawyer::Lawyer(const std::string& name, int age, const std::string& spec,
               double rate, bool available)
    : Person(name, age), specialization(spec), 
      hourlyRate(rate), isAvailable(available) {}

std::string Lawyer::getSpecialization() const { return specialization; }
bool Lawyer::getAvailability() const { return isAvailable; }
double Lawyer::getHourlyRate() const { return hourlyRate; }

const std::vector<Case*>& Lawyer::getCases() const { return cases; }

void Lawyer::setSpecialization(const std::string& spec) { specialization = spec; }
void Lawyer::setAvailability(bool available) { isAvailable = available; }
void Lawyer::setHourlyRate(double rate) { hourlyRate = rate; }

void Lawyer::addCase(Case* newCase) {
    if (newCase && std::find(cases.begin(), cases.end(), newCase) == cases.end()) {
        cases.push_back(newCase);
        newCase->setLawyer(this);
        
        if (isAvailable && !cases.empty()) {
            isAvailable = false;
        }
        
        std::cout << "Case " << newCase->getCaseId() 
                  << " added to lawyer " << getName() << std::endl;
    }
}

void Lawyer::removeCase(Case* caseToRemove) {
    if (!caseToRemove) return;
    
    auto it = std::find(cases.begin(), cases.end(), caseToRemove);
    if (it != cases.end()) {
        cases.erase(it);
        caseToRemove->setLawyer(nullptr);
        
        std::cout << "Case " << caseToRemove->getCaseId() 
                  << " removed from lawyer " << getName() << std::endl;
    }
    
    if (cases.empty()) {
        isAvailable = true;
    }
}

bool Lawyer::hasCase(const std::string& caseId) const {
    for (const auto& casePtr : cases) {
        if (casePtr && casePtr->getCaseId() == caseId) {
            return true;
        }
    }
    return false;
}

int Lawyer::getCasesCount() const {
    return cases.size();
}

double Lawyer::calculateEstimatedCost(double hours) const {
    return hourlyRate * hours;
}

void Lawyer::toggleAvailability() {
    isAvailable = !isAvailable;
}

std::string Lawyer::toString() const {
    std::stringstream ss;
    ss << Person::toString() << "\n"
       << "Specialization: " << specialization << "\n"
       << "Hourly Rate: $" << hourlyRate << "\n"
       << "Available: " << (isAvailable ? "Yes" : "No") << "\n"
       << "Active Cases: " << getCasesCount();
    
    if (!cases.empty()) {
        ss << "\nCases:";
        for (const auto& casePtr : cases) {
            if (casePtr) {
                ss << "\n  - " << casePtr->getCaseId() 
                   << " (" << casePtr->getStatus() << ")";
            }
        }
    }
    
    return ss.str();
}
