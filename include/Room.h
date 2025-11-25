/**
 * @file Room.h
 * @brief Заголовковий файл класів Room (абстрактний), LuxuryRoom, StandardRoom
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <iostream>

/**
 * @enum RoomType
 * @brief Перелік типів номерів
 */
enum class RoomType {
    LUXURY,      ///< Люкс
    STANDARD     ///< Стандарт
};

/**
 * @class Room
 * @brief Абстрактний базовий клас для представлення номера в готелі
 * 
 * Цей клас є базовим для всіх типів номерів.
 * Містить чисті віртуальні методи для реалізації в класах-нащадках.
 */
class Room {
protected:
    int id;                    ///< Унікальний ідентифікатор номера
    int hotelId;               ///< ID готелю, до якого належить номер
    int capacity;              ///< Кількість місць (2 або 3)
    bool isOccupied;           ///< Чи зайнятий номер
    
    static int nextId;         ///< Лічильник для генерації ID

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    Room();
    
    /**
     * @brief Конструктор з параметрами
     * @param hotelId ID готелю
     * @param capacity Кількість місць
     */
    Room(int hotelId, int capacity);
    
    /**
     * @brief Конструктор з усіма параметрами
     * @param id ID номера
     * @param hotelId ID готелю
     * @param capacity Кількість місць
     * @param isOccupied Статус зайнятості
     */
    Room(int id, int hotelId, int capacity, bool isOccupied);
    
    /**
     * @brief Копіювальний конструктор
     * @param other Інший об'єкт Room
     */
    Room(const Room& other);
    
    /**
     * @brief Переміщувальний конструктор
     * @param other Інший об'єкт Room
     */
    Room(Room&& other) noexcept;
    
    /**
     * @brief Віртуальний деструктор
     */
    virtual ~Room();
    
    /**
     * @brief Оператор присвоєння копіюванням
     */
    Room& operator=(const Room& other);
    
    /**
     * @brief Оператор присвоєння переміщенням
     */
    Room& operator=(Room&& other) noexcept;
    
    // Геттери
    int getId() const;
    int getHotelId() const;
    int getCapacity() const;
    bool getIsOccupied() const;
    
    // Сеттери
    void setId(int id);
    void setHotelId(int hotelId);
    void setCapacity(int capacity);
    void setIsOccupied(bool occupied);
    
    /**
     * @brief Чисто віртуальний метод отримання типу номера
     * @return Тип номера
     */
    virtual RoomType getType() const = 0;
    
    /**
     * @brief Чисто віртуальний метод отримання назви типу
     * @return Назва типу номера
     */
    virtual std::string getTypeName() const = 0;
    
    /**
     * @brief Чисто віртуальний метод виведення інформації про номер
     */
    virtual void display() const = 0;
    
    /**
     * @brief Чисто віртуальний метод розрахунку вартості
     * @return Вартість номера за добу
     */
    virtual double calculatePrice() const = 0;
    
    /**
     * @brief Перевірити валідність даних номера
     * @return true якщо дані валідні
     */
    virtual bool validate() const;
    
    /**
     * @brief Конвертувати об'єкт у рядок CSV формату
     * @return Рядок у форматі CSV
     */
    virtual std::string toCSV() const;
    
    /**
     * @brief Оновити наступний доступний ID
     * @param id Значення ID
     */
    static void updateNextId(int id);
    
    /**
     * @brief Створити об'єкт Room з рядка CSV
     * @param csvLine Рядок CSV
     * @return Вказівник на створений об'єкт Room
     */
    static Room* fromCSV(const std::string& csvLine);
};

/**
 * @class LuxuryRoom
 * @brief Клас для представлення номера типу "Люкс"
 * 
 * Успадковується від абстрактного класу Room.
 * Реалізує специфічну поведінку для люкс-номерів.
 */
class LuxuryRoom : public Room {
private:
    static const double BASE_PRICE; ///< Базова ціна люкс-номера

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    LuxuryRoom();
    
    /**
     * @brief Конструктор з параметрами
     * @param hotelId ID готелю
     * @param capacity Кількість місць (2 або 3)
     */
    LuxuryRoom(int hotelId, int capacity);
    
    /**
     * @brief Конструктор з усіма параметрами
     * @param id ID номера
     * @param hotelId ID готелю
     * @param capacity Кількість місць
     * @param isOccupied Статус зайнятості
     */
    LuxuryRoom(int id, int hotelId, int capacity, bool isOccupied);
    
    /**
     * @brief Копіювальний конструктор
     */
    LuxuryRoom(const LuxuryRoom& other);
    
    /**
     * @brief Переміщувальний конструктор
     */
    LuxuryRoom(LuxuryRoom&& other) noexcept;
    
    /**
     * @brief Деструктор
     */
    ~LuxuryRoom() override;
    
    /**
     * @brief Отримати тип номера
     * @return RoomType::LUXURY
     */
    RoomType getType() const override;
    
    /**
     * @brief Отримати назву типу
     * @return "Люкс"
     */
    std::string getTypeName() const override;
    
    /**
     * @brief Вивести інформацію про люкс-номер
     */
    void display() const override;
    
    /**
     * @brief Розрахувати вартість люкс-номера
     * @return Вартість за добу
     */
    double calculatePrice() const override;
};

/**
 * @class StandardRoom
 * @brief Клас для представлення номера типу "Стандарт"
 * 
 * Успадковується від абстрактного класу Room.
 * Реалізує специфічну поведінку для стандартних номерів.
 */
class StandardRoom : public Room {
private:
    static const double BASE_PRICE; ///< Базова ціна стандартного номера

public:
    /**
     * @brief Конструктор за замовчуванням
     */
    StandardRoom();
    
    /**
     * @brief Конструктор з параметрами
     * @param hotelId ID готелю
     * @param capacity Кількість місць (2 або 3)
     */
    StandardRoom(int hotelId, int capacity);
    
    /**
     * @brief Конструктор з усіма параметрами
     * @param id ID номера
     * @param hotelId ID готелю
     * @param capacity Кількість місць
     * @param isOccupied Статус зайнятості
     */
    StandardRoom(int id, int hotelId, int capacity, bool isOccupied);
    
    /**
     * @brief Копіювальний конструктор
     */
    StandardRoom(const StandardRoom& other);
    
    /**
     * @brief Переміщувальний конструктор
     */
    StandardRoom(StandardRoom&& other) noexcept;
    
    /**
     * @brief Деструктор
     */
    ~StandardRoom() override;
    
    /**
     * @brief Отримати тип номера
     * @return RoomType::STANDARD
     */
    RoomType getType() const override;
    
    /**
     * @brief Отримати назву типу
     * @return "Стандарт"
     */
    std::string getTypeName() const override;
    
    /**
     * @brief Вивести інформацію про стандартний номер
     */
    void display() const override;
    
    /**
     * @brief Розрахувати вартість стандартного номера
     * @return Вартість за добу
     */
    double calculatePrice() const override;
};

#endif // ROOM_H