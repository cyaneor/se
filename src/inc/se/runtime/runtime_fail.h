/**
 * @file runtime_fail.h
 * @brief Заголовочный файл,
 *        содержащий макрос для обработки ошибок времени выполнения.
 *
 * Этот файл определяет макрос `se_runtime_fail`, который используется для установки
 * кода ошибки времени выполнения и немедленного завершения выполнения функции.
 * Он зависит от типов и функциональности, определенных в `runtime_return.h` и
 * `runtime_error_code.h`.
 *
 * @see runtime_return.h
 * @see runtime_error_code.h
 */

#ifndef SE_RUNTIME_FAIL_H
#define SE_RUNTIME_FAIL_H

#include "runtime_return.h"
#include "runtime_error_code.h"

/**
 * @def se_runtime_fail(code, ...)
 * @brief Устанавливает код ошибки времени выполнения
 *        и немедленно завершает выполнение функции.
 *
 * Этот макрос комбинирует установку кода ошибки времени выполнения в переменную
 * `se_runtime_error_code` и последующий немедленный выход из функции с возвратом
 * заданного значения (если оно указано).
 *
 * Используется для обработки ошибок,
 * когда необходимо зафиксировать код ошибки и прервать выполнение.
 *
 * @param code Код ошибки типа `se_error_code_t`,
 *             который будет сохранен в `se_runtime_error_code`.
 * @param ... (опционально) Значение, которое будет возвращено из функции.
 *            Если не указано, функция просто завершится без возврата значения.
 *
 * @return Возвращает значение,
 *         переданное в параметре `...`, если оно указано.
 *
 * @see se_runtime_error_code
 * @see se_runtime_return
 *
 * Пример использования:
 * @code
 * void example_function(int value) {
 *     if (value < 0) {
 *         // Устанавливает код ошибки и возвращает -1
 *         se_runtime_fail(SE_ERROR_INVALID_INPUT, -1);
 *     }
 *     // Дальнейшая логика
 * }
 * @endcode
 */
#define se_runtime_fail(code, ...)                                                                 \
    se_runtime_error_code = code;                                                                  \
    se_runtime_return(__VA_ARGS__)

#endif // SE_RUNTIME_FAIL_H