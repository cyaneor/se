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
 * В противном случае переходит к предыдущему фрейму
 * и выполняет `longjmp` с указанным кодом исключения.
 *
 * В режиме отладки (`SE_COMPILE_OPTION_DEBUG`) дополнительно записывает информацию
 * о трассировке (время, файл, функция) в поле `trace` предыдущего фрейма.
 *
 * @param code Код исключения.
 * @param ... Дополнительные аргументы для передачи в `se_runtime_fail` (в случае ошибки).
 */
#ifdef SE_COMPILE_OPTION_DEBUG
#    define se_runtime_throw(code, ...)                                                            \
        do                                                                                         \
        {                                                                                          \
            if (se_runtime_except_frame_is_begin())                                                \
            {                                                                                      \
                se_runtime_fail(code, __VA_ARGS__);                                                \
            }                                                                                      \
                                                                                                   \
            se_except_frame_t *prev = se_runtime_except_frame_prev();                              \
            prev->trace = (se_except_trace_t){__TIMESTAMP__, __FILE_NAME__, __FUNCTION__};         \
            longjmp(prev->env, code);                                                              \
        } while (0)
#else
#    define se_runtime_throw(code, ...)                                                            \
        do                                                                                         \
        {                                                                                          \
            if (se_runtime_except_frame_is_begin())                                                \
            {                                                                                      \
                se_runtime_fail(code, __VA_ARGS__);                                                \
            }                                                                                      \
            se_runtime_except_frame_load(code);                                                    \
        } while (0)
#endif // SE_COMPILE_OPTION_DEBUG

#endif // SE_RUNTIME_THROW_H
