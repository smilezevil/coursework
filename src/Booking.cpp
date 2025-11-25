/**
 * @file Booking.cpp
 * @brief Реалізація класу Booking для системи бронювання готелів
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/Booking.h"
#include "../include/Constants.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

// Ініціалізація статичної змінної
int Booking::nextId = 1;

/**
 * @brief Конструктор за замовчуванням
 */
Booking::Booking() : id(0), guestId(0), roomId(0), checkInDate(""), checkOutDate("") {
}

/**
 * @brief Конструктор з параметрами
 */
Booking::Booking(int guestId, int roomId, const std::string& checkInDate,
                 const std::string& checkOutDate)
    : id(nextId++), guestId(guestId), roomId(roomId),
      checkInDate(checkInDate), checkOutDate(checkOutDate) {
    if (!validate()) {
        throw std::invalid_argument("Некоректні дані бронювання");
    }
}

/**
 * @brief Конструктор з усіма параметрами
 */
Booking::Booking(int id, int guestId, int roomId, const std::string& checkInDate,
                 const std::string& checkOutDate)
    : id(id), guestId(guestId), roomId(roomId),
      checkInDate(checkInDate), checkOutDate(checkOutDate) {
    if (!validate()) {
        throw std::invalid_argument("Некоректні дані бронювання");
    }
}

/**
 * @brief Копіювальний конструктор
 */
Booking::Booking(const Booking& other)
    : id(other.id), guestId(other.guestId), roomId(other.roomId),
      checkInDate(other.checkInDate), checkOutDate(other.checkOutDate) {
}

/**
 * @brief Переміщувальний конструктор
 */
Booking::Booking(Booking&& other) noexcept
    : id(other.id), guestId(other.guestId), roomId(other.roomId),
      checkInDate(std::move(other.checkInDate)),
      checkOutDate(std::move(other.checkOutDate)) {
    other.id = 0;
    other.guestId = 0;
    other.roomId = 0;
}

/**
 * @brief Деструктор
 */
Booking::~Booking() {
    // Деструктор
    if (id != 0) {
        // std::cout << "Бронювання ID: " << id << " знищено\n";
    }
}

/**
 * @brief Оператор присвоєння копіюванням
 */
Booking& Booking::operator=(const Booking& other) {
    if (this != &other) {
        id = other.id;
        guestId = other.guestId;
        roomId = other.roomId;
        checkInDate = other.checkInDate;
        checkOutDate = other.checkOutDate;
    }
    return *this;
}

/**
 * @brief Оператор присвоєння переміщенням
 */
Booking& Booking::operator=(Booking&& other) noexcept {
    if (this != &other) {
        id = other.id;
        guestId = other.guestId;
        roomId = other.roomId;
        checkInDate = std::move(other.checkInDate);
        checkOutDate = std::move(other.checkOutDate);

        other.id = 0;
        other.guestId = 0;
        other.roomId = 0;
    }
    return *this;
}

// Геттери
int Booking::getId() const {
    return id;
}

int Booking::getGuestId() const {
    return guestId;
}

int Booking::getRoomId() const {
    return roomId;
}

std::string Booking::getCheckInDate() const {
    return checkInDate;
}

std::string Booking::getCheckOutDate() const {
    return checkOutDate;
}

// Сеттери
void Booking::setId(int id) {
    this->id = id;
}

void Booking::setGuestId(int guestId) {
    if (guestId <= 0) {
        throw std::invalid_argument("ID гостя має бути додатнім");
    }
    this->guestId = guestId;
}

void Booking::setRoomId(int roomId) {
    if (roomId <= 0) {
        throw std::invalid_argument("ID номера має бути додатнім");
    }
    this->roomId = roomId;
}

void Booking::setCheckInDate(const std::string& checkInDate) {
    if (!isValidDate(checkInDate)) {
        throw std::invalid_argument("Некоректна дата заїзду");
    }
    this->checkInDate = checkInDate;
}

void Booking::setCheckOutDate(const std::string& checkOutDate) {
    if (!isValidDate(checkOutDate)) {
        throw std::invalid_argument("Некоректна дата виїзду");
    }
    this->checkOutDate = checkOutDate;
}

/**
 * @brief Вивести інформацію про бронювання
 */
