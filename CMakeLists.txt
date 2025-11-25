cmake_minimum_required(VERSION 3.15)
project(HotelBookingSystem)

# Встановлюємо стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Додаємо шлях до заголовкових файлів
include_directories(${CMAKE_SOURCE_DIR}/include)

# Список всіх вихідних файлів
set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/Hotel.cpp
        ${CMAKE_SOURCE_DIR}/src/Room.cpp
        ${CMAKE_SOURCE_DIR}/src/Guest.cpp
        ${CMAKE_SOURCE_DIR}/src/Booking.cpp
        ${CMAKE_SOURCE_DIR}/src/User.cpp
        ${CMAKE_SOURCE_DIR}/src/HotelManager.cpp
        ${CMAKE_SOURCE_DIR}/src/RoomManager.cpp
        ${CMAKE_SOURCE_DIR}/src/GuestManager.cpp
        ${CMAKE_SOURCE_DIR}/src/BookingManager.cpp
        ${CMAKE_SOURCE_DIR}/src/UserManager.cpp
        ${CMAKE_SOURCE_DIR}/src/Utils.cpp
        ${CMAKE_SOURCE_DIR}/src/Menu.cpp
)

# Список всіх заголовкових файлів
set(HEADERS
        ${CMAKE_SOURCE_DIR}/include/Hotel.h
        ${CMAKE_SOURCE_DIR}/include/Room.h
        ${CMAKE_SOURCE_DIR}/include/Guest.h
        ${CMAKE_SOURCE_DIR}/include/Booking.h
        ${CMAKE_SOURCE_DIR}/include/User.h
        ${CMAKE_SOURCE_DIR}/include/HotelManager.h
        ${CMAKE_SOURCE_DIR}/include/RoomManager.h
        ${CMAKE_SOURCE_DIR}/include/GuestManager.h
        ${CMAKE_SOURCE_DIR}/include/BookingManager.h
        ${CMAKE_SOURCE_DIR}/include/UserManager.h
        ${CMAKE_SOURCE_DIR}/include/Utils.h
        ${CMAKE_SOURCE_DIR}/include/Menu.h
        include/Constants.h
)

# Створення виконуваного файлу
add_executable(HotelBookingSystem ${SOURCES} ${HEADERS})

# Налаштування для macOS (підтримка UTF-8)
if(APPLE)
    set_target_properties(HotelBookingSystem PROPERTIES
            XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++17"
            XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++"
    )
    target_compile_options(HotelBookingSystem PRIVATE
            -Wall
            -Wextra
            -std=c++17
            -stdlib=libc++
    )
    target_link_options(HotelBookingSystem PRIVATE -stdlib=libc++)
endif()

# Налаштування для інших Unix систем
if(UNIX AND NOT APPLE)
    target_compile_options(HotelBookingSystem PRIVATE -Wall -Wextra)
endif()

# Створення папки data при збірці
add_custom_command(TARGET HotelBookingSystem POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/data
)

# Повідомлення про успішну конфігурацію
message(STATUS "===========================================")
message(STATUS "Проєкт 'Система бронювання номерів в готелях'")
message(STATUS "Платформа: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Стандарт C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Компілятор: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "===========================================")
