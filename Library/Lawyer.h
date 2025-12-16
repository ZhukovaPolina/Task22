#ifndef LAWYER_H
#define LAWYER_H

#include "Person.h"
#include <string>
#include <vector>

class Case;

class Lawyer : public Person {
private:
    std::string specialization;
    bool isAvailable;
    double hourlyRate;
    std::vector<Case*> cases;

public:
    Lawyer(const std::string& name, int age, const std::string& spec,
           double rate, bool available = true);
    
    std::string getSpecialization() const;
    bool getAvailability() const;
    double getHourlyRate() const;
    const std::vector<Case*>& getCases() const;
    
    void setSpecialization(const std::string& spec);
    void setAvailability(bool available);
    void setHourlyRate(double rate);
    
    void addCase(Case* newCase);
    void removeCase(Case* caseToRemove);
    bool hasCase(const std::string& caseId) const;
    int getCasesCount() const;
    
    double calculateEstimatedCost(double hours) const;
    void toggleAvailability();
    
    std::string toString() const override;
};

#endif // LAWYER_H
