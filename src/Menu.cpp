/**
 * @file Menu.cpp
 * @brief Реалізація класу Menu для інтерфейсу системи
 * @author Демʼянчук Анастасія
 * @date 2025
 */

#include "../include/Menu.h"
#include "../include/Utils.h"
#include "../include/Room.h"
#include <iostream>
#include <iomanip>

/**
 * @brief Конструктор
 */
Menu::Menu(HotelManager& hotelMgr, RoomManager& roomMgr, GuestManager& guestMgr,
           BookingManager& bookingMgr, UserManager& userMgr)
    : hotelManager(hotelMgr), roomManager(roomMgr), guestManager(guestMgr),
      bookingManager(bookingMgr), userManager(userMgr), isRunning(false) {
}

/**
 * @brief Деструктор
 */
Menu::~Menu() {
}

/**
 * @brief Запустити головне меню системи
 */
void Menu::run() {
    Utils::clearScreen();
    Utils::printLogo();

    // Завантажити дані
    loadAllData();

    // Авторизація
    if (!showLoginScreen()) {
        Utils::printError("Не вдалося авторизуватися!");
        return;
    }

    isRunning = true;

    while (isRunning) {
        showMainMenu();
    }

    // Зберегти дані перед виходом
    saveAllData();

    Utils::clearScreen();
    Utils::printSuccess("До побачення! Дані збережено.");
}

// ==================== АВТОРИЗАЦІЯ ====================

/**
 * @brief Показати екран авторизації
 */
bool Menu::showLoginScreen() {
    Utils::printHeader("АВТОРИЗАЦІЯ");

    int attempts = 3;
    while (attempts > 0) {
        std::string username = Utils::getStringInput("Логін: ");
        std::string password = Utils::getStringInput("Пароль: ");

        if (userManager.login(username, password)) {
            Utils::printSuccess("Ви успішно увійшли в систему!");
            User* currentUser = userManager.getCurrentUser();
            if (currentUser) {
                std::cout << "Вітаємо, " << currentUser->getUsername() << "!" << std::endl;
                if (currentUser->getIsAdmin()) {
                    std::cout << "Роль: Адміністратор" << std::endl;
                }
            }
            Utils::pause();
            return true;
        } else {
            attempts--;
            Utils::printError("Невірний логін або пароль! Залишилось спроб: " +
                            std::to_string(attempts));
        }
    }

    return false;
}

// ==================== ГОЛОВНЕ МЕНЮ ====================

/**
 * @brief Показати головне меню
 */
void Menu::showMainMenu() {
    Utils::clearScreen();

    std::vector<std::string> options = {
        "Керування готелями",
        "Керування номерами",
        "Керування гостями",
        "Керування бронюваннями",
        "Пошук бронювань",
        "Допомога",
        "Адміністрування",
        "Вихід та збереження"
    };

    int choice = Utils::displayMenu("ГОЛОВНЕ МЕНЮ", options);

    switch (choice) {
        case 1: hotelMenu(); break;
        case 2: roomMenu(); break;
        case 3: guestMenu(); break;
        case 4: bookingMenu(); break;
        case 5: searchBookings(); break;
        case 6: showHelp(); break;
        case 7: adminMenu(); break;
        case 8:
        case 0:
            saveAllData();
            isRunning = false;
            break;
        default:
            Utils::printError("Невірний вибір!");
            Utils::pause();
    }
}

// ==================== 1. КЕРУВАННЯ ГОТЕЛЯМИ ====================

/**
 * @brief Меню керування готелями
 */
void Menu::hotelMenu() {
    while (true) {
        Utils::clearScreen();

        std::vector<std::string> options = {
            "Додати готель",
            "Редагувати готель",
            "Видалити готель",
            "Переглянути всі готелі",
            "Пошук готелів",
            "Сортування готелів"
        };

        int choice = Utils::displayMenu("КЕРУВАННЯ ГОТЕЛЯМИ", options);

        switch (choice) {
            case 1: addHotel(); break;
            case 2: editHotel(); break;
            case 3: deleteHotel(); break;
            case 4: viewAllHotels(); break;
            case 5: searchHotels(); break;
            case 6: sortHotels(); break;
            case 0: return;
            default:
                Utils::printError("Невірний вибір!");
                Utils::pause();
        }
    }
}

/**
 * @brief Додати готель
 */
void Menu::addHotel() {
    Utils::clearScreen();
    Utils::printHeader("ДОДАТИ ГОТЕЛЬ");

    try {
        std::string name = Utils::getStringInput("Назва готелю: ");
        std::string city = Utils::getStringInput("Місто: ");
        int stars = Utils::getIntInput("Кількість зірок (1-5): ", 1, 5);

        Hotel hotel(name, city, stars);

        if (hotelManager.addHotel(hotel)) {
            Utils::printSuccess("Готель успішно додано!");
        } else {
            Utils::printError("Не вдалося додати готель!");
        }
    } catch (const std::exception& e) {
        Utils::printError(std::string("Помилка: ") + e.what());
    }

    Utils::pause();
}

/**
 * @brief Редагувати готель
 */
