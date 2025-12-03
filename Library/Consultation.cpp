#include "Consultation.h"

Consultation::Consultation(const std::string& name, double price,
    const std::string& category)
    : LegalService(name, price, category) {}

std::string Consultation::getServiceType() const {
    return "Консультация";
}