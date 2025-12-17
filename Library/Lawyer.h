#pragma once
#include "Person.h"
#include <string>
#include <vector>
#include <memory>

class Case;

class Lawyer : public Person {
private:
    std::string specialization;
    bool isAvailable;
    double hourlyRate;
    std::vector<std::shared_ptr<Case>> cases;
     
public:
    Lawyer(const std::string& name, int age, const std::string& spec,
        double rate, bool available = true);

    std::string getSpecialization() const { return specialization; }
    bool getIsAvailable() const { return isAvailable; }
    double getHourlyRate() const { return hourlyRate; }
    const std::vector<std::shared_ptr<Case>>& getCases() const { return cases; }

    void setSpecialization(const std::string& spec) { specialization = spec; }
    void setAvailability(bool available) { isAvailable = available; }
    void setHourlyRate(double rate) { hourlyRate = rate; }

    void addCase(std::shared_ptr<Case> newCase);
    void removeCase(std::shared_ptr<Case> caseToRemove);
    bool hasCase(int caseId) const;
    int getCasesCount() const;

    double calculateEstimatedCost(double hours) const { return hourlyRate * hours; }
    void toggleAvailability() { isAvailable = !isAvailable; }

    std::string toString() const;
    std::string getInfo() const override;
    std::string getRole() const override;
};