void Menu::editHotel() {
    Utils::clearScreen();
    Utils::printHeader("РЕДАГУВАТИ ГОТЕЛЬ");

    int hotelId = selectHotel();
    if (hotelId == -1) return;

    Hotel* hotel = hotelManager.findHotelById(hotelId);
    if (!hotel) {
        Utils::printError("Готель не знайдено!");
        Utils::pause();
        return;
    }

    std::cout << "\nПоточні дані готелю:\n";
    hotel->display();

    std::cout << "\nЩо редагувати?\n";
    std::cout << "1. Назву\n";
    std::cout << "2. Місто\n";
    std::cout << "3. Кількість зірок\n";
    std::cout << "4. Все\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 4);

    try {
        std::string name = hotel->getName();
        std::string city = hotel->getCity();
        int stars = hotel->getStars();

        switch (choice) {
            case 1:
                name = Utils::getStringInput("Нова назва (або Enter щоб залишити): ", true);
                if (name.empty()) name = hotel->getName();
                break;
            case 2:
                city = Utils::getStringInput("Нове місто (або Enter щоб залишити): ", true);
                if (city.empty()) city = hotel->getCity();
                break;
            case 3:
                stars = Utils::getIntInput("Нова кількість зірок (1-5): ", 1, 5);
                break;
            case 4:
                name = Utils::getStringInput("Нова назва: ");
                city = Utils::getStringInput("Нове місто: ");
                stars = Utils::getIntInput("Нова кількість зірок (1-5): ", 1, 5);
                break;
            case 0:
                return;
        }

        Hotel newHotel(name, city, stars);

        if (hotelManager.editHotel(hotelId, newHotel)) {
            Utils::printSuccess("Готель успішно відредаговано!");
        } else {
            Utils::printError("Не вдалося відредагувати готель!");
        }
    } catch (const std::exception& e) {
        Utils::printError(std::string("Помилка: ") + e.what());
    }

    Utils::pause();
}

/**
 * @brief Видалити готель
 */
void Menu::deleteHotel() {
    Utils::clearScreen();
    Utils::printHeader("ВИДАЛИТИ ГОТЕЛЬ");

    int hotelId = selectHotel();
    if (hotelId == -1) return;

    Hotel* hotel = hotelManager.findHotelById(hotelId);
    if (!hotel) {
        Utils::printError("Готель не знайдено!");
        Utils::pause();
        return;
    }

    std::cout << "\nГотель, який буде видалено:\n";
    hotel->display();

    Utils::printWarning("При видаленні готелю будуть також видалені всі його номери та бронювання!");

    if (Utils::getConfirmation("Ви впевнені, що хочете видалити цей готель?")) {
        // Видаляємо всі номери цього готелю
        int deletedRooms = roomManager.deleteRoomsByHotelId(hotelId);

        // Видаляємо готель
        if (hotelManager.deleteHotel(hotelId)) {
            Utils::printSuccess("Готель успішно видалено! Також видалено номерів: " +
                              std::to_string(deletedRooms));
        } else {
            Utils::printError("Не вдалося видалити готель!");
        }
    } else {
        Utils::printInfo("Видалення скасовано.");
    }

    Utils::pause();
}

/**
 * @brief Переглянути всі готелі
 */
void Menu::viewAllHotels() {
    Utils::clearScreen();
    hotelManager.displayAll();
    Utils::pause();
}

/**
 * @brief Пошук готелів
 */
void Menu::searchHotels() {
    Utils::clearScreen();
    Utils::printHeader("ПОШУК ГОТЕЛІВ");

    std::cout << "Шукати за:\n";
    std::cout << "1. Назвою\n";
    std::cout << "2. Містом\n";
    std::cout << "3. Кількістю зірок\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 3);

    std::vector<Hotel> results;

    switch (choice) {
        case 1: {
            std::string name = Utils::getStringInput("Введіть назву готелю: ");
            results = hotelManager.searchByName(name);
            break;
        }
        case 2: {
            std::string city = Utils::getStringInput("Введіть місто: ");
            results = hotelManager.searchByCity(city);
            break;
        }
        case 3: {
            int stars = Utils::getIntInput("Введіть кількість зірок (1-5): ", 1, 5);
            results = hotelManager.searchByStars(stars);
            break;
        }
        case 0:
            return;
    }

    Utils::clearScreen();
    if (results.empty()) {
        Utils::printInfo("Нічого не знайдено!");
    } else {
        Utils::printHeader("РЕЗУЛЬТАТИ ПОШУКУ (" + std::to_string(results.size()) + ")");
        for (const auto& hotel : results) {
            hotel.display();
            std::cout << std::endl;
        }
    }

    Utils::pause();
}

/**
 * @brief Сортування готелів
 */
void Menu::sortHotels() {
    Utils::clearScreen();
    Utils::printHeader("СОРТУВАННЯ ГОТЕЛІВ");

    std::cout << "Сортувати за:\n";
    std::cout << "1. Назвою\n";
    std::cout << "2. Містом\n";
    std::cout << "3. Кількістю зірок\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 3);

    switch (choice) {
        case 1:
            hotelManager.sortByName();
            Utils::printSuccess("Готелі відсортовано за назвою!");
            break;
        case 2:
            hotelManager.sortByCity();
            Utils::printSuccess("Готелі відсортовано за містом!");
            break;
        case 3:
            hotelManager.sortByStars();
            Utils::printSuccess("Готелі відсортовано за кількістю зірок!");
            break;
        case 0:
            return;
    }

    viewAllHotels();
}

// ==================== 2. КЕРУВАННЯ НОМЕРАМИ ====================

/**
 * @brief Меню керування номерами
 */
void Menu::roomMenu() {
    while (true) {
        Utils::clearScreen();

        std::vector<std::string> options = {
            "Додати номер",
            "Редагувати номер",
            "Видалити номер",
            "Переглянути всі номери",
            "Переглянути номери готелю",
            "Пошук вільних номерів",
            "Сортування номерів"
        };

        int choice = Utils::displayMenu("КЕРУВАННЯ НОМЕРАМИ", options);

        switch (choice) {
            case 1: addRoom(); break;
            case 2: editRoom(); break;
            case 3: deleteRoom(); break;
            case 4: viewAllRooms(); break;
            case 5: viewRoomsByHotel(); break;
            case 6: searchFreeRooms(); break;
            case 7: sortRooms(); break;
            case 0: return;
            default:
                Utils::printError("Невірний вибір!");
                Utils::pause();
        }
    }
}

