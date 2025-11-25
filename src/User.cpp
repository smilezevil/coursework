/**
 * @file User.cpp
 * @brief Реалізація класу User для системи авторизації
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/User.h"
#include "../include/Constants.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

/**
 * @brief Конструктор за замовчуванням
 */
User::User() : username(""), password(""), isAdmin(false) {
}

/**
 * @brief Конструктор з параметрами
 */
User::User(const std::string& username, const std::string& password, bool isAdmin)
    : username(username), password(password), isAdmin(isAdmin) {
    if (!validate()) {
        throw std::invalid_argument("Некоректні дані користувача");
    }
}

/**
 * @brief Копіювальний конструктор
 */
User::User(const User& other)
    : username(other.username), password(other.password), isAdmin(other.isAdmin) {
}

/**
 * @brief Переміщувальний конструктор
 */
User::User(User&& other) noexcept
    : username(std::move(other.username)),
      password(std::move(other.password)),
      isAdmin(other.isAdmin) {
    other.isAdmin = false;
}

/**
 * @brief Деструктор
 */
User::~User() {
    if (!username.empty()) {
    }
}

/**
 * @brief Оператор присвоєння копіюванням
 */
User& User::operator=(const User& other) {
    if (this != &other) {
        username = other.username;
        password = other.password;
        isAdmin = other.isAdmin;
    }
    return *this;
}

/**
 * @brief Оператор присвоєння переміщенням
 */
User& User::operator=(User&& other) noexcept {
    if (this != &other) {
        username = std::move(other.username);
        password = std::move(other.password);
        isAdmin = other.isAdmin;

        other.isAdmin = false;
    }
    return *this;
}

// Геттери
std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

bool User::getIsAdmin() const {
    return isAdmin;
}

// Сеттери
void User::setUsername(const std::string& username) {
    if (!isValidUsername(username)) {
        throw std::invalid_argument("Некоректний логін");
    }
    this->username = username;
}

void User::setPassword(const std::string& password) {
    if (!isValidPassword(password)) {
        throw std::invalid_argument("Некоректний пароль");
    }
    this->password = password;
}

void User::setIsAdmin(bool isAdmin) {
    this->isAdmin = isAdmin;
}

/**
 * @brief Вивести інформацію про користувача
 */
void User::display() const {
    std::cout << "┌────────────────────────────────────────┐\n";
    std::cout << "        ІНФОРМАЦІЯ ПРО КОРИСТУВАЧА        \n";
    std::cout << "├────────────────────────────────────────┤\n";
    std::cout << " Логін: " << std::left << std::setw(33) << username << "\n";
    std::cout << " Роль: " << std::left << std::setw(34)
              << (isAdmin ? "Адміністратор" : "Користувач") << "\n";
    std::cout << "└────────────────────────────────────────┘\n";
}

/**
 * @brief Перевірити валідність даних користувача
 */
bool User::validate() const {
    if (!isValidUsername(username)) {
        return false;
    }
    if (!isValidPassword(password)) {
        return false;
    }
    return true;
}

/**
 * @brief Перевірити валідність логіну
 */
bool User::isValidUsername(const std::string& username) {
    if (username.empty() || username.length() < Constants::Limits::MIN_USERNAME_LEN) {
        return false;
    }

    // Логін може містити лише літери, цифри та підкреслення
    for (char c : username) {
        if (!std::isalnum(c) && c != '_') {
            return false;
        }
    }

    return true;
}

/**
 * @brief Перевірити валідність пароля
 */
bool User::isValidPassword(const std::string& password) {
    // Пароль має бути довжиною мінімум 4 символи
    if (password.empty() || password.length() < Constants::Limits::MIN_PASSWORD_LEN) {
        return false;
    }

    return true;
}

/**
 * @brief Перевірити, чи співпадає пароль
 */
bool User::checkPassword(const std::string& password) const {
    return this->password == password;
}

/**
 * @brief Конвертувати об'єкт у рядок для збереження у файл
 */
std::string User::toString() const {
    std::ostringstream oss;
    oss << username << ":" << password << ":" << (isAdmin ? "1" : "0");
    return oss.str();
}

/**
 * @brief Створити об'єкт User з рядка
 */
User User::fromString(const std::string& line) {
    std::istringstream iss(line);
    std::string username, password, adminStr;

    try {
        // Читаємо логін
        std::getline(iss, username, ':');

        // Читаємо пароль
        std::getline(iss, password, ':');

        // Читаємо статус адміністратора
        std::getline(iss, adminStr, ':');
        bool isAdmin = (adminStr == "1");

        return User(username, password, isAdmin);
    } catch (const std::exception& e) {
        throw std::runtime_error("Помилка парсингу рядка користувача: " +
                                 std::string(e.what()));
    }
}

/**
 * @brief Оператор порівняння на рівність
 */
bool User::operator==(const User& other) const {
    return username == other.username;
}