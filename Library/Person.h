#pragma once
#include <string>

class Person {
protected:
    std::string fullName;
    int age;

public:
    Person(const std::string& name, int personAge);
    virtual ~Person() = default;

    const std::string& getFullName() const { return fullName; }
    int getAge() const { return age; }

    virtual std::string getInfo() const = 0;
    virtual std::string getRole() const = 0;
};