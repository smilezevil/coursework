/**
 * @file UserManager.h
 * @brief Заголовковий файл класу UserManager для керування користувачами
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "User.h"
#include <vector>
#include <string>

/**
 * @class UserManager
 * @brief Клас для управління колекцією користувачів системи
 *
 * Цей клас забезпечує функціонал для роботи з користувачами:
 * авторизація, додавання, видалення користувачів.
 * Також відповідає за завантаження та збереження даних у файл.
 */
class UserManager {
private:
    std::vector<User> users;       ///< Колекція користувачів
    std::string filename;          ///< Ім'я файлу для збереження даних
    User* currentUser;             ///< Поточний авторизований користувач

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    UserManager();

    /**
     * @brief Конструктор з параметром
     * @param filename Ім'я файлу для збереження даних
     */
    UserManager(const std::string& filename);

    /**
     * @brief Копіювальний конструктор
     * @param other Інший об'єкт UserManager
     */
    UserManager(const UserManager& other);

    /**
     * @brief Переміщувальний конструктор
     * @param other Інший об'єкт UserManager
     */
    UserManager(UserManager&& other) noexcept;

    /**
     * @brief Деструктор
     */
    ~UserManager();

    /**
     * @brief Оператор присвоєння копіюванням
     */
    UserManager& operator=(const UserManager& other);

    /**
     * @brief Оператор присвоєння переміщенням
     */
    UserManager& operator=(UserManager&& other) noexcept;

    /**
     * @brief Ініціалізувати систему з адміністратором за замовчуванням
     */
    void initializeDefaultAdmin();

    /**
     * @brief Авторизувати користувача
     * @param username Логін
     * @param password Пароль
     * @return true якщо авторизація успішна
     */
    bool login(const std::string& username, const std::string& password);

    /**
     * @brief Вийти з системи
     */
    void logout();

    /**
     * @brief Отримати поточного користувача
     * @return Вказівник на поточного користувача або nullptr
     */
    User* getCurrentUser();

    /**
     * @brief Перевірити, чи користувач авторизований
     * @return true якщо авторизований
     */
    bool isLoggedIn() const;

    /**
     * @brief Перевірити, чи поточний користувач адміністратор
     * @return true якщо адміністратор
     */
    bool isCurrentUserAdmin() const;

    /**
     * @brief Додати нового користувача (тільки для адміністратора)
     * @param user Користувач для додавання
     * @return true якщо успішно додано
     */
    bool addUser(const User& user);

    /**
     * @brief Видалити користувача (тільки для адміністратора)
     * @param username Логін користувача для видалення
     * @return true якщо успішно видалено
     */
    bool deleteUser(const std::string& username);

    /**
     * @brief Знайти користувача за логіном
     * @param username Логін користувача
     * @return Вказівник на користувача або nullptr
     */
    User* findUserByUsername(const std::string& username);

    /**
     * @brief Перевірити, чи існує користувач з таким логіном
     * @param username Логін користувача
     * @return true якщо існує
     */
    bool userExists(const std::string& username) const;

    /**
     * @brief Отримати всіх користувачів
     * @return Вектор всіх користувачів
     */
    std::vector<User> getAllUsers() const;

    /**
     * @brief Отримати кількість користувачів
     * @return Кількість користувачів
     */
    size_t getUserCount() const;

    /**
     * @brief Вивести всіх користувачів (для адміністратора)
     */
    void displayAll() const;

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

#endif // USER_MANAGER_H