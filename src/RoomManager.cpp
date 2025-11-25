/**
 * @file RoomManager.cpp
 * @brief Реалізація класу RoomManager для керування номерами
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/RoomManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>

/**
 * @brief Конструктор за замовчуванням
 */
RoomManager::RoomManager() : filename("data_rooms.csv") {
}

/**
 * @brief Конструктор з параметром
 */
RoomManager::RoomManager(const std::string& filename) : filename(filename) {
}

/**
 * @brief Копіювальний конструктор
 */
RoomManager::RoomManager(const RoomManager& other) : filename(other.filename) {
    for (const auto& room : other.rooms) {
        if (room->getType() == RoomType::LUXURY) {
            rooms.push_back(new LuxuryRoom(*dynamic_cast<LuxuryRoom*>(room)));
        } else {
            rooms.push_back(new StandardRoom(*dynamic_cast<StandardRoom*>(room)));
        }
    }
}

/**
 * @brief Переміщувальний конструктор
 */
RoomManager::RoomManager(RoomManager&& other) noexcept
    : rooms(std::move(other.rooms)), filename(std::move(other.filename)) {
}

/**
 * @brief Деструктор
 */
RoomManager::~RoomManager() {
    clear();
}

/**
 * @brief Оператор присвоєння копіюванням
 */
RoomManager& RoomManager::operator=(const RoomManager& other) {
    if (this != &other) {
        clear();
        filename = other.filename;
        for (const auto& room : other.rooms) {
            if (room->getType() == RoomType::LUXURY) {
                rooms.push_back(new LuxuryRoom(*dynamic_cast<LuxuryRoom*>(room)));
            } else {
                rooms.push_back(new StandardRoom(*dynamic_cast<StandardRoom*>(room)));
            }
        }
    }
    return *this;
}

/**
 * @brief Оператор присвоєння переміщенням
 */
RoomManager& RoomManager::operator=(RoomManager&& other) noexcept {
    if (this != &other) {
        clear();
        rooms = std::move(other.rooms);
        filename = std::move(other.filename);
    }
    return *this;
}

/**
 * @brief Додати новий номер
 */
bool RoomManager::addRoom(Room* room) {
    try {
        if (room != nullptr) {
            rooms.push_back(room);
            return true;
        }
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Помилка при додаванні номера: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Редагувати номер за ID
 */
bool RoomManager::editRoom(int id, Room* newRoom) {
    for (size_t i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getId() == id) {
            delete rooms[i];
            rooms[i] = newRoom;
            rooms[i]->setId(id); // Зберігаємо оригінальний ID
            return true;
        }
    }
    return false;
}

/**
 * @brief Видалити номер за ID
 */
bool RoomManager::deleteRoom(int id) {
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            rooms.erase(it);
            return true;
        }
    }
    return false;
}

/**
 * @brief Видалити всі номери готелю
 */
int RoomManager::deleteRoomsByHotelId(int hotelId) {
    int count = 0;
    auto it = rooms.begin();
    while (it != rooms.end()) {
        if ((*it)->getHotelId() == hotelId) {
            delete *it;
            it = rooms.erase(it);
            count++;
        } else {
            ++it;
        }
    }
    return count;
}

/**
 * @brief Знайти номер за ID
 */
Room* RoomManager::findRoomById(int id) {
    for (auto& room : rooms) {
        if (room->getId() == id) {
            return room;
        }
    }
    return nullptr;
}

/**
 * @brief Пошук номерів за ID готелю
 */
std::vector<Room*> RoomManager::searchByHotelId(int hotelId) const {
    std::vector<Room*> result;
    for (const auto& room : rooms) {
        if (room->getHotelId() == hotelId) {
            result.push_back(room);
        }
    }
    return result;
}

/**
 * @brief Пошук номерів за типом
 */
std::vector<Room*> RoomManager::searchByType(RoomType type) const {
    std::vector<Room*> result;
    for (const auto& room : rooms) {
        if (room->getType() == type) {
            result.push_back(room);
        }
    }
    return result;
}

/**
 * @brief Пошук номерів за кількістю місць
 */
std::vector<Room*> RoomManager::searchByCapacity(int capacity) const {
    std::vector<Room*> result;
    for (const auto& room : rooms) {
        if (room->getCapacity() == capacity) {
            result.push_back(room);
        }
    }
    return result;
}

/**
 * @brief Пошук вільних номерів
 */
