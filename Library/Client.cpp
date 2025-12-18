#include "Client.h"
#include "Case.h"
#include <algorithm>
#include <sstream>

Client::Client(const std::string& name, int age, const std::string& contact)
    : Person(name, age), contactInfo(contact) {}

std::string Client::getContactInfo() const { return contactInfo; }
const std::vector<std::shared_ptr<Case>>& Client::getCases() const { return cases; }
void Client::setContactInfo(const std::string& contact) { contactInfo = contact; } 

void Client::addCase(std::shared_ptr<Case> newCase) {
    if (!newCase) return;
    if (std::find(cases.begin(), cases.end(), newCase) != cases.end()) return; 
    cases.push_back(newCase);
}

void Client::removeCase(std::shared_ptr<Case> caseToRemove) {
    auto it = std::find(cases.begin(), cases.end(), caseToRemove);
    if (it != cases.end()) {
        cases.erase(it);
    }
}

bool Client::hasCase(int caseId) const {
    return std::any_of(cases.begin(), cases.end(),
        [caseId](const auto& c) { return c && c->getId() == caseId; });
}

int Client::getCasesCount() const { return static_cast<int>(cases.size()); }

std::vector<std::string> Client::getServiceTypes() const {
    std::vector<std::string> types;
    for (const auto& c : cases) {
        if (c) {
            types.push_back(c->getServiceCategory());
        }
    }
    std::sort(types.begin(), types.end());
    types.erase(std::unique(types.begin(), types.end()), types.end());
    return types;
}

std::string Client::toString() const {
    std::stringstream ss;
    ss << getRole() << ": " << fullName << " (" << age << " лет)\n"
        << "Контакт: " << contactInfo << "\n"
        << "Дел: " << getCasesCount();
    if (!cases.empty()) {
        ss << "\nДела: ";
        for (size_t i = 0; i < cases.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << "#" << cases[i]->getId();
        }
    }
    return ss.str();
}

std::string Client::getInfo() const {
    return "Контакт: " + contactInfo;
}

std::string Client::getRole() const { return "Клиент"; }