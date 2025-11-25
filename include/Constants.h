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
 * @brief Простір імен для всіх констант програми
 */
namespace Constants {

    // ==================== ШЛЯХИ ДО ФАЙЛІВ ====================

    namespace FilePaths {
        const std::string USERS_FILE = "users.txt";
        const std::string HOTELS_FILE = "data_hotels.csv";
        const std::string ROOMS_FILE = "data_rooms.csv";
        const std::string GUESTS_FILE = "data_guests.csv";
        const std::string BOOKINGS_FILE = "data_bookings.csv";
    }

    // ==================== ПАРАМЕТРИ СИСТЕМИ ====================

    namespace System {
        const int MIN_STARS = 1;
        const int MAX_STARS = 5;
        const int MIN_ROOM_CAPACITY = 2;
        const int MAX_ROOM_CAPACITY = 3;
        const int MIN_PHONE_DIGITS = 10;
        const int MIN_USERNAME_LENGTH = 3;
        const int MIN_PASSWORD_LENGTH = 4;
        const int DATE_STRING_LENGTH = 10;
        const int MENU_WIDTH = 60;
        const int SEPARATOR_LENGTH = 50;
        const int MAX_LOGIN_ATTEMPTS = 3;
    }

    // ==================== ЦІНИ НОМЕРІВ ====================

    namespace Prices {
        const double LUXURY_BASE_PRICE = 2500.0;
        const double STANDARD_BASE_PRICE = 1200.0;
        const double EXTRA_PERSON_LUXURY = 500.0;
        const double EXTRA_PERSON_STANDARD = 300.0;
    }

    // ==================== ПОВІДОМЛЕННЯ ====================

    namespace Messages {

        // Успішні операції
        const std::string SUCCESS_LOGIN = "Ви успішно увійшли в систему!";
        const std::string SUCCESS_ADD = "Успішно додано!";
        const std::string SUCCESS_EDIT = "Успішно відредаговано!";
        const std::string SUCCESS_DELETE = "Успішно видалено!";
        const std::string SUCCESS_SAVE = "Всі дані успішно збережено!";
        const std::string SUCCESS_LOAD = "Дані завантажено!";
        const std::string SUCCESS_LOGOUT = "До побачення! Дані збережено.";

        // Помилки
        const std::string ERROR_LOGIN_FAILED = "Невірний логін або пароль!";
        const std::string ERROR_FILE_OPEN = "Не вдалося відкрити файл";
        const std::string ERROR_FILE_SAVE = "Не вдалося зберегти дані у файл";
        const std::string ERROR_INVALID_INPUT = "Некоректне введення!";
        const std::string ERROR_INVALID_CHOICE = "Невірний вибір!";
        const std::string ERROR_EMPTY_STRING = "Рядок не може бути порожнім!";
        const std::string ERROR_INVALID_DATE = "Некоректна дата!";
        const std::string ERROR_INVALID_PHONE = "Некоректний формат номера телефону";
        const std::string ERROR_INVALID_STARS = "Кількість зірок має бути від 1 до 5";
        const std::string ERROR_INVALID_CAPACITY = "Кількість місць має бути 2 або 3";
        const std::string ERROR_NOT_FOUND = "Не знайдено!";
        const std::string ERROR_ACCESS_DENIED = "Доступ заборонено! Тільки для адміністраторів.";
        const std::string ERROR_USER_EXISTS = "Користувач з таким логіном вже існує!";
        const std::string ERROR_CANNOT_DELETE_ADMIN = "Не можна видалити адміністратора!";
        const std::string ERROR_CANNOT_DELETE_SELF = "Не можна видалити себе!";
        const std::string ERROR_ROOM_OCCUPIED = "Номер вже зайнятий в цей період!";
        const std::string ERROR_NO_FREE_ROOMS = "Немає вільних номерів!";

        // Попередження
        const std::string WARNING_CASCADE_DELETE_HOTEL =
            "При видаленні готелю будуть також видалені всі його номери та бронювання!";
        const std::string WARNING_CASCADE_DELETE_ROOM =
            "При видаленні номера будуть також видалені всі його бронювання!";
        const std::string WARNING_CASCADE_DELETE_GUEST =
            "При видаленні гостя будуть також видалені всі його бронювання!";

        // Інформаційні повідомлення
        const std::string INFO_SAVING_DATA = "Збереження даних...";
        const std::string INFO_LOADING_DATA = "Завантаження даних...";
        const std::string INFO_EMPTY_LIST = "Список порожній.";
        const std::string INFO_DELETION_CANCELLED = "Видалення скасовано.";
        const std::string INFO_NO_RESULTS = "Нічого не знайдено!";

