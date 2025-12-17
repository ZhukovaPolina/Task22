#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include "../Library/LawFirm.h"
#include "../Library/LegalService.h"
#include "../Library/Lawyer.h"
#include "../Library/Client.h"
#include "../Library/Case.h"

 
enum ReportType {
    SERVICES = 1,
    CIVIL_CLIENTS = 2,
    CRIMINAL_LAWYERS = 3,
    CASE_1 = 4,
    CASE_4 = 5,
    CASE_99 = 6,
    PERSONS = 7,
    LAWYERS_INFO = 8,
    REMOVE_CASE = 9
};

int main() {
    LawFirm firm;

    firm.addClient(std::make_unique<Client>("Иванов И.И.", 35, "тел: +7-900-111-11-11"));
    firm.addClient(std::make_unique<Client>("Петрова А.С.", 28, "тел: +7-900-222-22-22"));
    firm.addClient(std::make_unique<Client>("Сидоров В.П.", 42, "тел: +7-900-333-33-33"));

    firm.addLawyer(std::make_unique<Lawyer>("Смирнов А.В.", 40, "Гражданские", 3000.0));
    firm.addLawyer(std::make_unique<Lawyer>("Козлова Е.Н.", 37, "Уголовные", 5000.0));
    firm.addLawyer(std::make_unique<Lawyer>("Морозов Д.К.", 33, "Семейные", 2500.0));

    firm.addService(std::make_unique<LegalService>("Консультация по гражданским делам", 5000.0, "Гражданские"));
    firm.addService(std::make_unique<LegalService>("Защита по уголовным делам", 100000.0, "Уголовные"));
    firm.addService(std::make_unique<LegalService>("Консультация по семейным делам", 4000.0, "Семейные"));
    firm.addService(std::make_unique<LegalService>("Ведение гражданского дела", 50000.0, "Гражданские"));
    firm.addService(std::make_unique<LegalService>("Ведение уголовного дела", 150000.0, "Уголовные"));

    auto lawyers = firm.getLawyers();
    auto clients = firm.getClients();
    auto services = firm.getServices();

    if (lawyers.size() > 0 && clients.size() > 0 && services.size() > 0)
        firm.addCase(std::make_shared<Case>(1, "Консультация по договору аренды", lawyers[0], clients[0], services[0]));
    if (lawyers.size() > 1 && clients.size() > 1 && services.size() > 1)
        firm.addCase(std::make_shared<Case>(2, "Защита по ст. 158 УК РФ", lawyers[1], clients[1], services[1]));
    if (lawyers.size() > 2 && clients.size() > 2 && services.size() > 2)
        firm.addCase(std::make_shared<Case>(3, "Консультация по разделу имущества", lawyers[2], clients[2], services[2]));
    if (lawyers.size() > 0 && clients.size() > 0 && services.size() > 3)
        firm.addCase(std::make_shared<Case>(4, "Взыскание задолженности", lawyers[0], clients[0], services[3]));

    std::cout << "=== АДВОКАТСКАЯ КОНТОРА ===\n\n";

    int section = 1;
    switch (section) {
    case SERVICES: {
        std::cout << "1. СПИСОК УСЛУГ И ЦЕН:\n";
        auto servicesWithPrices = firm.getServicesWithPrices();
        for (const auto& [name, price] : servicesWithPrices) {
            std::cout << "   • " << std::left << std::setw(40) << name
                << ": " << std::right << std::setw(10) << std::fixed << std::setprecision(2)
                << price << " руб.\n";
        }
        break;
    }
    }

    section = 2;
    switch (section) {
    case CIVIL_CLIENTS: {
        std::cout << "\n2. КЛИЕНТЫ, ОБРАЩАВШИЕСЯ ПО КАТЕГОРИИ 'Гражданские':\n";
        auto clientsByService = firm.getClientsByServiceType("Гражданские");
        for (const auto& client : clientsByService) {
            std::cout << "   • " << client->getFullName() << "\n";
        }
        break;
    }
    }section = 3;
    switch (section) {
    case CRIMINAL_LAWYERS: {
        std::cout << "\n3. СВОБОДНЫЕ АДВОКАТЫ ПО КАТЕГОРИИ 'Уголовные':\n";
        auto availableLawyers = firm.getAvailableLawyersByService("Уголовные");
        if (availableLawyers.empty()) {
            std::cout << "   Нет свободных адвокатов\n";
        }
        else {
            for (const auto& lawyer : availableLawyers) {
                std::cout << "   • " << lawyer->getFullName() << "\n";
            }
        }
        break;
    }
    }

    section = 4;
    switch (section) {
    case CASE_1:
        std::cout << "\n4. СОДЕРЖАНИЕ ДЕЛА №1:\n   " << firm.getCaseContent(1) << "\n";
        break;
    }

    section = 5;
    switch (section) {
    case CASE_4:
        std::cout << "\n5. СОДЕРЖАНИЕ ДЕЛА №4:\n   " << firm.getCaseContent(4) << "\n";
        break;
    }

    section = 6;
    switch (section) {
    case CASE_99:
        std::cout << "\n6. ПОПЫТКА ПОЛУЧИТЬ НЕСУЩЕСТВУЮЩЕЕ ДЕЛО (№99):\n   " << firm.getCaseContent(99) << "\n";
        break;
    }

    section = 7;
    switch (section) {
    case PERSONS: {
        std::cout << "\n=== КОЛЛЕКЦИЯ PERSON ===\n";
        auto allPeople = firm.getAllPeople();
        for (const auto& person : allPeople) {
            std::cout << "• " << person->getRole() << ": " << person->getFullName() << "\n";
        }
        break;
    }
    }

    section = 8;
    switch (section) {
    case LAWYERS_INFO: {
        std::cout << "\n=== ДОПОЛНИТЕЛЬНАЯ ИНФОРМАЦИЯ ===\n";
        std::cout << "Общее количество дел: " << firm.getTotalCases() << "\n";

        std::cout << "\nАдвокаты и их дела:\n";
        for (const auto& lawyer : firm.getLawyers()) {
            std::cout << "• " << lawyer->getFullName()
                << " (дел: " << lawyer->getCasesCount()
                << ", доступен: " << (lawyer->getIsAvailable() ? "да" : "нет") << ")\n";
        }
        break;
    }
    }

    section = 9;
    switch (section) {
    case REMOVE_CASE: {
        std::cout << "\n>>> Удаляем дело №2...\n";
        firm.removeCase(2);
        std::cout << "• Дело №2 удалено. Адвокат '" << firm.getLawyers()[1]->getFullName()
            << "' теперь " << (firm.getLawyers()[1]->getIsAvailable() ? "свободен" : "занят") << "\n";

        std::cout << "\nПроверка целостности связей: "
            << (firm.validateRelationships() ? "OK" : "ОШИБКА") << "\n";
        break;
    }
    }
    
    return 0;
}
