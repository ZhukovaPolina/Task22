#pragma once
#include "Person.h"
#include <string>
#include <vector>
#include <memory>

class Case;

class Client : public Person {
private:
    std::string contactInfo;
    std::vector<std::shared_ptr<Case>> cases;

public:
    Client(const std::string& name, int age, const std::string& contact);

    std::string getContactInfo() const;
    const std::vector<std::shared_ptr<Case>>& getCases() const;
    void setContactInfo(const std::string& contact);

    void addCase(std::shared_ptr<Case> newCase);
    void removeCase(std::shared_ptr<Case> caseToRemove);
    bool hasCase(int caseId) const;
    int getCasesCount() const;
    std::vector<std::string> getServiceTypes() const;

    std::string toString() const;
    std::string getInfo() const override;
    std::string getRole() const override;
};