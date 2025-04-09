/**
 * @file runtime_throw_release.h
 * @brief Заголовочный файл, содержащий макросы
 *        для обработки исключений в режиме релиза.
 *
 * Этот файл определяет макросы для выбрасывания исключений в `runtime` окружении
 * с использованием `longjmp` для управления потоком выполнения.
 *
 * Макросы предоставляют возможность обработки ошибок
 * в минимальной конфигурации, когда отключены опции отладки.
 *
 * Доступные макросы:
 * - `se_runtime_throw(code, desc, ...)`:
 *    выбрасывает исключение с кодом ошибки и описанием
 *    (при включенной опции `SE_LIBRARY_OPTION_ERROR_DESC`
 *     и отключенной `SE_COMPILE_OPTION_DEBUG`).
 * - `se_runtime_throw(code, ...)`:
 *    выбрасывает исключение с кодом ошибки
 *    (в минимальной конфигурации, когда отключены обе опции).
 *
 * @see se_runtime_exception_frame_is_begin
 * @see se_runtime_exception_frame_prev
 * @see se_exception_frame_t
 * @see se_error_t
 */

#ifndef SE_RUNTIME_THROW_RELEASE_H
#define SE_RUNTIME_THROW_RELEASE_H

#include "runtime_exception_frame.h"
#include "runtime_return_with_error.h"

#ifndef SE_COMPILE_OPTION_DEBUG
#    ifdef SE_LIBRARY_OPTION_ERROR_DESC
/**
 * @def se_runtime_throw(code, desc, ...)
 * @brief Выбрасывает исключение в runtime с кодом ошибки и описанием (без отладки).
 *
 * Этот макрос генерирует исключение в runtime окружении,
 * когда опция `SE_COMPILE_OPTION_DEBUG` отключена, но включена `SE_LIBRARY_OPTION_ERROR_DESC`.
 * Он передает управление предыдущему фрейму исключений через `longjmp`,
 * устанавливая код ошибки и описание без трассировки.
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
 * @note Трассировка (временная метка, файл, функция) не записывается в этой конфигурации.
 *
 * @see se_runtime_exception_frame_is_begin
 * @see se_runtime_exception_frame_prev
 * @see se_exception_frame_t
 * @see se_error_t
 * @see se_runtime_return_with_error
 */
#        define se_runtime_throw(code, desc, ...)                                                  \
            do                                                                                     \
            {                                                                                      \
                if (!se_runtime_exception_frame_is_begin())                                        \
                {                                                                                  \
                    se_exception_frame_t *prev = se_runtime_exception_frame_prev();                \
                    prev->err                  = (se_error_t){code, desc};                         \
                    longjmp(prev->env, code);                                                      \
                }                                                                                  \
                se_runtime_return_with_error(code, desc, __VA_ARGS__);                             \
            } while (0)
#    else
/**
 * @def se_runtime_throw(code, ...)
 * @brief Выбрасывает исключение в runtime с кодом ошибки (минимальная версия).
 *
 * Этот макрос генерирует исключение в runtime окружении в минимальной конфигурации,
 * когда отключены опции `SE_COMPILE_OPTION_DEBUG` и `SE_LIBRARY_OPTION_ERROR_DESC`.
 * Он передает управление предыдущему фрейму исключений через `longjmp`,
 * устанавливая только код ошибки без описания и трассировки.
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
 * @note Описание ошибки и трассировка не поддерживаются в этой конфигурации.
 *
 * @see se_runtime_exception_frame_is_begin
 * @see se_runtime_exception_frame_prev
 * @see se_exception_frame_t
 * @see se_error_t
 * @see se_runtime_return_with_error
 */
#        define se_runtime_throw(code, ...)                                                        \
            do                                                                                     \
            {                                                                                      \
                if (!se_runtime_exception_frame_is_begin())                                        \
                {                                                                                  \
                    se_exception_frame_t *prev = se_runtime_exception_frame_prev();                \
                    prev->err                  = (se_error_t){code};                               \
                    longjmp(prev->env, code);                                                      \
                }                                                                                  \
                se_runtime_return_with_error(code, __VA_ARGS__);                                   \
            } while (0)
#    endif // SE_LIBRARY_OPTION_ERROR_DESC
#endif     // SE_COMPILE_OPTION_DEBUG

#endif // SE_RUNTIME_THROW_RELEASE_H
