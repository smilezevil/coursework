/**
 * @file Guest.h
 * @brief Заголовковий файл класу Guest для системи бронювання готелів
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef GUEST_H
#define GUEST_H

#include <string>
#include <iostream>

/**
 * @class Guest
 * @brief Клас для представлення гостя готелю
 * 
 * Цей клас зберігає інформацію про гостя: прізвище, ім'я та номер телефону.
 * Підтримує операції додавання, редагування та видалення гостей.
 */
class Guest {
private:
    int id;                    ///< Унікальний ідентифікатор гостя
    std::string lastName;      ///< Прізвище гостя
    std::string firstName;     ///< Ім'я гостя
    std::string phone;         ///< Номер телефону
    
    static int nextId;         ///< Лічильник для генерації ID

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    Guest();
    
    /**
     * @brief Конструктор з параметрами
     * @param lastName Прізвище гостя
     * @param firstName Ім'я гостя
     * @param phone Номер телефону
     */
    Guest(const std::string& lastName, const std::string& firstName, 
          const std::string& phone);
    
    /**
     * @brief Конструктор з усіма параметрами (включно з ID)
     * @param id Ідентифікатор гостя
     * @param lastName Прізвище гостя
     * @param firstName Ім'я гостя
     * @param phone Номер телефону
     */
    Guest(int id, const std::string& lastName, const std::string& firstName, 
          const std::string& phone);
    
    /**
     * @brief Копіювальний конструктор
     * @param other Інший об'єкт Guest для копіювання
     */
    Guest(const Guest& other);
    
    /**
     * @brief Переміщувальний конструктор
     * @param other Інший об'єкт Guest для переміщення
     */
    Guest(Guest&& other) noexcept;
    
    /**
     * @brief Деструктор
     */
    ~Guest();
    
    /**
     * @brief Оператор присвоєння копіюванням
     * @param other Інший об'єкт Guest
     * @return Посилання на поточний об'єкт
     */
    Guest& operator=(const Guest& other);
    
    /**
     * @brief Оператор присвоєння переміщенням
     * @param other Інший об'єкт Guest
     * @return Посилання на поточний об'єкт
     */
    Guest& operator=(Guest&& other) noexcept;
    
    // Геттери
    /**
     * @brief Отримати ID гостя
     * @return ID гостя
     */
    int getId() const;
    
    /**
     * @brief Отримати прізвище гостя
     * @return Прізвище гостя
     */
    std::string getLastName() const;
    
    /**
     * @brief Отримати ім'я гостя
     * @return Ім'я гостя
     */
    std::string getFirstName() const;
    
    /**
     * @brief Отримати повне ім'я гостя
     * @return Повне ім'я (Прізвище Ім'я)
     */
    std::string getFullName() const;
    
    /**
     * @brief Отримати номер телефону
     * @return Номер телефону
     */
    std::string getPhone() const;
    
    // Сеттери
    /**
     * @brief Встановити ID гостя
     * @param id Новий ID
     */
    void setId(int id);
    
    /**
     * @brief Встановити прізвище гостя
     * @param lastName Нове прізвище
     */
    void setLastName(const std::string& lastName);
    
    /**
     * @brief Встановити ім'я гостя
     * @param firstName Нове ім'я
     */
    void setFirstName(const std::string& firstName);
    
    /**
     * @brief Встановити номер телефону
     * @param phone Новий номер телефону
     */
    void setPhone(const std::string& phone);
    
    // Методи
    /**
     * @brief Вивести інформацію про гостя
     */
    void display() const;
    
    /**
     * @brief Перевірити валідність даних гостя
     * @return true якщо дані валідні, false інакше
     */
    bool validate() const;
    
    /**
     * @brief Перевірити валідність номера телефону
     * @param phone Номер телефону для перевірки
     * @return true якщо номер валідний, false інакше
     */
    static bool isValidPhone(const std::string& phone);
    
    /**
     * @brief Конвертувати об'єкт у рядок CSV формату
     * @return Рядок у форматі CSV
     */
    std::string toCSV() const;
    
    /**
     * @brief Створити об'єкт Guest з рядка CSV формату
     * @param csvLine Рядок у форматі CSV
     * @return Об'єкт Guest
     */
    static Guest fromCSV(const std::string& csvLine);
    
    /**
     * @brief Оновити наступний доступний ID
     * @param id Значення ID
     */
    static void updateNextId(int id);
    
    /**
     * @brief Оператор порівняння за ім'ям (для сортування)
     * @param other Інший гість
     * @return true якщо поточний гість менший за іншого
     */
    bool operator<(const Guest& other) const;
    
    /**
     * @brief Оператор порівняння на рівність
     * @param other Інший гість
     * @return true якщо гості рівні
     */
    bool operator==(const Guest& other) const;
};

#endif // GUEST_H