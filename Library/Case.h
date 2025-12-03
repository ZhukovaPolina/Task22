#pragma once
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

    int getId() const;
    std::string getContent() const;
    Lawyer* getLawyer() const;
    Client* getClient() const;
    LegalService* getService() const;
    std::string getServiceType() const;
    std::string getServiceCategory() const;

    void setContent(const std::string& newContent);
};