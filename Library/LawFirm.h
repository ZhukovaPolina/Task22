#pragma once
#include <vector>
#include <memory>
#include "LegalService.h"
#include "Lawyer.h"
#include "Client.h"
#include "Case.h"

class LawFirm {
private:
    std::vector<std::unique_ptr<LegalService>> services;
    std::vector<std::unique_ptr<Lawyer>> lawyers;
    std::vector<std::unique_ptr<Client>> clients;
    std::vector<std::unique_ptr<Case>> cases;

public:
    LawFirm();

    void addService(std::unique_ptr<LegalService> service);
    void addLawyer(std::unique_ptr<Lawyer> lawyer);
    void addClient(std::unique_ptr<Client> client);
    void addCase(std::unique_ptr<Case> casePtr);

    std::vector<LegalService*> getServices() const;
    std::vector<Client*> getClientsByService(const std::string& serviceType) const;
    std::vector<Lawyer*> getAvailableLawyersByService(const std::string& serviceType) const;
    std::string getCaseContent(int caseId) const;
};