std::vector<Room*> RoomManager::searchFreeRooms() const {
    std::vector<Room*> result;
    for (const auto& room : rooms) {
        if (!room->getIsOccupied()) {
            result.push_back(room);
        }
    }
    return result;
}

/**
 * @brief Пошук вільних номерів у готелі
 */
std::vector<Room*> RoomManager::searchFreeRoomsByHotelId(int hotelId) const {
    std::vector<Room*> result;
    for (const auto& room : rooms) {
        if (room->getHotelId() == hotelId && !room->getIsOccupied()) {
            result.push_back(room);
        }
    }
    return result;
}

/**
 * @brief Отримати всі номери
 */
std::vector<Room*> RoomManager::getAllRooms() const {
    return rooms;
}

/**
 * @brief Отримати кількість номерів
 */
size_t RoomManager::getRoomCount() const {
    return rooms.size();
}

/**
 * @brief Отримати кількість номерів у готелі
 */
size_t RoomManager::getRoomCountByHotelId(int hotelId) const {
    return std::count_if(rooms.begin(), rooms.end(),
        [hotelId](const Room* r) { return r->getHotelId() == hotelId; });
}

/**
 * @brief Отримати кількість вільних номерів у готелі
 */
size_t RoomManager::getFreeRoomCountByHotelId(int hotelId) const {
    return std::count_if(rooms.begin(), rooms.end(),
        [hotelId](const Room* r) {
            return r->getHotelId() == hotelId && !r->getIsOccupied();
        });
}

/**
 * @brief Перевірити, чи існує номер з певним ID
 */
bool RoomManager::roomExists(int id) const {
    return std::any_of(rooms.begin(), rooms.end(),
        [id](const Room* r) { return r->getId() == id; });
}

/**
 * @brief Сортувати номери за ID готелю
 */
void RoomManager::sortByHotelId() {
    std::sort(rooms.begin(), rooms.end(),
        [](const Room* a, const Room* b) {
            return a->getHotelId() < b->getHotelId();
        });
}

/**
 * @brief Сортувати номери за типом
 */
void RoomManager::sortByType() {
    std::sort(rooms.begin(), rooms.end(),
        [](const Room* a, const Room* b) {
            return a->getType() < b->getType();
        });
}

/**
 * @brief Сортувати номери за кількістю місць
 */
void RoomManager::sortByCapacity() {
    std::sort(rooms.begin(), rooms.end(),
        [](const Room* a, const Room* b) {
            return a->getCapacity() > b->getCapacity();
        });
}

/**
 * @brief Вивести всі номери
 */
void RoomManager::displayAll() const {
    if (rooms.empty()) {
        std::cout << "\nСписок номерів порожній.\n" << std::endl;
        return;
    }

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "СПИСОК НОМЕРІВ (Всього: " << rooms.size() << ")" << std::endl;
    std::cout << std::string(50, '=') << "\n" << std::endl;

    for (const auto& room : rooms) {
        room->display();
        std::cout << std::endl;
    }
}

/**
 * @brief Вивести номери готелю
 */
void RoomManager::displayByHotelId(int hotelId) const {
    auto hotelRooms = searchByHotelId(hotelId);

    if (hotelRooms.empty()) {
        std::cout << "\nУ цьому готелі немає номерів.\n" << std::endl;
        return;
    }

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "НОМЕРИ ГОТЕЛЮ (ID: " << hotelId << ", Всього: "
              << hotelRooms.size() << ")" << std::endl;
    std::cout << std::string(50, '=') << "\n" << std::endl;

    for (const auto& room : hotelRooms) {
        room->display();
        std::cout << std::endl;
    }
}

/**
 * @brief Завантажити дані з файлу
 */
bool RoomManager::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
        return false;
    }

    clear();
    std::string line;

    try {
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            Room* room = Room::fromCSV(line);
            rooms.push_back(room);
            Room::updateNextId(room->getId());
        }
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Помилка при завантаженні даних: " << e.what() << std::endl;
        file.close();
        return false;
    }
}

/**
 * @brief Зберегти дані у файл
 */
bool RoomManager::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename << std::endl;
        return false;
    }

    try {
        for (const auto& room : rooms) {
            file << room->toCSV() << std::endl;
        }
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Помилка при збереженні даних: " << e.what() << std::endl;
        file.close();
        return false;
    }
}

/**
 * @brief Очистити всі дані
 */
void RoomManager::clear() {
    for (auto& room : rooms) {
        delete room;
    }
    rooms.clear();
}