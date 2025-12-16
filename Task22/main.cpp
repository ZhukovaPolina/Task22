#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include "../Library/LawFirm.h"
#include "../Library/LegalService.h"
#include "../Library/Lawyer.h"
#include "../Library/Client.h"
#include "../Library/Case.h"

int main() {
    LawFirm firm;
    
    std::vector<std::unique_ptr<Person>> peopleCollection;
    
    peopleCollection.push_back(std::make_unique<Lawyer>("Адвокат 1", "Гражданские", 3000.0));
    peopleCollection.push_back(std::make_unique<Lawyer>("Адвокат 2", "Уголовные", 5000.0));
    peopleCollection.push_back(std::make_unique<Lawyer>("Адвокат 3", "Семейные", 2500.0));
    
    peopleCollection.push_back(std::make_unique<Client>("Клиент 1", "тел: 111-11-11"));
    peopleCollection.push_back(std::make_unique<Client>("Клиент 2", "тел: 222-22-22"));
    peopleCollection.push_back(std::make_unique<Client>("Клиент 3", "тел: 333-33-33"));
    
    for (auto& person : peopleCollection) {
        if (auto lawyer = dynamic_cast<Lawyer*>(person.get())) {
            firm.addLawyer(std::unique_ptr<Lawyer>(dynamic_cast<Lawyer*>(person.release())));
        }
        else if (auto client = dynamic_cast<Client*>(person.get())) {
            firm.addClient(std::unique_ptr<Client>(dynamic_cast<Client*>(person.release())));
        }
    }
    
    firm.addService(std::make_unique<LegalService>("Консультация по гражданским делам", 5000.0, "Гражданские"));
    firm.addService(std::make_unique<LegalService>("Защита по уголовным делам", 100000.0, "Уголовные"));
    firm.addService(std::make_unique<LegalService>("Консультация по семейным делам", 4000.0, "Семейные"));
    firm.addService(std::make_unique<LegalService>("Ведение гражданского дела", 50000.0, "Гражданские"));
    firm.addService(std::make_unique<LegalService>("Ведение уголовного дела", 150000.0, "Уголовные"));
    
    auto lawyers = firm.getLawyers();
    auto clients = firm.getClients();
    auto services = firm.getServices();
    
    if (lawyers.size() > 0 && clients.size() > 0 && services.size() > 0) {
        firm.addCase(std::make_unique<Case>(
            1, 
            "Консультация по договору аренды коммерческой недвижимости",
            lawyers[0], 
            clients[0], 
            services[0]
        ));
    }
    
    if (lawyers.size() > 1 && clients.size() > 1 && services.size() > 1) {
        firm.addCase(std::make_unique<Case>(
            2, 
            "Защита по уголовному делу по статье 158 УК РФ",
            lawyers[1], 
            clients[1], 
            services[1]
        ));
    }
    
    if (lawyers.size() > 2 && clients.size() > 2 && services.size() > 2) {
        firm.addCase(std::make_unique<Case>(
            3, 
            "Консультация по вопросу раздела имущества при разводе",
            lawyers[2], 
            clients[2], 
            services[2]
        ));
    }
    
    if (lawyers.size() > 0 && clients.size() > 0 && services.size() > 3) {
        firm.addCase(std::make_unique<Case>(
            4, 
            "Ведение дела о взыскании задолженности",
            lawyers[0], 
            clients[0], 
            services[3]
        ));
    }
    
    std::cout << "=== АДВОКАТСКАЯ КОНТОРА ===\n" << std::endl;
    
    std::cout << "1. СПИСОК УСЛУГ И ЦЕН:\n";
    auto servicesWithPrices = firm.getServicesWithPrices();
    for (const auto& [name, price] : servicesWithPrices) {
        std::cout << "   • " << std::left << std::setw(40) << name 
                  << ": " << std::right << std::setw(10) << std::fixed << std::setprecision(2) 
                  << price << " руб.\n";
    }
    
    std::cout << "\n2. КЛИЕНТЫ, ОБРАЩАВШИЕСЯ ЗА УСЛУГОЙ 'Гражданские':\n";
    auto clientsByService = firm.getClientsByServiceType("Гражданские");
    if (clientsByService.empty()) {
        std::cout << "   Нет клиентов\n";
    } else {
        for (const auto& client : clientsByService) {
            std::cout << "   • " << client->getFullName() 
                      << " (" << client->getContactInfo() << ")\n";
        }
    }
    
    std::cout << "\n3. СВОБОДНЫЕ АДВОКАТЫ ПО УСЛУГЕ 'Уголовные':\n";
    auto availableLawyers = firm.getAvailableLawyersByService("Уголовные");
    if (availableLawyers.empty()) {
        std::cout << "   Нет свободных адвокатов\n";
    } else {
        for (const auto& lawyer : availableLawyers) {
            std::cout << "   • " << lawyer->getFullName() 
                      << " (специализация: " << lawyer->getSpecialization() 
                      << ", ставка: " << lawyer->getHourlyRate() << " руб/час)\n";
        }
    }
    
    std::cout << "\n4. СОДЕРЖАНИЕ ДЕЛА №1:\n";
    std::cout << "   " << firm.getCaseContent(1) << "\n";
    
    std::cout << "\n5. СОДЕРЖАНИЕ ДЕЛА №4:\n";
    std::cout << "   " << firm.getCaseContent(4) << "\n";
    
    std::cout << "\n6. ПОПЫТКА ПОЛУЧИТЬ НЕСУЩЕСТВУЮЩЕЕ ДЕЛО (№99):\n";
    std::cout << "   " << firm.getCaseContent(99) << "\n";
    
    std::cout << "\n=== КОЛЛЕКЦИЯ PERSON (базовый класс) ===\n";
    
    std::vector<Person*> allPeople = firm.getAllPeople();
    
    for (const auto& person : allPeople) {
        std::cout << "• " << person->getRole() << ": " << person->getFullName()
                  << " | " << person->getInfo() << "\n";
    }
    
    std::cout << "\n=== ДОПОЛНИТЕЛЬНАЯ ИНФОРМАЦИЯ ===\n";
    
    std::cout << "Общее количество дел в конторе: " << firm.getTotalCases() << "\n";
    
    std::cout << "\nАдвокаты и их дела:\n";
    for (const auto& lawyer : firm.getLawyers()) {
        std::cout << "• " << lawyer->getFullName() 
                  << " (дел: " << lawyer->getCaseCount() 
                  << ", доступен: " << (lawyer->getIsAvailable() ? "да" : "нет") << ")\n";
    }
    
    std::cout << "\nКлиенты и их дела:\n";
    for (const auto& client : firm.getClients()) {
        auto serviceTypes = client->getServiceTypes();
        std::cout << "• " << client->getFullName() 
                  << " (дел: " << client->getCaseCount() 
                  << ", услуги: ";
        for (size_t i = 0; i < serviceTypes.size(); ++i) {
            std::cout << serviceTypes[i];
            if (i < serviceTypes.size() - 1) std::cout << ", ";
        }
        std::cout << ")\n";
    }
    
    std::cout << "\nПроверка целостности взаимосвязей: ";
    if (firm.validateRelationships()) {
        std::cout << "ОК (все связи корректны)\n";
    } else {
        std::cout << "ОШИБКА (нарушены связи между объектами)\n";
    }
    
    return 0;
}
