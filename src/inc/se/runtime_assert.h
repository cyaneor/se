/**
 * @file runtime_assert.h
 * @brief Макросы для проверки утверждений времени выполнения.
 *
 * Заголовочный файл предоставляет набор макросов
 * для проверки утверждений с генерацией исключений при их нарушении.
 *
 * Основные возможности:
 * - Проверка условий с выбрасыванием исключений с описанием ошибки
 * - Фиксированный код ошибки `SE_RUNTIME_ERROR_INTERRUPT`
 * - Поддержка как позитивных, так и негативных проверок
 * - Вариативный интерфейс для удобного использования
 */

#ifndef SE_RUNTIME_ASSERT_H
#define SE_RUNTIME_ASSERT_H

#include "runtime_throw_with_desc.h"

/**
 * @def se_runtime_assert_if
 * @brief Проверяет условие и выбрасывает исключение с описанием, если оно истинно.
 *
 * @param expr Выражение для проверки.
 * @param desc Описание ошибки (строковый литерал).
 * @note Всегда использует код ошибки `SE_RUNTIME_ERROR_INTERRUPT`.
 *
 * Пример использования:
 * @code
 * // Выбросить исключение если указатель NULL
 * se_runtime_assert_if(ptr == NULL, "Null pointer encountered");
 * @endcode
 *
 * @see se_runtime_throw_with_desc
 */
#define se_runtime_assert_if(expr, desc)                                                           \
    if (expr)                                                                                      \
    se_runtime_throw_with_desc(desc)

/**
 * @def se_runtime_assert_ifn
 * @brief Проверяет условие и выбрасывает исключение с описанием, если оно ложно.
 *
 * @param expr Выражение для проверки.
 * @param desc Описание ошибки (строковый литерал).
 * @note Всегда использует код ошибки `SE_RUNTIME_ERROR_INTERRUPT`.
 *
 * Пример использования:
 * @code
 * // Выбросить исключение если выделение памяти не удалось
 * se_runtime_assert_ifn(memory != NULL, "Memory allocation failed");
 * @endcode
 *
 * @see se_runtime_assert_if
 */
#define se_runtime_assert_ifn(expr, desc) se_runtime_assert_if(!(expr), desc)

/**
 * @def se_runtime_assert
 * @brief Основной макрос проверки утверждений (псевдоним для se_runtime_assert_ifn).
 *
 * Проверяет условие и выбрасывает исключение с описанием, если оно ложно.
 * Поддерживает вариативный синтаксис.
 *
 * @param ... Условие и описание ошибки (аналогично `se_runtime_assert_ifn`).
 * @note Всегда использует код ошибки `SE_RUNTIME_ERROR_INTERRUPT`.
 *
 * Пример использования:
 * @code
 * // Проверка допустимого диапазона
 * se_runtime_assert(index < max_size, "Index out of bounds");
 * @endcode
 *
 * @see se_runtime_assert_ifn
 */
#define se_runtime_assert(...) se_runtime_assert_ifn(__VA_ARGS__)

#endif // SE_RUNTIME_ASSERT_H