/**
 * @brief Додати номер
 */
void Menu::addRoom() {
    Utils::clearScreen();
    Utils::printHeader("ДОДАТИ НОМЕР");

    int hotelId = selectHotel();
    if (hotelId == -1) return;

    try {
        std::cout << "\nТип номера:\n";
        std::cout << "1. Люкс\n";
        std::cout << "2. Стандарт\n";
        int typeChoice = Utils::getIntInput("Оберіть тип: ", 1, 2);

        int capacity = Utils::getIntInput("Кількість місць (2 або 3): ", 2, 3);

        Room* room = nullptr;
        if (typeChoice == 1) {
            room = new LuxuryRoom(hotelId, capacity);
        } else {
            room = new StandardRoom(hotelId, capacity);
        }

        if (roomManager.addRoom(room)) {
            Utils::printSuccess("Номер успішно додано!");
        } else {
            delete room;
            Utils::printError("Не вдалося додати номер!");
        }
    } catch (const std::exception& e) {
        Utils::printError(std::string("Помилка: ") + e.what());
    }

    Utils::pause();
}

/**
 * @brief Редагувати номер
 */
void Menu::editRoom() {
    Utils::clearScreen();
    Utils::printHeader("РЕДАГУВАТИ НОМЕР");

    int roomId = selectRoom();
    if (roomId == -1) return;

    Room* room = roomManager.findRoomById(roomId);
    if (!room) {
        Utils::printError("Номер не знайдено!");
        Utils::pause();
        return;
    }

    std::cout << "\nПоточні дані номера:\n";
    room->display();

    std::cout << "\nЩо редагувати?\n";
    std::cout << "1. Тип номера\n";
    std::cout << "2. Кількість місць\n";
    std::cout << "3. Все\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 3);

    try {
        int hotelId = room->getHotelId();
        RoomType type = room->getType();
        int capacity = room->getCapacity();

        switch (choice) {
            case 1: {
                std::cout << "Новий тип:\n1. Люкс\n2. Стандарт\n";
                int typeChoice = Utils::getIntInput("Оберіть: ", 1, 2);
                type = (typeChoice == 1) ? RoomType::LUXURY : RoomType::STANDARD;
                break;
            }
            case 2:
                capacity = Utils::getIntInput("Нова кількість місць (2 або 3): ", 2, 3);
                break;
            case 3: {
                std::cout << "Новий тип:\n1. Люкс\n2. Стандарт\n";
                int typeChoice = Utils::getIntInput("Оберіть: ", 1, 2);
                type = (typeChoice == 1) ? RoomType::LUXURY : RoomType::STANDARD;
                capacity = Utils::getIntInput("Нова кількість місць (2 або 3): ", 2, 3);
                break;
            }
            case 0:
                return;
        }

        Room* newRoom = nullptr;
        if (type == RoomType::LUXURY) {
            newRoom = new LuxuryRoom(hotelId, capacity);
        } else {
            newRoom = new StandardRoom(hotelId, capacity);
        }

        if (roomManager.editRoom(roomId, newRoom)) {
            Utils::printSuccess("Номер успішно відредаговано!");
        } else {
            delete newRoom;
            Utils::printError("Не вдалося відредагувати номер!");
        }
    } catch (const std::exception& e) {
        Utils::printError(std::string("Помилка: ") + e.what());
    }

    Utils::pause();
}

/**
 * @brief Видалити номер
 */
void Menu::deleteRoom() {
    Utils::clearScreen();
    Utils::printHeader("ВИДАЛИТИ НОМЕР");

    int roomId = selectRoom();
    if (roomId == -1) return;

    Room* room = roomManager.findRoomById(roomId);
    if (!room) {
        Utils::printError("Номер не знайдено!");
        Utils::pause();
        return;
    }

    std::cout << "\nНомер, який буде видалено:\n";
    room->display();

    Utils::printWarning("При видаленні номера будуть також видалені всі його бронювання!");

    if (Utils::getConfirmation("Ви впевнені, що хочете видалити цей номер?")) {
        // Видаляємо всі бронювання цього номера
        int deletedBookings = bookingManager.deleteBookingsByRoomId(roomId);

        // Видаляємо номер
        if (roomManager.deleteRoom(roomId)) {
            Utils::printSuccess("Номер успішно видалено! Також видалено бронювань: " +
                              std::to_string(deletedBookings));
        } else {
            Utils::printError("Не вдалося видалити номер!");
        }
    } else {
        Utils::printInfo("Видалення скасовано.");
    }

    Utils::pause();
}

/**
 * @brief Переглянути всі номери
 */
void Menu::viewAllRooms() {
    Utils::clearScreen();
    roomManager.displayAll();
    Utils::pause();
}

/**
 * @brief Переглянути номери готелю
 */
void Menu::viewRoomsByHotel() {
    Utils::clearScreen();
    Utils::printHeader("НОМЕРИ ГОТЕЛЮ");

    int hotelId = selectHotel();
    if (hotelId == -1) return;

    Utils::clearScreen();
    roomManager.displayByHotelId(hotelId);
    Utils::pause();
}

/**
 * @brief Пошук вільних номерів
 */
void Menu::searchFreeRooms() {
    Utils::clearScreen();
    Utils::printHeader("ПОШУК ВІЛЬНИХ НОМЕРІВ");

    std::cout << "Шукати в:\n";
    std::cout << "1. Всіх готелях\n";
    std::cout << "2. Конкретному готелі\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 2);

    std::vector<Room*> results;

    switch (choice) {
        case 1:
            results = roomManager.searchFreeRooms();
            break;
        case 2: {
            int hotelId = selectHotel();
            if (hotelId == -1) return;
            results = roomManager.searchFreeRoomsByHotelId(hotelId);
            break;
        }
        case 0:
            return;
    }

    Utils::clearScreen();
    if (results.empty()) {
        Utils::printInfo("Вільних номерів не знайдено!");
    } else {
        Utils::printHeader("ВІЛЬНІ НОМЕРИ (" + std::to_string(results.size()) + ")");
        for (const auto& room : results) {
            room->display();
            std::cout << std::endl;
        }
    }

    Utils::pause();
}

