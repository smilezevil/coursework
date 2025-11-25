/**
 * @file Constants.h
 * @brief Файл з константами для системи бронювання готелів
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

/**
 * @namespace Constants
 * @brief Простір імен для констант програми
 */
namespace Constants {

    // ==================== ШЛЯХИ ДО ФАЙЛІВ ====================
    // (використовуються у багатьох Manager класах)

    namespace Files {
        const std::string USERS = "users.txt";
        const std::string HOTELS = "data_hotels.csv";
        const std::string ROOMS = "data_rooms.csv";
        const std::string GUESTS = "data_guests.csv";
        const std::string BOOKINGS = "data_bookings.csv";
    }

    // ==================== МЕЖІ ТА ОБМЕЖЕННЯ ====================
    // (повторюються у валідації у різних класах)

    namespace Limits {
        const int MIN_STARS = 1;
        const int MAX_STARS = 5;
        const int MIN_CAPACITY = 2;
        const int MAX_CAPACITY = 3;
        const int MIN_USERNAME_LEN = 3;
        const int MIN_PASSWORD_LEN = 4;
        const int MIN_PHONE_DIGITS = 10;
        const int DATE_LENGTH = 10;
        const int MAX_LOGIN_ATTEMPTS = 3;
    }

    // ==================== ЦІНИ (базові значення) ====================

    namespace Prices {
        const double LUXURY_BASE = 2500.0;
        const double STANDARD_BASE = 1200.0;
        const double LUXURY_EXTRA_PERSON = 500.0;
        const double STANDARD_EXTRA_PERSON = 300.0;
    }

    // ==================== ПОВТОРЮВАНІ ПОВІДОМЛЕННЯ ====================
    // (ті що зустрічаються у ДЕКІЛЬКОХ місцях коду)

    namespace Messages {
        // Помилки які повторюються
        const std::string ERR_FILE_OPEN = "Не вдалося відкрити файл: ";
        const std::string ERR_FILE_SAVE = "Не вдалося відкрити файл для запису: ";
        const std::string ERR_LOAD_DATA = "Помилка при завантаженні даних: ";
        const std::string ERR_SAVE_DATA = "Помилка при збереженні даних: ";
        const std::string ERR_CSV_PARSE = "Помилка парсингу CSV: ";
        const std::string ERR_INVALID_DATA = "Некоректні дані";

        // Формати дат та роздільники
        const std::string DATE_FORMAT = "YYYY-MM-DD";
        const char CSV_DELIMITER = ',';
        const char USER_DELIMITER = ':';
    }

    // ==================== ТИПИ НОМЕРІВ ====================

    namespace RoomType {
        const std::string LUXURY = "Люкс";
        const std::string STANDARD = "Стандарт";
    }

    // ==================== КОРИСТУВАЧ ЗА ЗАМОВЧУВАННЯМ ====================

    namespace DefaultUser {
        const std::string ADMIN_LOGIN = "admin";
        const std::string ADMIN_PASSWORD = "admin";
    }

} // namespace Constants

#endif // CONSTANTS_H