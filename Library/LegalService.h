#pragma once
#include <string>

class LegalService {
private:
    std::string name;
    std::string description;
    double price;

public:
    LegalService(const std::string& serviceName, const std::string& serviceDesc, double servicePrice);

    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    void setPrice(double newPrice);
};