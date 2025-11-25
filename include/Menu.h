/**
 * @file Menu.h
 * @brief Заголовковий файл класу Menu для інтерфейсу системи
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#ifndef MENU_H
#define MENU_H

#include "HotelManager.h"
#include "RoomManager.h"
#include "GuestManager.h"
#include "BookingManager.h"
#include "UserManager.h"

/**
 * @class Menu
 * @brief Клас для управління інтерфейсом системи бронювання готелів
 * 
 * Цей клас відповідає за всю взаємодію з користувачем:
 * меню, введення/виведення даних, навігацію.
 */
class Menu {
private:
    HotelManager& hotelManager;       ///< Менеджер готелів
    RoomManager& roomManager;         ///< Менеджер номерів
    GuestManager& guestManager;       ///< Менеджер гостей
    BookingManager& bookingManager;   ///< Менеджер бронювань
    UserManager& userManager;         ///< Менеджер користувачів
    
    bool isRunning;                   ///< Прапорець роботи програми

public:
    /**
     * @brief Конструктор
     * @param hotelMgr Менеджер готелів
     * @param roomMgr Менеджер номерів
     * @param guestMgr Менеджер гостей
     * @param bookingMgr Менеджер бронювань
     * @param userMgr Менеджер користувачів
     */
    Menu(HotelManager& hotelMgr, RoomManager& roomMgr, GuestManager& guestMgr,
         BookingManager& bookingMgr, UserManager& userMgr);
    
    /**
     * @brief Деструктор
     */
    ~Menu();
    
    /**
     * @brief Запустити головне меню системи
     */
    void run();
    
private:
    // ==================== АВТОРИЗАЦІЯ ====================
    
    /**
     * @brief Показати екран авторизації
     * @return true якщо авторизація успішна
     */
    bool showLoginScreen();
    
    // ==================== ГОЛОВНЕ МЕНЮ ====================
    
    /**
     * @brief Показати головне меню
     */
    void showMainMenu();
    
    // ==================== 1. КЕРУВАННЯ ГОТЕЛЯМИ ====================
    
    /**
     * @brief Меню керування готелями
     */
    void hotelMenu();
    
    /**
     * @brief Додати готель
     */
    void addHotel();
    
    /**
     * @brief Редагувати готель
     */
    void editHotel();
    
    /**
     * @brief Видалити готель
     */
    void deleteHotel();
    
    /**
     * @brief Переглянути всі готелі
     */
    void viewAllHotels();
    
    /**
     * @brief Пошук готелів
     */
    void searchHotels();
    
    /**
     * @brief Сортування готелів
     */
    void sortHotels();
    
    // ==================== 2. КЕРУВАННЯ НОМЕРАМИ ====================
    
    /**
     * @brief Меню керування номерами
     */
    void roomMenu();
    
    /**
     * @brief Додати номер
     */
    void addRoom();
    
    /**
     * @brief Редагувати номер
     */
    void editRoom();
    
    /**
     * @brief Видалити номер
     */
    void deleteRoom();
    
    /**
     * @brief Переглянути всі номери
     */
    void viewAllRooms();
    
    /**
     * @brief Переглянути номери готелю
     */
    void viewRoomsByHotel();
    
    /**
     * @brief Пошук вільних номерів
     */
    void searchFreeRooms();
    
    /**
     * @brief Сортування номерів
     */
    void sortRooms();
    
    // ==================== 3. КЕРУВАННЯ ГОСТЯМИ ====================
    
    /**
     * @brief Меню керування гостями
     */
    void guestMenu();
    
    /**
     * @brief Додати гостя
     */
    void addGuest();
    
    /**
     * @brief Редагувати гостя
     */
    void editGuest();
    
    /**
     * @brief Видалити гостя
     */
    void deleteGuest();
    
    /**
     * @brief Переглянути всіх гостей
     */
    void viewAllGuests();
    
    /**
     * @brief Пошук гостей
     */
    void searchGuests();
    
    /**
     * @brief Сортування гостей
     */
    void sortGuests();
    
    // ==================== 4. КЕРУВАННЯ БРОНЮВАННЯМИ ====================
    
    /**
     * @brief Меню керування бронюваннями
     */
    void bookingMenu();
    
    /**
     * @brief Додати бронювання
     */
    void addBooking();
    
    /**
     * @brief Редагувати бронювання
     */
    void editBooking();
    
    /**
     * @brief Видалити бронювання
     */
    void deleteBooking();
    
    /**
     * @brief Переглянути всі бронювання
     */
    void viewAllBookings();
    
    /**
     * @brief Пошук бронювань
     */
    void searchBookings();
    
    /**
     * @brief Сортування бронювань
     */
    void sortBookings();
    
    // ==================== 7. ДОПОМОГА ====================
    
    /**
     * @brief Показати довідку
     */
    void showHelp();
    
    // ==================== 8. АДМІНІСТРУВАННЯ ====================
    
    /**
     * @brief Меню адміністрування (тільки для адміна)
     */
    void adminMenu();
    
    /**
     * @brief Додати користувача
     */
    void addUser();
    
    /**
     * @brief Видалити користувача
     */
    void deleteUser();
    
    /**
     * @brief Переглянути всіх користувачів
     */
    void viewAllUsers();
    
    // ==================== ДОПОМІЖНІ МЕТОДИ ====================
    
    /**
     * @brief Зберегти всі дані
     */
    void saveAllData();
    
    /**
     * @brief Завантажити всі дані
     */
    void loadAllData();
    
    /**
     * @brief Вибрати готель зі списку
     * @return ID обраного готелю або -1
     */
    int selectHotel();
    
    /**
     * @brief Вибрати номер зі списку
     * @return ID обраного номера або -1
     */
    int selectRoom();
    
    /**
     * @brief Вибрати гостя зі списку
     * @return ID обраного гостя або -1
     */
    int selectGuest();
};

#endif // MENU_H