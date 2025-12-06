#include "LegalService.h"

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

void LegalService::setPrice(double newPrice) {
    price = newPrice;
}

void LegalService::setCategory(const std::string& newCategory) {
    category = newCategory;
}