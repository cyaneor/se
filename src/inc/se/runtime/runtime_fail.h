/**
 * @file runtime_fail.h
 * @brief Заголовочный файл для обработки ошибок выполнения.
 *
 * Этот файл содержит макрос для обработки ошибок выполнения,
 * который позволяет установить код ошибки и вернуть управление
 * с соответствующим сообщением.
 */

#ifndef SE_RUNTIME_FAIL_H
#define SE_RUNTIME_FAIL_H

#include "runtime_return.h"
#include "runtime_error_code.h"

/**
 * @macro se_runtime_fail
 * @brief Устанавливает код ошибки и возвращает управление.
 *
 * Этот макрос устанавливает глобальный код ошибки `se_runtime_error_code`
 * и вызывает функцию `se_runtime_return` с переданными аргументами.
 *
 * @param code Код ошибки, который будет установлен.
 * @param ... Дополнительные аргументы для функции `se_runtime_return`.
 */
#define se_runtime_fail(code, ...)                                                                 \
    se_runtime_error_code = code;                                                                  \
    se_runtime_return(__VA_ARGS__)

#endif // SE_RUNTIME_FAIL_H