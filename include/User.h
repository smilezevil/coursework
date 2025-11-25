/**
 * @file User.h
 * @brief Заголовковий файл класу User для системи авторизації
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

/**
 * @class User
 * @brief Клас для представлення користувача системи
 * 
 * Цей клас зберігає інформацію про користувача: логін та пароль.
 * Підтримує систему авторизації та адміністрування користувачів.
 */
class User {
private:
    std::string username;      ///< Логін користувача
    std::string password;      ///< Пароль користувача
    bool isAdmin;              ///< Чи є користувач адміністратором

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    User();
    
    /**
     * @brief Конструктор з параметрами
     * @param username Логін користувача
     * @param password Пароль користувача
     * @param isAdmin Чи є користувач адміністратором
     */
    User(const std::string& username, const std::string& password, 
         bool isAdmin = false);
    
    /**
     * @brief Копіювальний конструктор
     * @param other Інший об'єкт User для копіювання
     */
    User(const User& other);
    
    /**
     * @brief Переміщувальний конструктор
     * @param other Інший об'єкт User для переміщення
     */
    User(User&& other) noexcept;
    
    /**
     * @brief Деструктор
     */
    ~User();
    
    /**
     * @brief Оператор присвоєння копіюванням
     * @param other Інший об'єкт User
     * @return Посилання на поточний об'єкт
     */
    User& operator=(const User& other);
    
    /**
     * @brief Оператор присвоєння переміщенням
     * @param other Інший об'єкт User
     * @return Посилання на поточний об'єкт
     */
    User& operator=(User&& other) noexcept;
    
    // Геттери
    /**
     * @brief Отримати логін користувача
     * @return Логін користувача
     */
    std::string getUsername() const;
    
    /**
     * @brief Отримати пароль користувача
     * @return Пароль користувача
     */
    std::string getPassword() const;
    
    /**
     * @brief Перевірити, чи є користувач адміністратором
     * @return true якщо адміністратор, false інакше
     */
    bool getIsAdmin() const;
    
    // Сеттери
    /**
     * @brief Встановити логін користувача
     * @param username Новий логін
     */
    void setUsername(const std::string& username);
    
    /**
     * @brief Встановити пароль користувача
     * @param password Новий пароль
     */
    void setPassword(const std::string& password);
    
    /**
     * @brief Встановити статус адміністратора
     * @param isAdmin Статус адміністратора
     */
    void setIsAdmin(bool isAdmin);
    
    // Методи
    /**
     * @brief Вивести інформацію про користувача
     */
    void display() const;
    
    /**
     * @brief Перевірити валідність даних користувача
     * @return true якщо дані валідні, false інакше
     */
    bool validate() const;
    
    /**
     * @brief Перевірити валідність логіну
     * @param username Логін для перевірки
     * @return true якщо логін валідний, false інакше
     */
    static bool isValidUsername(const std::string& username);
    
    /**
     * @brief Перевірити валідність пароля
     * @param password Пароль для перевірки
     * @return true якщо пароль валідний, false інакше
     */
    static bool isValidPassword(const std::string& password);
    
    /**
     * @brief Перевірити, чи співпадає пароль
     * @param password Пароль для порівняння
     * @return true якщо пароль співпадає
     */
    bool checkPassword(const std::string& password) const;
    
    /**
     * @brief Конвертувати об'єкт у рядок для збереження у файл
     * @return Рядок у форматі username:password:isAdmin
     */
    std::string toString() const;
    
    /**
     * @brief Створити об'єкт User з рядка
     * @param line Рядок у форматі username:password:isAdmin
     * @return Об'єкт User
     */
    static User fromString(const std::string& line);
    
    /**
     * @brief Оператор порівняння на рівність
     * @param other Інший користувач
     * @return true якщо користувачі рівні
     */
    bool operator==(const User& other) const;
};

#endif // USER_H