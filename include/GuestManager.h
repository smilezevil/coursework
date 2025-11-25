/**
 * @file GuestManager.h
 * @brief Заголовковий файл класу GuestManager для керування гостями
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef GUEST_MANAGER_H
#define GUEST_MANAGER_H

#include "Guest.h"
#include <vector>
#include <string>

/**
 * @class GuestManager
 * @brief Клас для управління колекцією гостей
 *
 * Цей клас забезпечує функціонал для роботи з базою гостей:
 * додавання, редагування, видалення, пошук, сортування.
 * Також відповідає за завантаження та збереження даних у файл.
 */
class GuestManager {
private:
    std::vector<Guest> guests;     ///< Колекція гостей
    std::string filename;          ///< Ім'я файлу для збереження даних

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    GuestManager();

    /**
     * @brief Конструктор з параметром
     * @param filename Ім'я файлу для збереження даних
     */
    GuestManager(const std::string& filename);

    /**
     * @brief Копіювальний конструктор
     * @param other Інший об'єкт GuestManager
     */
    GuestManager(const GuestManager& other);

    /**
     * @brief Переміщувальний конструктор
     * @param other Інший об'єкт GuestManager
     */
    GuestManager(GuestManager&& other) noexcept;

    /**
     * @brief Деструктор
     */
    ~GuestManager();

    /**
     * @brief Оператор присвоєння копіюванням
     */
    GuestManager& operator=(const GuestManager& other);

    /**
     * @brief Оператор присвоєння переміщенням
     */
    GuestManager& operator=(GuestManager&& other) noexcept;

    /**
     * @brief Додати нового гостя
     * @param guest Гість для додавання
     * @return true якщо успішно додано
     */
    bool addGuest(const Guest& guest);

    /**
     * @brief Редагувати гостя за ID
     * @param id ID гостя
     * @param newGuest Нові дані гостя
     * @return true якщо успішно відредаговано
     */
    bool editGuest(int id, const Guest& newGuest);

    /**
     * @brief Видалити гостя за ID
     * @param id ID гостя
     * @return true якщо успішно видалено
     */
    bool deleteGuest(int id);

    /**
     * @brief Знайти гостя за ID
     * @param id ID гостя
     * @return Вказівник на гостя або nullptr
     */
    Guest* findGuestById(int id);

    /**
     * @brief Пошук гостей за прізвищем
     * @param lastName Прізвище або частина прізвища
     * @return Вектор знайдених гостей
     */
    std::vector<Guest> searchByLastName(const std::string& lastName) const;

    /**
     * @brief Пошук гостей за ім'ям
     * @param firstName Ім'я або частина імені
     * @return Вектор знайдених гостей
     */
    std::vector<Guest> searchByFirstName(const std::string& firstName) const;

    /**
     * @brief Пошук гостя за номером телефону
     * @param phone Номер телефону
     * @return Вектор знайдених гостей
     */
    std::vector<Guest> searchByPhone(const std::string& phone) const;

    /**
     * @brief Отримати всіх гостей
     * @return Вектор всіх гостей
     */
    std::vector<Guest> getAllGuests() const;

    /**
     * @brief Отримати кількість гостей
     * @return Кількість гостей
     */
    size_t getGuestCount() const;

    /**
     * @brief Перевірити, чи існує гість з певним ID
     * @param id ID гостя
     * @return true якщо існує
     */
    bool guestExists(int id) const;

    /**
     * @brief Сортувати гостей за прізвищем
     */
    void sortByLastName();

    /**
     * @brief Сортувати гостей за ім'ям
     */
    void sortByFirstName();

    /**
     * @brief Сортувати гостей за повним ім'ям (прізвище + ім'я)
     */
    void sortByFullName();

    /**
     * @brief Вивести всіх гостей
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

#endif // GUEST_MANAGER_H