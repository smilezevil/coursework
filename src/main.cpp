/*
* @file main.cpp
 * @brief Головний файл програми - Система бронювання номерів в готелях
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/HotelManager.h"
#include "../include/RoomManager.h"
#include "../include/GuestManager.h"
#include "../include/BookingManager.h"
#include "../include/UserManager.h"
#include "../include/Menu.h"
#include <iostream>

/**
 * @brief Головна функція програми
 * @return Код завершення програми (0 - успішно)
 */
int main() {
    try {
        // Ініціалізація менеджерів
        HotelManager hotelManager("data_hotels.csv");
        RoomManager roomManager("data_rooms.csv");
        GuestManager guestManager("data_guests.csv");
        BookingManager bookingManager("data_bookings.csv");
        UserManager userManager("users.txt");

        // Створення та запуск меню
        Menu menu(hotelManager, roomManager, guestManager, bookingManager, userManager);
        menu.run();

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Критична помилка: " << e.what() << std::endl;
        return 1;
    }
}