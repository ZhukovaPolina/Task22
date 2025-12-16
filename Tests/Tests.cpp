#include <gtest/gtest.h>
#include "../Library/Person.h"
#include "../Library/Lawyer.h"
#include "../Library/Client.h"
#include "../Library/LegalService.h"
#include "../Library/Case.h"
#include "../Library/LawFirm.h"

TEST(PersonTest, CreationAndGetters) {
    Lawyer lawyer("Адвокат", "Гражданские", 3000.0);
    EXPECT_EQ(lawyer.getFullName(), "Адвокат");
    
    Client client("Клиент", "контакт");
    EXPECT_EQ(client.getFullName(), "Клиент");
}

TEST(LawyerTest, Creation) {
    Lawyer lawyer("Адвокат", "Гражданские", 3000.0);
    
    EXPECT_EQ(lawyer.getFullName(), "Адвокат");
    EXPECT_EQ(lawyer.getSpecialization(), "Гражданские");
    EXPECT_EQ(lawyer.getHourlyRate(), 3000.0);
    EXPECT_TRUE(lawyer.getIsAvailable());
    EXPECT_EQ(lawyer.getCaseCount(), 0);
    EXPECT_EQ(lawyer.getRole(), "Адвокат");
}

TEST(LawyerTest, GetInfo) {
    Lawyer lawyer("Иванов И.И.", "Уголовные", 5000.0);
    
    std::string expectedInfo = "Адвокат Иванов И.И., специализация: Уголовные, ставка: 5000.00 руб/час, дел: 0";
    EXPECT_EQ(lawyer.getInfo(), expectedInfo);
}

TEST(LawyerTest, CaseAssignment) {
    Lawyer lawyer("Адвокат", "Гражданские", 3000.0);
    Client client("Клиент");
    LegalService service("Консультация", 5000.0, "Гражданские");
    Case caseObj(1, "Дело", &lawyer, &client, &service);
    
    EXPECT_FALSE(lawyer.getIsAvailable());
    EXPECT_EQ(lawyer.getCaseCount(), 1);
    
    EXPECT_TRUE(lawyer.involvedInCaseType("Гражданские"));
    EXPECT_TRUE(lawyer.involvedInCase("Гражданские", 1));
}

TEST(ClientTest, Creation) {
    Client client("Клиент", "тел: 111-11-11");
    
    EXPECT_EQ(client.getFullName(), "Клиент");
    EXPECT_EQ(client.getContactInfo(), "тел: 111-11-11");
    EXPECT_EQ(client.getCaseCount(), 0);
    EXPECT_EQ(client.getRole(), "Клиент");
}

TEST(ClientTest, GetInfo) {
    Client client("Петров П.П.", "email@example.com");
    
    std::string expectedInfo = "Клиент Петров П.П., контакты: email@example.com, дел: 0";
    EXPECT_EQ(client.getInfo(), expectedInfo);
}

TEST(ClientTest, AddCase) {
    Client client("Клиент");
    Lawyer lawyer("Адвокат", "Гражданские", 3000.0);
    LegalService service("Консультация", 5000.0, "Гражданские");
    Case caseObj(1, "Дело", &lawyer, &client, &service);
    
    EXPECT_EQ(client.getCaseCount(), 1);
    
    auto serviceTypes = client.getServiceTypes();
    EXPECT_EQ(serviceTypes.size(), 1);
    EXPECT_EQ(serviceTypes[0], "Гражданские");
    
    EXPECT_TRUE(client.involvedInCaseType("Гражданские"));
    EXPECT_TRUE(client.involvedInCase("Гражданские", 1));
}

TEST(LegalServiceTest, Creation) {
    LegalService service("Консультация", 5000.0, "Гражданские");
    
    EXPECT_EQ(service.getName(), "Консультация");
    EXPECT_EQ(service.getPrice(), 5000.0);
    EXPECT_EQ(service.getCategory(), "Гражданские");
}

TEST(LegalServiceTest, Modifiers) {
    LegalService service("Услуга", 1000.0, "Категория");
    
    service.setPrice(2000.0);
    EXPECT_EQ(service.getPrice(), 2000.0);
    
    service.setCategory("Новая категория");
    EXPECT_EQ(service.getCategory(), "Новая категория");
}

TEST(CaseTest, Creation) {
    Lawyer lawyer("Адвокат", "Гражданские", 3000.0);
    Client client("Клиент");
    LegalService service("Консультация", 5000.0, "Гражданские");
    Case caseObj(123, "Содержание дела", &lawyer, &client, &service);
    
    EXPECT_EQ(caseObj.getId(), 123);
    EXPECT_EQ(caseObj.getContent(), "Содержание дела");
    EXPECT_EQ(caseObj.getServiceCategory(), "Гражданские");
    EXPECT_EQ(caseObj.getLawyer(), &lawyer);
    EXPECT_EQ(caseObj.getClient(), &client);
    EXPECT_EQ(caseObj.getService(), &service);
}

