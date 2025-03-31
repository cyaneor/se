# Установка переменной gtest_force_shared_crt, для сборки под Windows
set(gtest_force_shared_crt ON CACHE BOOL
        "Установка переменной gtest_force_shared_crt значение ON, чтобы использовать общий CRT в Google Test.")

# Включаем тестирование
enable_testing()

# Создаём исполняемый файл для тестов
add_executable(${CMAKE_PROJECT_NAME}_tests
        src/numeric_limits.cpp
)

# Линкуем с Google Test и библиотекой se
target_link_libraries(${CMAKE_PROJECT_NAME}_tests
        PRIVATE gtest gtest_main se
)

# Добавляем тесты в систему
add_test(NAME ${CMAKE_PROJECT_NAME}_tests COMMAND ${CMAKE_PROJECT_NAME}_tests)