/**
 * @brief Сортування номерів
 */
void Menu::sortRooms() {
    Utils::clearScreen();
    Utils::printHeader("СОРТУВАННЯ НОМЕРІВ");

    std::cout << "Сортувати за:\n";
    std::cout << "1. ID готелю\n";
    std::cout << "2. Типом\n";
    std::cout << "3. Кількістю місць\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 3);

    switch (choice) {
        case 1:
            roomManager.sortByHotelId();
            Utils::printSuccess("Номери відсортовано за ID готелю!");
            break;
        case 2:
            roomManager.sortByType();
            Utils::printSuccess("Номери відсортовано за типом!");
            break;
        case 3:
            roomManager.sortByCapacity();
            Utils::printSuccess("Номери відсортовано за кількістю місць!");
            break;
        case 0:
            return;
    }

    viewAllRooms();
}

// ==================== 3. КЕРУВАННЯ ГОСТЯМИ ====================

/**
 * @brief Меню керування гостями
 */
void Menu::guestMenu() {
    while (true) {
        Utils::clearScreen();

        std::vector<std::string> options = {
            "Додати гостя",
            "Редагувати гостя",
            "Видалити гостя",
            "Переглянути всіх гостей",
            "Пошук гостей",
            "Сортування гостей"
        };

        int choice = Utils::displayMenu("КЕРУВАННЯ ГОСТЯМИ", options);

        switch (choice) {
            case 1: addGuest(); break;
            case 2: editGuest(); break;
            case 3: deleteGuest(); break;
            case 4: viewAllGuests(); break;
            case 5: searchGuests(); break;
            case 6: sortGuests(); break;
            case 0: return;
            default:
                Utils::printError("Невірний вибір!");
                Utils::pause();
        }
    }
}

/**
 * @brief Додати гостя
 */
void Menu::addGuest() {
    Utils::clearScreen();
    Utils::printHeader("ДОДАТИ ГОСТЯ");

    try {
        std::string lastName = Utils::getStringInput("Прізвище: ");
        std::string firstName = Utils::getStringInput("Ім'я: ");
        std::string phone = Utils::getStringInput("Номер телефону: ");

        Guest guest(lastName, firstName, phone);

        if (guestManager.addGuest(guest)) {
            Utils::printSuccess("Гостя успішно додано!");
        } else {
            Utils::printError("Не вдалося додати гостя!");
        }
    } catch (const std::exception& e) {
        Utils::printError(std::string("Помилка: ") + e.what());
    }

    Utils::pause();
}

/**
 * @brief Редагувати гостя
 */
void Menu::editGuest() {
    Utils::clearScreen();
    Utils::printHeader("РЕДАГУВАТИ ГОСТЯ");

    int guestId = selectGuest();
    if (guestId == -1) return;

    Guest* guest = guestManager.findGuestById(guestId);
    if (!guest) {
        Utils::printError("Гостя не знайдено!");
        Utils::pause();
        return;
    }

    std::cout << "\nПоточні дані гостя:\n";
    guest->display();

    std::cout << "\nЩо редагувати?\n";
    std::cout << "1. Прізвище\n";
    std::cout << "2. Ім'я\n";
    std::cout << "3. Номер телефону\n";
    std::cout << "4. Все\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 4);

    try {
        std::string lastName = guest->getLastName();
        std::string firstName = guest->getFirstName();
        std::string phone = guest->getPhone();

        switch (choice) {
            case 1:
                lastName = Utils::getStringInput("Нове прізвище (або Enter щоб залишити): ", true);
                if (lastName.empty()) lastName = guest->getLastName();
                break;
            case 2:
                firstName = Utils::getStringInput("Нове ім'я (або Enter щоб залишити): ", true);
                if (firstName.empty()) firstName = guest->getFirstName();
                break;
            case 3:
                phone = Utils::getStringInput("Новий номер телефону (або Enter щоб залишити): ", true);
                if (phone.empty()) phone = guest->getPhone();
                break;
            case 4:
                lastName = Utils::getStringInput("Нове прізвище: ");
                firstName = Utils::getStringInput("Нове ім'я: ");
                phone = Utils::getStringInput("Новий номер телефону: ");
                break;
            case 0:
                return;
        }

        Guest newGuest(lastName, firstName, phone);

        if (guestManager.editGuest(guestId, newGuest)) {
            Utils::printSuccess("Гостя успішно відредаговано!");
        } else {
            Utils::printError("Не вдалося відредагувати гостя!");
        }
    } catch (const std::exception& e) {
        Utils::printError(std::string("Помилка: ") + e.what());
    }

    Utils::pause();
}

/**
 * @brief Видалити гостя
 */
void Menu::deleteGuest() {
    Utils::clearScreen();
    Utils::printHeader("ВИДАЛИТИ ГОСТЯ");

    int guestId = selectGuest();
    if (guestId == -1) return;

    Guest* guest = guestManager.findGuestById(guestId);
    if (!guest) {
        Utils::printError("Гостя не знайдено!");
        Utils::pause();
        return;
    }

    std::cout << "\nГість, якого буде видалено:\n";
    guest->display();

    Utils::printWarning("При видаленні гостя будуть також видалені всі його бронювання!");

    if (Utils::getConfirmation("Ви впевнені, що хочете видалити цього гостя?")) {
        // Видаляємо всі бронювання цього гостя
        int deletedBookings = bookingManager.deleteBookingsByGuestId(guestId);

        // Видаляємо гостя
        if (guestManager.deleteGuest(guestId)) {
            Utils::printSuccess("Гостя успішно видалено! Також видалено бронювань: " +
                              std::to_string(deletedBookings));
        } else {
            Utils::printError("Не вдалося видалити гостя!");
        }
    } else {
        Utils::printInfo("Видалення скасовано.");
    }

    Utils::pause();
}

