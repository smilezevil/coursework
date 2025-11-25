/**
 * @file Utils.h
 * @brief Заголовковий файл допоміжних функцій для роботи програми
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <limits>

/**
 * @namespace Utils
 * @brief Простір імен для допоміжних функцій
 */
namespace Utils {

    /**
     * @brief Очистити екран консолі
     */
    void clearScreen();

    /**
     * @brief Пауза - чекати натискання Enter
     * @param message Повідомлення для користувача
     */
    void pause(const std::string& message = "Натисніть Enter для продовження...");

    /**
     * @brief Вивести заголовок
     * @param title Текст заголовку
     */
    void printHeader(const std::string& title);

    /**
     * @brief Вивести розділювач
     * @param length Довжина розділювача
     */
    void printSeparator(int length = 50);

    /**
     * @brief Безпечне введення цілого числа
     * @param prompt Текст запиту
     * @param min Мінімальне значення
     * @param max Максимальне значення
     * @return Введене число
     */
    int getIntInput(const std::string& prompt, int min = 0,
                    int max = std::numeric_limits<int>::max());

    /**
     * @brief Безпечне введення рядка
     * @param prompt Текст запиту
     * @param allowEmpty Чи дозволяти порожній рядок
     * @return Введений рядок
     */
    std::string getStringInput(const std::string& prompt, bool allowEmpty = false);

    /**
     * @brief Запитати підтвердження (так/ні)
     * @param prompt Текст запиту
     * @return true якщо користувач підтвердив
     */
    bool getConfirmation(const std::string& prompt);

    /**
     * @brief Перевірити валідність дати
     * @param date Дата у форматі YYYY-MM-DD
     * @return true якщо дата валідна
     */
    bool isValidDate(const std::string& date);

    /**
     * @brief Отримати дату від користувача
     * @param prompt Текст запиту
     * @return Дата у форматі YYYY-MM-DD
     */
    std::string getDateInput(const std::string& prompt);

    /**
     * @brief Очистити буфер введення
     */
    void clearInputBuffer();

    /**
     * @brief Вивести повідомлення про успіх
     * @param message Текст повідомлення
     */
    void printSuccess(const std::string& message);

    /**
     * @brief Вивести повідомлення про помилку
     * @param message Текст повідомлення
     */
    void printError(const std::string& message);

    /**
     * @brief Вивести попередження
     * @param message Текст повідомлення
     */
    void printWarning(const std::string& message);

    /**
     * @brief Вивести інформаційне повідомлення
     * @param message Текст повідомлення
     */
    void printInfo(const std::string& message);

    /**
     * @brief Перевести рядок у нижній регістр
     * @param str Вхідний рядок
     * @return Рядок у нижньому регістрі
     */
    std::string toLowerCase(const std::string& str);

    /**
     * @brief Перевести рядок у верхній регістр
     * @param str Вхідний рядок
     * @return Рядок у верхньому регістрі
     */
    std::string toUpperCase(const std::string& str);

    /**
     * @brief Обрізати пробіли з початку та кінця рядка
     * @param str Вхідний рядок
     * @return Обрізаний рядок
     */
    std::string trim(const std::string& str);

    /**
     * @brief Отримати поточну дату у форматі YYYY-MM-DD
     * @return Поточна дата
     */
    std::string getCurrentDate();

    /**
     * @brief Вивести ASCII лого системи
     */
    void printLogo();

    /**
     * @brief Вивести меню вибору (з можливістю вибору пункту)
     * @param title Заголовок меню
     * @param options Варіанти вибору
     * @return Номер обраного пункту (1-based) або 0 для виходу
     */
    int displayMenu(const std::string& title, const std::vector<std::string>& options);

} // namespace Utils

#endif // UTILS_H