#include <iostream>
#include <vector>
#include <memory>
#include "../LawFirmLibrary/LawFirm.h"
#include "../LawFirmLibrary/LegalService.h"
#include "../LawFirmLibrary/Lawyer.h"
#include "../LawFirmLibrary/Client.h"
#include "../LawFirmLibrary/Case.h"

int main() {
    LawFirm firm;

    
    firm.addService(std::make_unique<LegalService>("Гражданские дела", 50000.0, "Гражданские"));
    firm.addService(std::make_unique<LegalService>("Уголовные дела", 100000.0, "Уголовные"));
    firm.addService(std::make_unique<LegalService>("Семейные дела", 40000.0, "Семейные"));

    
    firm.addLawyer(std::make_unique<Lawyer>("Иванов И.И.", "Гражданские", 3000.0));
    firm.addLawyer(std::make_unique<Lawyer>("Петров П.П.", "Уголовные", 5000.0));
    firm.addLawyer(std::make_unique<Lawyer>("Сидорова С.С.", "Семейные", 2500.0));

    firm.addClient(std::make_unique<Client>("Клиент А", "тел: 111-11-11"));
    firm.addClient(std::make_unique<Client>("Клиент Б", "тел: 222-22-22"));
    firm.addClient(std::make_unique<Client>("Клиент В", "тел: 333-33-33"));

    
    auto lawyers = firm.getLawyers();
    auto clients = firm.getClients();
    auto services = firm.getServices();

    firm.addCase(std::make_unique<Case>(1, "Дело о договоре аренды",
        lawyers[0], clients[0], services[0]));

    firm.addCase(std::make_unique<Case>(2, "Уголовное дело о краже",
        lawyers[1], clients[1], services[1]));


    
    std::cout << "1. УСЛУГИ И ЦЕНЫ:\n";
    for (const auto& [name, price] : firm.getServicesWithPrices()) {
        std::cout << "   " << name << ": " << price << " руб.\n";
    }

    
    std::cout << "\n2. КЛИЕНТЫ ПО 'Гражданские дела':\n";
    for (const auto& client : firm.getClientsByServiceType("Гражданские")) {
        std::cout << "   " << client->getFullName() << "\n";
    }

    
    std::cout << "\n3. СВОБОДНЫЕ АДВОКАТЫ ПО 'Семейные дела':\n";
    for (const auto& lawyer : firm.getAvailableLawyersByService("Семейные")) {
        std::cout << "   " << lawyer->getFullName() << "\n";
    }

    
    std::cout << "\n4. СОДЕРЖАНИЕ ДЕЛА №1:\n";
    std::cout << "   " << firm.getCaseContent(1) << "\n";

    
    std::cout << "\n=== КОЛЛЕКЦИЯ PERSON ===\n";

    
    std::vector<Person*> allPeople = firm.getAllPeople();

    
    for (const auto& person : allPeople) {
        std::cout << person->getInfo() << "\n";
    }

    
    std::cout << "\n=== ВСЕ АДВОКАТЫ (фильтр по роли) ===\n";
    auto allLawyersAsPerson = firm.getPeopleByRole("Адвокат");
    for (const auto& person : allLawyersAsPerson) {
        std::cout << person->getInfo() << "\n";
    }

    
    std::cout << "\n=== ЛЮДИ В 'Гражданские дела' ===\n";
    auto peopleInCivilCases = firm.getPeopleInvolvedInCaseType("Гражданские");
    for (const auto& person : peopleInCivilCases) {
        std::cout << person->getFullName() << " (" << person->getRole() << ")\n";
    }

    return 0;
}