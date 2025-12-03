#pragma once
#include "LegalService.h"

class Consultation : public LegalService {
public:
    Consultation(const std::string& name, double price, const std::string& category);

    std::string getServiceType() const override;
};