/**
 * @brief Переглянути всіх гостей
 */
void Menu::viewAllGuests() {
    Utils::clearScreen();
    guestManager.displayAll();
    Utils::pause();
}

/**
 * @brief Пошук гостей
 */
void Menu::searchGuests() {
    Utils::clearScreen();
    Utils::printHeader("ПОШУК ГОСТЕЙ");

    std::cout << "Шукати за:\n";
    std::cout << "1. Прізвищем\n";
    std::cout << "2. Ім'ям\n";
    std::cout << "3. Номером телефону\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 3);

    std::vector<Guest> results;

    switch (choice) {
        case 1: {
            std::string lastName = Utils::getStringInput("Введіть прізвище: ");
            results = guestManager.searchByLastName(lastName);
            break;
        }
        case 2: {
            std::string firstName = Utils::getStringInput("Введіть ім'я: ");
            results = guestManager.searchByFirstName(firstName);
            break;
        }
        case 3: {
            std::string phone = Utils::getStringInput("Введіть номер телефону: ");
            results = guestManager.searchByPhone(phone);
            break;
        }
        case 0:
            return;
    }

    Utils::clearScreen();
    if (results.empty()) {
        Utils::printInfo("Нічого не знайдено!");
    } else {
        Utils::printHeader("РЕЗУЛЬТАТИ ПОШУКУ (" + std::to_string(results.size()) + ")");
        for (const auto& guest : results) {
            guest.display();
            std::cout << std::endl;
        }
    }

    Utils::pause();
}

/**
 * @brief Сортування гостей
 */
void Menu::sortGuests() {
    Utils::clearScreen();
    Utils::printHeader("СОРТУВАННЯ ГОСТЕЙ");

    std::cout << "Сортувати за:\n";
    std::cout << "1. Прізвищем\n";
    std::cout << "2. Ім'ям\n";
    std::cout << "3. Повним ім'ям\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 3);

    switch (choice) {
        case 1:
            guestManager.sortByLastName();
            Utils::printSuccess("Гостей відсортовано за прізвищем!");
            break;
        case 2:
            guestManager.sortByFirstName();
            Utils::printSuccess("Гостей відсортовано за ім'ям!");
            break;
        case 3:
            guestManager.sortByFullName();
            Utils::printSuccess("Гостей відсортовано за повним ім'ям!");
            break;
        case 0:
            return;
    }

    viewAllGuests();
}

// ==================== 4. КЕРУВАННЯ БРОНЮВАННЯМИ ====================

/**
 * @brief Меню керування бронюваннями
 */
void Menu::bookingMenu() {
    while (true) {
        Utils::clearScreen();

        std::vector<std::string> options = {
            "Додати бронювання",
            "Редагувати бронювання",
            "Видалити бронювання",
            "Переглянути всі бронювання",
            "Сортування бронювань"
        };

        int choice = Utils::displayMenu("КЕРУВАННЯ БРОНЮВАННЯМИ", options);

        switch (choice) {
            case 1: addBooking(); break;
            case 2: editBooking(); break;
            case 3: deleteBooking(); break;
            case 4: viewAllBookings(); break;
            case 5: sortBookings(); break;
            case 0: return;
            default:
                Utils::printError("Невірний вибір!");
                Utils::pause();
        }
    }
}

/**
 * @brief Додати бронювання
 */
void Menu::addBooking() {
    Utils::clearScreen();
    Utils::printHeader("ДОДАТИ БРОНЮВАННЯ");

    // Показуємо вільні готелі та їх номери
    std::cout << "\n=== ВІЛЬНІ ГОТЕЛІ ТА НОМЕРИ ===\n\n";

    auto hotels = hotelManager.getAllHotels();
    for (const auto& hotel : hotels) {
        size_t freeRooms = roomManager.getFreeRoomCountByHotelId(hotel.getId());
        if (freeRooms > 0) {
            std::cout << "🏨 " << hotel.getName() << " (" << hotel.getCity()
                      << ") - Вільних номерів: " << freeRooms << std::endl;
        }
    }

    std::cout << "\n";
    Utils::printSeparator(50);

    // Вибір гостя
    int guestId = selectGuest();
    if (guestId == -1) return;

    // Вибір номера (тільки вільні)
    Utils::clearScreen();
    Utils::printHeader("ОБЕРІТЬ НОМЕР");

    auto freeRooms = roomManager.searchFreeRooms();
    if (freeRooms.empty()) {
        Utils::printError("Немає вільних номерів!");
        Utils::pause();
        return;
    }

    std::cout << "\nВільні номери:\n\n";
    for (size_t i = 0; i < freeRooms.size(); i++) {
        std::cout << (i + 1) << ". ";
        freeRooms[i]->display();
        std::cout << std::endl;
    }

    int roomChoice = Utils::getIntInput("Оберіть номер (0 для скасування): ",
                                        0, freeRooms.size());
    if (roomChoice == 0) return;

    int roomId = freeRooms[roomChoice - 1]->getId();

    // Введення дат
    std::string checkInDate = Utils::getDateInput("Дата заїзду");
    std::string checkOutDate = Utils::getDateInput("Дата виїзду");

    // Перевірка, чи номер вільний в цей період
    if (bookingManager.isRoomOccupied(roomId, checkInDate, checkOutDate)) {
        Utils::printError("Номер вже зайнятий в цей період!");
        Utils::pause();
        return;
    }

    try {
        Booking booking(guestId, roomId, checkInDate, checkOutDate);

        if (bookingManager.addBooking(booking)) {
            // Позначаємо номер як зайнятий
            Room* room = roomManager.findRoomById(roomId);
            if (room) {
                room->setIsOccupied(true);
            }

            Utils::printSuccess("Бронювання успішно створено!");

            // Показуємо деталі бронювання
            std::cout << "\n📋 Деталі бронювання:\n";
            booking.display();
        } else {
            Utils::printError("Не вдалося створити бронювання!");
        }
    } catch (const std::exception& e) {
        Utils::printError(std::string("Помилка: ") + e.what());
    }

    Utils::pause();
}

