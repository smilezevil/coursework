/**
 * @file Hotel.h
 * @brief Заголовковий файл класу Hotel для системи бронювання готелів
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <iostream>

/**
 * @class Hotel
 * @brief Клас для представлення готелю
 * 
 * Цей клас зберігає інформацію про готель: назву, місто та кількість зірок.
 * Підтримує операції додавання, редагування та видалення готелів.
 */
class Hotel {
private:
    int id;                    ///< Унікальний ідентифікатор готелю
    std::string name;          ///< Назва готелю
    std::string city;          ///< Місто розташування
    int stars;                 ///< Кількість зірок (1-5)
    
    static int nextId;         ///< Лічильник для генерації ID

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    Hotel();
    
    /**
     * @brief Конструктор з параметрами
     * @param name Назва готелю
     * @param city Місто розташування
     * @param stars Кількість зірок
     */
    Hotel(const std::string& name, const std::string& city, int stars);
    
    /**
     * @brief Конструктор з усіма параметрами (включно з ID)
     * @param id Ідентифікатор готелю
     * @param name Назва готелю
     * @param city Місто розташування
     * @param stars Кількість зірок
     */
    Hotel(int id, const std::string& name, const std::string& city, int stars);
    
    /**
     * @brief Копіювальний конструктор
     * @param other Інший об'єкт Hotel для копіювання
     */
    Hotel(const Hotel& other);
    
    /**
     * @brief Переміщувальний конструктор
     * @param other Інший об'єкт Hotel для переміщення
     */
    Hotel(Hotel&& other) noexcept;
    
    /**
     * @brief Деструктор
     */
    ~Hotel();
    
    /**
     * @brief Оператор присвоєння копіюванням
     * @param other Інший об'єкт Hotel
     * @return Посилання на поточний об'єкт
     */
    Hotel& operator=(const Hotel& other);
    
    /**
     * @brief Оператор присвоєння переміщенням
     * @param other Інший об'єкт Hotel
     * @return Посилання на поточний об'єкт
     */
    Hotel& operator=(Hotel&& other) noexcept;
    
    // Геттери
    /**
     * @brief Отримати ID готелю
     * @return ID готелю
     */
    int getId() const;
    
    /**
     * @brief Отримати назву готелю
     * @return Назва готелю
     */
    std::string getName() const;
    
    /**
     * @brief Отримати місто
     * @return Місто розташування
     */
    std::string getCity() const;
    
    /**
     * @brief Отримати кількість зірок
     * @return Кількість зірок
     */
    int getStars() const;
    
    // Сеттери
    /**
     * @brief Встановити ID готелю
     * @param id Новий ID
     */
    void setId(int id);
    
    /**
     * @brief Встановити назву готелю
     * @param name Нова назва
     */
    void setName(const std::string& name);
    
    /**
     * @brief Встановити місто
     * @param city Нове місто
     */
    void setCity(const std::string& city);
    
    /**
     * @brief Встановити кількість зірок
     * @param stars Нова кількість зірок (1-5)
     * @throw std::invalid_argument якщо кількість зірок поза межами 1-5
     */
    void setStars(int stars);
    
    // Методи
    /**
     * @brief Вивести інформацію про готель
     */
    void display() const;
    
    /**
     * @brief Перевірити валідність даних готелю
     * @return true якщо дані валідні, false інакше
     */
    bool validate() const;
    
    /**
     * @brief Конвертувати об'єкт у рядок CSV формату
     * @return Рядок у форматі CSV
     */
    std::string toCSV() const;
    
    /**
     * @brief Створити об'єкт Hotel з рядка CSV формату
     * @param csvLine Рядок у форматі CSV
     * @return Об'єкт Hotel
     */
    static Hotel fromCSV(const std::string& csvLine);
    
    /**
     * @brief Оновити наступний доступний ID
     * @param id Значення ID
     */
    static void updateNextId(int id);
};

#endif // HOTEL_H