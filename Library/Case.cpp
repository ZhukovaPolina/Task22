#include "Case.h"

Case::Case(int caseId, const std::string& caseContent, Lawyer* caseLawyer,
           Client* caseClient, LegalService* caseService)
    : id(caseId), content(caseContent), lawyer(caseLawyer), 
      client(caseClient), service(caseService) {
    
    
    if (lawyer) {
        lawyer->addCase(this);
        lawyer->assignCase(this);
    }
    if (client) {
        client->addCase(this);
    }
}

Case::~Case() {
    
    if (lawyer) {
        lawyer->removeCase(this);
    }
    if (client) {
        client->removeCase(this);
    }
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

std::string Case::getServiceCategory() const {
    return service ? service->getCategory() : "";
}

void Case::setContent(const std::string& newContent) {
    content = newContent;
}

void Case::setLawyer(Lawyer* newLawyer) {
    if (lawyer == newLawyer) return;
    
    if (lawyer) {
        lawyer->removeCase(this);
    }
    
   #include "Case.h"

Case::Case(int caseId, const std::string& caseContent, Lawyer* caseLawyer,
           Client* caseClient, LegalService* caseService)
    : id(caseId), content(caseContent), lawyer(caseLawyer), 
      client(caseClient), service(caseService) {
    
    
    if (lawyer) {
        lawyer->addCase(this);
        lawyer->assignCase(this);
    }
    if (client) {
        client->addCase(this);
    }
}

Case::~Case() {
    
    if (lawyer) {
        lawyer->removeCase(this);
    }
    if (client) {
        client->removeCase(this);
    }
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

std::string Case::getServiceCategory() const {
    return service ? service->getCategory() : "";
}

void Case::setContent(const std::string& newContent) {
    content = newContent;
}

void Case::setLawyer(Lawyer* newLawyer) {
    if (lawyer == newLawyer) return;
    
    
    if (lawyer) {
        lawyer->removeCase(this);
    }
    
    
    lawyer = newLawyer;
    if (lawyer) {
        lawyer->addCase(this);
        lawyer->assignCase(this);
    }
}

void Case::setClient(Client* newClient) {
    if (client == newClient) return;
    
    
    if (client) {
        client->removeCase(this);
    }
    
  
    client = newClient;
    if (client) {
        client->addCase(this);
    }
}

void Case::setService(LegalService* newService) {
    service = newService;
}
    lawyer = newLawyer;
    if (lawyer) {
        lawyer->addCase(this);
        lawyer->assignCase(this);
    }
}

void Case::setClient(Client* newClient) {
    if (client == newClient) return;
    

    if (client) {
        client->removeCase(this);
    }
    

    client = newClient;
    if (client) {
        client->addCase(this);
    }
}

void Case::setService(LegalService* newService) {
    service = newService;
}
