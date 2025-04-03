/**
 * @file runtime_no_null.h
 * @brief Заголовочный файл для проверки указателей
 *        на отсутствие `nullptr` с выбросом исключений.
 *
 * Этот файл предоставляет макрос `se_runtime_no_null` для удобной проверки указателей
 * на `nullptr` во время выполнения программы в языке C. Макрос заменяет повторяющиеся
 * вызовы `se_runtime_assert` с кодом ошибки `SE_RUNTIME_ERROR_NULL_POINTER`,
 * делая код более компактным и выразительным.
 */

#ifndef SE_RUNTIME_NO_NULL_H
#define SE_RUNTIME_NO_NULL_H

#include "runtime_assert.h"

/**
 * @def se_runtime_no_null(ptr, ...)
 * @brief Проверяет, что указатель не равен `nullptr`,
 *        и выбрасывает исключение при нарушении.
 *
 * Проверяет указатель `ptr` на ненулевое значение с использованием `se_runtime_assert`.
 * Если `ptr` равен `nullptr`, генерируется исключение с кодом `SE_RUNTIME_ERROR_NULL_POINTER`
 * и дополнительными данными, переданными через `__VA_ARGS__`.
 *
 * @param ptr Указатель, который не должен быть `nullptr`.
 * @param ... Дополнительные аргументы
 *            для `se_runtime_throw` (например, сообщение об ошибке).
 */
#define se_runtime_no_null(ptr, ...)                                                               \
    se_runtime_assert(ptr, SE_RUNTIME_ERROR_NULL_POINTER, __VA_ARGS__)

#endif // SE_RUNTIME_NO_NULL_H