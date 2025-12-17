#pragma once
#include <string>
#include <vector>
#include <memory>

class Case;

class Case;

class LegalService {
private:
    std::string name;
    double price;
    std::string category;
    std::vector<std::shared_ptr<Case>> cases;

public:
    LegalService(const std::string& serviceName, double servicePrice,
        const std::string& serviceCategory);

    std::string getName() const { return name; }
    double getPrice() const { return price; }
    std::string getCategory() const { return category; }

    void addCase(std::shared_ptr<Case> casePtr);
    void removeCase(std::shared_ptr<Case> casePtr);
    int getCaseCount() const { return static_cast<int>(cases.size()); }
    const std::vector<std::shared_ptr<Case>>& getCases() const { return cases; }

    void setPrice(double newPrice) { price = newPrice; }
    void setCategory(const std::string& newCategory) { category = newCategory; }
};