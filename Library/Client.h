#pragma once
#include <string>
#include <vector>

class Case;

class Client {
private:
    std::string name;
    std::string contactInfo;
    std::vector<Case*> cases;

public:
    Client(const std::string& clientName, const std::string& clientContact);

    std::string getName() const;
    std::string getContactInfo() const;
    void addCase(Case* casePtr);
    std::vector<std::string> getServiceTypes() const;
};