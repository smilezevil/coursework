/**
 * @file HotelManager.cpp
 * @brief Реалізація класу HotelManager для керування готелями
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/HotelManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>

/**
 * @brief Конструктор за замовчуванням
 */
HotelManager::HotelManager() : filename("data_hotels.csv") {
}

/**
 * @brief Конструктор з параметром
 */
HotelManager::HotelManager(const std::string& filename) : filename(filename) {
}

/**
 * @brief Копіювальний конструктор
 */
HotelManager::HotelManager(const HotelManager& other)
    : hotels(other.hotels), filename(other.filename) {
}

/**
 * @brief Переміщувальний конструктор
 */
HotelManager::HotelManager(HotelManager&& other) noexcept
    : hotels(std::move(other.hotels)), filename(std::move(other.filename)) {
}

/**
 * @brief Деструктор
 */
HotelManager::~HotelManager() {
    // Деструктор
}

/**
 * @brief Оператор присвоєння копіюванням
 */
HotelManager& HotelManager::operator=(const HotelManager& other) {
    if (this != &other) {
        hotels = other.hotels;
        filename = other.filename;
    }
    return *this;
}

/**
 * @brief Оператор присвоєння переміщенням
 */
HotelManager& HotelManager::operator=(HotelManager&& other) noexcept {
    if (this != &other) {
        hotels = std::move(other.hotels);
        filename = std::move(other.filename);
    }
    return *this;
}

/**
 * @brief Додати новий готель
 */
bool HotelManager::addHotel(const Hotel& hotel) {
    try {
        hotels.push_back(hotel);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Помилка при додаванні готелю: " << e.what() << std::endl;
        return false;
    }
}

/**
 * @brief Редагувати готель за ID
 */
bool HotelManager::editHotel(int id, const Hotel& newHotel) {
    for (auto& hotel : hotels) {
        if (hotel.getId() == id) {
            hotel = newHotel;
            hotel.setId(id); // Зберігаємо оригінальний ID
            return true;
        }
    }
    return false;
}

/**
 * @brief Видалити готель за ID
 */
bool HotelManager::deleteHotel(int id) {
    auto it = std::remove_if(hotels.begin(), hotels.end(),
        [id](const Hotel& h) { return h.getId() == id; });

    if (it != hotels.end()) {
        hotels.erase(it, hotels.end());
        return true;
    }
    return false;
}

/**
 * @brief Знайти готель за ID
 */
Hotel* HotelManager::findHotelById(int id) {
    for (auto& hotel : hotels) {
        if (hotel.getId() == id) {
            return &hotel;
        }
    }
    return nullptr;
}

/**
 * @brief Пошук готелів за назвою
 */
std::vector<Hotel> HotelManager::searchByName(const std::string& name) const {
    std::vector<Hotel> result;
    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (const auto& hotel : hotels) {
        std::string hotelName = hotel.getName();
        std::transform(hotelName.begin(), hotelName.end(), hotelName.begin(), ::tolower);

        if (hotelName.find(lowerName) != std::string::npos) {
            result.push_back(hotel);
        }
    }
    return result;
}

/**
 * @brief Пошук готелів за містом
 */
std::vector<Hotel> HotelManager::searchByCity(const std::string& city) const {
    std::vector<Hotel> result;
    std::string lowerCity = city;
    std::transform(lowerCity.begin(), lowerCity.end(), lowerCity.begin(), ::tolower);

    for (const auto& hotel : hotels) {
        std::string hotelCity = hotel.getCity();
        std::transform(hotelCity.begin(), hotelCity.end(), hotelCity.begin(), ::tolower);

        if (hotelCity.find(lowerCity) != std::string::npos) {
            result.push_back(hotel);
        }
    }
    return result;
}

/**
 * @brief Пошук готелів за кількістю зірок
 */
std::vector<Hotel> HotelManager::searchByStars(int stars) const {
    std::vector<Hotel> result;
    for (const auto& hotel : hotels) {
        if (hotel.getStars() == stars) {
            result.push_back(hotel);
        }
    }
    return result;
}

/**
 * @brief Отримати всі готелі
 */
std::vector<Hotel> HotelManager::getAllHotels() const {
    return hotels;
}

/**
 * @brief Отримати кількість готелів
 */
size_t HotelManager::getHotelCount() const {
    return hotels.size();
}

/**
 * @brief Перевірити, чи існує готель з певним ID
 */
bool HotelManager::hotelExists(int id) const {
    return std::any_of(hotels.begin(), hotels.end(),
        [id](const Hotel& h) { return h.getId() == id; });
}

/**
 * @brief Сортувати готелі за назвою
 */
void HotelManager::sortByName() {
    std::sort(hotels.begin(), hotels.end(),
        [](const Hotel& a, const Hotel& b) {
            return a.getName() < b.getName();
        });
}

/**
 * @brief Сортувати готелі за містом
 */
void HotelManager::sortByCity() {
    std::sort(hotels.begin(), hotels.end(),
        [](const Hotel& a, const Hotel& b) {
            return a.getCity() < b.getCity();
        });
}

/**
 * @brief Сортувати готелі за кількістю зірок
 */
void HotelManager::sortByStars() {
    std::sort(hotels.begin(), hotels.end(),
        [](const Hotel& a, const Hotel& b) {
            return a.getStars() > b.getStars(); // За спаданням
        });
}

/**
 * @brief Вивести всі готелі
 */
void HotelManager::displayAll() const {
    if (hotels.empty()) {
        std::cout << "\nСписок готелів порожній.\n" << std::endl;
        return;
    }

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "СПИСОК ГОТЕЛІВ (Всього: " << hotels.size() << ")" << std::endl;
    std::cout << std::string(50, '=') << "\n" << std::endl;

    for (const auto& hotel : hotels) {
        hotel.display();
        std::cout << std::endl;
    }
}

/**
 * @brief Завантажити дані з файлу
 */
bool HotelManager::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл: " << filename << std::endl;
        return false;
    }

    hotels.clear();
    std::string line;

    try {
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            Hotel hotel = Hotel::fromCSV(line);
            hotels.push_back(hotel);
            Hotel::updateNextId(hotel.getId());
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
bool HotelManager::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename << std::endl;
        return false;
    }

    try {
        for (const auto& hotel : hotels) {
            file << hotel.toCSV() << std::endl;
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
void HotelManager::clear() {
    hotels.clear();
}