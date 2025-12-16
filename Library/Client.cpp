#include "Client.h"
#include "Case.h"
#include <string>
#include <algorithm>

Client::Client(const std::string& name, const std::string& contact)
    : Person(name), contactInfo(contact) {}

std::string Client::getInfo() const {
    return "Клиент " + getFullName() + ", контакты: " + contactInfo + 
           ", дел: " + std::to_string(getCaseCount());
}

std::string Client::getRole() const {
    return "Клиент";
}

std::string Client::getContactInfo() const {
    return contactInfo;
}

void Client::setContactInfo(const std::string& contact) {
    contactInfo = contact;
}

std::vector<std::string> Client::getServiceTypes() const {
    std::vector<std::string> services;
    for (Case* casePtr : getCases()) {
        if (casePtr) {
            services.push_back(casePtr->getServiceCategory());
        }
    }
    std::sort(services.begin(), services.end());
    services.erase(std::unique(services.begin(), services.end()), services.end());
    return services;
}
