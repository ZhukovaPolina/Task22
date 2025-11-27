#pragma once
#include <string>
#include <vector>

class Case;

class Lawyer {
private:
    std::string name;
    std::string specialization;
    std::vector<Case*> assignedCases;
    bool isAvailable;

public:
    Lawyer(const std::string& lawyerName, const std::string& lawyerSpecialization);

    std::string getName() const;
    std::string getSpecialization() const;
    bool getIsAvailable() const;
    void assignCase(Case* casePtr);
    void removeCase(Case* casePtr);
    void setAvailability(bool available);
    int getCaseCount() const;
};