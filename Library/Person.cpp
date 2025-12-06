#include "Person.h"
#include "Case.h"
#include <algorithm>

Person::Person(const std::string& name) : fullName(name) {}

const std::string& Person::getFullName() const {
    return fullName;
}

void Person::addCase(Case* casePtr) {
    cases.push_back(casePtr);
}

bool Person::involvedInCaseType(const std::string& caseType) const {
    return std::any_of(cases.begin(), cases.end(), [&](const auto& casePtr) {
        return casePtr->getServiceCategory() == caseType;
        });
}

bool Person::involvedInCase(const std::string& caseType, int caseId) const {
    return std::any_of(cases.begin(), cases.end(), [&](const auto& casePtr) {
        return casePtr->getServiceCategory() == caseType && casePtr->getId() == caseId;
        });
}