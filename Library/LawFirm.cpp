#include "LawFirm.h"
#include <algorithm>

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
    if (auto service = casePtr->getService()) {
        service->addCase(casePtr.get());
    }
    
    cases.push_back(std::move(casePtr));
}

std::vector<LegalService*> LawFirm::getServices() const {
    std::vector<LegalService*> result;
    for (const auto& service : services) {
        result.push_back(service.get());
    }
    return result;
}

std::vector<Lawyer*> LawFirm::getLawyers() const {
    std::vector<Lawyer*> result;
    for (const auto& lawyer : lawyers) {
        result.push_back(lawyer.get());
    }
    return result;
}

std::vector<Client*> LawFirm::getClients() const {
    std::vector<Client*> result;
    for (const auto& client : clients) {
        result.push_back(client.get());
    }
    return result;
}

std::vector<Case*> LawFirm::getCases() const {
    std::vector<Case*> result;
    for (const auto& casePtr : cases) {
        result.push_back(casePtr.get());
    }
    return result;
}

std::vector<std::pair<std::string, double>> LawFirm::getServicesWithPrices() const {
    std::vector<std::pair<std::string, double>> result;
    for (const auto& service : services) {
        result.emplace_back(service->getName(), service->getPrice());
    }
    return result;
}

std::vector<Client*> LawFirm::getClientsByServiceType(const std::string& serviceType) const {
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
    return "Дело не найдено";
}

std::vector<Person*> LawFirm::getAllPeople() const {
    std::vector<Person*> result;
    
    for (const auto& lawyer : lawyers) {
        result.push_back(lawyer.get());
    }
    
    for (const auto& client : clients) {
        result.push_back(client.get());
    }
    
    return result;
}

int LawFirm::getTotalCases() const {
    return static_cast<int>(cases.size());
}

bool LawFirm::validateRelationships() const {
    for (const auto& casePtr : cases) {
        if (!casePtr) continue;
        
        Lawyer* lawyer = casePtr->getLawyer();
        Client* client = casePtr->getClient();
        LegalService* service = casePtr->getService();
        
        if (lawyer) {
            const auto& lawyerCases = lawyer->getCases();
            if (std::find(lawyerCases.begin(), lawyerCases.end(), casePtr.get()) == lawyerCases.end()) {
                return false;
            }
        }
        
        if (client) {
            const auto& clientCases = client->getCases();
            if (std::find(clientCases.begin(), clientCases.end(), casePtr.get()) == clientCases.end()) {
                return false;
            }
        }
        
        if (service) {
            const auto& serviceCases = service->getCases();
            if (std::find(serviceCases.begin(), serviceCases.end(), casePtr.get()) == serviceCases.end()) {
                return false;
            }
        }
    }
    
    return true;
}