        // Запити підтвердження
        const std::string CONFIRM_DELETE = "Ви впевнені, що хочете видалити";
        const std::string CONFIRM_YES_NO = " (так/ні): ";

        // Запити введення
        const std::string PROMPT_USERNAME = "Логін: ";
        const std::string PROMPT_PASSWORD = "Пароль: ";
        const std::string PROMPT_HOTEL_NAME = "Назва готелю: ";
        const std::string PROMPT_CITY = "Місто: ";
        const std::string PROMPT_STARS = "Кількість зірок (1-5): ";
        const std::string PROMPT_LAST_NAME = "Прізвище: ";
        const std::string PROMPT_FIRST_NAME = "Ім'я: ";
        const std::string PROMPT_PHONE = "Номер телефону: ";
        const std::string PROMPT_CHECK_IN = "Дата заїзду";
        const std::string PROMPT_CHECK_OUT = "Дата виїзду";
        const std::string PROMPT_CHOICE = "Ваш вибір: ";
        const std::string PROMPT_MENU = "Оберіть пункт меню: ";
        const std::string PROMPT_PRESS_ENTER = "Натисніть Enter для продовження...";
        const std::string PROMPT_DATE_FORMAT = " (формат: YYYY-MM-DD): ";

        // Заголовки
        const std::string HEADER_LOGIN = "АВТОРИЗАЦІЯ";
        const std::string HEADER_MAIN_MENU = "ГОЛОВНЕ МЕНЮ";
        const std::string HEADER_HOTELS = "КЕРУВАННЯ ГОТЕЛЯМИ";
        const std::string HEADER_ROOMS = "КЕРУВАННЯ НОМЕРАМИ";
        const std::string HEADER_GUESTS = "КЕРУВАННЯ ГОСТЯМИ";
        const std::string HEADER_BOOKINGS = "КЕРУВАННЯ БРОНЮВАННЯМИ";
        const std::string HEADER_SEARCH_BOOKINGS = "ПОШУК БРОНЮВАНЬ";
        const std::string HEADER_HELP = "ДОВІДКА";
        const std::string HEADER_ADMIN = "АДМІНІСТРУВАННЯ";
        const std::string HEADER_ADD = "ДОДАТИ";
        const std::string HEADER_EDIT = "РЕДАГУВАТИ";
        const std::string HEADER_DELETE = "ВИДАЛИТИ";
        const std::string HEADER_SEARCH = "ПОШУК";
        const std::string HEADER_SORT = "СОРТУВАННЯ";
    }

    // ==================== ТИПИ НОМЕРІВ ====================

    namespace RoomTypes {
        const std::string LUXURY = "Люкс";
        const std::string STANDARD = "Стандарт";
    }

    // ==================== КОРИСТУВАЧІ ====================

    namespace Users {
        const std::string DEFAULT_ADMIN_USERNAME = "admin";
        const std::string DEFAULT_ADMIN_PASSWORD = "admin";
        const std::string ROLE_ADMIN = "Адміністратор";
        const std::string ROLE_USER = "Користувач";
    }

    // ==================== ФОРМАТИ ====================

    namespace Formats {
        const std::string DATE_FORMAT = "YYYY-MM-DD";
        const std::string CSV_DELIMITER = ",";
        const std::string USER_DELIMITER = ":";
    }

    // ==================== РОКИ (для валідації дат) ====================

    namespace DateLimits {
        const int MIN_YEAR = 2020;
        const int MAX_YEAR = 2100;
        const int MIN_MONTH = 1;
        const int MAX_MONTH = 12;
        const int MIN_DAY = 1;
        const int MAX_DAY = 31;
        const int FEBRUARY = 2;
        const int LEAP_YEAR_FEB_DAYS = 29;
        const int NON_LEAP_YEAR_FEB_DAYS = 28;
        const int DAYS_IN_SHORT_MONTH = 30;
        const int DAYS_IN_LONG_MONTH = 31;
    }

    // ==================== ІКОНКИ/ЕМОДЗІ ====================

    namespace Icons {
        const std::string SUCCESS = "✅";
        const std::string ERROR = "❌";
        const std::string WARNING = "⚠️";
        const std::string INFO = "ℹ️";
        const std::string STAR = "★";
        const std::string EMPTY_STAR = "☆";
    }

    // ==================== ЧИСЛОВІ КОНСТАНТИ ====================

    namespace Numbers {
        const int ZERO = 0;
        const int ONE = 1;
        const int TWO = 2;
        const int THREE = 3;
        const int FOUR = 4;
        const int FIVE = 5;
    }

} // namespace Constants

#endif // CONSTANTS_H