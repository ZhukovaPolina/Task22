#ifndef CLIENT_H
#define CLIENT_H

#include "Person.h"
#include <string>
#include <vector>

class Case;

class Client : public Person {
private:
    std::string contactInfo;
    std::vector<Case*> cases;

public:
    Client(const std::string& name, int age, const std::string& contact);
    
    std::string getContactInfo() const;
    const std::vector<Case*>& getCases() const;
    
    void setContactInfo(const std::string& contact);
    
    void addCase(Case* newCase);
    void removeCase(Case* caseToRemove);
    bool hasCase(const std::string& caseId) const;
    int getCasesCount() const;
    
    std::string toString() const override;
};

#endif // CLIENT_H
