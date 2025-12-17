#include "LawFirm.h"
#include "LegalService.h"
#include "Lawyer.h"
#include "Client.h"
#include "Case.h"
#include <algorithm>

void LawFirm::addService(std::unique_ptr<LegalService> service) {
    services.push_back(std::move(service));
}

void LawFirm::addLawyer(std::unique_ptr<Lawyer> lawyer) { 
    lawyers.push_back(std::move(lawyer));
}

void LawFirm::addClient(std::unique_ptr<Client> client) {
    clients.push_back(std::move(client));
}

void LawFirm::addCase(std::shared_ptr<Case> casePtr) {
    if (!casePtr) return;

    if (auto l = casePtr->getLawyer()) l->addCase(casePtr);
    if (auto c = casePtr->getClient()) c->addCase(casePtr);
    if (auto s = casePtr->getService()) s->addCase(casePtr);

    cases.push_back(casePtr);
}

bool LawFirm::removeCase(int caseId) {
    auto it = std::find_if(cases.begin(), cases.end(),
        [caseId](const auto& c) { return c && c->getId() == caseId; });
    if (it == cases.end()) return false;

    auto casePtr = std::move(*it);
    cases.erase(it);

    if (auto l = casePtr->getLawyer()) l->removeCase(casePtr);
    if (auto c = casePtr->getClient()) c->removeCase(casePtr);
    if (auto s = casePtr->getService()) s->removeCase(casePtr);

    return true;
}

std::vector<LegalService*> LawFirm::getServices() const {
    std::vector<LegalService*> res;
    for (const auto& s : services) res.push_back(s.get());
    return res;
}

std::vector<Lawyer*> LawFirm::getLawyers() const {
    std::vector<Lawyer*> res;
    for (const auto& l : lawyers) res.push_back(l.get());
    return res;
}

std::vector<Client*> LawFirm::getClients() const {
    std::vector<Client*> res;
    for (const auto& c : clients) res.push_back(c.get());
    return res;
}

std::vector<Case*> LawFirm::getCases() const {
    std::vector<Case*> res;
    for (const auto& c : cases) res.push_back(c.get());
    return res;
}

std::vector<std::pair<std::string, double>> LawFirm::getServicesWithPrices() const {
    std::vector<std::pair<std::string, double>> res;
    for (const auto& s : services) {
        res.emplace_back(s->getName(), s->getPrice());
    }
    return res;
}

std::vector<Client*> LawFirm::getClientsByServiceType(const std::string& serviceType) const {
    std::vector<Client*> res;
    for (const auto& c_ptr : clients) {
        auto types = c_ptr->getServiceTypes();
        if (std::find(types.begin(), types.end(), serviceType) != types.end()) {
            res.push_back(c_ptr.get());
        }
    }
    return res;
}

std::vector<Lawyer*> LawFirm::getAvailableLawyersByService(const std::string& serviceType) const {
    std::vector<Lawyer*> res;
    for (const auto& l_ptr : lawyers) {
        if (l_ptr->getIsAvailable() && l_ptr->getSpecialization() == serviceType) {
            res.push_back(l_ptr.get());
        }
    }
    return res;
}

std::string LawFirm::getCaseContent(int caseId) const {
    for (const auto& c : cases) {
        if (c && c->getId() == caseId) {
            return c->getContent();
        }
    }
    return "Дело не найдено";
}

std::vector<Person*> LawFirm::getAllPeople() const {
    std::vector<Person*> res;
    for (const auto& l : lawyers) res.push_back(l.get());
    for (const auto& c : clients) res.push_back(c.get());
    return res;
}bool LawFirm::validateRelationships() const {
    for (const auto& casePtr : cases) {
        if (!casePtr) continue;

        auto lawyer = casePtr->getLawyer();
        auto client = casePtr->getClient();
        auto service = casePtr->getService();

        if (lawyer) {
            bool found = std::any_of(lawyer->getCases().begin(), lawyer->getCases().end(),
                [&](const std::shared_ptr<Case>& c) { return c == casePtr; });
            if (!found) return false;
        }

        if (client) {
            bool found = std::any_of(client->getCases().begin(), client->getCases().end(),
                [&](const std::shared_ptr<Case>& c) { return c == casePtr; });
            if (!found) return false;
        }

        if (service) {
            bool found = std::any_of(service->getCases().begin(), service->getCases().end(),
                [&](const std::shared_ptr<Case>& c) { return c == casePtr; });
            if (!found) return false;
        }
    }
    return true;
}