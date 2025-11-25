/**
 * @file BookingManager.cpp
 * @brief Реалізація класу BookingManager для керування бронюваннями
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/BookingManager.h"
#include "../include/Constants.h"
#include <fstream>
#include <algorithm>
#include <iostream>

/**
 * @brief Конструктор за замовчуванням
 */
BookingManager::BookingManager() : filename(Constants::Files::BOOKINGS) {
}

/**
 * @brief Конструктор з параметром
 */
BookingManager::BookingManager(const std::string& filename) : filename(filename) {
}

/**
 * @brief Копіювальний конструктор
 */
BookingManager::BookingManager(const BookingManager& other)
    : bookings(other.bookings), filename(other.filename) {
}

/**
 * @brief Переміщувальний конструктор
 */
BookingManager::BookingManager(BookingManager&& other) noexcept
    : bookings(std::move(other.bookings)), filename(std::move(other.filename)) {
}

/**
 * @brief Деструктор
 */
BookingManager::~BookingManager() {
    // Деструктор
}

/**
 * @brief Оператор присвоєння копіюванням
 */
BookingManager& BookingManager::operator=(const BookingManager& other) {
    if (this != &other) {
        bookings = other.bookings;
        filename = other.filename;
    }
    return *this;
}

/**
 * @brief Оператор присвоєння переміщенням
 */
BookingManager& BookingManager::operator=(BookingManager&& other) noexcept {
    if (this != &other) {
        bookings = std::move(other.bookings);
        filename = std::move(other.filename);
    }
    return *this;
}

/**
 * @brief Додати нове бронювання
 */
