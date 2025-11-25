/**
 * @file Room.cpp
 * @brief Реалізація класів Room, LuxuryRoom та StandardRoom
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/Room.h"
#include "../include/Constants.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>

// Ініціалізація статичних змінних
int Room::nextId = 1;
const double LuxuryRoom::BASE_PRICE = Constants::Prices::LUXURY_BASE;
const double StandardRoom::BASE_PRICE = Constants::Prices::STANDARD_BASE;

/**
 * @brief Конструктор за замовчуванням
 */
Room::Room() : id(0), hotelId(0), capacity(2), isOccupied(false) {
}

/**
 * @brief Конструктор з параметрами
 */
Room::Room(int hotelId, int capacity)
    : id(nextId++), hotelId(hotelId), capacity(capacity), isOccupied(false) {
}

/**
 * @brief Конструктор з усіма параметрами
 */
Room::Room(int id, int hotelId, int capacity, bool isOccupied)
    : id(id), hotelId(hotelId), capacity(capacity), isOccupied(isOccupied) {
}

/**
 * @brief Копіювальний конструктор
 */
Room::Room(const Room& other)
    : id(other.id), hotelId(other.hotelId),
      capacity(other.capacity), isOccupied(other.isOccupied) {
}

/**
 * @brief Переміщувальний конструктор
 */
Room::Room(Room&& other) noexcept
    : id(other.id), hotelId(other.hotelId),
      capacity(other.capacity), isOccupied(other.isOccupied) {
    other.id = 0;
    other.hotelId = 0;
    other.capacity = 0;
    other.isOccupied = false;
}

/**
 * @brief Віртуальний деструктор
 */
Room::~Room() {
    // Деструктор базового класу
}

/**
 * @brief Оператор присвоєння копіюванням
 */
Room& Room::operator=(const Room& other) {
    if (this != &other) {
        id = other.id;
        hotelId = other.hotelId;
        capacity = other.capacity;
        isOccupied = other.isOccupied;
    }
    return *this;
}

/**
 * @brief Оператор присвоєння переміщенням
 */
Room& Room::operator=(Room&& other) noexcept {
    if (this != &other) {
        id = other.id;
        hotelId = other.hotelId;
        capacity = other.capacity;
        isOccupied = other.isOccupied;

        other.id = 0;
        other.hotelId = 0;
        other.capacity = 0;
        other.isOccupied = false;
    }
    return *this;
}

// Геттери
int Room::getId() const { return id; }
int Room::getHotelId() const { return hotelId; }
int Room::getCapacity() const { return capacity; }
bool Room::getIsOccupied() const { return isOccupied; }

// Сеттери
void Room::setId(int id) { this->id = id; }
void Room::setHotelId(int hotelId) { this->hotelId = hotelId; }

void Room::setCapacity(int capacity) {
    if (capacity != Constants::Limits::MIN_CAPACITY &&
        capacity != Constants::Limits::MAX_CAPACITY) {
        throw std::invalid_argument("Кількість місць має бути 2 або 3");
    }
    this->capacity = capacity;
}

void Room::setIsOccupied(bool occupied) {
    this->isOccupied = occupied;
}

/**
 * @brief Перевірити валідність даних номера
 */
bool Room::validate() const {
    if (hotelId <= 0) return false;
    if (capacity != Constants::Limits::MIN_CAPACITY &&
        capacity != Constants::Limits::MAX_CAPACITY) return false;
    return true;
}

/**
 * @brief Конвертувати об'єкт у рядок CSV формату
 */
std::string Room::toCSV() const {
    std::ostringstream oss;
    oss << id << "," << hotelId << "," << getTypeName() << ","
        << capacity << "," << (isOccupied ? "1" : "0");
    return oss.str();
}

/**
 * @brief Оновити наступний доступний ID
 */
void Room::updateNextId(int id) {
    if (id >= nextId) {
        nextId = id + 1;
    }
}

/**
 * @brief Створити об'єкт Room з рядка CSV
 */
