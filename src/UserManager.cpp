/**
 * @file UserManager.cpp
 * @brief Реалізація класу UserManager для керування користувачами
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/UserManager.h"
#include "../include/Constants.h"
#include <fstream>
#include <algorithm>
#include <iostream>

/**
 * @brief Конструктор за замовчуванням
 */
UserManager::UserManager() : filename(Constants::Files::USERS), currentUser(nullptr) {
}

/**
 * @brief Конструктор з параметром
 */
UserManager::UserManager(const std::string& filename)
    : filename(filename), currentUser(nullptr) {
    initializeDefaultAdmin();
}

/**
 * @brief Копіювальний конструктор
 */
UserManager::UserManager(const UserManager& other)
    : users(other.users), filename(other.filename), currentUser(nullptr) {
    // currentUser не копіюємо - кожен екземпляр має свою сесію
}

/**
 * @brief Переміщувальний конструктор
 */
UserManager::UserManager(UserManager&& other) noexcept
    : users(std::move(other.users)), filename(std::move(other.filename)),
      currentUser(other.currentUser) {
    other.currentUser = nullptr;
}

/**
 * @brief Деструктор
 */
UserManager::~UserManager() {
    currentUser = nullptr;
}

/**
 * @brief Оператор присвоєння копіюванням
 */
UserManager& UserManager::operator=(const UserManager& other) {
    if (this != &other) {
        users = other.users;
        filename = other.filename;
        currentUser = nullptr;
    }
    return *this;
}

/**
 * @brief Оператор присвоєння переміщенням
 */
UserManager& UserManager::operator=(UserManager&& other) noexcept {
    if (this != &other) {
        users = std::move(other.users);
        filename = std::move(other.filename);
        currentUser = other.currentUser;
        other.currentUser = nullptr;
    }
    return *this;
}

/**
 * @brief Ініціалізувати систему з адміністратором за замовчуванням
 */
void UserManager::initializeDefaultAdmin() {
    // Перевіряємо, чи вже є адміністратор
    if (!userExists(Constants::DefaultUser::ADMIN_LOGIN)) {
        try {
            User admin(Constants::DefaultUser::ADMIN_LOGIN,
                       Constants::DefaultUser::ADMIN_PASSWORD, true);
            users.push_back(admin);
        } catch (const std::exception& e) {
            std::cerr << "Помилка створення адміністратора: " << e.what() << std::endl;
        }
    }
}

/**
 * @brief Авторизувати користувача
 */
bool UserManager::login(const std::string& username, const std::string& password) {
    for (auto& user : users) {
        if (user.getUsername() == username && user.checkPassword(password)) {
            currentUser = &user;
            return true;
        }
    }
    return false;
}

/**
 * @brief Вийти з системи
 */
void UserManager::logout() {
    currentUser = nullptr;
}

/**
 * @brief Отримати поточного користувача
 */
User* UserManager::getCurrentUser() {
    return currentUser;
}

/**
 * @brief Перевірити, чи користувач авторизований
 */
bool UserManager::isLoggedIn() const {
    return currentUser != nullptr;
}

/**
 * @brief Перевірити, чи поточний користувач адміністратор
 */
bool UserManager::isCurrentUserAdmin() const {
    return currentUser != nullptr && currentUser->getIsAdmin();
}

/**
 * @brief Додати нового користувача
 */
bool UserManager::addUser(const User& user) {
    try {
        // Перевіряємо чи не існує вже такий користувач
        if (userExists(user.getUsername())) {
            std::cerr << "Користувач з таким логіном вже існує!" << std::endl;
            return false;
        }

        users.push_back(user);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Помилка при додаванні користувача: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Видалити користувача
 */
bool UserManager::deleteUser(const std::string& username) {
    // Не можна видалити admin
    if (username == Constants::DefaultUser::ADMIN_LOGIN) {
        std::cerr << "Не можна видалити адміністратора!" << std::endl;
        return false;
    }

    // Не можна видалити себе
    if (currentUser && currentUser->getUsername() == username) {
        std::cerr << "Не можна видалити себе!" << std::endl;
        return false;
    }

    auto it = std::remove_if(users.begin(), users.end(),
        [&username](const User& u) { return u.getUsername() == username; });

    if (it != users.end()) {
        users.erase(it, users.end());
        return true;
    }
    return false;
}

/**
 * @brief Знайти користувача за логіном
 */
User* UserManager::findUserByUsername(const std::string& username) {
    for (auto& user : users) {
        if (user.getUsername() == username) {
            return &user;
        }
    }
    return nullptr;
}

/**
 * @brief Перевірити, чи існує користувач з таким логіном
 */
bool UserManager::userExists(const std::string& username) const {
    return std::any_of(users.begin(), users.end(),
        [&username](const User& u) { return u.getUsername() == username; });
}

/**
 * @brief Отримати всіх користувачів
 */
std::vector<User> UserManager::getAllUsers() const {
    return users;
}

/**
 * @brief Отримати кількість користувачів
 */
size_t UserManager::getUserCount() const {
    return users.size();
}

/**
 * @brief Вивести всіх користувачів
 */
void UserManager::displayAll() const {
    if (users.empty()) {
        std::cout << "\nСписок користувачів порожній.\n" << std::endl;
        return;
    }

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "СПИСОК КОРИСТУВАЧІВ (Всього: " << users.size() << ")" << std::endl;
    std::cout << std::string(50, '=') << "\n" << std::endl;

    for (const auto& user : users) {
        user.display();
        std::cout << std::endl;
    }
}

/**
 * @brief Завантажити дані з файлу
 */
bool UserManager::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
        // Якщо файл не існує, створюємо адміністратора за замовчуванням
        initializeDefaultAdmin();
        return false;
    }

    users.clear();
    std::string line;

    try {
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            User user = User::fromString(line);
            users.push_back(user);
        }
        file.close();

        // Якщо після завантаження немає адміністратора, створюємо його
        if (!userExists(Constants::DefaultUser::ADMIN_LOGIN)) {
            initializeDefaultAdmin();
        }

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Помилка при завантаженні даних: " << e.what() << std::endl;
        file.close();

        // У разі помилки створюємо адміністратора за замовчуванням
        users.clear();
        initializeDefaultAdmin();
        return false;
    }
}

/**
 * @brief Зберегти дані у файл
 */
bool UserManager::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename << std::endl;
        return false;
    }

    try {
        for (const auto& user : users) {
            file << user.toString() << std::endl;
        }
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Помилка при збереженні даних: " << e.what() << std::endl;
        file.close();
        return false;
    }
}

/**
 * @brief Очистити всі дані
 */
void UserManager::clear() {
    users.clear();
    currentUser = nullptr;
    initializeDefaultAdmin();
}