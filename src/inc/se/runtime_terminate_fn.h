/**
 * @file runtime_terminate_fn.h
 * @brief Заголовочный файл, определяющий тип функции аварийного завершения.
 *
 * Этот файл содержит объявление типа `se_runtime_terminate_fn` — функции,
 * которая вызывается при критических ошибках в рамках библиотеки.
 *
 * @see se_runtime_terminate()
 * @see se_runtime_terminate_set()
 */

#ifndef SE_RUNTIME_TERMINATE_FN_H
#define SE_RUNTIME_TERMINATE_FN_H

#include "attribute.h"

/**
 * @typedef se_runtime_terminate_fn
 * @brief Тип функции для обработки аварийного завершения программы.
 *
 * Функция этого типа должна:
 * 1. **Не возвращать управление** (помечена атрибутом `NORETURN`).
 * 2. **Завершать программу** (например, через `abort()`, `_Exit()` или аналоги).
 *
 * @note - Используется в сочетании с `se_runtime_terminate_set()`
 *         для переопределения поведения при критических ошибках.
 *       - По умолчанию может быть инициализирована как `abort()`
 *         (см. опцию CMake `SE_LIBRARY_OPTION_TERMINATE_INIT_STDLIB`).
 *
 * Пример использования:
 * @code
 * void custom_terminate() {
 *     log_error("Critical failure!");
 *     _Exit(EXIT_FAILURE);
 * }
 *
 * se_runtime_terminate_set(custom_terminate); // Установка кастомного обработчика
 * @endcode
 *
 * @see se_runtime_terminate()
 * @see se_runtime_terminate_set()
 */
typedef void(se_runtime_terminate_fn)(void);

#endif // SE_RUNTIME_TERMINATE_FN_H