#pragma once
#include <string>

class LegalService {
protected:
    std::string name;
    double price;
    std::string category;  // гражданские, уголовные, семейные

public:
    LegalService(const std::string& serviceName, double servicePrice,
        const std::string& serviceCategory);
    virtual ~LegalService() = default;

    
    virtual std::string getServiceType() const = 0;

    
    std::string getName() const;
    double getPrice() const;
    std::string getCategory() const;

    void setPrice(double newPrice);
};