void Booking::display() const {
    std::cout << "┌────────────────────────────────────────┐\n";
    std::cout << "        ІНФОРМАЦІЯ ПРО БРОНЮВАННЯ         \n";
    std::cout << "├────────────────────────────────────────┤\n";
    std::cout << " ID бронювання: " << std::left << std::setw(23) << id << "\n";
    std::cout << " ID гостя: " << std::left << std::setw(30) << guestId << "\n";
    std::cout << " ID номера: " << std::left << std::setw(29) << roomId << "\n";
    std::cout << " Дата заїзду: " << std::left << std::setw(27) << checkInDate << "\n";
    std::cout << " Дата виїзду: " << std::left << std::setw(27) << checkOutDate << "\n";
    std::cout << " Кількість днів: " << std::left << std::setw(24) << calculateDays() << "\n";
    std::cout << "└────────────────────────────────────────┘\n";
}

/**
 * @brief Перевірити валідність даних бронювання
 */
bool Booking::validate() const {
    if (guestId <= 0 || roomId <= 0) {
        return false;
    }
    if (!isValidDate(checkInDate) || !isValidDate(checkOutDate)) {
        return false;
    }
    if (!areDatesValid()) {
        return false;
    }
    return true;
}

/**
 * @brief Перевірити валідність дати
 */
bool Booking::isValidDate(const std::string& date) {
    if (date.length() != Constants::Limits::DATE_LENGTH) {
        return false;
    }

    // Перевіряємо формат YYYY-MM-DD
    if (date[4] != '-' || date[7] != '-') {
        return false;
    }

    try {
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));

        // Перевірка діапазонів
        if (year < 2020 || year > 2100) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;

        // Перевірка днів у місяці
        if (month == 2) {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > (isLeap ? 29 : 28)) return false;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day > 30) return false;
        }

        return true;
    } catch (...) {
        return false;
    }
}

/**
 * @brief Перевірити, чи дата заїзду раніше дати виїзду
 */
bool Booking::areDatesValid() const {
    return compareDates(checkInDate, checkOutDate) < 0;
}

/**
 * @brief Розрахувати кількість днів проживання
 */
int Booking::calculateDays() const {
    try {
        int year1 = std::stoi(checkInDate.substr(0, 4));
        int month1 = std::stoi(checkInDate.substr(5, 2));
        int day1 = std::stoi(checkInDate.substr(8, 2));

        int year2 = std::stoi(checkOutDate.substr(0, 4));
        int month2 = std::stoi(checkOutDate.substr(5, 2));
        int day2 = std::stoi(checkOutDate.substr(8, 2));

        // Спрощений розрахунок (не враховує всі нюанси)
        int days1 = year1 * 365 + month1 * 30 + day1;
        int days2 = year2 * 365 + month2 * 30 + day2;

        return days2 - days1;
    } catch (...) {
        return 0;
    }
}

/**
 * @brief Конвертувати об'єкт у рядок CSV формату
 */
std::string Booking::toCSV() const {
    std::ostringstream oss;
    oss << id << "," << guestId << "," << roomId << ","
        << checkInDate << "," << checkOutDate;
    return oss.str();
}

/**
 * @brief Створити об'єкт Booking з рядка CSV формату
 */
Booking Booking::fromCSV(const std::string& csvLine) {
    std::istringstream iss(csvLine);
    std::string token;
    int id, guestId, roomId;
    std::string checkInDate, checkOutDate;

    try {
        // Читаємо ID
        std::getline(iss, token, ',');
        id = std::stoi(token);

        // Читаємо ID гостя
        std::getline(iss, token, ',');
        guestId = std::stoi(token);

        // Читаємо ID номера
        std::getline(iss, token, ',');
        roomId = std::stoi(token);

        // Читаємо дату заїзду
        std::getline(iss, checkInDate, ',');

        // Читаємо дату виїзду
        std::getline(iss, checkOutDate, ',');

        return Booking(id, guestId, roomId, checkInDate, checkOutDate);
    } catch (const std::exception& e) {
        throw std::runtime_error("Помилка парсингу CSV: " + std::string(e.what()));
    }
}

/**
 * @brief Оновити наступний доступний ID
 */
void Booking::updateNextId(int id) {
    if (id >= nextId) {
        nextId = id + 1;
    }
}

/**
 * @brief Порівняти дві дати
 */
int Booking::compareDates(const std::string& date1, const std::string& date2) {
    if (date1 < date2) return -1;
    if (date1 > date2) return 1;
    return 0;
}