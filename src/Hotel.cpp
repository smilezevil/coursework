/**
 * @file Hotel.cpp
 * @brief Реалізація класу Hotel для системи бронювання готелів
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/Hotel.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>

// Ініціалізація статичної змінної
int Hotel::nextId = 1;

/**
 * @brief Конструктор за замовчуванням
 */
Hotel::Hotel() : id(0), name(""), city(""), stars(0) {
    // Порожній конструктор
}

/**
 * @brief Конструктор з параметрами
 */
Hotel::Hotel(const std::string& name, const std::string& city, int stars)
    : id(nextId++), name(name), city(city), stars(stars) {
    if (!validate()) {
        throw std::invalid_argument("Некоректні дані готелю");
    }
}

/**
 * @brief Конструктор з усіма параметрами
 */
Hotel::Hotel(int id, const std::string& name, const std::string& city, int stars)
    : id(id), name(name), city(city), stars(stars) {
    if (!validate()) {
        throw std::invalid_argument("Некоректні дані готелю");
    }
}

/**
 * @brief Копіювальний конструктор
 */
Hotel::Hotel(const Hotel& other)
    : id(other.id), name(other.name), city(other.city), stars(other.stars) {
    // Конструктор копіювання
}

/**
 * @brief Переміщувальний конструктор
 */
Hotel::Hotel(Hotel&& other) noexcept
    : id(other.id), name(std::move(other.name)),
      city(std::move(other.city)), stars(other.stars) {
    other.id = 0;
    other.stars = 0;
}

/**
 * @brief Деструктор
 */
Hotel::~Hotel() {
    // Деструктор - виведення повідомлення про знищення
    if (id != 0) {
        // std::cout << "Готель " << name << " (ID: " << id << ") знищено\n";
    }
}

/**
 * @brief Оператор присвоєння копіюванням
 */
Hotel& Hotel::operator=(const Hotel& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        city = other.city;
        stars = other.stars;
    }
    return *this;
}

/**
 * @brief Оператор присвоєння переміщенням
 */
Hotel& Hotel::operator=(Hotel&& other) noexcept {
    if (this != &other) {
        id = other.id;
        name = std::move(other.name);
        city = std::move(other.city);
        stars = other.stars;

        other.id = 0;
        other.stars = 0;
    }
    return *this;
}

// Геттери
int Hotel::getId() const {
    return id;
}

std::string Hotel::getName() const {
    return name;
}

std::string Hotel::getCity() const {
    return city;
}

int Hotel::getStars() const {
    return stars;
}

// Сеттери
void Hotel::setId(int id) {
    this->id = id;
}

void Hotel::setName(const std::string& name) {
    this->name = name;
}

void Hotel::setCity(const std::string& city) {
    this->city = city;
}

void Hotel::setStars(int stars) {
    if (stars < 1 || stars > 5) {
        throw std::invalid_argument("Кількість зірок має бути від 1 до 5");
    }
    this->stars = stars;
}

/**
 * @brief Вивести інформацію про готель
 */
void Hotel::display() const {
    std::cout << "┌────────────────────────────────────────┐\n";
    std::cout << " ID: " << std::left << std::setw(35) << id << "\n";
    std::cout << " Назва: " << std::left << std::setw(32) << name << "\n";
    std::cout << " Місто: " << std::left << std::setw(32) << city << "\n";
    std::cout << " Зірок: ";
    for (int i = 0; i < stars; i++) {
        std::cout << "★";
    }
    for (int i = stars; i < 5; i++) {
        std::cout << "☆";
    }
    std::cout << std::setw(32 - stars * 3) << " " << "\n";
    std::cout << "└────────────────────────────────────────┘\n";
}

/**
 * @brief Перевірити валідність даних готелю
 */
bool Hotel::validate() const {
    if (name.empty()) {
        return false;
    }
    if (city.empty()) {
        return false;
    }
    if (stars < 1 || stars > 5) {
        return false;
    }
    return true;
}

/**
 * @brief Конвертувати об'єкт у рядок CSV формату
 */
std::string Hotel::toCSV() const {
    std::ostringstream oss;
    oss << id << "," << name << "," << city << "," << stars;
    return oss.str();
}

/**
 * @brief Створити об'єкт Hotel з рядка CSV формату
 */
Hotel Hotel::fromCSV(const std::string& csvLine) {
    std::istringstream iss(csvLine);
    std::string token;
    int id, stars;
    std::string name, city;

    try {
        // Читаємо ID
        std::getline(iss, token, ',');
        id = std::stoi(token);

        // Читаємо назву
        std::getline(iss, name, ',');

        // Читаємо місто
        std::getline(iss, city, ',');

        // Читаємо зірки
        std::getline(iss, token, ',');
        stars = std::stoi(token);

        return Hotel(id, name, city, stars);
    } catch (const std::exception& e) {
        throw std::runtime_error("Помилка парсингу CSV: " + std::string(e.what()));
    }
}

/**
 * @brief Оновити наступний доступний ID
 */
void Hotel::updateNextId(int id) {
    if (id >= nextId) {
        nextId = id + 1;
    }
}