#pragma once
#include <vector>
#include <memory>
#include <string>

class LegalService;
class Lawyer;
class Client;
class Case;
class Person;

class LawFirm {
private:
    std::vector<std::unique_ptr<LegalService>> services;
    std::vector<std::unique_ptr<Lawyer>> lawyers;
    std::vector<std::unique_ptr<Client>> clients; 
    std::vector<std::shared_ptr<Case>> cases;
     
public:
    LawFirm() = default;
    ~LawFirm() = default;
    LawFirm(const LawFirm&) = delete;
    LawFirm& operator=(const LawFirm&) = delete;

    void addService(std::unique_ptr<LegalService> service);
    void addLawyer(std::unique_ptr<Lawyer> lawyer);
    void addClient(std::unique_ptr<Client> client);
    void addCase(std::shared_ptr<Case> casePtr);
    bool removeCase(int caseId);

    std::vector<LegalService*> getServices() const;
    std::vector<Lawyer*> getLawyers() const;
    std::vector<Client*> getClients() const;
    std::vector<Case*> getCases() const;

    std::vector<std::pair<std::string, double>> getServicesWithPrices() const;
    std::vector<Client*> getClientsByServiceType(const std::string& serviceType) const;
    std::vector<Lawyer*> getAvailableLawyersByService(const std::string& serviceType) const;
    std::string getCaseContent(int caseId) const;

    std::vector<Person*> getAllPeople() const;
    int getTotalCases() const { return static_cast<int>(cases.size()); }
    bool validateRelationships() const;
};