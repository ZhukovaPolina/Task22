cmake_minimum_required(VERSION 3.14)
project(Task22 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Пути  
set(TASK22_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/Task22)
set(LIBRARY_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/Library)
set(TEST_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/Tests)

# Проверка существования
if(NOT EXISTS ${TASK22_DIR}/main.cpp)
    message(FATAL_ERROR "main.cpp not found at ${TASK22_DIR}/main.cpp")
endif()
if(NOT EXISTS ${LIBRARY_DIR}/Case.h)
    message(FATAL_ERROR "Library headers not found in ${LIBRARY_DIR}")
endif()
if(NOT EXISTS ${TEST_DIR}/Tests.cpp)
    message(FATAL_ERROR "Tests.cpp not found in ${TEST_DIR}")
endif()

# === Библиотека: все классы (без main.cpp) ===
set(LIB_SOURCES
    ${LIBRARY_DIR}/Person.cpp
    ${LIBRARY_DIR}/Client.cpp
    ${LIBRARY_DIR}/Lawyer.cpp
    ${LIBRARY_DIR}/LegalService.cpp
    ${LIBRARY_DIR}/Case.cpp
    ${LIBRARY_DIR}/LawFirm.cpp
)

add_library(LawFirmLib STATIC ${LIB_SOURCES})
target_include_directories(LawFirmLib PUBLIC ${LIBRARY_DIR})

# === Основная программа ===
add_executable(Task22 ${TASK22_DIR}/main.cpp)
target_link_libraries(Task22 LawFirmLib)

# === Тесты ===
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0  # v1.14.0 совместим с C++17 и стабилен
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Task22_tests ${TEST_DIR}/Tests.cpp)
target_link_libraries(Task22_tests LawFirmLib GTest::gtest_main)
add_test(NAME Task22Test COMMAND Task22_tests)