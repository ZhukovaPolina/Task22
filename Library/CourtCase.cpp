#include "CourtCase.h"

CourtCase::CourtCase(const std::string& name, double price,
    const std::string& category)
    : LegalService(name, price, category) {}

std::string CourtCase::getServiceType() const {
    return "Ведение дела в суде";
}