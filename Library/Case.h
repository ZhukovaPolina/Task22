#ifndef CASE_H
#define CASE_H

#include <string>
#include "Lawyer.h"
#include "Client.h"
#include "LegalService.h"

class Case {
private:
    int id;
    std::string content;
    Lawyer* lawyer;
    Client* client;
    LegalService* service;
    
public:
    Case(int caseId, const std::string& caseContent, Lawyer* caseLawyer, 
         Client* caseClient, LegalService* caseService);
    ~Case();
    
    Case(const Case&) = delete;
    Case& operator=(const Case&) = delete;
    
    int getId() const;
    std::string getContent() const;
    Lawyer* getLawyer() const;
    Client* getClient() const;
    LegalService* getService() const;
    std::string getServiceCategory() const;
    
    void setContent(const std::string& newContent);
    void setLawyer(Lawyer* newLawyer);
    void setClient(Client* newClient);
    void setService(LegalService* newService);
};

#endif
