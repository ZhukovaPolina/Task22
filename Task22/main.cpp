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

    

    firm.addService(std::make_unique<LegalService>("Гражданские дела", "Ведение гражданских дел", 25000.0));
    firm.addService(std::make_unique<LegalService>("Уголовные дела", "Защита по уголовным делам", 50000.0));
    firm.addService(std::make_unique<LegalService>("Семейные дела", "Семейные споры", 20000.0));
    firm.addService(std::make_unique<LegalService>("Жилищные дела", "Жилищные споры", 30000.0));

   
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 1", "Гражданские дела"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 2", "Уголовные дела"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 3", "Семейные дела"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 4", "Жилищные дела"));

    
    firm.addClient(std::make_unique<Client>("Клиент 1", "контакт1"));
    firm.addClient(std::make_unique<Client>("Клиент 2", "контакт2"));
    firm.addClient(std::make_unique<Client>("Клиент 3", "контакт3"));

    
    auto lawyers = firm.getAvailableLawyersByService("Гражданские дела");
    auto clients = firm.getClientsByService("");
    if (!lawyers.empty() && !clients.empty()) {
        firm.addCase(std::make_unique<Case>(1, "Содержание дела 1", lawyers[0], clients[0], "Гражданские дела"));
    }

    lawyers = firm.getAvailableLawyersByService("Уголовные дела");
    if (!lawyers.empty() && clients.size() > 1) {
        firm.addCase(std::make_unique<Case>(2, "Содержание дела 2", lawyers[0], clients[1], "Уголовные дела"));
    }

    

    
    std::cout << "=== СПИСОК УСЛУГ И ЦЕН ===\n";
    auto services = firm.getServices();
    for (const auto& service : services) {
        std::cout << "Услуга: " << service->getName()
            << " | Цена: " << service->getPrice() << " руб.\n";
    }

    
    std::cout << "\n=== КЛИЕНТЫ ПО УСЛУГЕ 'Гражданские дела' ===\n";
    auto civilClients = firm.getClientsByService("Гражданские дела");
    for (const auto& client : civilClients) {
        std::cout << "Клиент: " << client->getName() << "\n";
    }

    std::cout << "\n=== СВОБОДНЫЕ АДВОКАТЫ ПО УСЛУГЕ 'Семейные дела' ===\n";
    auto availableLawyers = firm.getAvailableLawyersByService("Семейные дела");
    for (const auto& lawyer : availableLawyers) {
        std::cout << "Адвокат: " << lawyer->getName()
            << " | Специализация: " << lawyer->getSpecialization() << "\n";
    }

    
    std::cout << "\n=== СОДЕРЖАНИЕ ДЕЛА №1 ===\n";
    std::cout << firm.getCaseContent(1) << "\n";

    std::cout << "\n=== СОДЕРЖАНИЕ ДЕЛА №2 ===\n";
    std::cout << firm.getCaseContent(2) << "\n";

    return 0;
}