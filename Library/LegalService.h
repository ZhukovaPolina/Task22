#ifndef LEGALSERVICE_H
#define LEGALSERVICE_H

#include <string>

class LegalService {
private:
    std::string name;
    double price;
    std::string category;  // гражданские, уголовные, семейные

public:
    LegalService(const std::string& serviceName, double servicePrice,
        const std::string& serviceCategory);

    std::string getName() const;
    double getPrice() const;
    std::string getCategory() const;

    void setPrice(double newPrice);
    void setCategory(const std::string& newCategory);
};

#endif