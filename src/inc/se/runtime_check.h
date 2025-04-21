/**
 * @file runtime_check.h
 * @brief Макросы для проверки условий времени выполнения.
 *
 * Заголовочный файл предоставляет набор макросов
 * для проверки условий с генерацией исключений при их нарушении.
 *
 * Основные возможности:
 * - Проверка условий с выбрасыванием исключений
 * - Поддержка как позитивных, так и негативных проверок
 * - Вариативный интерфейс для удобного использования
 * - Интеграция с системой обработки исключений
 */

#ifndef SE_RUNTIME_CHECK_H
#define SE_RUNTIME_CHECK_H

#include "runtime_throw_with_code.h"

/**
 * @def se_runtime_check_if
 * @brief Проверяет условие и выбрасывает исключение, если оно истинно.
 *
 * @param expr Выражение для проверки.
 * @param code Код ошибки для выбрасывания, если условие истинно.
 *
 * Пример использования:
 * @code
 * // Выбросить исключение если указатель NULL
 * se_runtime_check_if(ptr == NULL, SE_ERROR_NULL_POINTER);
 * @endcode
 *
 * @see se_runtime_throw_with_code
 */
#define se_runtime_check_if(expr, code)                                                            \
    if (expr)                                                                                      \
    se_runtime_throw_with_code(code)

/**
 * @def se_runtime_check_ifn
 * @brief Проверяет условие и выбрасывает исключение, если оно ложно.
 *
 * @param expr Выражение для проверки.
 * @param code Код ошибки для выбрасывания, если условие ложно.
 *
 * Пример использования:
 * @code
 * // Выбросить исключение если выделение памяти не удалось
 * se_runtime_check_ifn(memory != NULL, SE_ERROR_ALLOC_FAILED);
 * @endcode
 *
 * @see se_runtime_check_if
 */
#define se_runtime_check_ifn(expr, code) se_runtime_check_if(!(expr), code)

/**
 * @def se_runtime_check
 * @brief Основной макрос проверки (псевдоним для se_runtime_check_ifn).
 *
 * Проверяет условие и выбрасывает исключение, если оно ложно.
 * Поддерживает вариативный синтаксис.
 *
 * @param ... Условие и код ошибки (аналогично se_runtime_check_ifn).
 *
 * Пример использования:
 * @code
 * // Проверка допустимого диапазона
 * se_runtime_check(index < max_size, SE_ERROR_OUT_OF_RANGE);
 * @endcode
 *
 * @see se_runtime_check_ifn
 */
#define se_runtime_check(...) se_runtime_check_ifn(__VA_ARGS__)

#endif // SE_RUNTIME_CHECK_H