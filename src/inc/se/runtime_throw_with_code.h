/**
 * @file runtime_throw_with_code.h
 * @brief Упрощенный интерфейс для выброса исключений по коду ошибки.
 *
 * Заголовочный файл предоставляет специализированный
 * макрос @ref se_runtime_throw_with_code для случаев,
 * когда необходимо выбросить исключение,
 * указав только код ошибки без дополнительных параметров.
 *
 * Основные характеристики:
 * - Является тонкой оберткой над @ref se_runtime_throw
 * - Оптимизирует частый случай выброса исключений
 * - Сохраняет все особенности базового механизма исключений
 * - В DEBUG-сборках автоматически добавляет контекст ошибки
 */

#ifndef SE_RUNTIME_THROW_WITH_CODE_H
#define SE_RUNTIME_THROW_WITH_CODE_H

#include "runtime_throw.h"

/**
 * @def se_runtime_throw_with_code
 * @brief Упрощенный макрос для выброса исключения с указанием только кода ошибки.
 *
 * Предоставляет сокращенный синтаксис для вызова `se_runtime_throw` с минимальным набором
 * параметров, когда требуется передать только код ошибки без дополнительных данных.
 *
 * @param code Код ошибки типа se_error_code_t (например, `SE_ERROR_INVALID_ARGUMENT`).
 * @note Фактически является алиасом для вызова `se_runtime_throw(code)`.
 *
 * Пример использования:
 * @code
 * // Выброс исключения при недопустимом аргументе
 * if (arg == nullptr) {
 *     se_runtime_throw_with_code(SE_ERROR_NULL_ARGUMENT);
 * }
 * @endcode
 *
 * @see se_runtime_throw
 * @see se_runtime_exception_catch_stack_throw_error
 */
#define se_runtime_throw_with_code(code) se_runtime_throw(code)

#endif // SE_RUNTIME_THROW_WITH_CODE_H