#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "../Library/LawFirm.h"
#include "../Library/Client.h"
#include "../Library/Lawyer.h"
#include "../Library/LegalService.h"
#include "../Library/Case.h"

TEST(LawFirmTest, AddAndGetEntities) {
    LawFirm firm;

    firm.addService(std::make_unique<LegalService>("Консультация", 5000.0, "Гражданские"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат 1", 35, "Уголовные", 5000.0));
    firm.addClient(std::make_unique<Client>("Клиент 1", 30, "client1@test.ru"));

    
    auto services = firm.getServices();
    auto lawyers = firm.getLawyers();
    auto clients = firm.getClients();

    ASSERT_EQ(services.size(), 1);
    ASSERT_EQ(lawyers.size(), 1);
    ASSERT_EQ(clients.size(), 1);

    EXPECT_EQ(services[0]->getName(), "Консультация");
    EXPECT_EQ(lawyers[0]->getFullName(), "Адвокат 1");
    EXPECT_EQ(clients[0]->getFullName(), "Клиент 1");
}

TEST(LawFirmTest, AddCasePropagatesToAllEntities) {
    LawFirm firm;

    firm.addClient(std::make_unique<Client>("Иванов", 28, "ivanov@test.com"));
    firm.addLawyer(std::make_unique<Lawyer>("Смирнова", 34, "Гражданские", 2900.0));
    firm.addService(std::make_unique<LegalService>("Договор", 12000.0, "Гражданские"));

    auto clients = firm.getClients();
    auto lawyers = firm.getLawyers();
    auto services = firm.getServices();

    auto casePtr = std::make_shared<Case>(101, "Составление договора",
        lawyers[0], clients[0], services[0]);

    firm.addCase(casePtr);

    
    EXPECT_EQ(firm.getTotalCases(), 1);
    EXPECT_EQ(firm.getCases().size(), 1);
    EXPECT_EQ(firm.getCases()[0], casePtr.get());

    
    EXPECT_EQ(lawyers[0]->getCasesCount(), 1);
    EXPECT_EQ(clients[0]->getCasesCount(), 1);
    EXPECT_EQ(services[0]->getCaseCount(), 1);

    
    EXPECT_FALSE(lawyers[0]->getIsAvailable());
}

TEST(LawFirmTest, GetServicesWithPrices) {
    LawFirm firm;

    firm.addService(std::make_unique<LegalService>("Консультация", 5000.0, "Гражданские"));
    firm.addService(std::make_unique<LegalService>("Защита", 120000.0, "Уголовные"));

    auto prices = firm.getServicesWithPrices();

    ASSERT_EQ(prices.size(), 2);
    EXPECT_EQ(prices[0].first, "Консультация");
    EXPECT_DOUBLE_EQ(prices[0].second, 5000.0);
    EXPECT_EQ(prices[1].first, "Защита");
    EXPECT_DOUBLE_EQ(prices[1].second, 120000.0);
}

TEST(LawFirmTest, GetClientsByServiceType) {
    LawFirm firm;

    firm.addClient(std::make_unique<Client>("Клиент A", 40, "a@test.ru"));
    firm.addClient(std::make_unique<Client>("Клиент B", 35, "b@test.ru"));
    firm.addLawyer(std::make_unique<Lawyer>("Любой", 30, "Любой", 1000.0));
    firm.addService(std::make_unique<LegalService>("Гражданская", 10000.0, "Гражданские"));
    firm.addService(std::make_unique<LegalService>("Уголовная", 50000.0, "Уголовные"));

    auto clients = firm.getClients();
    auto lawyers = firm.getLawyers();
    auto services = firm.getServices();

    
    auto case1 = std::make_shared<Case>(1, "Гражданское дело", lawyers[0], clients[0], services[0]);
    firm.addCase(case1);

    
    auto case2 = std::make_shared<Case>(2, "Уголовное дело", lawyers[0], clients[1], services[1]);
    firm.addCase(case2);

    auto civilClients = firm.getClientsByServiceType("Гражданские");
    ASSERT_EQ(civilClients.size(), 1);
    EXPECT_EQ(civilClients[0]->getFullName(), "Клиент A");

    auto criminalClients = firm.getClientsByServiceType("Уголовные");
    ASSERT_EQ(criminalClients.size(), 1);
    EXPECT_EQ(criminalClients[0]->getFullName(), "Клиент B");
}TEST(LawFirmTest, GetAvailableLawyersByService) {
    LawFirm firm;

    auto lawyer1 = std::make_unique<Lawyer>("Свободный", 32, "Гражданские", 2800.0);
    auto lawyer2 = std::make_unique<Lawyer>("Занятый", 38, "Гражданские", 3100.0);
    auto lawyer3 = std::make_unique<Lawyer>("Другой", 40, "Уголовные", 5200.0);

    firm.addLawyer(std::move(lawyer1));
    firm.addLawyer(std::move(lawyer2));
    firm.addLawyer(std::move(lawyer3));

    firm.addClient(std::make_unique<Client>("Клиент", 30, "c@test.ru"));
    firm.addService(std::make_unique<LegalService>("Услуга", 8000.0, "Гражданские"));

    auto lawyers = firm.getLawyers();
    auto clients = firm.getClients();
    auto services = firm.getServices();

    
    auto casePtr = std::make_shared<Case>(1, "Дело", lawyers[1], clients[0], services[0]);
    firm.addCase(casePtr);

    
    auto available = firm.getAvailableLawyersByService("Гражданские");
    ASSERT_EQ(available.size(), 1);
    EXPECT_EQ(available[0]->getFullName(), "Свободный");

    auto availableCriminal = firm.getAvailableLawyersByService("Уголовные");
    ASSERT_EQ(availableCriminal.size(), 1);
    EXPECT_EQ(availableCriminal[0]->getFullName(), "Другой");
}

TEST(LawFirmTest, GetCaseContent) {
    LawFirm firm;

    firm.addClient(std::make_unique<Client>("Клиент", 30, "test@test.ru"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат", 35, "Семейные", 2500.0));
    firm.addService(std::make_unique<LegalService>("Консультация", 4000.0, "Семейные"));

    auto casePtr = std::make_shared<Case>(555, "Раздел имущества",
        firm.getLawyers()[0], firm.getClients()[0], firm.getServices()[0]);

    firm.addCase(casePtr);

    EXPECT_EQ(firm.getCaseContent(555), "Раздел имущества");
    EXPECT_EQ(firm.getCaseContent(999), "Дело не найдено");
}



TEST(LawFirmTest, RemoveCaseById) {
    LawFirm firm;

    firm.addClient(std::make_unique<Client>("Клиент", 30, "c@test.ru"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат", 35, "Гражданские", 3000.0));
    firm.addService(std::make_unique<LegalService>("Услуга", 10000.0, "Гражданские"));

    auto casePtr = std::make_shared<Case>(777, "Тестовое дело",
        firm.getLawyers()[0], firm.getClients()[0], firm.getServices()[0]);

    firm.addCase(casePtr);

    
    EXPECT_EQ(firm.getTotalCases(), 1);
    EXPECT_EQ(firm.getLawyers()[0]->getCasesCount(), 1);
    EXPECT_EQ(firm.getClients()[0]->getCasesCount(), 1);
    EXPECT_EQ(firm.getServices()[0]->getCaseCount(), 1);
    EXPECT_FALSE(firm.getLawyers()[0]->getIsAvailable());

    
    bool removed = firm.removeCase(777);
    EXPECT_TRUE(removed);

    
    EXPECT_EQ(firm.getTotalCases(), 0);
    EXPECT_EQ(firm.getLawyers()[0]->getCasesCount(), 0);
    EXPECT_EQ(firm.getClients()[0]->getCasesCount(), 0);
    EXPECT_EQ(firm.getServices()[0]->getCaseCount(), 0);
    EXPECT_TRUE(firm.getLawyers()[0]->getIsAvailable()); // снова доступен
}

TEST(LawFirmTest, RemoveNonExistentCaseReturnsFalse) {
    LawFirm firm;
    bool removed = firm.removeCase(999);
    EXPECT_FALSE(removed);
}


TEST(LawFirmTest, ValidateRelationshipsPassesForConsistentState) {
    LawFirm firm;

    firm.addClient(std::make_unique<Client>("Клиент", 30, "c@test.ru"));
    firm.addLawyer(std::make_unique<Lawyer>("Адвокат", 35, "Уголовные", 5000.0));
    firm.addService(std::make_unique<LegalService>("Защита", 100000.0, "Уголовные"));

    auto casePtr = std::make_shared<Case>(1, "Дело",
        firm.getLawyers()[0], firm.getClients()[0], firm.getServices()[0]);

    firm.addCase(casePtr);

    EXPECT_TRUE(firm.validateRelationships());
}TEST(LawFirmTest, GetAllPeopleReturnsCorrectCountAndTypes) {
    LawFirm firm;

    firm.addLawyer(std::make_unique<Lawyer>("Л1", 30, "Т", 1000.0));
    firm.addLawyer(std::make_unique<Lawyer>("Л2", 35, "Т", 1000.0));
    firm.addClient(std::make_unique<Client>("К1", 25, "k1@test.ru"));
    firm.addClient(std::make_unique<Client>("К2", 28, "k2@test.ru"));
    firm.addClient(std::make_unique<Client>("К3", 40, "k3@test.ru"));

    auto people = firm.getAllPeople();

    EXPECT_EQ(people.size(), 5);
    EXPECT_EQ(people[0]->getRole(), "Адвокат");
    EXPECT_EQ(people[1]->getRole(), "Адвокат");
    EXPECT_EQ(people[2]->getRole(), "Клиент");
    EXPECT_EQ(people[3]->getRole(), "Клиент");
    EXPECT_EQ(people[4]->getRole(), "Клиент");
}  