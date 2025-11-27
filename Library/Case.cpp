#include "Case.h"

Case::Case(int caseId, const std::string& caseContent, Lawyer* caseLawyer, Client* caseClient, const std::string& service)
    : id(caseId), content(caseContent), lawyer(caseLawyer), client(caseClient), serviceType(service) {}

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

std::string Case::getServiceType() const {
    return serviceType;
}

void Case::setContent(const std::string& newContent) {
    content = newContent;
}