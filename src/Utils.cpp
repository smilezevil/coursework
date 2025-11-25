/**
 * @file Utils.cpp
 * @brief Реалізація допоміжних функцій для роботи програми
 * @author Ваше ПІБ
 * @date 2025
 */

#include "../include/Utils.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <ctime>

#ifdef _WIN32
    #include <windows.h>
#endif

namespace Utils {

    /**
     * @brief Очистити екран консолі
     */
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            // macOS, Linux та інші Unix системи
            system("clear");
        #endif
    }

    /**
     * @brief Пауза - чекати натискання Enter
     */
    void pause(const std::string& message) {
        std::cout << "\n" << message;
        clearInputBuffer();
        std::cin.get();
    }

    /**
     * @brief Вивести заголовок
     */
    void printHeader(const std::string& title) {
        int width = 60;
        int padding = (width - title.length() - 2) / 2;

        std::cout << "\n" << std::string(width, '=') << std::endl;
        std::cout << std::string(padding, ' ') << " " << title << std::endl;
        std::cout << std::string(width, '=') << std::endl;
    }

    /**
     * @brief Вивести розділювач
     */
    void printSeparator(int length) {
        std::cout << std::string(length, '-') << std::endl;
    }

    /**
     * @brief Безпечне введення цілого числа
     */
    int getIntInput(const std::string& prompt, int min, int max) {
        int value;
        while (true) {
            std::cout << prompt;

            if (std::cin >> value) {
                if (value >= min && value <= max) {
                    clearInputBuffer();
                    return value;
                } else {
                    printError("Число має бути в діапазоні від " +
                              std::to_string(min) + " до " + std::to_string(max));
                }
            } else {
                printError("Некоректне введення! Введіть число.");
                std::cin.clear();
                clearInputBuffer();
            }
        }
    }

    /**
     * @brief Безпечне введення рядка
     */
    std::string getStringInput(const std::string& prompt, bool allowEmpty) {
        std::string input;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            input = trim(input);

            if (!input.empty() || allowEmpty) {
                return input;
            } else {
                printError("Рядок не може бути порожнім!");
            }
        }
    }

    /**
     * @brief Запитати підтвердження
     */
    bool getConfirmation(const std::string& prompt) {
        std::string input;
        std::cout << prompt << " (так/ні): ";
        std::getline(std::cin, input);
        input = toLowerCase(trim(input));

        return (input == "так" || input == "yes" || input == "y" ||
                input == "т" || input == "1");
    }

    /**
     * @brief Перевірити валідність дати
     */
    bool isValidDate(const std::string& date) {
        if (date.length() != 10) return false;
        if (date[4] != '-' || date[7] != '-') return false;

        try {
            int year = std::stoi(date.substr(0, 4));
            int month = std::stoi(date.substr(5, 2));
            int day = std::stoi(date.substr(8, 2));

            if (year < 2020 || year > 2100) return false;
            if (month < 1 || month > 12) return false;
            if (day < 1 || day > 31) return false;

            // Перевірка днів у місяці
            if (month == 2) {
                bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
                if (day > (isLeap ? 29 : 28)) return false;
            } else if (month == 4 || month == 6 || month == 9 || month == 11) {
                if (day > 30) return false;
            }

            return true;
        } catch (...) {
            return false;
        }
    }

    /**
     * @brief Отримати дату від користувача
     */
    std::string getDateInput(const std::string& prompt) {
        std::string date;
        while (true) {
            std::cout << prompt << " (формат: YYYY-MM-DD): ";
            std::getline(std::cin, date);
            date = trim(date);

            if (isValidDate(date)) {
                return date;
            } else {
                printError("Некоректна дата! Використовуйте формат YYYY-MM-DD");
            }
        }
    }

    /**
     * @brief Очистити буфер введення
     */
    void clearInputBuffer() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    /**
     * @brief Вивести повідомлення про успіх
     */
    void printSuccess(const std::string& message) {
        std::cout << "\n✅ " << message << "\n" << std::endl;
    }

    /**
     * @brief Вивести повідомлення про помилку
     */
    void printError(const std::string& message) {
        std::cout << "\n❌ Помилка: " << message << "\n" << std::endl;
    }

    /**
     * @brief Вивести попередження
     */
    void printWarning(const std::string& message) {
        std::cout << "\n⚠️  Попередження: " << message << "\n" << std::endl;
    }

    /**
     * @brief Вивести інформаційне повідомлення
     */
    void printInfo(const std::string& message) {
        std::cout << "\nℹ️  " << message << "\n" << std::endl;
    }

    /**
     * @brief Перевести рядок у нижній регістр
     */
    std::string toLowerCase(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    /**
     * @brief Перевести рядок у верхній регістр
     */
    std::string toUpperCase(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    /**
     * @brief Обрізати пробіли з початку та кінця рядка
     */
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == std::string::npos) return "";

        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }

    /**
     * @brief Отримати поточну дату
     */
    std::string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        std::ostringstream oss;
        oss << (1900 + ltm->tm_year) << "-"
            << (ltm->tm_mon + 1 < 10 ? "0" : "") << (ltm->tm_mon + 1) << "-"
            << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday;

        return oss.str();
    }

    /**
     * @brief Вивести ASCII лого системи
     */
    void printLogo() {
        std::cout << R"(
╔═══════════════════════════════════════════════════════════╗
║                                                           ║
║           СИСТЕМА БРОНЮВАННЯ НОМЕРІВ В ГОТЕЛЯХ            ║
║                                                           ║
╚═══════════════════════════════════════════════════════════╝
        )" << std::endl;
    }

    /**
     * @brief Вивести меню вибору
     */
    int displayMenu(const std::string& title, const std::vector<std::string>& options) {
        printHeader(title);

        for (size_t i = 0; i < options.size(); i++) {
            std::cout << "  " << (i + 1) << ". " << options[i] << std::endl;
        }
        std::cout << "  0. Повернутися назад / Вихід" << std::endl;

        printSeparator(60);

        int choice = getIntInput("Оберіть пункт меню: ", 0, options.size());
        return choice;
    }

} // namespace Utils