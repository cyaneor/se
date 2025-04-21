/**
 * @file runtime_throw.h
 * @brief Упрощенный интерфейс для генерации исключений времени выполнения
 *
 * Данный заголовочный файл предоставляет макрос `se_runtime_throw` для удобного
 * выброса исключений с возможностью передачи произвольных параметров ошибки.
 *
 * Основные особенности:
 * - Синтаксис с переменным числом аргументов для инициализации структуры ошибки
 * - Автоматическое добавление отладочной информации в DEBUG-сборках
 * - Интеграция с системой обработки исключений через `runtime_exception_catch_stack`
 *
 * @warning Необходимо наличие хотя бы одного обработчика исключений,
 *          иначе приводит к аварийному завершению программы.
 *
 * @see se_runtime_throw
 * @see runtime_error_code.h
 * @see runtime_exception_catch_stack.h
 */

#ifndef SE_RUNTIME_THROW_H
#define SE_RUNTIME_THROW_H

#include "runtime_error_code.h"
#include "runtime_exception_catch_stack.h"

/**
 * @def se_runtime_throw
 * @brief Макрос для генерации и выбрасывания исключения времени выполнения.
 *
 * Упрощает вызов механизма обработки исключений,
 * позволяя указать параметры ошибки в виде списка инициализации структуры `se_error_t`.
 * В DEBUG-сборках автоматически добавляет отладочную информацию (временную метку, файл, функцию).
 *
 * @param ... Аргументы для инициализации `se_error_t` (код ошибки и описание)
 *
 * @warning При отсутствии активных обработчиков исключений
 *          приводит к аварийному завершению программы.
 *
 * Пример использования:
 * @code
 * // Простое исключение с кодом ошибки
 * se_runtime_throw(SE_ERROR_INVALID_ARGUMENT);
 *
 * // Исключение с дополнительными параметрами
 * se_runtime_throw(SE_ERROR_FILE_IO, "Failed to open file");
 * @endcode
 *
 * @see se_runtime_exception_catch_stack_throw
 */
#ifdef SE_COMPILE_OPTION_DEBUG
#    define se_runtime_throw(...)                                                                  \
        se_runtime_exception_catch_stack_throw(&(se_exception_t){                                  \
            .err = {__VA_ARGS__}, .trace = {__TIMESTAMP__, __FILE__, __FUNCTION__}})
#else
#    define se_runtime_throw(...)                                                                  \
        se_runtime_exception_catch_stack_throw(&(se_exception_t){.err = {__VA_ARGS__}})
#endif // SE_COMPILE_OPTION_DEBUG

/**
 * @def se_runtime_rethrow
 * @brief Макрос для повторного возбуждения текущего исключения.
 *
 * Перенаправляет вызов на функцию `se_runtime_exception_catch_stack_rethrow()`.
 * Используется для повторного возбуждения текущего обрабатываемого исключения.
 *
 * @note Сохраняет оригинальное исключение и его контекст
 * @note Потокобезопасен, так как работает с thread-local хранилищем
 *
 * @see se_runtime_exception_catch_stack_rethrow()
 * @see se_runtime_exception_catch_stack_get_current()
 *
 * @par Пример использования:
 * @code
 * try {
 *     // код, который может вызвать исключение
 * } catch {
 *     // обработка исключения
 *     se_runtime_rethrow(); // повторное возбуждение того же исключения
 * }
 * @endcode
 */
#define se_runtime_rethrow() se_runtime_exception_catch_stack_rethrow()

#endif // SE_RUNTIME_THROW_H