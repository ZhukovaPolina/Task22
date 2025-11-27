#include <gtest/gtest.h>
#include "../LawFirmLibrary/LawFirm.h"
#include "../LawFirmLibrary/LegalService.h"
#include "../LawFirmLibrary/Lawyer.h"
#include "../LawFirmLibrary/Client.h"
#include "../LawFirmLibrary/Case.h"

TEST(LegalServiceTest, CreationAndGetters) {
    LegalService service("Услуга", "Описание услуги", 10000.0);

    EXPECT_EQ(service.getName(), "Услуга");
    EXPECT_EQ(service.getDescription(), "Описание услуги");
    EXPECT_EQ(service.getPrice(), 10000.0);
}

TEST(LegalServiceTest, PriceModification) {
    LegalService service("Услуга", "Описание", 5000.0);

    service.setPrice(7500.0);
    EXPECT_EQ(service.getPrice(), 7500.0);
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
    Client client("Клиент", "Контакты");
    Case caseObj(1, "Содержание", &lawyer, &client, "Услуга");

    lawyer.assignCase(&caseObj);
    EXPECT_FALSE(lawyer.getIsAvailable());
    EXPECT_EQ(lawyer.getCaseCount(), 1);

    lawyer.removeCase(&caseObj);
    EXPECT_TRUE(lawyer.getIsAvailable());
    EXPECT_EQ(lawyer.getCaseCount(), 0);
}

TEST(ClientTest, CreationAndCases) {
    Client client("Клиент", "Контактная информация");

    EXPECT_EQ(client.getName(), "Клиент");
    EXPECT_EQ(client.getContactInfo(), "Контактная информация");

    auto services = client.getServiceTypes();
    EXPECT_TRUE(services.empty());
}

TEST(ClientTest, ServiceTypes) {
    Client client("Клиент", "Контакты");
    Lawyer lawyer("Адвокат", "Услуга");
    Case case1(1, "Содержание 1", &lawyer, &client, "Услуга 1");
    Case case2(2, "Содержание 2", &lawyer, &client, "Услуга 2");

    client.addCase(&case1);
    client.addCase(&case2);

    auto services = client.getServiceTypes();
    EXPECT_EQ(services.size(), 2);
    EXPECT_EQ(services[0], "Услуга 1");
    EXPECT_EQ(services[1], "Услуга 2");
}

TEST(CaseTest, CreationAndGetters) {
    Lawyer lawyer("Адвокат", "Специализация");
    Client client("Клиент", "Контакты");
    Case caseObj(123, "Содержание дела", &lawyer, &client, "Тип услуги");

    EXPECT_EQ(caseObj.getId(), 123);
    EXPECT_EQ(caseObj.getContent(), "Содержание дела");
    EXPECT_EQ(caseObj.getServiceType(), "Тип услуги");
    EXPECT_EQ(caseObj.getLawyer(), &lawyer);
    EXPECT_EQ(caseObj.getClient(), &client);
}

TEST(CaseTest, ContentModification) {
    Lawyer lawyer("Адвокат", "Специализация");
    Client client("Клиент", "Контакты");
    Case caseObj(1, "Исходное содержание", &lawyer, &client, "Услуга");

    caseObj.setContent("Новое содержание");
    EXPECT_EQ(caseObj.getContent(), "Новое содержание");
}

TEST(LawFirmTest, ServiceManagement) {
    LawFirm firm;

    firm.addService(std::make_unique<LegalService>("Услуга 1", "Описание 1", 10000.0));
    firm.addService(std::make_unique<LegalService>("Услуга 2", "Описание 2", 20000.0));

    auto services = firm.getServices();
    EXPECT_EQ(services.size(), 2);
    EXPECT_EQ(services[0]->getName(), "Услуга 1");
    EXPECT_EQ(services[1]->getName(), "Услуга 2");
}

TEST(LawFirmTest, LawyerManagement) {
    LawFirm firm;

    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 1", "Специализация 1"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 2", "Специализация 2"));

    auto availableLawyers = firm.getAvailableLawyersByService("Специализация 1");
    EXPECT_EQ(availableLawyers.size(), 1);
    EXPECT_EQ(availableLawyers[0]->getName(), "Адвокат 1");
}

TEST(LawFirmTest, ClientManagement) {
    LawFirm firm;

    firm.addClient(std::make_unique<Client>("Клиент 1", "Контакты 1"));
    firm.addClient(std::make_unique<Client>("Клиент 2", "Контакты 2"));

    // Добавляем дело для клиента
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат", "Услуга"));
    firm.addCase(std::make_unique<Case>(1, "Содержание",
        firm.getAvailableLawyersByService("Услуга")[0],
        firm.getClientsByService("")[0],
        "Услуга"));

    auto clients = firm.getClientsByService("Услуга");
    EXPECT_EQ(clients.size(), 1);
    EXPECT_EQ(clients[0]->getName(), "Клиент 1");
}

TEST(LawFirmTest, CaseContentRetrieval) {
    LawFirm firm;

    firm.addLawyer(std::make_unique<Lawyer>("Адвокат", "Услуга"));
    firm.addClient(std::make_unique<Client>("Клиент", "Контакты"));
    firm.addCase(std::make_unique<Case>(1, "Содержание тестового дела",
        firm.getAvailableLawyersByService("Услуга")[0],
        firm.getClientsByService("")[0],
        "Услуга"));

    EXPECT_EQ(firm.getCaseContent(1), "Содержание тестового дела");
    EXPECT_EQ(firm.getCaseContent(999), "Case not found");
}

TEST(LawFirmTest, AvailableLawyersFiltering) {
    LawFirm firm;

    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 1", "Специализация А"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 2", "Специализация Б"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 3", "Специализация А"));

    auto availableLawyersA = firm.getAvailableLawyersByService("Специализация А");
    auto availableLawyersB = firm.getAvailableLawyersByService("Специализация Б");
    auto availableLawyersC = firm.getAvailableLawyersByService("Специализация В");

    EXPECT_EQ(availableLawyersA.size(), 2);
    EXPECT_EQ(availableLawyersB.size(), 1);
    EXPECT_EQ(availableLawyersC.size(), 0);
}