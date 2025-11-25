/**
 * @file Guest.cpp
 * @brief Реалізація класу Guest для системи бронювання готелів
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/Guest.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <cctype>

// Ініціалізація статичної змінної
int Guest::nextId = 1;

/**
 * @brief Конструктор за замовчуванням
 */
Guest::Guest() : id(0), lastName(""), firstName(""), phone("") {
}

/**
 * @brief Конструктор з параметрами
 */
Guest::Guest(const std::string& lastName, const std::string& firstName,
             const std::string& phone)
    : id(nextId++), lastName(lastName), firstName(firstName), phone(phone) {
    if (!validate()) {
        throw std::invalid_argument("Некоректні дані гостя");
    }
}

/**
 * @brief Конструктор з усіма параметрами
 */
Guest::Guest(int id, const std::string& lastName, const std::string& firstName,
             const std::string& phone)
    : id(id), lastName(lastName), firstName(firstName), phone(phone) {
    if (!validate()) {
        throw std::invalid_argument("Некоректні дані гостя");
    }
}

/**
 * @brief Копіювальний конструктор
 */
Guest::Guest(const Guest& other)
    : id(other.id), lastName(other.lastName),
      firstName(other.firstName), phone(other.phone) {
}

/**
 * @brief Переміщувальний конструктор
 */
Guest::Guest(Guest&& other) noexcept
    : id(other.id), lastName(std::move(other.lastName)),
      firstName(std::move(other.firstName)), phone(std::move(other.phone)) {
    other.id = 0;
}

/**
 * @brief Деструктор
 */
Guest::~Guest() {
    // Деструктор - виведення повідомлення про знищення
    if (id != 0) {
        // std::cout << "Гість " << getFullName() << " (ID: " << id << ") знищено\n";
    }
}

/**
 * @brief Оператор присвоєння копіюванням
 */
Guest& Guest::operator=(const Guest& other) {
    if (this != &other) {
        id = other.id;
        lastName = other.lastName;
        firstName = other.firstName;
        phone = other.phone;
    }
    return *this;
}

/**
 * @brief Оператор присвоєння переміщенням
 */
Guest& Guest::operator=(Guest&& other) noexcept {
    if (this != &other) {
        id = other.id;
        lastName = std::move(other.lastName);
        firstName = std::move(other.firstName);
        phone = std::move(other.phone);

        other.id = 0;
    }
    return *this;
}

// Геттери
int Guest::getId() const {
    return id;
}

std::string Guest::getLastName() const {
    return lastName;
}

std::string Guest::getFirstName() const {
    return firstName;
}

std::string Guest::getFullName() const {
    return lastName + " " + firstName;
}

std::string Guest::getPhone() const {
    return phone;
}

// Сеттери
void Guest::setId(int id) {
    this->id = id;
}

void Guest::setLastName(const std::string& lastName) {
    if (lastName.empty()) {
        throw std::invalid_argument("Прізвище не може бути порожнім");
    }
    this->lastName = lastName;
}

void Guest::setFirstName(const std::string& firstName) {
    if (firstName.empty()) {
        throw std::invalid_argument("Ім'я не може бути порожнім");
    }
    this->firstName = firstName;
}

void Guest::setPhone(const std::string& phone) {
    if (!isValidPhone(phone)) {
        throw std::invalid_argument("Некоректний формат номера телефону");
    }
    this->phone = phone;
}

/**
 * @brief Вивести інформацію про гостя
 */
void Guest::display() const {
    std::cout << "┌────────────────────────────────────────┐\n";
    std::cout << "           ІНФОРМАЦІЯ ПРО ГОСТЯ           \n";
    std::cout << "├────────────────────────────────────────┤\n";
    std::cout << " ID: " << std::left << std::setw(36) << id << "\n";
    std::cout << " Прізвище: " << std::left << std::setw(30) << lastName << "\n";
    std::cout << " Ім'я: " << std::left << std::setw(34) << firstName << "\n";
    std::cout << " Телефон: " << std::left << std::setw(31) << phone << "\n";
    std::cout << "└────────────────────────────────────────┘\n";
}

/**
 * @brief Перевірити валідність даних гостя
 */
bool Guest::validate() const {
    if (lastName.empty() || firstName.empty()) {
        return false;
    }
    if (!isValidPhone(phone)) {
        return false;
    }
    return true;
}

/**
 * @brief Перевірити валідність номера телефону
 */
bool Guest::isValidPhone(const std::string& phone) {
    if (phone.empty()) {
        return false;
    }

    // Перевіряємо чи містить номер лише цифри, пробіли, дужки, + та -
    for (char c : phone) {
        if (!std::isdigit(c) && c != ' ' && c != '+' &&
            c != '-' && c != '(' && c != ')') {
            return false;
        }
    }

    // Підраховуємо кількість цифр
    int digitCount = 0;
    for (char c : phone) {
        if (std::isdigit(c)) {
            digitCount++;
        }
    }

    // Мінімум 10 цифр для валідного номера
    return digitCount >= 10;
}

/**
 * @brief Конвертувати об'єкт у рядок CSV формату
 */
std::string Guest::toCSV() const {
    std::ostringstream oss;
    oss << id << "," << lastName << "," << firstName << "," << phone;
    return oss.str();
}

/**
 * @brief Створити об'єкт Guest з рядка CSV формату
 */
Guest Guest::fromCSV(const std::string& csvLine) {
    std::istringstream iss(csvLine);
    std::string token;
    int id;
    std::string lastName, firstName, phone;

    try {
        // Читаємо ID
        std::getline(iss, token, ',');
        id = std::stoi(token);

        // Читаємо прізвище
        std::getline(iss, lastName, ',');

        // Читаємо ім'я
        std::getline(iss, firstName, ',');

        // Читаємо телефон
        std::getline(iss, phone, ',');

        return Guest(id, lastName, firstName, phone);
    } catch (const std::exception& e) {
        throw std::runtime_error("Помилка парсингу CSV: " + std::string(e.what()));
    }
}

/**
 * @brief Оновити наступний доступний ID
 */
void Guest::updateNextId(int id) {
    if (id >= nextId) {
        nextId = id + 1;
    }
}

/**
 * @brief Оператор порівняння за ім'ям (для сортування)
 */
bool Guest::operator<(const Guest& other) const {
    // Спочатку порівнюємо за прізвищем
    if (lastName != other.lastName) {
        return lastName < other.lastName;
    }
    // Якщо прізвища однакові, порівнюємо за ім'ям
    return firstName < other.firstName;
}

/**
 * @brief Оператор порівняння на рівність
 */
bool Guest::operator==(const Guest& other) const {
    return id == other.id;
}