#include "LawFirm.h"

LawFirm::LawFirm() {}

void LawFirm::addService(std::unique_ptr<LegalService> service) {
    services.push_back(std::move(service));
}

void LawFirm::addLawyer(std::unique_ptr<Lawyer> lawyer) {
    lawyers.push_back(std::move(lawyer));
}

void LawFirm::addClient(std::unique_ptr<Client> client) {
    clients.push_back(std::move(client));
}

void LawFirm::addCase(std::unique_ptr<Case> casePtr) {
    cases.push_back(std::move(casePtr));
}

std::vector<LegalService*> LawFirm::getServices() const {
    std::vector<LegalService*> result;
    for (const auto& service : services) {
        result.push_back(service.get());
    }
    return result;
}

std::vector<Client*> LawFirm::getClientsByService(const std::string& serviceType) const {
    std::vector<Client*> result;
    for (const auto& client : clients) {
        auto services = client->getServiceTypes();
        for (const auto& service : services) {
            if (service == serviceType) {
                result.push_back(client.get());
                break;
            }
        }
    }
    return result;
}

std::vector<Lawyer*> LawFirm::getAvailableLawyersByService(const std::string& serviceType) const {
    std::vector<Lawyer*> result;
    for (const auto& lawyer : lawyers) {
        if (lawyer->getIsAvailable() && lawyer->getSpecialization() == serviceType) {
            result.push_back(lawyer.get());
        }
    }
    return result;
}

std::string LawFirm::getCaseContent(int caseId) const {
    for (const auto& casePtr : cases) {
        if (casePtr->getId() == caseId) {
            return casePtr->getContent();
        }
    }
    return "Case not found";
}