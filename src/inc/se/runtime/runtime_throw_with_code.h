/**
 * @file runtime_throw_with_code.h
 * @brief Определение макроса для упрощенного выбрасывания исключений в runtime.
 *
 * Этот файл содержит макрос `se_runtime_throw_with_code`,
 * который упрощает процесс выбрасывания исключений
 * с указанием только кода ошибки.
 *
 * Макрос является оберткой над функцией `se_runtime_throw`,
 * предоставляя более удобный интерфейс для случаев,
 * когда дополнительное описание ошибки не требуется.
 *
 * В зависимости от конфигурации библиотеки (опция `SE_LIBRARY_OPTION_ERROR_DESC`),
 * макрос может либо передавать `nullptr` в качестве описания ошибки,
 * либо использовать только код ошибки и дополнительные аргументы.
 *
 * @note Использование данного макроса позволяет избежать необходимости
 *       предоставления описания ошибки, что делает код более чистым и понятным.
 *
 * @warning Убедитесь, что `se_runtime_throw` корректно реализован и
 *          фреймы исключений инициализированы перед использованием этого макроса.
 *
 * @see se_runtime_throw
 * @see se_runtime_except_frame_is_begin
 * @see se_except_frame_t
 * @see se_error_t
 */

#ifndef SE_RUNTIME_THROW_WITH_CODE_H
#define SE_RUNTIME_THROW_WITH_CODE_H

#include "runtime_throw.h"
#include <se/core/nullptr.h>
#include <se/runtime/runtime_throw_with_code.h>

/**
 * @def se_runtime_throw_with_code(code, ...)
 * @brief Выбрасывает исключение в runtime только с кодом ошибки, упрощая вызов `se_runtime_throw`.
 *
 * Этот макрос является оберткой над `se_runtime_throw`, предоставляя упрощенный интерфейс
 * для случаев, когда требуется указать только код ошибки без дополнительного описания.
 * Поведение макроса зависит от опции `SE_LIBRARY_OPTION_ERROR_DESC`:
 *
 * - Если опция включена, макрос передает `nullptr` в качестве описания ошибки (`desc`).
 * - Если опция отключена, макрос напрямую передает только код ошибки и остальные аргументы.
 *
 * Как и `se_runtime_throw`, макрос передает управление предыдущему фрейму
 * исключений через `longjmp`, если текущий фрейм не является начальным
 * (`se_runtime_except_frame_is_begin() == false`).
 *
 * @param code Код ошибки типа `se_error_t`.
 * @param ... Значения, возвращаемые при прерывании выполнения
 *            (например, значение по умолчанию).
 *
 * @note Этот макрос удобен, когда описание ошибки не требуется или не поддерживается,
 *       обеспечивая единообразный вызов независимо от конфигурации.
 *
 * @warning Зависит от правильной реализации `se_runtime_throw`
 *          и инициализации фреймов исключений.
 *
 * @see se_runtime_throw
 * @see se_runtime_except_frame_is_begin
 * @see se_except_frame_t
 * @see se_error_t
 */
#if SE_LIBRARY_OPTION_ERROR_DESC
#    define se_runtime_throw_with_code(code, ...) se_runtime_throw(code, nullptr, __VA_ARGS__)
#else
#    define se_runtime_throw_with_code(code, ...) se_runtime_throw(code, __VA_ARGS__)
#endif // SE_LIBRARY_OPTION_ERROR_DESC

#endif // SE_RUNTIME_THROW_WITH_CODE_H
