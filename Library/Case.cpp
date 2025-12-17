#include "Case.h"
#include "Lawyer.h"
#include "Client.h"
#include "LegalService.h"

Case::Case(int caseId, const std::string& caseContent,
    Lawyer* caseLawyer, Client* caseClient, LegalService* caseService)
    : id(caseId), content(caseContent), lawyer(caseLawyer),
    client(caseClient), service(caseService) {}

std::string Case::getServiceCategory() const {
    return service ? service->getCategory() : "Неизвестно"; 
}

void Case::setContent(const std::string& newContent) { content = newContent; }
void Case::setLawyer(Lawyer* newLawyer) { lawyer = newLawyer; }
void Case::setClient(Client* newClient) { client = newClient; }
void Case::setService(LegalService* newService) { service = newService; }