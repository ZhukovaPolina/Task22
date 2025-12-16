#ifndef LEGALSERVICE_H
#define LEGALSERVICE_H

#include <string>
#include <vector>

class Case;

class LegalService {
private:
    std::string name;
    double price;
    std::string category;
    std::vector<Case*> cases;
    
public:
    LegalService(const std::string& serviceName, double servicePrice, 
                 const std::string& serviceCategory);
    
    std::string getName() const;
    double getPrice() const;
    std::string getCategory() const;
    
    void addCase(Case* casePtr);
    void removeCase(Case* casePtr);
    int getCaseCount() const;
    const std::vector<Case*>& getCases() const;
    
    void setPrice(double newPrice);
    void setCategory(const std::string& newCategory);
};

#endif
