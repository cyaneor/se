/**
 * @file runtime_throw.h
 * @brief Заголовочный файл
 *        для реализации механизма выброса исключений во время выполнения.
 *
 * Этот файл предоставляет макросы для генерации и повторного выброса исключений,
 * используя фреймы исключений из `runtime_except_frame.h`
 * и обработку ошибок из `runtime_fail.h`.
 */

#ifndef SE_RUNTIME_THROW_H
#define SE_RUNTIME_THROW_H

#include "runtime_fail.h"
#include "runtime_except_frame.h"

/**
 * @def se_runtime_throw(code, ...)
 * @brief Выбрасывает исключение с указанным кодом
 *        и дополнительными аргументами.
 *
 * Если текущий фрейм исключений находится в начале стека,
 * вызывает `se_runtime_fail` для завершения программы с ошибкой.
 *
 * В противном случае выполняет переход к предыдущему фрейму с помощью
 * `se_runtime_except_frame_load`, передавая указанный код исключения.
 *
 * @param code Код исключения.
 * @param ... Дополнительные аргументы для передачи в `se_runtime_fail`.
 */
#define se_runtime_throw(code, ...)                                                                \
    do                                                                                             \
    {                                                                                              \
        if (se_runtime_except_frame_is_begin())                                                    \
        {                                                                                          \
            se_runtime_fail(code, __VA_ARGS__);                                                    \
        }                                                                                          \
        se_runtime_except_frame_load(code);                                                        \
    } while (0)

/**
 * @def se_runtime_rethrow(code, ...)
 * @brief Повторно выбрасывает исключение
 *        с указанным кодом и дополнительными аргументами.
 *
 * Эквивалентен `se_runtime_throw`, используется
 * для явного указания повторного выброса исключения.
 *
 * @param code Код исключения.
 * @param ... Дополнительные аргументы для передачи в `se_runtime_fail`.
 */
#define se_runtime_rethrow(code, ...) se_runtime_throw(code, __VA_ARGS__)

/**
 * @def se_runtime_raise(...)
 * @brief Повторно выбрасывает текущее исключение с кодом из фрейма `e`.
 *
 * Использует код исключения из текущего фрейма `e`
 * и передаёт его в `se_runtime_rethrow` вместе с дополнительными аргументами.
 *
 * @param ... Дополнительные аргументы для передачи в `se_runtime_fail`.
 * @note Предполагается, что `e` определён в контексте вызова.
 */
#define se_runtime_raise(...) se_runtime_rethrow(e.code, __VA_ARGS__)

#endif // SE_RUNTIME_THROW_H
