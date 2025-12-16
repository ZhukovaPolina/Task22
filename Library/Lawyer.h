#ifndef LAWYER_H
#define LAWYER_H

#include "Person.h"
#include <string>

class Lawyer : public Person {
private:
    std::string specialization;
    bool isAvailable;
    double hourlyRate;
    
public:
    Lawyer(const std::string& name, const std::string& specialization, double rate);
    
    std::string getInfo() const override;
    std::string getRole() const override;
    
    std::string getSpecialization() const;
    bool getIsAvailable() const;
    double getHourlyRate() const;
    
    void assignCase(Case* casePtr);
    void completeCase(Case* casePtr);
    void setAvailability(bool available);
    void setHourlyRate(double rate);
};

#endif
