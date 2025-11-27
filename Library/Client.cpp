#include "Client.h"
#include "Case.h"

Client::Client(const std::string& clientName, const std::string& clientContact)
    : name(clientName), contactInfo(clientContact) {}

std::string Client::getName() const {
    return name;
}

std::string Client::getContactInfo() const {
    return contactInfo;
}

void Client::addCase(Case* casePtr) {
    cases.push_back(casePtr);
}

std::vector<std::string> Client::getServiceTypes() const {
    std::vector<std::string> services;
    for (const auto& casePtr : cases) {
        services.push_back(casePtr->getServiceType());
    }
    return services;
}