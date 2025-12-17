#include "Lawyer.h"
#include "Case.h"
#include <algorithm>
#include <sstream>

Lawyer::Lawyer(const std::string& name, int age, const std::string& spec,
    double rate, bool available)
    : Person(name, age), specialization(spec), isAvailable(available),
    hourlyRate(rate) {}

void Lawyer::addCase(std::shared_ptr<Case> newCase) {
    if (!newCase) return;
    if (std::find(cases.begin(), cases.end(), newCase) != cases.end()) return;
    cases.push_back(newCase);
    isAvailable = false;
}

void Lawyer::removeCase(std::shared_ptr<Case> caseToRemove) {
    auto it = std::find(cases.begin(), cases.end(), caseToRemove);
    if (it != cases.end()) {
        cases.erase(it);
        isAvailable = cases.empty();
    }
}

bool Lawyer::hasCase(int caseId) const {
    return std::any_of(cases.begin(), cases.end(),
        [caseId](const auto& c) { return c && c->getId() == caseId; });
}

int Lawyer::getCasesCount() const { return static_cast<int>(cases.size()); }

std::string Lawyer::toString() const {
    std::stringstream ss;
    ss << getRole() << ": " << fullName << " (" << age << " лет)\n"
        << "Специализация: " << specialization << "\n"
        << "Ставка: " << hourlyRate << " руб/час\n"
        << "Доступен: " << (isAvailable ? "да" : "нет") << "\n"
        << "Дел: " << getCasesCount();
    if (!cases.empty()) {
        ss << "\nДела: ";
        for (size_t i = 0; i < cases.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << "#" << cases[i]->getId();
        }
    }
    return ss.str();
}

std::string Lawyer::getInfo() const {
    return "Специализация: " + specialization + ", ставка: " + std::to_string(hourlyRate) + " руб/час";
}

std::string Lawyer::getRole() const { return "Адвокат"; }