#pragma once
#include <string>
#include <vector>

class Case;

class Client {
private:
    std::string name;
    std::vector<Case*> cases;

public:
    Client(const std::string& clientName);

    std::string getName() const;
    void addCase(Case* casePtr);
    std::vector<std::string> getServiceTypes() const;
    int getCaseCount() const;
};