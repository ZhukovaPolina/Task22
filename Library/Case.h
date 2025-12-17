#pragma once
#include <string>
#include <memory>

class Lawyer;
class Client;
class LegalService;

class Case {
private: 
    int id;
    std::string content;
    Lawyer* lawyer;
    Client* client;
    LegalService* service;
    
public:
    Case(int caseId, const std::string& caseContent,
        Lawyer* caseLawyer, Client* caseClient, LegalService* caseService); 
    ~Case() = default;

    Case(const Case&) = delete;
    Case& operator=(const Case&) = delete;

    int getId() const { return id; }
    std::string getContent() const { return content; }
    Lawyer* getLawyer() const { return lawyer; }
    Client* getClient() const { return client; }
    LegalService* getService() const { return service; }
    std::string getServiceCategory() const;
    
    void setContent(const std::string& newContent);
    void setLawyer(Lawyer* newLawyer);
    void setClient(Client* newClient);
    void setService(LegalService* newService);
};