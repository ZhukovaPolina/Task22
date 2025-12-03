#pragma once
#include "LegalService.h"

class CourtCase : public LegalService {
public:
    CourtCase(const std::string& name, double price, const std::string& category);

    std::string getServiceType() const override;
};