Room* Room::fromCSV(const std::string& csvLine) {
    std::istringstream iss(csvLine);
    std::string token;
    int id, hotelId, capacity;
    std::string type;
    bool isOccupied;

    try {
        // Читаємо ID
        std::getline(iss, token, ',');
        id = std::stoi(token);

        // Читаємо ID готелю
        std::getline(iss, token, ',');
        hotelId = std::stoi(token);

        // Читаємо тип
        std::getline(iss, type, ',');

        // Читаємо кількість місць
        std::getline(iss, token, ',');
        capacity = std::stoi(token);

        // Читаємо статус зайнятості
        std::getline(iss, token, ',');
        isOccupied = (token == "1");

        // Створюємо відповідний тип номера
        if (type == "Люкс") {
            return new LuxuryRoom(id, hotelId, capacity, isOccupied);
        } else {
            return new StandardRoom(id, hotelId, capacity, isOccupied);
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Помилка парсингу CSV: " + std::string(e.what()));
    }
}

// ============================================================================
// РЕАЛІЗАЦІЯ КЛАСУ LUXURYROOM (Люкс)
// ============================================================================

/**
 * @brief Конструктор за замовчуванням
 */
LuxuryRoom::LuxuryRoom() : Room() {
}

/**
 * @brief Конструктор з параметрами
 */
LuxuryRoom::LuxuryRoom(int hotelId, int capacity)
    : Room(hotelId, capacity) {
}

/**
 * @brief Конструктор з усіма параметрами
 */
LuxuryRoom::LuxuryRoom(int id, int hotelId, int capacity, bool isOccupied)
    : Room(id, hotelId, capacity, isOccupied) {
}

/**
 * @brief Копіювальний конструктор
 */
LuxuryRoom::LuxuryRoom(const LuxuryRoom& other) : Room(other) {
}

/**
 * @brief Переміщувальний конструктор
 */
LuxuryRoom::LuxuryRoom(LuxuryRoom&& other) noexcept : Room(std::move(other)) {
}

/**
 * @brief Деструктор
 */
LuxuryRoom::~LuxuryRoom() {
    // Деструктор люкс-номера
}

/**
 * @brief Отримати тип номера
 */
RoomType LuxuryRoom::getType() const {
    return RoomType::LUXURY;
}

/**
 * @brief Отримати назву типу
 */
std::string LuxuryRoom::getTypeName() const {
    return Constants::RoomType::LUXURY;
}

/**
 * @brief Вивести інформацію про люкс-номер
 */
void LuxuryRoom::display() const {
    std::cout << "┌────────────────────────────────────────┐\n";
    std::cout << "                 ЛЮКС НОМЕР               \n";
    std::cout << "├────────────────────────────────────────┤\n";
    std::cout << " ID номера: " << std::left << std::setw(27) << id << "\n";
    std::cout << " ID готелю: " << std::left << std::setw(27) << hotelId << "\n";
    std::cout << " Місць: " << std::left << std::setw(31) << capacity << "\n";
    std::cout << " Статус: " << std::left << std::setw(30)
              << (isOccupied ? "Зайнятий" : "Вільний") << "\n";
    std::cout << " Ціна: " << std::left << std::setw(32)
              << (std::to_string((int)calculatePrice()) + " грн/доба") << "\n";
    std::cout << "└────────────────────────────────────────┘\n";
}

/**
 * @brief Розрахувати вартість люкс-номера
 */
double LuxuryRoom::calculatePrice() const {
    return BASE_PRICE + (capacity > Constants::Limits::MIN_CAPACITY ?
                         Constants::Prices::LUXURY_EXTRA_PERSON : 0.0);
}

// ============================================================================
// РЕАЛІЗАЦІЯ КЛАСУ STANDARDROOM (Стандарт)
// ============================================================================

/**
 * @brief Конструктор за замовчуванням
 */
StandardRoom::StandardRoom() : Room() {
}

/**
 * @brief Конструктор з параметрами
 */
StandardRoom::StandardRoom(int hotelId, int capacity)
    : Room(hotelId, capacity) {
}

/**
 * @brief Конструктор з усіма параметрами
 */
StandardRoom::StandardRoom(int id, int hotelId, int capacity, bool isOccupied)
    : Room(id, hotelId, capacity, isOccupied) {
}

/**
 * @brief Копіювальний конструктор
 */
StandardRoom::StandardRoom(const StandardRoom& other) : Room(other) {
}

/**
 * @brief Переміщувальний конструктор
 */
StandardRoom::StandardRoom(StandardRoom&& other) noexcept : Room(std::move(other)) {
}

/**
 * @brief Деструктор
 */
StandardRoom::~StandardRoom() {
    // Деструктор стандартного номера
}

/**
 * @brief Отримати тип номера
 */
RoomType StandardRoom::getType() const {
    return RoomType::STANDARD;
}

/**
 * @brief Отримати назву типу
 */
std::string StandardRoom::getTypeName() const {
    return Constants::RoomType::STANDARD;
}

/**
 * @brief Вивести інформацію про стандартний номер
 */
void StandardRoom::display() const {
    std::cout << "┌────────────────────────────────────────┐\n";
    std::cout << "             СТАНДАРТНИЙ НОМЕР            \n";
    std::cout << "├────────────────────────────────────────┤\n";
    std::cout << " ID номера: " << std::left << std::setw(27) << id << "\n";
    std::cout << " ID готелю: " << std::left << std::setw(27) << hotelId << "\n";
    std::cout << " Місць: " << std::left << std::setw(31) << capacity << "\n";
    std::cout << " Статус: " << std::left << std::setw(30)
              << (isOccupied ? "Зайнятий" : "Вільний") << "\n";
    std::cout << " Ціна: " << std::left << std::setw(32)
              << (std::to_string((int)calculatePrice()) + " грн/доба") << "\n";
    std::cout << "└────────────────────────────────────────┘\n";
}

/**
 * @brief Розрахувати вартість стандартного номера
 */
double StandardRoom::calculatePrice() const {
    return BASE_PRICE + (capacity > Constants::Limits::MIN_CAPACITY ?
                         Constants::Prices::STANDARD_EXTRA_PERSON : 0.0);
}