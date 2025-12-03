#include <iostream>
#include <vector>
#include <memory>
#include "../LawFirmLibrary/LawFirm.h"
#include "../LawFirmLibrary/LegalService.h"
#include "../LawFirmLibrary/Consultation.h"
#include "../LawFirmLibrary/CourtCase.h"
#include "../LawFirmLibrary/Lawyer.h"
#include "../LawFirmLibrary/Client.h"
#include "../LawFirmLibrary/Case.h"

int main() {
    
    LawFirm firm;

    
    std::vector<std::unique_ptr<LegalService>> servicesCollection;

    
    servicesCollection.push_back(std::make_unique<Consultation>(
        "Консультация по гражданским делам",
        5000.0,
        "Гражданские"
    ));

    servicesCollection.push_back(std::make_unique<Consultation>(
        "Консультация по уголовным делам",
        7000.0,
        "Уголовные"
    ));

    servicesCollection.push_back(std::make_unique<CourtCase>(
        "Ведение гражданского дела в суде",
        50000.0,
        "Гражданские"
    ));

    servicesCollection.push_back(std::make_unique<CourtCase>(
        "Ведение уголовного дела в суде",
        100000.0,
        "Уголовные"
    ));

    servicesCollection.push_back(std::make_unique<Consultation>(
        "Консультация по семейным делам",
        4000.0,
        "Семейные"
    ));

    
    for (auto& service : servicesCollection) {
        firm.addService(std::move(service));
    }

    
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 1", "Гражданские"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 2", "Уголовные"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 3", "Семейные"));

    
    firm.addClient(std::make_unique<Client>("Клиент 1"));
    firm.addClient(std::make_unique<Client>("Клиент 2"));
    firm.addClient(std::make_unique<Client>("Клиент 3"));

    
    auto lawyers = firm.getLawyers();
    auto clients = firm.getClients();
    auto services = firm.getServices();

    // Дело 1: Консультация по гражданским делам
    if (lawyers.size() > 0 && clients.size() > 0 && services.size() > 0) {
        firm.addCase(std::make_unique<Case>(
            1,
            "Консультация по договору аренды",
            lawyers[0],
            clients[0],
            services[0]
        ));
    }

    // Дело 2: Ведение уголовного дела
    if (lawyers.size() > 1 && clients.size() > 1 && services.size() > 3) {
        firm.addCase(std::make_unique<Case>(
            2,
            "Защита по уголовному делу",
            lawyers[1],
            clients[1],
            services[3]
        ));
    }

    // Дело 3: Консультация по семейным делам
    if (lawyers.size() > 2 && clients.size() > 2 && services.size() > 4) {
        firm.addCase(std::make_unique<Case>(
            3,
            "Консультация по вопросу раздела имущества",
            lawyers[2],
            clients[2],
            services[4]
        ));
    }

   

    // 1. Показывать список предоставляемых услуг и их цену
    std::cout << "1. СПИСОК УСЛУГ И ЦЕН:\n";
    auto servicesWithPrices = firm.getServicesWithPrices();
    for (const auto& [name, price] : servicesWithPrices) {
        std::cout << "   " << name << ": " << price << " руб.\n";
    }

    // 2. Выдавать список клиентов, обращавшихся за данной услугой
    std::cout << "\n2. КЛИЕНТЫ ПО УСЛУГЕ 'Консультация':\n";
    auto clientsByService = firm.getClientsByServiceType("Консультация");
    for (const auto& client : clientsByService) {
        std::cout << "   " << client->getName() << "\n";
    }

    // 3. Выдавать список свободных адвокатов по выбранной услуге
    std::cout << "\n3. СВОБОДНЫЕ АДВОКАТЫ ПО УСЛУГЕ 'Семейные':\n";
    auto availableLawyers = firm.getAvailableLawyersByService("Семейные");
    for (const auto& lawyer : availableLawyers) {
        std::cout << "   " << lawyer->getName()
            << " (специализация: " << lawyer->getSpecialization() << ")\n";
    }

    // 4. Выдавать содержание Дела по его номеру
    std::cout << "\n4. СОДЕРЖАНИЕ ДЕЛА №2:\n";
    std::cout << "   " << firm.getCaseContent(2) << "\n";

    // === КОЛЛЕКЦИЯ БАЗОВОГО КЛАССА (требование из задания) ===
    std::cout << "\n=== КОЛЛЕКЦИЯ УСЛУГ (базовый класс LegalService) ===\n";

    // Проитерировать коллекцию элементов как коллекцию базового класса
    auto allServices = firm.getServices();
    for (const auto& service : allServices) {
        // Выводим информацию о текущем объекте
        std::cout << "Услуга: " << service->getName()
            << " | Тип: " << service->getServiceType()
            << " | Цена: " << service->getPrice() << " руб.\n";
    }

    return 0;
}