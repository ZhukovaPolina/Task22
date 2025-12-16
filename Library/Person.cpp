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

void Person::removeCase(Case* casePtr) {
    auto it = std::find(cases.begin(), cases.end(), casePtr);
    if (it != cases.end()) {
        cases.erase(it);
    }
}

int Person::getCaseCount() const {
    return static_cast<int>(cases.size());
}

const std::vector<Case*>& Person::getCases() const {
    return cases;
}

bool Person::involvedInCaseType(const std::string& caseType) const {
    return std::any_of(cases.begin(), cases.end(), [&](Case* casePtr) {
        return casePtr && casePtr->getServiceCategory() == caseType;
    });
}

bool Person::involvedInCase(const std::string& caseType, int caseId) const {
    return std::any_of(cases.begin(), cases.end(), [&](Case* casePtr) {
        return casePtr && casePtr->getServiceCategory() == caseType && 
               casePtr->getId() == caseId;
    });
}