bool BookingManager::addBooking(const Booking& booking) {
    try {
        bookings.push_back(booking);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Помилка при додаванні бронювання: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Редагувати бронювання за ID
 */
bool BookingManager::editBooking(int id, const Booking& newBooking) {
    for (auto& booking : bookings) {
        if (booking.getId() == id) {
            booking = newBooking;
            booking.setId(id); // Зберігаємо оригінальний ID
            return true;
        }
    }
    return false;
}

/**
 * @brief Видалити бронювання за ID
 */
bool BookingManager::deleteBooking(int id) {
    auto it = std::remove_if(bookings.begin(), bookings.end(),
        [id](const Booking& b) { return b.getId() == id; });

    if (it != bookings.end()) {
        bookings.erase(it, bookings.end());
        return true;
    }
    return false;
}

/**
 * @brief Видалити всі бронювання гостя
 */
int BookingManager::deleteBookingsByGuestId(int guestId) {
    auto it = std::remove_if(bookings.begin(), bookings.end(),
        [guestId](const Booking& b) { return b.getGuestId() == guestId; });

    int count = std::distance(it, bookings.end());
    bookings.erase(it, bookings.end());
    return count;
}

/**
 * @brief Видалити всі бронювання номера
 */
int BookingManager::deleteBookingsByRoomId(int roomId) {
    auto it = std::remove_if(bookings.begin(), bookings.end(),
        [roomId](const Booking& b) { return b.getRoomId() == roomId; });

    int count = std::distance(it, bookings.end());
    bookings.erase(it, bookings.end());
    return count;
}

/**
 * @brief Знайти бронювання за ID
 */
Booking* BookingManager::findBookingById(int id) {
    for (auto& booking : bookings) {
        if (booking.getId() == id) {
            return &booking;
        }
    }
    return nullptr;
}

/**
 * @brief Пошук бронювань за ID гостя
 */
std::vector<Booking> BookingManager::searchByGuestId(int guestId) const {
    std::vector<Booking> result;
    for (const auto& booking : bookings) {
        if (booking.getGuestId() == guestId) {
            result.push_back(booking);
        }
    }
    return result;
}

/**
 * @brief Пошук бронювань за ID номера
 */
std::vector<Booking> BookingManager::searchByRoomId(int roomId) const {
    std::vector<Booking> result;
    for (const auto& booking : bookings) {
        if (booking.getRoomId() == roomId) {
            result.push_back(booking);
        }
    }
    return result;
}

/**
 * @brief Пошук бронювань за датою заїзду
 */
std::vector<Booking> BookingManager::searchByCheckInDate(const std::string& checkInDate) const {
    std::vector<Booking> result;
    for (const auto& booking : bookings) {
        if (booking.getCheckInDate() == checkInDate) {
            result.push_back(booking);
        }
    }
    return result;
}

/**
 * @brief Пошук бронювань за датою виїзду
 */
std::vector<Booking> BookingManager::searchByCheckOutDate(const std::string& checkOutDate) const {
    std::vector<Booking> result;
    for (const auto& booking : bookings) {
        if (booking.getCheckOutDate() == checkOutDate) {
            result.push_back(booking);
        }
    }
    return result;
}

/**
 * @brief Перевірити чи номер зайнятий в певний період
 */
bool BookingManager::isRoomOccupied(int roomId, const std::string& checkInDate,
                                    const std::string& checkOutDate) const {
    for (const auto& booking : bookings) {
        if (booking.getRoomId() == roomId) {
            // Перевіряємо перетин дат
            // Період зайнятий, якщо:
            // - новий заїзд раніше старого виїзду АБО
            // - новий виїзд пізніше старого заїзду
            if (!(checkOutDate <= booking.getCheckInDate() ||
                  checkInDate >= booking.getCheckOutDate())) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Отримати всі бронювання
 */
std::vector<Booking> BookingManager::getAllBookings() const {
    return bookings;
}

/**
 * @brief Отримати кількість бронювань
 */
size_t BookingManager::getBookingCount() const {
    return bookings.size();
}

/**
 * @brief Перевірити, чи існує бронювання з певним ID
 */
bool BookingManager::bookingExists(int id) const {
    return std::any_of(bookings.begin(), bookings.end(),
        [id](const Booking& b) { return b.getId() == id; });
}

/**
 * @brief Сортувати бронювання за датою заїзду
 */
void BookingManager::sortByCheckInDate() {
    std::sort(bookings.begin(), bookings.end(),
        [](const Booking& a, const Booking& b) {
            return a.getCheckInDate() < b.getCheckInDate();
        });
}

/**
 * @brief Сортувати бронювання за датою виїзду
 */
void BookingManager::sortByCheckOutDate() {
    std::sort(bookings.begin(), bookings.end(),
        [](const Booking& a, const Booking& b) {
            return a.getCheckOutDate() < b.getCheckOutDate();
        });
}

/**
 * @brief Сортувати бронювання за ID гостя
 */
void BookingManager::sortByGuestId() {
    std::sort(bookings.begin(), bookings.end(),
        [](const Booking& a, const Booking& b) {
            return a.getGuestId() < b.getGuestId();
        });
}

/**
 * @brief Вивести всі бронювання
 */
void BookingManager::displayAll() const {
    if (bookings.empty()) {
        std::cout << "\nСписок бронювань порожній.\n" << std::endl;
        return;
    }

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "СПИСОК БРОНЮВАНЬ (Всього: " << bookings.size() << ")" << std::endl;
    std::cout << std::string(50, '=') << "\n" << std::endl;

    for (const auto& booking : bookings) {
        booking.display();
        std::cout << std::endl;
    }
}

/**
 * @brief Вивести бронювання гостя
 */
void BookingManager::displayByGuestId(int guestId) const {
    auto guestBookings = searchByGuestId(guestId);

    if (guestBookings.empty()) {
        std::cout << "\nУ цього гостя немає бронювань.\n" << std::endl;
        return;
    }

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "БРОНЮВАННЯ ГОСТЯ (ID: " << guestId << ", Всього: "
              << guestBookings.size() << ")" << std::endl;
    std::cout << std::string(50, '=') << "\n" << std::endl;

    for (const auto& booking : guestBookings) {
        booking.display();
        std::cout << std::endl;
    }
}

/**
 * @brief Вивести бронювання номера
 */
void BookingManager::displayByRoomId(int roomId) const {
    auto roomBookings = searchByRoomId(roomId);

    if (roomBookings.empty()) {
        std::cout << "\nДля цього номера немає бронювань.\n" << std::endl;
        return;
    }

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "БРОНЮВАННЯ НОМЕРА (ID: " << roomId << ", Всього: "
              << roomBookings.size() << ")" << std::endl;
    std::cout << std::string(50, '=') << "\n" << std::endl;

    for (const auto& booking : roomBookings) {
        booking.display();
        std::cout << std::endl;
    }
}

/**
 * @brief Завантажити дані з файлу
 */
bool BookingManager::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
        return false;
    }

    bookings.clear();
    std::string line;

    try {
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            Booking booking = Booking::fromCSV(line);
            bookings.push_back(booking);
            Booking::updateNextId(booking.getId());
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
bool BookingManager::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename << std::endl;
        return false;
    }

    try {
        for (const auto& booking : bookings) {
            file << booking.toCSV() << std::endl;
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
void BookingManager::clear() {
    bookings.clear();
}