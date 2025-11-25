/**
 * @file Booking.h
 * @brief Заголовковий файл класу Booking для системи бронювання готелів
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <iostream>
#include <ctime>

/**
 * @class Booking
 * @brief Клас для представлення бронювання номера в готелі
 * 
 * Цей клас зберігає інформацію про бронювання: гостя, номер, дати заїзду/виїзду.
 * Підтримує операції додавання, редагування та видалення бронювань.
 */
class Booking {
private:
    int id;                    ///< Унікальний ідентифікатор бронювання
    int guestId;               ///< ID гостя
    int roomId;                ///< ID номера
    std::string checkInDate;   ///< Дата заїзду (формат: YYYY-MM-DD)
    std::string checkOutDate;  ///< Дата виїзду (формат: YYYY-MM-DD)
    
    static int nextId;         ///< Лічильник для генерації ID

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    Booking();
    
    /**
     * @brief Конструктор з параметрами
     * @param guestId ID гостя
     * @param roomId ID номера
     * @param checkInDate Дата заїзду
     * @param checkOutDate Дата виїзду
     */
    Booking(int guestId, int roomId, const std::string& checkInDate, 
            const std::string& checkOutDate);
    
    /**
     * @brief Конструктор з усіма параметрами (включно з ID)
     * @param id Ідентифікатор бронювання
     * @param guestId ID гостя
     * @param roomId ID номера
     * @param checkInDate Дата заїзду
     * @param checkOutDate Дата виїзду
     */
    Booking(int id, int guestId, int roomId, const std::string& checkInDate, 
            const std::string& checkOutDate);
    
    /**
     * @brief Копіювальний конструктор
     * @param other Інший об'єкт Booking для копіювання
     */
    Booking(const Booking& other);
    
    /**
     * @brief Переміщувальний конструктор
     * @param other Інший об'єкт Booking для переміщення
     */
    Booking(Booking&& other) noexcept;
    
    /**
     * @brief Деструктор
     */
    ~Booking();
    
    /**
     * @brief Оператор присвоєння копіюванням
     * @param other Інший об'єкт Booking
     * @return Посилання на поточний об'єкт
     */
    Booking& operator=(const Booking& other);
    
    /**
     * @brief Оператор присвоєння переміщенням
     * @param other Інший об'єкт Booking
     * @return Посилання на поточний об'єкт
     */
    Booking& operator=(Booking&& other) noexcept;
    
    // Геттери
    /**
     * @brief Отримати ID бронювання
     * @return ID бронювання
     */
    int getId() const;
    
    /**
     * @brief Отримати ID гостя
     * @return ID гостя
     */
    int getGuestId() const;
    
    /**
     * @brief Отримати ID номера
     * @return ID номера
     */
    int getRoomId() const;
    
    /**
     * @brief Отримати дату заїзду
     * @return Дата заїзду
     */
    std::string getCheckInDate() const;
    
    /**
     * @brief Отримати дату виїзду
     * @return Дата виїзду
     */
    std::string getCheckOutDate() const;
    
    // Сеттери
    /**
     * @brief Встановити ID бронювання
     * @param id Новий ID
     */
    void setId(int id);
    
    /**
     * @brief Встановити ID гостя
     * @param guestId Новий ID гостя
     */
    void setGuestId(int guestId);
    
    /**
     * @brief Встановити ID номера
     * @param roomId Новий ID номера
     */
    void setRoomId(int roomId);
    
    /**
     * @brief Встановити дату заїзду
     * @param checkInDate Нова дата заїзду
     */
    void setCheckInDate(const std::string& checkInDate);
    
    /**
     * @brief Встановити дату виїзду
     * @param checkOutDate Нова дата виїзду
     */
    void setCheckOutDate(const std::string& checkOutDate);
    
    // Методи
    /**
     * @brief Вивести інформацію про бронювання
     */
    void display() const;
    
    /**
     * @brief Перевірити валідність даних бронювання
     * @return true якщо дані валідні, false інакше
     */
    bool validate() const;
    
    /**
     * @brief Перевірити валідність дати
     * @param date Дата у форматі YYYY-MM-DD
     * @return true якщо дата валідна, false інакше
     */
    static bool isValidDate(const std::string& date);
    
    /**
     * @brief Перевірити, чи дата заїзду раніше дати виїзду
     * @return true якщо порядок дат правильний
     */
    bool areDatesValid() const;
    
    /**
     * @brief Розрахувати кількість днів проживання
     * @return Кількість днів
     */
    int calculateDays() const;
    
    /**
     * @brief Конвертувати об'єкт у рядок CSV формату
     * @return Рядок у форматі CSV
     */
    std::string toCSV() const;
    
    /**
     * @brief Створити об'єкт Booking з рядка CSV формату
     * @param csvLine Рядок у форматі CSV
     * @return Об'єкт Booking
     */
    static Booking fromCSV(const std::string& csvLine);
    
    /**
     * @brief Оновити наступний доступний ID
     * @param id Значення ID
     */
    static void updateNextId(int id);
    
    /**
     * @brief Порівняти дві дати
     * @param date1 Перша дата
     * @param date2 Друга дата
     * @return -1 якщо date1 < date2, 0 якщо рівні, 1 якщо date1 > date2
     */
    static int compareDates(const std::string& date1, const std::string& date2);
};

#endif // BOOKING_H