cmake_minimum_required(VERSION 3.12)
project(se LANGUAGES C CXX)

# Настройки для C (совпадают с src/CMakeLists.txt)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Настройки для C++ (для Google Test)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем директории
add_subdirectory(src)
add_subdirectory(tests)

# Подключаем Google Test как подмодуль
add_subdirectory(ext/googletest EXCLUDE_FROM_ALL)