TEST(CaseTest, ContentModification) {
    Lawyer lawyer("Адвокат", "Гражданские", 3000.0);
    Client client("Клиент");
    LegalService service("Услуга", 5000.0, "Категория");
    Case caseObj(1, "Старое содержание", &lawyer, &client, &service);
    
    caseObj.setContent("Новое содержание");
    EXPECT_EQ(caseObj.getContent(), "Новое содержание");
}

TEST(LawFirmTest, AddAndGetObjects) {
    LawFirm firm;
    
    firm.addService(std::make_unique<LegalService>("Консультация", 5000.0, "Гражданские"));
    firm.addService(std::make_unique<LegalService>("Защита", 100000.0, "Уголовные"));
    
    auto services = firm.getServices();
    EXPECT_EQ(services.size(), 2);
    EXPECT_EQ(services[0]->getName(), "Консультация");
    EXPECT_EQ(services[1]->getName(), "Защита");
    
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 1", "Гражданские", 3000.0));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 2", "Уголовные", 5000.0));
    
    auto lawyers = firm.getLawyers();
    EXPECT_EQ(lawyers.size(), 2);
    EXPECT_EQ(lawyers[0]->getFullName(), "Адвокат 1");
    EXPECT_EQ(lawyers[1]->getFullName(), "Адвокат 2");
    
    firm.addClient(std::make_unique<Client>("Клиент 1", "контакт1"));
    firm.addClient(std::make_unique<Client>("Клиент 2", "контакт2"));
    
    auto clients = firm.getClients();
    EXPECT_EQ(clients.size(), 2);
    EXPECT_EQ(clients[0]->getFullName(), "Клиент 1");
    EXPECT_EQ(clients[1]->getFullName(), "Клиент 2");
}

TEST(LawFirmTest, GetServicesWithPrices) {
    LawFirm firm;
    
    firm.addService(std::make_unique<LegalService>("Услуга 1", 10000.0, "Категория 1"));
    firm.addService(std::make_unique<LegalService>("Услуга 2", 20000.0, "Категория 2"));
    
    auto servicesWithPrices = firm.getServicesWithPrices();
    EXPECT_EQ(servicesWithPrices.size(), 2);
    EXPECT_EQ(servicesWithPrices[0].first, "Услуга 1");
    EXPECT_EQ(servicesWithPrices[0].second, 10000.0);
    EXPECT_EQ(servicesWithPrices[1].first, "Услуга 2");
    EXPECT_EQ(servicesWithPrices[1].second, 20000.0);
}

TEST(LawFirmTest, GetClientsByServiceType) {
    LawFirm firm;
    
    firm.addService(std::make_unique<LegalService>("Консультация", 5000.0, "Гражданские"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат", "Гражданские", 3000.0));
    firm.addClient(std::make_unique<Client>("Клиент 1"));
    firm.addClient(std::make_unique<Client>("Клиент 2"));
    
    firm.addCase(std::make_unique<Case>(1, "Дело 1", 
        firm.getLawyers()[0], 
        firm.getClients()[0], 
        firm.getServices()[0]));
    
    auto clientsByService = firm.getClientsByServiceType("Гражданские");
    EXPECT_EQ(clientsByService.size(), 1);
    EXPECT_EQ(clientsByService[0]->getFullName(), "Клиент 1");
    
    auto clientsByWrongService = firm.getClientsByServiceType("Уголовные");
    EXPECT_EQ(clientsByWrongService.size(), 0);
}

TEST(LawFirmTest, GetAvailableLawyersByService) {
    LawFirm firm;
    
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 1", "Гражданские", 3000.0));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 2", "Уголовные", 5000.0));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 3", "Гражданские", 4000.0));
    
    firm.addService(std::make_unique<LegalService>("Консультация", 5000.0, "Гражданские"));
    firm.addClient(std::make_unique<Client>("Клиент"));
    firm.addCase(std::make_unique<Case>(1, "Дело", 
        firm.getLawyers()[0], 
        firm.getClients()[0], 
        firm.getServices()[0]));
    
    auto availableLawyers = firm.getAvailableLawyersByService("Гражданские");
    EXPECT_EQ(availableLawyers.size(), 1);
    EXPECT_EQ(availableLawyers[0]->getFullName(), "Адвокат 3");
    
    auto availableLawyers2 = firm.getAvailableLawyersByService("Уголовные");
    EXPECT_EQ(
