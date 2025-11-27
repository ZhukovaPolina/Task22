#pragma once
#include <string>
#include "Lawyer.h"
#include "Client.h"

class Case {
private:
    int id;
    std::string content;
    Lawyer* lawyer;
    Client* client;
    std::string serviceType;

public:
    Case(int caseId, const std::string& caseContent, Lawyer* caseLawyer, Client* caseClient, const std::string& service);

    int getId() const;
    std::string getContent() const;
    Lawyer* getLawyer() const;
    Client* getClient() const;
    std::string getServiceType() const;
    void setContent(const std::string& newContent);
};
