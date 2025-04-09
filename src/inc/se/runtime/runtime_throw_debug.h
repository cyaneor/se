/**
 * @file runtime_throw_debug.h
 * @brief Заголовочный файл, содержащий макросы
 *        для обработки исключений в режиме отладки.
 *
 * Этот файл определяет макросы для выбрасывания исключений
 * в `runtime` окружении с использованием `longjmp` для управления потоком выполнения.
 * Макросы предоставляют возможность включения дополнительной информации об ошибках и трассировке,
 * если включены соответствующие опции компиляции.
 *
 * Доступные макросы:
 * - `se_runtime_throw(code, desc, ...)`:
 *    выбрасывает исключение с кодом ошибки и описанием
 *    (при включенных опциях `SE_COMPILE_OPTION_DEBUG` и `SE_LIBRARY_OPTION_ERROR_DESC`).
 * - `se_runtime_throw(code, ...)`:
 *    выбрасывает исключение с кодом ошибки и трассировкой
 *    (при включенной опции `SE_COMPILE_OPTION_DEBUG`,
 *    но отключенной `SE_LIBRARY_OPTION_ERROR_DESC`).
 *
 * @see se_runtime_exception_frame_is_begin
 * @see se_runtime_exception_frame_prev
 * @see se_exception_frame_t
 * @see se_error_t
 * @see se_exception_trace_t
 */

#ifndef SE_RUNTIME_THROW_DEBUG_H
#define SE_RUNTIME_THROW_DEBUG_H

#include "runtime_exception_frame.h"
#include "runtime_return_with_error.h"

#ifdef SE_COMPILE_OPTION_DEBUG
#    ifdef SE_LIBRARY_OPTION_ERROR_DESC
/**
 * @def se_runtime_throw(code, desc, ...)
 * @brief Выбрасывает исключение в runtime с кодом ошибки,
 *        описанием и трассировкой (режим отладки).
 *
 * Этот макрос генерирует исключение в runtime окружении с полной информацией об ошибке,
 * когда включены опции `SE_COMPILE_OPTION_DEBUG` и `SE_LIBRARY_OPTION_ERROR_DESC`.
 * Он передает управление предыдущему фрейму исключений через `longjmp`,
 * устанавливая код ошибки, описание и данные трассировки
 * (временная метка, имя файла, имя функции).
 *
 * Если текущий фрейм исключений является начальным
 * (`se_runtime_exception_frame_is_begin() == true`),
 * макрос устанавливает код ошибки и описание через `se_error_set()` и возвращает значение,
 * указанное в `__VA_ARGS__`, используя механизм `se_runtime_return_with_error`.
 *
 * @param code Код ошибки типа `se_error_t`.
 * @param desc Описание ошибки (строка).
 * @param ... Значения, возвращаемые при прерывании выполнения
 *            (например, значение по умолчанию).
 *
 * @note Поле `trace` структуры `se_exception_frame_t`
 *       заполняется данными `__TIMESTAMP__`, `__FILE__`, и `__FUNCTION__` для отладки.
 *
 * @see se_runtime_exception_frame_is_begin
 * @see se_runtime_exception_frame_prev
 * @see se_exception_frame_t
 * @see se_error_t
 * @see se_exception_trace_t
 * @see se_runtime_return_with_error
 */
#        define se_runtime_throw(code, desc, ...)                                                  \
            do                                                                                     \
            {                                                                                      \
                if (!se_runtime_exception_frame_is_begin())                                        \
                {                                                                                  \
                    se_exception_frame_t *prev = se_runtime_exception_frame_prev();                \
                                                                                                   \
                    prev->err   = (se_error_t){code, desc};                                        \
                    prev->trace = (se_exception_trace_t){__TIMESTAMP__, __FILE__, __FUNCTION__};   \
                                                                                                   \
                    longjmp(prev->env, code);                                                      \
                }                                                                                  \
                se_runtime_return_with_error(code, desc, __VA_ARGS__);                             \
            } while (0)
#    else
/**
 * @def se_runtime_throw(code, ...)
 * @brief Выбрасывает исключение в `runtime`
 *        с кодом ошибки и трассировкой (режим отладки).
 *
 * Этот макрос генерирует исключение в runtime окружении с трассировкой,
 * когда включена опция `SE_COMPILE_OPTION_DEBUG`,
 * но отключена `SE_LIBRARY_OPTION_ERROR_DESC`.
 *
 * Он передает управление предыдущему фрейму исключений через `longjmp`,
 * устанавливая код ошибки и данные трассировки
 * (временная метка, имя файла, имя функции).
 *
 * Если текущий фрейм исключений является начальным
 * (`se_runtime_exception_frame_is_begin() == true`),
 * макрос устанавливает код ошибки через `se_error_set()` и возвращает значение,
 * указанное в `__VA_ARGS__`, используя механизм `se_runtime_return_with_error`.
 *
 * @param code Код ошибки типа `se_error_t`.
 * @param ... Значения, возвращаемые при прерывании выполнения
 *            (например, значение по умолчанию).
 *
 * @note Поле `trace` структуры `se_exception_frame_t` заполняется данными
 *       `__TIMESTAMP__`, `__FILE__`, и `__FUNCTION__` для отладки.
 *       Описание ошибки не поддерживается в этой конфигурации.
 *
 * @see se_runtime_exception_frame_is_begin
 * @see se_runtime_exception_frame_prev
 * @see se_exception_frame_t
 * @see se_error_t
 * @see se_exception_trace_t
 * @see se_runtime_return_with_error
 */
#        define se_runtime_throw(code, ...)                                                        \
            do                                                                                     \
            {                                                                                      \
                if (!se_runtime_exception_frame_is_begin())                                        \
                {                                                                                  \
                    se_exception_frame_t *prev = se_runtime_exception_frame_prev();                \
                                                                                                   \
                    prev->err   = (se_error_t){code};                                              \
                    prev->trace = (se_exception_trace_t){__TIMESTAMP__, __FILE__, __FUNCTION__};   \
                                                                                                   \
                    longjmp(prev->env, code);                                                      \
                }                                                                                  \
                se_runtime_return_with_error(code, __VA_ARGS__);                                   \
            } while (0)
#    endif // SE_LIBRARY_OPTION_ERROR_DESC
#endif     // SE_COMPILE_OPTION_DEBUG

#endif // SE_RUNTIME_THROW_DEBUG_H
