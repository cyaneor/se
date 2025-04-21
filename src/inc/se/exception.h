/**
 * @file exception.h
 * @brief Заголовочный файл, содержащий определение структуры исключения.
 *
 * Данный файл содержит определение структуры `se_exception_t`, 
 * которая представляет собой исключение в системе. 
 * 
 * Исключение содержит информацию об ошибке и,
 * в отладочном режиме, информацию о трассировке стека.
 */

#ifndef SE_EXCEPTION_H
#define SE_EXCEPTION_H

#include "error.h"

#ifdef SE_COMPILE_OPTION_DEBUG
#    include "exception_trace.h"
#endif // SE_COMPILE_OPTION_DEBUG

/**
 * @brief Структура, представляющая исключение.
 *
 * Структура содержит информацию об ошибке, которая произошла,
 * и, в отладочном режиме, дополнительную информацию о трассировке стека вызовов.
 */
typedef struct se_exception
{
    se_error_t err; /**< Содержит код ошибки и связанное с ней сообщение. */

#ifdef SE_COMPILE_OPTION_DEBUG
    se_exception_trace_t trace; /**< Информация о трассировке исключения. */
#endif

} se_exception_t;

#endif // SE_EXCEPTION_H