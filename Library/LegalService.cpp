#include "LegalService.h"
#include "Case.h"
#include <algorithm>

LegalService::LegalService(const std::string& serviceName, double servicePrice,
                           const std::string& serviceCategory)
    : name(serviceName), price(servicePrice), category(serviceCategory) {}

std::string LegalService::getName() const {
    return name;
}

double LegalService::getPrice() const {
    return price;
}

std::string LegalService::getCategory() const {
    return category;
}

void LegalService::addCase(Case* casePtr) {
    cases.push_back(casePtr);
}

void LegalService::removeCase(Case* casePtr) {
    auto it = std::find(cases.begin(), cases.end(), casePtr);
    if (it != cases.end()) {
        cases.erase(it);
    }
}

int LegalService::getCaseCount() const {
    return static_cast<int>(cases.size());
}

const std::vector<Case*>& LegalService::getCases() const {
    return cases;
}

void LegalService::setPrice(double newPrice) {
    price = newPrice;
}

void LegalService::setCategory(const std::string& newCategory) {
    category = newCategory;
}
