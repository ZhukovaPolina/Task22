#include <gtest/gtest.h>
#include "../LawFirmLibrary/LawFirm.h"
#include "../LawFirmLibrary/LegalService.h"
#include "../LawFirmLibrary/Lawyer.h"
#include "../LawFirmLibrary/Client.h"
#include "../LawFirmLibrary/Case.h"


TEST(LegalServiceTest, CreationAndGetters) {
    LegalService service("Услуга 1", 10000.0, "Гражданские");

    EXPECT_EQ(service.getName(), "Услуга 1");
    EXPECT_EQ(service.getPrice(), 10000.0);
    EXPECT_EQ(service.getCategory(), "Гражданские");
}
 
TEST(LegalServiceTest, PriceModification) {
    LegalService service("Услуга", 5000.0, "Категория");

    service.setPrice(7500.0);
    EXPECT_EQ(service.getPrice(), 7500.0);
}

TEST(LegalServiceTest, CategoryModification) {
    LegalService service("Услуга", 5000.0, "Старая категория");

    service.setCategory("Новая категория");
    EXPECT_EQ(service.getCategory(), "Новая категория");
}


TEST(LawyerTest, CreationAndAvailability) {
    Lawyer lawyer("Адвокат", "Специализация");

    EXPECT_EQ(lawyer.getName(), "Адвокат");
    EXPECT_EQ(lawyer.getSpecialization(), "Специализация");
    EXPECT_TRUE(lawyer.getIsAvailable());
    EXPECT_EQ(lawyer.getCaseCount(), 0);
}

TEST(LawyerTest, CaseAssignment) {
    Lawyer lawyer("Адвокат", "Специализация");
    Client client("Клиент");
    LegalService service("Услуга", 10000.0, "Категория");
    Case caseObj(1, "Содержание", &lawyer, &client, &service);

    
    EXPECT_FALSE(lawyer.getIsAvailable());
    EXPECT_EQ(lawyer.getCaseCount(), 1);
}

TEST(LawyerTest, AvailabilityChange) {
    Lawyer lawyer("Адвокат", "Специализация");

    lawyer.setAvailability(false);
    EXPECT_FALSE(lawyer.getIsAvailable());

    lawyer.setAvailability(true);
    EXPECT_TRUE(lawyer.getIsAvailable());
}


TEST(ClientTest, Creation) {
    Client client("Клиент");

    EXPECT_EQ(client.getName(), "Клиент");
    EXPECT_EQ(client.getCaseCount(), 0);
}

TEST(ClientTest, AddCase) {
    Client client("Клиент");
    Lawyer lawyer("Адвокат", "Специализация");
    LegalService service("Услуга", 10000.0, "Категория");
    Case caseObj(1, "Содержание", &lawyer, &client, &service);

    EXPECT_EQ(client.getCaseCount(), 1);

    auto serviceTypes = client.getServiceTypes();
    EXPECT_EQ(serviceTypes.size(), 1);
    EXPECT_EQ(serviceTypes[0], "Категория");
}

TEST(ClientTest, MultipleCases) {
    Client client("Клиент");
    Lawyer lawyer1("Адвокат 1", "Специализация 1");
    Lawyer lawyer2("Адвокат 2", "Специализация 2");
    LegalService service1("Услуга 1", 10000.0, "Категория 1");
    LegalService service2("Услуга 2", 20000.0, "Категория 2");

    Case case1(1, "Дело 1", &lawyer1, &client, &service1);
    Case case2(2, "Дело 2", &lawyer2, &client, &service2);

    EXPECT_EQ(client.getCaseCount(), 2);

    auto serviceTypes = client.getServiceTypes();
    EXPECT_EQ(serviceTypes.size(), 2);
    EXPECT_EQ(serviceTypes[0], "Категория 1");
    EXPECT_EQ(serviceTypes[1], "Категория 2");
}


