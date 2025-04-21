# -------------------------------------------------------------------------------------- #
# Обработка пользовательских опций сборки                                                #
#                                                                                        #
# Этот скрипт получает все переменные (опции), проверяет их на соответствие              #
# определенному шаблону и добавляет их в список приватных определений компиляции,        #
# если они активированы.                                                                 #
# -------------------------------------------------------------------------------------- #

# Получаем список всех переменных (опций) в текущем каталоге CMake
get_property(CMAKE_OPTIONS DIRECTORY PROPERTY VARIABLES)

# Проходим по всем найденным опциям
message(STATUS "Listing all enabled configuration options:")
foreach (CMAKE_OPTION IN ITEMS ${CMAKE_OPTIONS})
    # Проверяем, соответствует ли имя опции шаблону "^SE_LIBRARY_OPTION_.*" и не равно ли оно "OFF".
    # Если оба условия выполняются, добавляем опцию в список определений компиляции.
    if (CMAKE_OPTION MATCHES "^SE_LIBRARY_OPTION_.*" AND NOT ${CMAKE_OPTION} STREQUAL "OFF")
        # Печатаем ключ и значение опции с дополнительным форматированием
        message(STATUS ":: ${CMAKE_OPTION}")
        # Добавляем опцию в список SE_PRIVATE_COMPILE_DEFINITIONS
        list(APPEND SE_TARGET_PRIVATE_COMPILE_DEFINITIONS ${CMAKE_OPTION})
    endif ()
endforeach ()

