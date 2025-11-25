/**
 * @file BookingManager.h
 * @brief Заголовковий файл класу BookingManager для керування бронюваннями
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef BOOKING_MANAGER_H
#define BOOKING_MANAGER_H

#include "Booking.h"
#include <vector>
#include <string>

/**
 * @class BookingManager
 * @brief Клас для управління колекцією бронювань
 *
 * Цей клас забезпечує функціонал для роботи з базою бронювань:
 * додавання, редагування, видалення, пошук, фільтрування.
 * Також відповідає за завантаження та збереження даних у файл.
 */
class BookingManager {
private:
    std::vector<Booking> bookings;     ///< Колекція бронювань
    std::string filename;              ///< Ім'я файлу для збереження даних

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    BookingManager();

    /**
     * @brief Конструктор з параметром
     * @param filename Ім'я файлу для збереження даних
     */
    BookingManager(const std::string& filename);

    /**
     * @brief Копіювальний конструктор
     * @param other Інший об'єкт BookingManager
     */
    BookingManager(const BookingManager& other);

    /**
     * @brief Переміщувальний конструктор
     * @param other Інший об'єкт BookingManager
     */
    BookingManager(BookingManager&& other) noexcept;

    /**
     * @brief Деструктор
     */
    ~BookingManager();

    /**
     * @brief Оператор присвоєння копіюванням
     */
    BookingManager& operator=(const BookingManager& other);

    /**
     * @brief Оператор присвоєння переміщенням
     */
    BookingManager& operator=(BookingManager&& other) noexcept;

    /**
     * @brief Додати нове бронювання
     * @param booking Бронювання для додавання
     * @return true якщо успішно додано
     */
    bool addBooking(const Booking& booking);

    /**
     * @brief Редагувати бронювання за ID
     * @param id ID бронювання
     * @param newBooking Нові дані бронювання
     * @return true якщо успішно відредаговано
     */
    bool editBooking(int id, const Booking& newBooking);

    /**
     * @brief Видалити бронювання за ID
     * @param id ID бронювання
     * @return true якщо успішно видалено
     */
    bool deleteBooking(int id);

    /**
     * @brief Видалити всі бронювання гостя
     * @param guestId ID гостя
     * @return Кількість видалених бронювань
     */
    int deleteBookingsByGuestId(int guestId);

    /**
     * @brief Видалити всі бронювання номера
     * @param roomId ID номера
     * @return Кількість видалених бронювань
     */
    int deleteBookingsByRoomId(int roomId);

    /**
     * @brief Знайти бронювання за ID
     * @param id ID бронювання
     * @return Вказівник на бронювання або nullptr
     */
    Booking* findBookingById(int id);

    /**
     * @brief Пошук бронювань за ID гостя
     * @param guestId ID гостя
     * @return Вектор знайдених бронювань
     */
    std::vector<Booking> searchByGuestId(int guestId) const;

    /**
     * @brief Пошук бронювань за ID номера
     * @param roomId ID номера
     * @return Вектор знайдених бронювань
     */
    std::vector<Booking> searchByRoomId(int roomId) const;

    /**
     * @brief Пошук бронювань за датою заїзду
     * @param checkInDate Дата заїзду
     * @return Вектор знайдених бронювань
     */
    std::vector<Booking> searchByCheckInDate(const std::string& checkInDate) const;

    /**
     * @brief Пошук бронювань за датою виїзду
     * @param checkOutDate Дата виїзду
     * @return Вектор знайдених бронювань
     */
    std::vector<Booking> searchByCheckOutDate(const std::string& checkOutDate) const;

    /**
     * @brief Перевірити чи номер зайнятий в певний період
     * @param roomId ID номера
     * @param checkInDate Дата заїзду
     * @param checkOutDate Дата виїзду
     * @return true якщо номер зайнятий
     */
    bool isRoomOccupied(int roomId, const std::string& checkInDate,
                        const std::string& checkOutDate) const;

    /**
     * @brief Отримати всі бронювання
     * @return Вектор всіх бронювань
     */
    std::vector<Booking> getAllBookings() const;

    /**
     * @brief Отримати кількість бронювань
     * @return Кількість бронювань
     */
    size_t getBookingCount() const;

    /**
     * @brief Перевірити, чи існує бронювання з певним ID
     * @param id ID бронювання
     * @return true якщо існує
     */
    bool bookingExists(int id) const;

    /**
     * @brief Сортувати бронювання за датою заїзду
     */
    void sortByCheckInDate();

    /**
     * @brief Сортувати бронювання за датою виїзду
     */
    void sortByCheckOutDate();

    /**
     * @brief Сортувати бронювання за ID гостя
     */
    void sortByGuestId();

    /**
     * @brief Вивести всі бронювання
     */
    void displayAll() const;

    /**
     * @brief Вивести бронювання гостя
     * @param guestId ID гостя
     */
    void displayByGuestId(int guestId) const;

    /**
     * @brief Вивести бронювання номера
     * @param roomId ID номера
     */
    void displayByRoomId(int roomId) const;

    /**
     * @brief Завантажити дані з файлу
     * @return true якщо успішно завантажено
     */
    bool loadFromFile();

    /**
     * @brief Зберегти дані у файл
     * @return true якщо успішно збережено
     */
    bool saveToFile() const;

    /**
     * @brief Очистити всі дані
     */
    void clear();
};

#endif // BOOKING_MANAGER_H