/**
 * @brief Редагувати бронювання
 */
void Menu::editBooking() {
    Utils::clearScreen();
    Utils::printHeader("РЕДАГУВАТИ БРОНЮВАННЯ");

    if (bookingManager.getBookingCount() == 0) {
        Utils::printInfo("Немає бронювань для редагування!");
        Utils::pause();
        return;
    }

    // Показуємо всі бронювання
    bookingManager.displayAll();

    int bookingId = Utils::getIntInput("Введіть ID бронювання (0 для скасування): ", 0);
    if (bookingId == 0) return;

    Booking* booking = bookingManager.findBookingById(bookingId);
    if (!booking) {
        Utils::printError("Бронювання не знайдено!");
        Utils::pause();
        return;
    }

    std::cout << "\nПоточні дані бронювання:\n";
    booking->display();

    std::cout << "\nЩо редагувати?\n";
    std::cout << "1. Гостя\n";
    std::cout << "2. Номер\n";
    std::cout << "3. Дату заїзду\n";
    std::cout << "4. Дату виїзду\n";
    std::cout << "5. Все\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 5);

    try {
        int guestId = booking->getGuestId();
        int roomId = booking->getRoomId();
        std::string checkInDate = booking->getCheckInDate();
        std::string checkOutDate = booking->getCheckOutDate();

        switch (choice) {
            case 1:
                guestId = selectGuest();
                if (guestId == -1) return;
                break;
            case 2:
                roomId = selectRoom();
                if (roomId == -1) return;
                break;
            case 3:
                checkInDate = Utils::getDateInput("Нова дата заїзду");
                break;
            case 4:
                checkOutDate = Utils::getDateInput("Нова дата виїзду");
                break;
            case 5:
                guestId = selectGuest();
                if (guestId == -1) return;
                roomId = selectRoom();
                if (roomId == -1) return;
                checkInDate = Utils::getDateInput("Нова дата заїзду");
                checkOutDate = Utils::getDateInput("Нова дата виїзду");
                break;
            case 0:
                return;
        }

        Booking newBooking(guestId, roomId, checkInDate, checkOutDate);

        if (bookingManager.editBooking(bookingId, newBooking)) {
            Utils::printSuccess("Бронювання успішно відредаговано!");
        } else {
            Utils::printError("Не вдалося відредагувати бронювання!");
        }
    } catch (const std::exception& e) {
        Utils::printError(std::string("Помилка: ") + e.what());
    }

    Utils::pause();
}

/**
 * @brief Видалити бронювання
 */
void Menu::deleteBooking() {
    Utils::clearScreen();
    Utils::printHeader("ВИДАЛИТИ БРОНЮВАННЯ");

    if (bookingManager.getBookingCount() == 0) {
        Utils::printInfo("Немає бронювань для видалення!");
        Utils::pause();
        return;
    }

    // Показуємо всі бронювання
    bookingManager.displayAll();

    int bookingId = Utils::getIntInput("Введіть ID бронювання (0 для скасування): ", 0);
    if (bookingId == 0) return;

    Booking* booking = bookingManager.findBookingById(bookingId);
    if (!booking) {
        Utils::printError("Бронювання не знайдено!");
        Utils::pause();
        return;
    }

    std::cout << "\nБронювання, яке буде видалено:\n";
    booking->display();

    if (Utils::getConfirmation("Ви впевнені, що хочете видалити це бронювання?")) {
        int roomId = booking->getRoomId();

        if (bookingManager.deleteBooking(bookingId)) {
            // Звільняємо номер
            Room* room = roomManager.findRoomById(roomId);
            if (room) {
                room->setIsOccupied(false);
            }

            Utils::printSuccess("Бронювання успішно видалено! Номер звільнено.");
        } else {
            Utils::printError("Не вдалося видалити бронювання!");
        }
    } else {
        Utils::printInfo("Видалення скасовано.");
    }

    Utils::pause();
}

/**
 * @brief Переглянути всі бронювання
 */
void Menu::viewAllBookings() {
    Utils::clearScreen();
    bookingManager.displayAll();
    Utils::pause();
}

/**
 * @brief Пошук бронювань
 */
void Menu::searchBookings() {
    Utils::clearScreen();
    Utils::printHeader("ПОШУК БРОНЮВАНЬ");

    std::cout << "Шукати за:\n";
    std::cout << "1. Гостем\n";
    std::cout << "2. Номером\n";
    std::cout << "3. Датою заїзду\n";
    std::cout << "4. Датою виїзду\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 4);

    std::vector<Booking> results;

    switch (choice) {
        case 1: {
            int guestId = selectGuest();
            if (guestId == -1) return;
            results = bookingManager.searchByGuestId(guestId);
            break;
        }
        case 2: {
            int roomId = selectRoom();
            if (roomId == -1) return;
            results = bookingManager.searchByRoomId(roomId);
            break;
        }
        case 3: {
            std::string date = Utils::getDateInput("Дата заїзду");
            results = bookingManager.searchByCheckInDate(date);
            break;
        }
        case 4: {
            std::string date = Utils::getDateInput("Дата виїзду");
            results = bookingManager.searchByCheckOutDate(date);
            break;
        }
        case 0:
            return;
    }

    Utils::clearScreen();
    if (results.empty()) {
        Utils::printInfo("Нічого не знайдено!");
    } else {
        Utils::printHeader("РЕЗУЛЬТАТИ ПОШУКУ (" + std::to_string(results.size()) + ")");
        for (const auto& booking : results) {
            booking.display();
            std::cout << std::endl;
        }
    }

    Utils::pause();
}

