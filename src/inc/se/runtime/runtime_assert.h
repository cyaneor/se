/**
 * @file runtime_assert.h
 * @brief Определение макросов для проверки условий
 *        и выбрасывания исключений с описанием в runtime.
 *
 * Этот файл содержит макросы, которые упрощают процесс проверки условий
 * и выбрасывания исключений с описанием в зависимости от выполнения этих условий.
 *
 * Макросы предоставляют удобный интерфейс для обработки ошибок в коде,
 * позволяя избежать дублирования кода и улучшая читаемость.
 *
 * Включает следующие макросы:
 * - `se_runtime_assert_if`:
 *    Проверяет условие и выбрасывает исключение с описанием,
 *    если оно истинно.
 * - `se_runtime_assert_ifn`:
 *    Проверяет условие на ложность и выбрасывает исключение с описанием,
 *    если оно ложно.
 * - `se_runtime_assert`:
 *    Удобная обертка для проверки условий
 *    с произвольным количеством аргументов.
 *
 * Все макросы зависят от реализации `se_runtime_throw_with_desc`,
 * которая отвечает за фактическое выбрасывание исключений с описанием.
 * Убедитесь, что эта функция корректно реализована и фреймы исключений
 * инициализированы перед использованием данных макросов.
 *
 * @note Использование этих макросов позволяет упростить обработку ошибок
 *       и сделать код более чистым и понятным.
 *
 * @warning Неправильное использование макросов может привести к
 *          некорректному поведению программы, поэтому важно следить
 *          за их правильной реализацией и инициализацией фреймов исключений.
 *
 * @see se_runtime_throw_with_desc
 */

#ifndef SE_RUNTIME_ASSERT_H
#define SE_RUNTIME_ASSERT_H

#include "runtime_throw_with_desc.h"

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
/**
 * @def se_runtime_assert_if(expr, ...)
 * @brief Проверяет условие и выбрасывает исключение с описанием,
 *        если оно истинно.
 *
 * Этот макрос выполняет проверку заданного условия `expr`.
 * Если условие истинно, он вызывает макрос `se_runtime_throw_with_desc`
 * с переданными аргументами.
 *
 * Это позволяет удобно обрабатывать ситуации, когда необходимо выбросить исключение
 * с описанием в зависимости от выполнения определенного условия.
 *
 * @param expr Условие, которое необходимо проверить.
 * @param ... Дополнительные аргументы, передаваемые в `se_runtime_throw_with_desc`.
 *
 * @note Использование данного макроса позволяет избежать дублирования кода
 *       при проверке условий и выбрасывании исключений с описанием.
 */
#    define se_runtime_assert_if(expr, ...)                                                        \
        if (expr)                                                                                  \
        se_runtime_throw_with_desc(__VA_ARGS__)

/**
 * @def se_runtime_assert_ifn(expr, ...)
 * @brief Проверяет условие на ложность
 *        и выбрасывает исключение с описанием, если оно ложно.
 *
 * Этот макрос является инверсией `se_runtime_assert_if`.
 * Он проверяет заданное условие `expr`. Если условие ложно,
 * он вызывает макрос `se_runtime_throw_with_desc` с переданными аргументами.
 *
 * @param expr Условие, которое необходимо проверить на ложность.
 * @param ... Дополнительные аргументы, передаваемые в `se_runtime_throw_with_desc`.
 *
 * @note Данный макрос полезен для случаев, когда необходимо выбросить
 *       исключение с описанием, если условие не выполняется.
 */
#    define se_runtime_assert_ifn(expr, ...) se_runtime_assert_if(!(expr), __VA_ARGS__)

/**
 * @def se_runtime_assert(...)
 * @brief Проверяет условие на ложность
 *        и выбрасывает исключение с описанием, если оно ложно.
 *
 * Этот макрос является удобной оберткой над `se_runtime_assert_ifn`,
 * позволяя вызывать проверку условий с произвольным количеством аргументов.
 * Он проверяет, что переданные аргументы не являются истинными,
 * и выбрасывает исключение с описанием, если это так.
 *
 * @param ... Условия и дополнительные аргументы, передаваемые в `se_runtime_throw_with_desc`.
 *
 * @note Использование данного макроса позволяет упростить код,
 *       обеспечивая единообразный способ проверки условий
 *       и выбрасывания исключений с описанием.
 */
#    define se_runtime_assert(...) se_runtime_assert_ifn(__VA_ARGS__)
#else
#    error "You must enable SE_LIBRARY_ERROR_DESC option in CMake to use error description macros."
#endif // SE_LIBRARY_OPTION_ERROR_DESC

#endif // SE_RUNTIME_ASSERT_H
