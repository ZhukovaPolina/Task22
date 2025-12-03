#include "Case.h"

Case::Case(int caseId, const std::string& caseContent, Lawyer* caseLawyer,
    Client* caseClient, LegalService* caseService)
    : id(caseId), content(caseContent), lawyer(caseLawyer),
    client(caseClient), service(caseService) {
    if (lawyer) lawyer->assignCase(this);
    if (client) client->addCase(this);
}

int Case::getId() const {
    return id;
}

std::string Case::getContent() const {
    return content;
}

Lawyer* Case::getLawyer() const {
    return lawyer;
}

Client* Case::getClient() const {
    return client;
}

LegalService* Case::getService() const {
    return service;
}

std::string Case::getServiceType() const {
    return service ? service->getServiceType() : "";
}

std::string Case::getServiceCategory() const {
    return service ? service->getCategory() : "";
}

void Case::setContent(const std::string& newContent) {
    content = newContent;
}