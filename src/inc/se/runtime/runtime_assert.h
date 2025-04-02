/**
 * @file runtime_assert.h
 * @brief Заголовочный файл для реализации утверждений с выбросом исключений.
 *
 * Этот файл предоставляет макросы для проверки условий во время выполнения программы.
 * При нарушении условий вызывается `se_runtime_throw` для генерации исключений.
 * Зависит от механизма обработки исключений, определённого в `runtime_throw.h`.
 */

#ifndef SE_RUNTIME_ASSERT_H
#define SE_RUNTIME_ASSERT_H

#include "runtime_throw.h"

/**
 * @def se_runtime_assert_if(expr, ...)
 * @brief Выбрасывает исключение, если выражение истинно.
 *
 * Проверяет условие `expr` и, если оно истинно, вызывает `se_runtime_throw`
 * с переданными аргументами для генерации исключения.
 *
 * @param expr Выражение, которое проверяется на истинность.
 * @param ... Аргументы для `se_runtime_throw` (например, код исключения и дополнительные данные).
 */
#define se_runtime_assert_if(expr, ...)                                                            \
    if (expr)                                                                                      \
    se_runtime_throw(__VA_ARGS__)

/**
 * @def se_runtime_assert_ifn(expr, ...)
 * @brief Выбрасывает исключение, если выражение ложно.
 *
 * Инвертирует результат выражения `expr` и передаёт его в `se_runtime_assert_if`.
 * Если выражение ложно, вызывает `se_runtime_throw` с переданными аргументами.
 *
 * @param expr Выражение, которое проверяется на ложность.
 * @param ... Аргументы для `se_runtime_throw` (например, код исключения и дополнительные данные).
 */
#define se_runtime_assert_ifn(expr, ...) se_runtime_assert_if(!(expr), __VA_ARGS__)

/**
 * @def se_runtime_assert(...)
 * @brief Утверждение, выбрасывающее исключение при ложном условии.
 *
 * Эквивалентен `se_runtime_assert_ifn`, используется как более короткая форма
 * для проверки условия и выброса исключения, если оно не выполняется.
 *
 * @param ... Выражение для проверки и аргументы для `se_runtime_throw`.
 */
#define se_runtime_assert(...) se_runtime_assert_ifn(__VA_ARGS__)

#endif // SE_RUNTIME_ASSERT_H
