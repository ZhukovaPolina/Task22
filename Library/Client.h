#ifndef CLIENT_H
#define CLIENT_H

#include "Person.h"
#include <string>
#include <vector>

class Case;

class Client : public Person {
private:
    std::string contactInfo;

public:
    Client(const std::string& name, const std::string& contact = "");

    
    std::string getInfo() const override;
    std::string getRole() const override;

    
    std::string getContactInfo() const;
    void setContactInfo(const std::string& contact);

    std::vector<std::string> getServiceTypes() const;
    int getCaseCount() const;
};

#endif