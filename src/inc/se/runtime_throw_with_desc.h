/**
 * @file runtime_throw_with_desc.h
 * @brief Интерфейс для выброса исключений с описанием ошибки.
 *
 * Заголовочный файл предоставляет специализированный макрос @ref se_runtime_throw_with_desc
 * для удобного выброса исключений с фиксированным кодом ошибки и пользовательским описанием.
 *
 * Основные характеристики:
 * - Автоматически использует код SE_RUNTIME_ERROR_INTERRUPT
 * - Позволяет передавать произвольное текстовое описание ошибки
 * - Сохраняет все возможности базового механизма исключений
 * - В DEBUG-сборках добавляет информацию о месте вызова
 */

#ifndef SE_RUNTIME_THROW_DESC_H
#define SE_RUNTIME_THROW_DESC_H

#include "runtime_error_code.h"
#include "runtime_throw.h"

/**
 * @def se_runtime_throw_with_desc
 * @brief Макрос для выброса исключения
 *        с фиксированным кодом ошибки и описанием.
 *
 * Предоставляет удобный интерфейс для генерации исключений с предопределенным кодом
 * SE_RUNTIME_ERROR_INTERRUPT и пользовательским описанием ошибки.
 *
 * @param desc Текстовое описание ошибки (строковый литерал или указатель на строку).
 * @note Всегда использует код ошибки `SE_RUNTIME_ERROR_INTERRUPT`.
 * @note В DEBUG-сборках добавляет информацию о файле и строке.
 *
 * Пример использования:
 * @code
 * // Прерывание операции с пояснением
 * if (operation_aborted) {
 *     se_runtime_throw_with_desc("Operation was manually aborted by user");
 * }
 * @endcode
 *
 * @see se_runtime_throw
 * @see se_runtime_throw_with_code
 * @see SE_RUNTIME_ERROR_INTERRUPT
 */
#define se_runtime_throw_with_desc(desc) se_runtime_throw(SE_RUNTIME_ERROR_INTERRUPT, desc)

#endif // SE_RUNTIME_THROW_DESC_H