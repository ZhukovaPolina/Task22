#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>
#include "../Library/LawFirm.h"
#include "../Library/LegalService.h"
#include "../Library/Lawyer.h"
#include "../Library/Client.h"
#include "../Library/Case.h"

enum class ServiceType {
    Civil,
    Criminal,
    Family
};

std::string serviceTypeToString(ServiceType type) {
    switch (type) {
        case ServiceType::Civil:    return "Гражданские";
        case ServiceType::Criminal: return "Уголовные";
        case ServiceType::Family:   return "Семейные";
        default:                    return "Неизвестно";
    }
}

ServiceType stringToServiceType(const std::string& str) {
    if (str == "Гражданские") return ServiceType::Civil;
    if (str == "Уголовные")   return ServiceType::Criminal;
    if (str == "Семейные")    return ServiceType::Family;
    throw std::invalid_argument("Неизвестный тип услуги: " + str);
}

int main() {
    LawFirm firm;

    firm.addClient(std::make_unique<Client>("Иванов И.И.", 35, "тел: +7-900-111-11-11"));
    firm.addClient(std::make_unique<Client>("Петрова А.С.", 28, "тел: +7-900-222-22-22"));
    firm.addClient(std::make_unique<Client>("Сидоров В.П.", 42, "тел: +7-900-333-33-33"));

    firm.addLawyer(std::make_unique<Lawyer>("Смирнов А.В.", 40, serviceTypeToString(ServiceType::Civil), 3000.0));
    firm.addLawyer(std::make_unique<Lawyer>("Козлова Е.Н.", 37, serviceTypeToString(ServiceType::Criminal), 5000.0));
    firm.addLawyer(std::make_unique<Lawyer>("Морозов Д.К.", 33, serviceTypeToString(ServiceType::Family), 2500.0));

    firm.addService(std::make_unique<LegalService>("Консультация по гражданским делам", 5000.0, serviceTypeToString(ServiceType::Civil)));
    firm.addService(std::make_unique<LegalService>("Защита по уголовным делам", 100000.0, serviceTypeToString(ServiceType::Criminal)));
    firm.addService(std::make_unique<LegalService>("Консультация по семейным делам", 4000.0, serviceTypeToString(ServiceType::Family)));
    firm.addService(std::make_unique<LegalService>("Ведение гражданского дела", 50000.0, serviceTypeToString(ServiceType::Civil)));
    firm.addService(std::make_unique<LegalService>("Ведение уголовного дела", 150000.0, serviceTypeToString(ServiceType::Criminal)));

    auto lawyers = firm.getLawyers();
    auto clients = firm.getClients();
    auto services = firm.getServices();

    if (lawyers.size() > 0 && clients.size() > 0 && services.size() > 0) {
        auto case1 = std::make_shared<Case>(1, "Консультация по договору аренды", lawyers[0], clients[0], services[0]);
        firm.addCase(case1);
    }
    if (lawyers.size() > 1 && clients.size() > 1 && services.size() > 1) {
        auto case2 = std::make_shared<Case>(2, "Защита по ст. 158 УК РФ", lawyers[1], clients[1], services[1]);
        firm.addCase(case2);
    }
    if (lawyers.size() > 2 && clients.size() > 2 && services.size() > 2) {
        auto case3 = std::make_shared<Case>(3, "Консультация по разделу имущества", lawyers[2], clients[2], services[2]);
        firm.addCase(case3);
    }
    if (lawyers.size() > 0 && clients.size() > 0 && services.size() > 3) {
        auto case4 = std::make_shared<Case>(4, "Взыскание задолженности", lawyers[0], clients[0], services[3]);
        firm.addCase(case4);
    }
std::cout << "=== АДВОКАТСКАЯ КОНТОРА ===\n\n";

    std::cout << "1. СПИСОК УСЛУГ И ЦЕН:\n";
    auto servicesWithPrices = firm.getServicesWithPrices();
    for (const auto& [name, price] : servicesWithPrices) {
        std::cout << "   • " << std::left << std::setw(40) << name
                  << ": " << std::right << std::setw(10) << std::fixed << std::setprecision(2)
                  << price << " руб.\n";
    }

    std::cout << "\n2. КЛИЕНТЫ, ОБРАЩАВШИЕСЯ ПО КАТЕГОРИИ 'Гражданские':\n";
    auto civilClients = firm.getClientsByServiceType(serviceTypeToString(ServiceType::Civil));
    for (const auto& client : civilClients) {
        std::cout << "   • " << client->getFullName() << "\n";
    }

    std::cout << "\n3. СВОБОДНЫЕ АДВОКАТЫ ПО КАТЕГОРИИ 'Уголовные':\n";
    auto availableLawyers = firm.getAvailableLawyersByService(serviceTypeToString(ServiceType::Criminal));
    if (availableLawyers.empty()) {
        std::cout << "   Нет свободных адвокатов\n";
    } else {
        for (const auto& lawyer : availableLawyers) {
            std::cout << "   • " << lawyer->getFullName() << "\n";
        }
    }

    std::cout << "\n4. СОДЕРЖАНИЕ ДЕЛА №1:\n   " << firm.getCaseContent(1) << "\n";
    std::cout << "\n5. СОДЕРЖАНИЕ ДЕЛА №4:\n   " << firm.getCaseContent(4) << "\n";
    std::cout << "\n6. ПОПЫТКА ПОЛУЧИТЬ НЕСУЩЕСТВУЮЩЕЕ ДЕЛО (№99):\n   " << firm.getCaseContent(99) << "\n";

    std::cout << "\n=== КОЛЛЕКЦИЯ PERSON ===\n";
    auto allPeople = firm.getAllPeople();
    for (const auto& person : allPeople) {
        std::cout << "• " << person->getRole() << ": " << person->getFullName() << "\n";
    }

    std::cout << "\n=== АДВОКАТЫ ПО СПЕЦИАЛИЗАЦИИ (ENUM) ===\n";
    for (const auto& lawyer : firm.getLawyers()) {
        std::string spec = lawyer->getSpecialization();
        try {
            ServiceType type = stringToServiceType(spec);
            std::cout << "• " << lawyer->getFullName() << " — ";
            switch (type) {
                case ServiceType::Civil:    std::cout << "[Гражданские]"; break;
                case ServiceType::Criminal: std::cout << "[Уголовные]";   break;
                case ServiceType::Family:   std::cout << "[Семейные]";    break;
            }
            std::cout << "\n";
        } catch (...) {
            std::cout << "• " << lawyer->getFullName() << " — [НЕИЗВЕСТНАЯ СПЕЦИАЛИЗАЦИЯ]\n";
        }
    }

    std::cout << "\n=== СТАТИСТИКА ПО ТИПАМ ДЕЛ ===\n";
    int civil = 0, criminal = 0, family = 0;
    for (const auto& casePtr : firm.getCases()) {
        std::string serviceType = casePtr->getService()->getServiceType();
        ServiceType type = stringToServiceType(serviceType);
        switch (type) {
            case ServiceType::Civil:    ++civil;    break;
            case ServiceType::Criminal: ++criminal; break;
            case ServiceType::Family:   ++family;   break;
        }
    }
    std::cout << "Гражданские дела: " << civil << "\n";
    std::cout << "Уголовные дела:  " << criminal << "\n";
    std::cout << "Семейные дела:    " << family << "\n";

    std::cout << "\n>>> Удаляем дело №2...\n";
    firm.removeCase(2);
    std::cout << "• Дело №2 удалено. Адвокат '" << firm.getLawyers()[1]->getFullName()
              << "' теперь " << (firm.getLawyers()[1]->getIsAvailable() ? "свободен" : "занят") << "\n";

    std::cout << "\nПроверка целостности связей: "
              << (firm.validateRelationships() ? "OK" : "ОШИБКА") << "\n";

    return 0;
}
