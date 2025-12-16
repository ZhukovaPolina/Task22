#include "Client.h"
#include "Case.h"
#include <algorithm>
#include <sstream>
#include <iostream>

Client::Client(const std::string& name, int age, const std::string& contact)
    : Person(name, age), contactInfo(contact) {}

std::string Client::getContactInfo() const { return contactInfo; }

const std::vector<Case*>& Client::getCases() const { return cases; }

void Client::setContactInfo(const std::string& contact) { contactInfo = contact; }

void Client::addCase(Case* newCase) {
    if (newCase && std::find(cases.begin(), cases.end(), newCase) == cases.end()) {
        cases.push_back(newCase);
        newCase->setClient(this);
        
        std::cout << "Case " << newCase->getCaseId() 
                  << " added to client " << getName() << std::endl;
    }
}

void Client::removeCase(Case* caseToRemove) {
    if (!caseToRemove) return;
    
    auto it = std::find(cases.begin(), cases.end(), caseToRemove);
    if (it != cases.end()) {
        cases.erase(it);
        caseToRemove->setClient(nullptr);
        
        std::cout << "Case " << caseToRemove->getCaseId() 
                  << " removed from client " << getName() << std::endl;
    }
}

bool Client::hasCase(const std::string& caseId) const {
    for (const auto& casePtr : cases) {
        if (casePtr && casePtr->getCaseId() == caseId) {
            return true;
        }
    }
    return false;
}

int Client::getCasesCount() const {
    return cases.size();
}

std::string Client::toString() const {
    std::stringstream ss;
    ss << Person::toString() << "\n"
       << "Contact: " << contactInfo << "\n"
       << "Cases: " << getCasesCount();
    
    if (!cases.empty()) {
        ss << "\nActive Cases:";
        for (const auto& casePtr : cases) {
            if (casePtr) {
                ss << "\n  - " << casePtr->getCaseId() 
                   << " (" << casePtr->getStatus() << ")";
            }
        }
    }
    
    return ss.str();
}