TEST(CaseTest, CreationAndGetters) {
    Lawyer lawyer("Адвокат", "Специализация");
    Client client("Клиент");
    LegalService service("Услуга", 10000.0, "Категория");
    Case caseObj(123, "Содержание дела", &lawyer, &client, &service);

    EXPECT_EQ(caseObj.getId(), 123);
    EXPECT_EQ(caseObj.getContent(), "Содержание дела");
    EXPECT_EQ(caseObj.getServiceType(), "Категория");
    EXPECT_EQ(caseObj.getLawyer(), &lawyer);
    EXPECT_EQ(caseObj.getClient(), &client);
    EXPECT_EQ(caseObj.getService(), &service);
}

TEST(CaseTest, ContentModification) {
    Lawyer lawyer("Адвокат", "Специализация");
    Client client("Клиент");
    LegalService service("Услуга", 10000.0, "Категория");
    Case caseObj(1, "Исходное содержание", &lawyer, &client, &service);

    caseObj.setContent("Новое содержание");
    EXPECT_EQ(caseObj.getContent(), "Новое содержание");
}


TEST(LawFirmTest, ServiceManagement) {
    LawFirm firm;

    firm.addService(std::make_unique<LegalService>("Услуга 1", 10000.0, "Категория 1"));
    firm.addService(std::make_unique<LegalService>("Услуга 2", 20000.0, "Категория 2"));

    auto services = firm.getServices();
    EXPECT_EQ(services.size(), 2);
    EXPECT_EQ(services[0]->getName(), "Услуга 1");
    EXPECT_EQ(services[1]->getName(), "Услуга 2");
}

TEST(LawFirmTest, LawyerManagement) {
    LawFirm firm;

    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 1", "Категория 1"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 2", "Категория 2"));

    auto lawyers = firm.getLawyers();
    EXPECT_EQ(lawyers.size(), 2);
    EXPECT_EQ(lawyers[0]->getName(), "Адвокат 1");
    EXPECT_EQ(lawyers[1]->getName(), "Адвокат 2");
}

TEST(LawFirmTest, ClientManagement) {
    LawFirm firm;

    firm.addClient(std::make_unique<Client>("Клиент 1"));
    firm.addClient(std::make_unique<Client>("Клиент 2"));

    auto clients = firm.getClients();
    EXPECT_EQ(clients.size(), 2);
    EXPECT_EQ(clients[0]->getName(), "Клиент 1");
    EXPECT_EQ(clients[1]->getName(), "Клиент 2");
}

