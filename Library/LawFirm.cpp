#include "LawFirm.h"
#include <algorithm>

LawFirm::LawFirm() {}



std::vector<Person*> LawFirm::getAllPeople() const {
    std::vector<Person*> result;

    
    for (const auto& lawyer : lawyers) {
        result.push_back(lawyer.get());
    }

    
    for (const auto& client : clients) {
        result.push_back(client.get());
    }

    return result;
}

std::vector<Person*> LawFirm::getPeopleByRole(const std::string& role) const {
    std::vector<Person*> result;
    auto allPeople = getAllPeople();

    std::copy_if(allPeople.begin(), allPeople.end(), std::back_inserter(result),
        [&](Person* person) {
            return person->getRole() == role;
        });

    return result;
}

std::vector<Person*> LawFirm::getPeopleInvolvedInCaseType(const std::string& caseType) const {
    std::vector<Person*> result;
    auto allPeople = getAllPeople();

    std::copy_if(allPeople.begin(), allPeople.end(), std::back_inserter(result),
        [&](Person* person) {
            return person->involvedInCaseType(caseType);
        });

    return result;
}