/**
 * @brief Сортування бронювань
 */
void Menu::sortBookings() {
    Utils::clearScreen();
    Utils::printHeader("СОРТУВАННЯ БРОНЮВАНЬ");

    std::cout << "Сортувати за:\n";
    std::cout << "1. Датою заїзду\n";
    std::cout << "2. Датою виїзду\n";
    std::cout << "3. ID гостя\n";
    std::cout << "0. Скасувати\n";

    int choice = Utils::getIntInput("Ваш вибір: ", 0, 3);

    switch (choice) {
        case 1:
            bookingManager.sortByCheckInDate();
            Utils::printSuccess("Бронювання відсортовано за датою заїзду!");
            break;
        case 2:
            bookingManager.sortByCheckOutDate();
            Utils::printSuccess("Бронювання відсортовано за датою виїзду!");
            break;
        case 3:
            bookingManager.sortByGuestId();
            Utils::printSuccess("Бронювання відсортовано за ID гостя!");
            break;
        case 0:
            return;
    }

    viewAllBookings();
}

// ==================== 7. ДОПОМОГА ====================

/**
 * @brief Показати довідку
 */
void Menu::showHelp() {
    Utils::clearScreen();
    Utils::printHeader("ДОВІДКА");

    std::cout << R"(
📖 ОПИС ФУНКЦІЙ ПРОГРАМИ:

1️⃣  КЕРУВАННЯ ГОТЕЛЯМИ
   - Додавання нових готелів до системи
   - Редагування інформації про готелі (назва, місто, зірки)
   - Видалення готелів (з автоматичним видаленням номерів)
   - Перегляд всіх готелів
   - Пошук готелів за назвою, містом або кількістю зірок
   - Сортування готелів

2️⃣  КЕРУВАННЯ НОМЕРАМИ
   - Додавання номерів до готелів (Люкс або Стандарт, 2-3 місця)
   - Редагування типу та кількості місць
   - Видалення номерів (з автоматичним видаленням бронювань)
   - Перегляд всіх номерів або номерів конкретного готелю
   - Пошук вільних номерів
   - Сортування номерів

3️⃣  КЕРУВАННЯ ГОСТЯМИ
   - Додавання нових гостей (ПІБ, телефон)
   - Редагування інформації про гостей
   - Видалення гостей (з автоматичним видаленням бронювань)
   - Перегляд всіх гостей
   - Пошук гостей за прізвищем, ім'ям або телефоном
   - Сортування гостей за іменем

4️⃣  КЕРУВАННЯ БРОНЮВАННЯМИ
   - Створення нових бронювань з вибором вільних номерів
   - Редагування бронювань (гість, номер, дати)
   - Видалення бронювань (номер автоматично звільняється)
   - Перегляд всіх бронювань
   - Сортування бронювань

5️⃣  ПОШУК БРОНЮВАНЬ
   - Пошук за гостем, номером або датами

6️⃣  ДОПОМОГА
   - Показує цю довідку

7️⃣  АДМІНІСТРУВАННЯ (тільки для адміністратора)
   - Додавання нових користувачів
   - Видалення користувачів
   - Перегляд всіх користувачів системи

💾 Всі дані автоматично зберігаються при виході з програми.

⚠️  ВАЖЛИВО:
   - При видаленні готелю видаляються всі його номери та бронювання
   - При видаленні номера видаляються всі його бронювання
   - При видаленні гостя видаляються всі його бронювання
   - Номер може бути заброньований тільки якщо він вільний

    )" << std::endl;

    Utils::pause();
}

// ==================== 8. АДМІНІСТРУВАННЯ ====================

/**
 * @brief Меню адміністрування
 */
void Menu::adminMenu() {
    // Перевірка прав адміністратора
    if (!userManager.isCurrentUserAdmin()) {
        Utils::printError("Доступ заборонено! Тільки для адміністраторів.");
        Utils::pause();
        return;
    }

    while (true) {
        Utils::clearScreen();

        std::vector<std::string> options = {
            "Додати користувача",
            "Видалити користувача",
            "Переглянути всіх користувачів"
        };

        int choice = Utils::displayMenu("АДМІНІСТРУВАННЯ", options);

        switch (choice) {
            case 1: addUser(); break;
            case 2: deleteUser(); break;
            case 3: viewAllUsers(); break;
            case 0: return;
            default:
                Utils::printError("Невірний вибір!");
                Utils::pause();
        }
    }
}

/**
 * @brief Додати користувача
 */
void Menu::addUser() {
    Utils::clearScreen();
    Utils::printHeader("ДОДАТИ КОРИСТУВАЧА");

    try {
        std::string username = Utils::getStringInput("Логін: ");

        if (userManager.userExists(username)) {
            Utils::printError("Користувач з таким логіном вже існує!");
            Utils::pause();
            return;
        }

        std::string password = Utils::getStringInput("Пароль: ");

        bool isAdmin = Utils::getConfirmation("Зробити адміністратором?");

        User user(username, password, isAdmin);

        if (userManager.addUser(user)) {
            Utils::printSuccess("Користувача успішно додано!");
        } else {
            Utils::printError("Не вдалося додати користувача!");
        }
    } catch (const std::exception& e) {
        Utils::printError(std::string("Помилка: ") + e.what());
    }

    Utils::pause();
}

