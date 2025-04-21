project(${CMAKE_PROJECT_NAME}_tests
        VERSION 3.14)

# Установка переменной gtest_force_shared_crt, для сборки под Windows
set(gtest_force_shared_crt ON CACHE BOOL
        "Установка переменной gtest_force_shared_crt значение ON, чтобы использовать общий CRT в Google Test.")

# Включаем тестирование
enable_testing()

# Создаём исполняемый файл для тестов
add_executable(${PROJECT_NAME}
        src/error.cpp
        src/memory_raw.cpp
        src/memory_view.cpp
        src/numeric_limits.cpp
)

# Линкуем с Google Test и библиотекой se
target_link_libraries(${CMAKE_PROJECT_NAME}_tests
        PRIVATE gtest gtest_main se
)

# Копирование библиотеки ae в директорию с исполняемым файлом
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:se> $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Добавляем тесты в систему
add_test(NAME ${CMAKE_PROJECT_NAME}_tests COMMAND ${CMAKE_PROJECT_NAME}_tests)