#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <memory>

class Case;  
class Person {
protected:
    std::string fullName;
    std::vector<Case*> cases;  

public:
    explicit Person(const std::string& name);
    virtual ~Person() = default;

    const std::string& getFullName() const;
    void addCase(Case* casePtr);

    
    virtual std::string getInfo() const = 0;
    virtual std::string getRole() const = 0;

    
    bool involvedInCaseType(const std::string& caseType) const;
    bool involvedInCase(const std::string& caseType, int caseId) const;
};

#endif