#include "Client.h"
#include "Case.h"
#include <string>

Client::Client(const std::string& name, const std::string& contact)
    : Person(name), contactInfo(contact) {}

std::string Client::getInfo() const {
    return "Клиент " + getFullName() + ", контакты: " + contactInfo;
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
    for (const auto& casePtr : cases) {
        services.push_back(casePtr->getServiceCategory());
    }
    return services;
}

int Client::getCaseCount() const {
    return cases.size();
}