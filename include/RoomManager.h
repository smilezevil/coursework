/**
 * @file RoomManager.h
 * @brief Заголовковий файл класу RoomManager для керування номерами
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

#include "Room.h"
#include <vector>
#include <string>
#include <memory>

/**
 * @class RoomManager
 * @brief Клас для управління колекцією номерів
 *
 * Цей клас забезпечує функціонал для роботи з базою номерів:
 * додавання, редагування, видалення, пошук, сортування.
 * Також відповідає за завантаження та збереження даних у файл.
 */
class RoomManager {
private:
    std::vector<Room*> rooms;      ///< Колекція вказівників на номери
    std::string filename;          ///< Ім'я файлу для збереження даних

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    RoomManager();

    /**
     * @brief Конструктор з параметром
     * @param filename Ім'я файлу для збереження даних
     */
    RoomManager(const std::string& filename);

    /**
     * @brief Копіювальний конструктор
     * @param other Інший об'єкт RoomManager
     */
    RoomManager(const RoomManager& other);

    /**
     * @brief Переміщувальний конструктор
     * @param other Інший об'єкт RoomManager
     */
    RoomManager(RoomManager&& other) noexcept;

    /**
     * @brief Деструктор
     */
    ~RoomManager();

    /**
     * @brief Оператор присвоєння копіюванням
     */
    RoomManager& operator=(const RoomManager& other);

    /**
     * @brief Оператор присвоєння переміщенням
     */
    RoomManager& operator=(RoomManager&& other) noexcept;

    /**
     * @brief Додати новий номер
     * @param room Вказівник на номер для додавання
     * @return true якщо успішно додано
     */
    bool addRoom(Room* room);

    /**
     * @brief Редагувати номер за ID
     * @param id ID номера
     * @param newRoom Вказівник на новий номер
     * @return true якщо успішно відредаговано
     */
    bool editRoom(int id, Room* newRoom);

    /**
     * @brief Видалити номер за ID
     * @param id ID номера
     * @return true якщо успішно видалено
     */
    bool deleteRoom(int id);

    /**
     * @brief Видалити всі номери готелю
     * @param hotelId ID готелю
     * @return Кількість видалених номерів
     */
    int deleteRoomsByHotelId(int hotelId);

    /**
     * @brief Знайти номер за ID
     * @param id ID номера
     * @return Вказівник на номер або nullptr
     */
    Room* findRoomById(int id);

    /**
     * @brief Пошук номерів за ID готелю
     * @param hotelId ID готелю
     * @return Вектор знайдених номерів
     */
    std::vector<Room*> searchByHotelId(int hotelId) const;

    /**
     * @brief Пошук номерів за типом
     * @param type Тип номера
     * @return Вектор знайдених номерів
     */
    std::vector<Room*> searchByType(RoomType type) const;

    /**
     * @brief Пошук номерів за кількістю місць
     * @param capacity Кількість місць
     * @return Вектор знайдених номерів
     */
    std::vector<Room*> searchByCapacity(int capacity) const;

    /**
     * @brief Пошук вільних номерів
     * @return Вектор вільних номерів
     */
    std::vector<Room*> searchFreeRooms() const;

    /**
     * @brief Пошук вільних номерів у готелі
     * @param hotelId ID готелю
     * @return Вектор вільних номерів
     */
    std::vector<Room*> searchFreeRoomsByHotelId(int hotelId) const;

    /**
     * @brief Отримати всі номери
     * @return Вектор всіх номерів
     */
    std::vector<Room*> getAllRooms() const;

    /**
     * @brief Отримати кількість номерів
     * @return Кількість номерів
     */
    size_t getRoomCount() const;

    /**
     * @brief Отримати кількість номерів у готелі
     * @param hotelId ID готелю
     * @return Кількість номерів
     */
    size_t getRoomCountByHotelId(int hotelId) const;

    /**
     * @brief Отримати кількість вільних номерів у готелі
     * @param hotelId ID готелю
     * @return Кількість вільних номерів
     */
    size_t getFreeRoomCountByHotelId(int hotelId) const;

    /**
     * @brief Перевірити, чи існує номер з певним ID
     * @param id ID номера
     * @return true якщо існує
     */
    bool roomExists(int id) const;

    /**
     * @brief Сортувати номери за ID готелю
     */
    void sortByHotelId();

    /**
     * @brief Сортувати номери за типом
     */
    void sortByType();

    /**
     * @brief Сортувати номери за кількістю місць
     */
    void sortByCapacity();

    /**
     * @brief Вивести всі номери
     */
    void displayAll() const;

    /**
     * @brief Вивести номери готелю
     * @param hotelId ID готелю
     */
    void displayByHotelId(int hotelId) const;

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

#endif // ROOM_MANAGER_H