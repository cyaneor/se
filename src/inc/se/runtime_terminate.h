/**
 * @file runtime_terminate.h
 * @brief Управление аварийным завершением программы в библиотеке.
 *
 * Модуль предоставляет:
 * - Глобальный обработчик `m_runtime_terminate` для аварийного завершения.
 * - Функцию `se_runtime_terminate()` для вызова текущего обработчика.
 * - Функцию `se_runtime_terminate_set_handler()` для переопределения обработчика.
 *
 * Поведение зависит от опции CMake `SE_LIBRARY_OPTION_TERMINATE_INIT_STDLIB`:
 * - Если `ON`, обработчик по умолчанию — `abort()`.
 * - Если `OFF`, обработчик инициализируется как `nullptr` (требует явной настройки).
 *
 * @warning Вызов `se_runtime_terminate()`
 *          без установленного обработчика (`nullptr`) приводит к UB.
 */

#ifndef SE_RUNTIME_TERMINATE_H
#define SE_RUNTIME_TERMINATE_H

#include "runtime_terminate_fn.h"

SE_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Устанавливает пользовательский обработчик аварийного завершения.
 *
 * @details Данная функция позволяет заменить стандартный обработчик завершения программы.
 *          Аналогична работе с `std::set_terminate()` в C++.
 *
 * @param[in] fn Указатель на функцию-обработчик.
 *               Может быть:
 *               - `nullptr`: сброс обработчика (приводит к UB при вызове `terminate`)
 *               - Указатель на валидную функцию: устанавливает новый обработчик.
 *
 * @return Указатель на предыдущий обработчик (может быть `nullptr`).
 *
 * @note Поведение при вызове `terminate` зависит от установленного обработчика:
 *       - Если `nullptr` → неопределённое поведение (UB).
 *       - Иначе → вызов назначенной функции.
 *
 * @see se_runtime_terminate()
 *
 * Пример использования:
 * @code
 * se_runtime_terminate_fn* old_handler = se_runtime_terminate_set(my_handler);
 * // ...
 * se_runtime_terminate_set(old_handler); // восстановление
 * @endcode
 */
SE_ATTRIBUTE(SYMBOL)
se_runtime_terminate_fn *
se_runtime_terminate_set(se_runtime_terminate_fn *fn);

/**
 * @brief Вызывает текущий обработчик аварийного завершения.
 *
 * @details Функция немедленно прерывает выполнение программы
 *          через текущий установленный обработчик.
 *          Аналогична поведению `std::terminate()` в C++.
 *
 * @note Поведение зависит от установленного обработчика:
 *       - Если обработчик не был установлен (или был сброшен в nullptr)
 *         → неопределённое поведение (UB).
 *       - Иначе → вызов назначенной функции-обработчика.
 *
 * @warning Функция не возвращает управление!
 *          Обработчик должен гарантированно завершать программу.
 *
 * @see se_runtime_terminate_set()
 *
 * Пример использования:
 * @code
 * if (critical_error) {
 *     se_runtime_terminate(); // Вызовет текущий обработчик (abort() по умолчанию)
 * }
 * @endcode
 *
 * Пример переопределения обработчика:
 * @code
 * SE_ATTRIBUTE(NORETURN)
 * void custom_terminate() {
 *     log_error("Fatal termination!");
 *     _Exit(127);
 * }
 *
 * int main() {
 *     se_runtime_terminate_set(custom_terminate);
 *     // ...
 *     se_runtime_terminate(); // Теперь вызовется custom_terminate()
 * }
 * @endcode
 */
SE_ATTRIBUTE(SYMBOL)
SE_ATTRIBUTE(NORETURN)
void
se_runtime_terminate(void);

SE_COMPILER(EXTERN_C_END)

#endif // SE_RUNTIME_TERMINATE_H