TEST(LawFirmTest, CaseManagement) {
    LawFirm firm;

    
    firm.addService(std::make_unique<LegalService>("Услуга", 10000.0, "Категория"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат", "Категория"));
    firm.addClient(std::make_unique<Client>("Клиент"));

    
    firm.addCase(std::make_unique<Case>(1, "Содержание дела",
        firm.getLawyers()[0],
        firm.getClients()[0],
        firm.getServices()[0]));

    auto cases = firm.getCases();
    EXPECT_EQ(cases.size(), 1);
    EXPECT_EQ(cases[0]->getId(), 1);
    EXPECT_EQ(cases[0]->getContent(), "Содержание дела");
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

    
    firm.addService(std::make_unique<LegalService>("Услуга", 10000.0, "Категория"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат", "Категория"));
    firm.addClient(std::make_unique<Client>("Клиент 1"));
    firm.addClient(std::make_unique<Client>("Клиент 2"));

    
    firm.addCase(std::make_unique<Case>(1, "Дело",
        firm.getLawyers()[0],
        firm.getClients()[0],
        firm.getServices()[0]));

    auto clientsByService = firm.getClientsByServiceType("Категория");
    EXPECT_EQ(clientsByService.size(), 1);
    EXPECT_EQ(clientsByService[0]->getName(), "Клиент 1");

    // Проверяем, что второй клиент не найден для этой услуги
    auto clientsByWrongService = firm.getClientsByServiceType("Другая категория");
    EXPECT_EQ(clientsByWrongService.size(), 0);
}

TEST(LawFirmTest, GetAvailableLawyersByService) {
    LawFirm firm;

    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 1", "Категория 1"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 2", "Категория 2"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 3", "Категория 1"));

    firm.addClient(std::make_unique<Client>("Клиент"));
    firm.addService(std::make_unique<LegalService>("Услуга", 10000.0, "Категория 1"));
    firm.addCase(std::make_unique<Case>(1, "Дело",
        firm.getLawyers()[0],
        firm.getClients()[0],
        firm.getServices()[0]));

    auto availableLawyers1 = firm.getAvailableLawyersByService("Категория 1");
   
    EXPECT_EQ(availableLawyers1.size(), 1);
    EXPECT_EQ(availableLawyers1[0]->getName(), "Адвокат 3");

    auto availableLawyers2 = firm.getAvailableLawyersByService("Категория 2");
    EXPECT_EQ(availableLawyers2.size(), 1);
    EXPECT_EQ(availableLawyers2[0]->getName(), "Адвокат 2");

    auto availableLawyers3 = firm.getAvailableLawyersByService("Несуществующая категория");
    EXPECT_EQ(availableLawyers3.size(), 0);
}

TEST(LawFirmTest, GetCaseContent) {
    LawFirm firm;

    firm.addService(std::make_unique<LegalService>("Услуга", 10000.0, "Категория"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат", "Категория"));
    firm.addClient(std::make_unique<Client>("Клиент"));

    firm.addCase(std::make_unique<Case>(1, "Содержание дела 1",
        firm.getLawyers()[0],
        firm.getClients()[0],
        firm.getServices()[0]));

    firm.addCase(std::make_unique<Case>(2, "Содержание дела 2",
        firm.getLawyers()[0],
        firm.getClients()[0],
        firm.getServices()[0]));

    EXPECT_EQ(firm.getCaseContent(1), "Содержание дела 1");
    EXPECT_EQ(firm.getCaseContent(2), "Содержание дела 2");
    EXPECT_EQ(firm.getCaseContent(999), "Дело не найдено");
}

TEST(LawFirmTest, ComplexScenario) {
    LawFirm firm;

    
    firm.addService(std::make_unique<LegalService>("Гражданская консультация", 5000.0, "Гражданские"));
    firm.addService(std::make_unique<LegalService>("Уголовная защита", 100000.0, "Уголовные"));
    firm.addService(std::make_unique<LegalService>("Семейная консультация", 4000.0, "Семейные"));

    
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 1", "Гражданские"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 2", "Уголовные"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 3", "Семейные"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 4", "Гражданские"));

    
    firm.addClient(std::make_unique<Client>("Клиент А"));
    firm.addClient(std::make_unique<Client>("Клиент Б"));
    firm.addClient(std::make_unique<Client>("Клиент В"));

    
    auto lawyers = firm.getLawyers();
    auto clients = firm.getClients();
    auto services = firm.getServices();

    
    firm.addCase(std::make_unique<Case>(1, "Дело о договоре",
        lawyers[0], clients[0], services[0]));

    
    firm.addCase(std::make_unique<Case>(2, "Уголовное дело",
        lawyers[1], clients[1], services[1]));

    
    firm.addCase(std::make_unique<Case>(3, "Семейный спор",
        lawyers[2], clients[2], services[2]));

    auto servicesWithPrices = firm.getServicesWithPrices();
    EXPECT_EQ(servicesWithPrices.size(), 3);

    
    auto civilClients = firm.getClientsByServiceType("Гражданские");
    EXPECT_EQ(civilClients.size(), 1);
    EXPECT_EQ(civilClients[0]->getName(), "Клиент А");

    
    auto availableCivilLawyers = firm.getAvailableLawyersByService("Гражданские");
    
    EXPECT_EQ(availableCivilLawyers.size(), 1);
    EXPECT_EQ(availableCivilLawyers[0]->getName(), "Адвокат 4");

    EXPECT_EQ(firm.getCaseContent(2), "Уголовное дело");

    
    EXPECT_FALSE(lawyers[0]->getIsAvailable()); 
    EXPECT_FALSE(lawyers[1]->getIsAvailable()); 
    EXPECT_FALSE(lawyers[2]->getIsAvailable()); 
    EXPECT_TRUE(lawyers[3]->getIsAvailable());  
}