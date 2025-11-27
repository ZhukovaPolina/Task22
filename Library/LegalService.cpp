#include "LegalService.h"

LegalService::LegalService(const std::string& serviceName, const std::string& serviceDesc, double servicePrice)
    : name(serviceName), description(serviceDesc), price(servicePrice) {}

std::string LegalService::getName() const {
    return name;
}

std::string LegalService::getDescription() const {
    return description;
}

double LegalService::getPrice() const {
    return price;
}

void LegalService::setPrice(double newPrice) {
    price = newPrice;
}