/**
 * @brief Видалити користувача
 */
void Menu::deleteUser() {
    Utils::clearScreen();
    Utils::printHeader("ВИДАЛИТИ КОРИСТУВАЧА");

    userManager.displayAll();

    std::string username = Utils::getStringInput("Логін користувача для видалення (або Enter для скасування): ", true);
    if (username.empty()) return;

    if (Utils::getConfirmation("Ви впевнені, що хочете видалити користувача " + username + "?")) {
        if (userManager.deleteUser(username)) {
            Utils::printSuccess("Користувача успішно видалено!");
        } else {
            Utils::printError("Не вдалося видалити користувача!");
        }
    } else {
        Utils::printInfo("Видалення скасовано.");
    }

    Utils::pause();
}

/**
 * @brief Переглянути всіх користувачів
 */
void Menu::viewAllUsers() {
    Utils::clearScreen();
    userManager.displayAll();
    Utils::pause();
}

// ==================== ДОПОМІЖНІ МЕТОДИ ====================

/**
 * @brief Зберегти всі дані
 */
void Menu::saveAllData() {
    Utils::printInfo("Збереження даних...");

    bool success = true;

    if (!hotelManager.saveToFile()) {
        Utils::printError("Помилка збереження готелів!");
        success = false;
    }

    if (!roomManager.saveToFile()) {
        Utils::printError("Помилка збереження номерів!");
        success = false;
    }

    if (!guestManager.saveToFile()) {
        Utils::printError("Помилка збереження гостей!");
        success = false;
    }

    if (!bookingManager.saveToFile()) {
        Utils::printError("Помилка збереження бронювань!");
        success = false;
    }

    if (!userManager.saveToFile()) {
        Utils::printError("Помилка збереження користувачів!");
        success = false;
    }

    if (success) {
        Utils::printSuccess("Всі дані успішно збережено!");
    }
}

/**
 * @brief Завантажити всі дані
 */
void Menu::loadAllData() {
    Utils::printInfo("Завантаження даних...");

    hotelManager.loadFromFile();
    roomManager.loadFromFile();
    guestManager.loadFromFile();
    bookingManager.loadFromFile();
    userManager.loadFromFile();

    Utils::printSuccess("Дані завантажено!");

    // Показуємо статистику
    std::cout << "\n📊 Статистика системи:\n";
    std::cout << "   Готелів: " << hotelManager.getHotelCount() << std::endl;
    std::cout << "   Номерів: " << roomManager.getRoomCount() << std::endl;
    std::cout << "   Гостей: " << guestManager.getGuestCount() << std::endl;
    std::cout << "   Бронювань: " << bookingManager.getBookingCount() << std::endl;
    std::cout << "   Користувачів: " << userManager.getUserCount() << std::endl;

    Utils::pause();
}

/**
 * @brief Вибрати готель зі списку
 */
int Menu::selectHotel() {
    auto hotels = hotelManager.getAllHotels();

    if (hotels.empty()) {
        Utils::printError("Немає готелів в системі! Спочатку додайте готель.");
        Utils::pause();
        return -1;
    }

    Utils::clearScreen();
    Utils::printHeader("ОБЕРІТЬ ГОТЕЛЬ");

    std::cout << "\nСписок готелів:\n\n";
    for (size_t i = 0; i < hotels.size(); i++) {
        std::cout << (i + 1) << ". " << hotels[i].getName()
                  << " (" << hotels[i].getCity() << ") - ";
        for (int j = 0; j < hotels[i].getStars(); j++) {
            std::cout << "★";
        }
        std::cout << std::endl;
    }

    int choice = Utils::getIntInput("\nОберіть готель (0 для скасування): ",
                                    0, hotels.size());

    if (choice == 0) return -1;

    return hotels[choice - 1].getId();
}

/**
 * @brief Вибрати номер зі списку
 */
int Menu::selectRoom() {
    auto rooms = roomManager.getAllRooms();

    if (rooms.empty()) {
        Utils::printError("Немає номерів в системі! Спочатку додайте номер.");
        Utils::pause();
        return -1;
    }

    Utils::clearScreen();
    Utils::printHeader("ОБЕРІТЬ НОМЕР");

    std::cout << "\nСписок номерів:\n\n";
    for (size_t i = 0; i < rooms.size(); i++) {
        std::cout << (i + 1) << ". ";
        std::cout << "ID: " << rooms[i]->getId()
                  << " | Готель ID: " << rooms[i]->getHotelId()
                  << " | Тип: " << rooms[i]->getTypeName()
                  << " | Місць: " << rooms[i]->getCapacity()
                  << " | " << (rooms[i]->getIsOccupied() ? "Зайнятий ❌" : "Вільний ✅")
                  << std::endl;
    }

    int choice = Utils::getIntInput("\nОберіть номер (0 для скасування): ",
                                    0, rooms.size());

    if (choice == 0) return -1;

    return rooms[choice - 1]->getId();
}

/**
 * @brief Вибрати гостя зі списку
 */
int Menu::selectGuest() {
    auto guests = guestManager.getAllGuests();

    if (guests.empty()) {
        Utils::printError("Немає гостей в системі! Спочатку додайте гостя.");
        Utils::pause();
        return -1;
    }

    Utils::clearScreen();
    Utils::printHeader("ОБЕРІТЬ ГОСТЯ");

    std::cout << "\nСписок гостей:\n\n";
    for (size_t i = 0; i < guests.size(); i++) {
        std::cout << (i + 1) << ". " << guests[i].getFullName()
                  << " (Тел: " << guests[i].getPhone() << ")" << std::endl;
    }

    int choice = Utils::getIntInput("\nОберіть гостя (0 для скасування): ",
                                    0, guests.size());

    if (choice == 0) return -1;

    return guests[choice - 1].getId();
}