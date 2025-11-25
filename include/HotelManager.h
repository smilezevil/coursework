/**
 * @file HotelManager.h
 * @brief Заголовковий файл класу HotelManager для керування готелями
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef HOTEL_MANAGER_H
#define HOTEL_MANAGER_H

#include "Hotel.h"
#include <vector>
#include <string>
#include <memory>

/**
 * @class HotelManager
 * @brief Клас для управління колекцією готелів
 * 
 * Цей клас забезпечує функціонал для роботи з базою готелів:
 * додавання, редагування, видалення, пошук, сортування.
 * Також відповідає за завантаження та збереження даних у файл.
 */
class HotelManager {
private:
    std::vector<Hotel> hotels;     ///< Колекція готелів
    std::string filename;          ///< Ім'я файлу для збереження даних

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    HotelManager();
    
    /**
     * @brief Конструктор з параметром
     * @param filename Ім'я файлу для збереження даних
     */
    HotelManager(const std::string& filename);
    
    /**
     * @brief Копіювальний конструктор
     * @param other Інший об'єкт HotelManager
     */
    HotelManager(const HotelManager& other);
    
    /**
     * @brief Переміщувальний конструктор
     * @param other Інший об'єкт HotelManager
     */
    HotelManager(HotelManager&& other) noexcept;
    
    /**
     * @brief Деструктор
     */
    ~HotelManager();
    
    /**
     * @brief Оператор присвоєння копіюванням
     */
    HotelManager& operator=(const HotelManager& other);
    
    /**
     * @brief Оператор присвоєння переміщенням
     */
    HotelManager& operator=(HotelManager&& other) noexcept;
    
    /**
     * @brief Додати новий готель
     * @param hotel Готель для додавання
     * @return true якщо успішно додано
     */
    bool addHotel(const Hotel& hotel);
    
    /**
     * @brief Редагувати готель за ID
     * @param id ID готелю
     * @param newHotel Нові дані готелю
     * @return true якщо успішно відредаговано
     */
    bool editHotel(int id, const Hotel& newHotel);
    
    /**
     * @brief Видалити готель за ID
     * @param id ID готелю
     * @return true якщо успішно видалено
     */
    bool deleteHotel(int id);
    
    /**
     * @brief Знайти готель за ID
     * @param id ID готелю
     * @return Вказівник на готель або nullptr
     */
    Hotel* findHotelById(int id);
    
    /**
     * @brief Пошук готелів за назвою
     * @param name Назва або частина назви
     * @return Вектор знайдених готелів
     */
    std::vector<Hotel> searchByName(const std::string& name) const;
    
    /**
     * @brief Пошук готелів за містом
     * @param city Назва міста
     * @return Вектор знайдених готелів
     */
    std::vector<Hotel> searchByCity(const std::string& city) const;
    
    /**
     * @brief Пошук готелів за кількістю зірок
     * @param stars Кількість зірок
     * @return Вектор знайдених готелів
     */
    std::vector<Hotel> searchByStars(int stars) const;
    
    /**
     * @brief Отримати всі готелі
     * @return Вектор всіх готелів
     */
    std::vector<Hotel> getAllHotels() const;
    
    /**
     * @brief Отримати кількість готелів
     * @return Кількість готелів
     */
    size_t getHotelCount() const;
    
    /**
     * @brief Перевірити, чи існує готель з певним ID
     * @param id ID готелю
     * @return true якщо існує
     */
    bool hotelExists(int id) const;
    
    /**
     * @brief Сортувати готелі за назвою
     */
    void sortByName();
    
    /**
     * @brief Сортувати готелі за містом
     */
    void sortByCity();
    
    /**
     * @brief Сортувати готелі за кількістю зірок
     */
    void sortByStars();
    
    /**
     * @brief Вивести всі готелі
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

#endif // HOTEL_MANAGER_H