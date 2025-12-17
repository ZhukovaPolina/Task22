#include "LegalService.h"
#include "Case.h"
#include <algorithm>

LegalService::LegalService(const std::string& serviceName, double servicePrice,
                           const std::string& serviceCategory)
    : name(serviceName), price(servicePrice), category(serviceCategory) {}

void LegalService::addCase(std::shared_ptr<Case> casePtr) {
    if (casePtr && std::find(cases.begin(), cases.end(), casePtr) == cases.end()) {
        cases.push_back(casePtr);
    }
}

void LegalService::removeCase(std::shared_ptr<Case> casePtr) {
    auto it = std::find(cases.begin(), cases.end(), casePtr); 
    if (it != cases.end()) { 
        cases.erase(it);
    }
}