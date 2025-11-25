/**
 * @file GuestManager.cpp
 * @brief Реалізація класу GuestManager для керування гостями
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/GuestManager.h"
#include "../include/Constants.h"
#include <fstream>
#include <algorithm>
#include <iostream>

/**
 * @brief Конструктор за замовчуванням
 */
GuestManager::GuestManager() : filename(Constants::Files::GUESTS) {
}

/**
 * @brief Конструктор з параметром
 */
GuestManager::GuestManager(const std::string& filename) : filename(filename) {
}

/**
 * @brief Копіювальний конструктор
 */
GuestManager::GuestManager(const GuestManager& other)
    : guests(other.guests), filename(other.filename) {
}

/**
 * @brief Переміщувальний конструктор
 */
GuestManager::GuestManager(GuestManager&& other) noexcept
    : guests(std::move(other.guests)), filename(std::move(other.filename)) {
}

/**
 * @brief Деструктор
 */
GuestManager::~GuestManager() {
    // Деструктор
}

/**
 * @brief Оператор присвоєння копіюванням
 */
GuestManager& GuestManager::operator=(const GuestManager& other) {
    if (this != &other) {
        guests = other.guests;
        filename = other.filename;
    }
    return *this;
}

/**
 * @brief Оператор присвоєння переміщенням
 */
GuestManager& GuestManager::operator=(GuestManager&& other) noexcept {
    if (this != &other) {
        guests = std::move(other.guests);
        filename = std::move(other.filename);
    }
    return *this;
}

/**
 * @brief Додати нового гостя
 */
bool GuestManager::addGuest(const Guest& guest) {
    try {
        guests.push_back(guest);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Помилка при додаванні гостя: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Редагувати гостя за ID
 */
bool GuestManager::editGuest(int id, const Guest& newGuest) {
    for (auto& guest : guests) {
        if (guest.getId() == id) {
            guest = newGuest;
            guest.setId(id); // Зберігаємо оригінальний ID
            return true;
        }
    }
    return false;
}

/**
 * @brief Видалити гостя за ID
 */
bool GuestManager::deleteGuest(int id) {
    auto it = std::remove_if(guests.begin(), guests.end(),
        [id](const Guest& g) { return g.getId() == id; });

    if (it != guests.end()) {
        guests.erase(it, guests.end());
        return true;
    }
    return false;
}

/**
 * @brief Знайти гостя за ID
 */
Guest* GuestManager::findGuestById(int id) {
    for (auto& guest : guests) {
        if (guest.getId() == id) {
            return &guest;
        }
    }
    return nullptr;
}

/**
 * @brief Пошук гостей за прізвищем
 */
std::vector<Guest> GuestManager::searchByLastName(const std::string& lastName) const {
    std::vector<Guest> result;
    std::string lowerLastName = lastName;
    std::transform(lowerLastName.begin(), lowerLastName.end(),
                   lowerLastName.begin(), ::tolower);

    for (const auto& guest : guests) {
        std::string guestLastName = guest.getLastName();
        std::transform(guestLastName.begin(), guestLastName.end(),
                       guestLastName.begin(), ::tolower);

        if (guestLastName.find(lowerLastName) != std::string::npos) {
            result.push_back(guest);
        }
    }
    return result;
}

/**
 * @brief Пошук гостей за ім'ям
 */
std::vector<Guest> GuestManager::searchByFirstName(const std::string& firstName) const {
    std::vector<Guest> result;
    std::string lowerFirstName = firstName;
    std::transform(lowerFirstName.begin(), lowerFirstName.end(),
                   lowerFirstName.begin(), ::tolower);

    for (const auto& guest : guests) {
        std::string guestFirstName = guest.getFirstName();
        std::transform(guestFirstName.begin(), guestFirstName.end(),
                       guestFirstName.begin(), ::tolower);

        if (guestFirstName.find(lowerFirstName) != std::string::npos) {
            result.push_back(guest);
        }
    }
    return result;
}

/**
 * @brief Пошук гостя за номером телефону
 */
std::vector<Guest> GuestManager::searchByPhone(const std::string& phone) const {
    std::vector<Guest> result;
    for (const auto& guest : guests) {
        if (guest.getPhone().find(phone) != std::string::npos) {
            result.push_back(guest);
        }
    }
    return result;
}

/**
 * @brief Отримати всіх гостей
 */
std::vector<Guest> GuestManager::getAllGuests() const {
    return guests;
}

/**
 * @brief Отримати кількість гостей
 */
size_t GuestManager::getGuestCount() const {
    return guests.size();
}

/**
 * @brief Перевірити, чи існує гість з певним ID
 */
bool GuestManager::guestExists(int id) const {
    return std::any_of(guests.begin(), guests.end(),
        [id](const Guest& g) { return g.getId() == id; });
}

/**
 * @brief Сортувати гостей за прізвищем
 */
void GuestManager::sortByLastName() {
    std::sort(guests.begin(), guests.end(),
        [](const Guest& a, const Guest& b) {
            return a.getLastName() < b.getLastName();
        });
}

/**
 * @brief Сортувати гостей за ім'ям
 */
void GuestManager::sortByFirstName() {
    std::sort(guests.begin(), guests.end(),
        [](const Guest& a, const Guest& b) {
            return a.getFirstName() < b.getFirstName();
        });
}

/**
 * @brief Сортувати гостей за повним ім'ям
 */
void GuestManager::sortByFullName() {
    std::sort(guests.begin(), guests.end(),
        [](const Guest& a, const Guest& b) {
            return a < b; // Використовуємо оператор < з класу Guest
        });
}

/**
 * @brief Вивести всіх гостей
 */
void GuestManager::displayAll() const {
    if (guests.empty()) {
        std::cout << "\nСписок гостей порожній.\n" << std::endl;
        return;
    }

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "СПИСОК ГОСТЕЙ (Всього: " << guests.size() << ")" << std::endl;
    std::cout << std::string(50, '=') << "\n" << std::endl;

    for (const auto& guest : guests) {
        guest.display();
        std::cout << std::endl;
    }
}

/**
 * @brief Завантажити дані з файлу
 */
bool GuestManager::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
        return false;
    }

    guests.clear();
    std::string line;

    try {
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            Guest guest = Guest::fromCSV(line);
            guests.push_back(guest);
            Guest::updateNextId(guest.getId());
        }
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Помилка при завантаженні даних: " << e.what() << std::endl;
        file.close();
        return false;
    }
}

/**
 * @brief Зберегти дані у файл
 */
bool GuestManager::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename << std::endl;
        return false;
    }

    try {
        for (const auto& guest : guests) {
            file << guest.toCSV() << std::endl;
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
void GuestManager::clear() {
    guests.clear();
}