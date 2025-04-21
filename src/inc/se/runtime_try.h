/**
 * @file runtime_try.h
 * @brief API для обработки исключений в стиле `try/catch`.
 *
 * Данный файл предоставляет макросы для организации структурированной
 * обработки исключений в стиле try/catch/return. Реализация построена
 * на базе механизма исключений `runtime_exception_catch_stack`.
 *
 * Основные возможности:
 * - Безопасные блоки try/catch
 * - Гарантированное освобождение ресурсов
 * - Поддержка вложенных обработчиков
 * - Интеграция с системой возврата значений
 *
 * @note Максимальная глубина вложенности определяется `SE_RUNTIME_EXCEPTION_CATCH_STACK_MAX`.
 * @warning Для корректной работы требуется парное использование `try/catch`.
 */

#ifndef SE_RUNTIME_TRY_H
#define SE_RUNTIME_TRY_H

#include "runtime_exception_catch_stack.h"
#include "runtime_return.h"

/**
 * @def se_runtime_try
 * @brief Макрос для организации блока обработки исключений (try-блок)
 *
 * Создает блок кода с обработкой исключений, выполняя:
 * 1. Создание фрейма исключения с автоматическим хранением
 * 2. Установку точки входа для обработки исключений
 * 3. Проверку контекста выполнения (первичный вход или переход при исключении)
 *
 * @param e Имя переменной фрейма исключения (автоматически создаваемой)
 *
 * @note Используется как основа для реализации try/catch блоков
 * @warning Требует соответствующего блока обработки исключений
 * @warning Поддерживает только локальные фреймы исключений (автоматическое хранение)
 *
 * Пример использования:
 * @code
 * se_runtime_try(frame) {
 *     // Код, который может вызвать исключение
 * }
 * @endcode
 *
 * @see se_runtime_catch()
 * @see se_runtime_exception_catch_stack_capture()
 * @see se_exception_catch_t
 */
#define se_runtime_try(e)                                                                          \
    se_exception_catch_t e = {};                                                                   \
    if (se_runtime_exception_catch_stack_capture(&e) == 0)

/**
 * @def se_runtime_try_finalize
 * @brief Макрос для завершения блока обработки исключений
 *        и возврата предыдущего контекста.
 *
 * Выполняет корректное завершение блока обработки исключений:
 * 1. Удаляет текущий фрейм исключения из стека.
 * 2. Возвращает указатель на предыдущий обработчик.
 * 3. Подготавливает контекст для выхода из блока try/catch.
 *
 * @return Указатель на предыдущий фрейм исключения.
 * @return nullptr если стек обработчиков пуст.
 *
 * @note Используется для явного завершения блока обработки исключений.
 * @warning Должен вызываться в конце блока try перед переходом к catch.
 * @warning Необходим для поддержания целостности стека обработчиков.
 *
 * Пример использования:
 * @code
 * se_runtime_try(frame) {
 *     // Код try-блока
 *     se_runtime_try_finalize();
 * }
 * se_runtime_catch(frame) {
 *     // Обработка исключения
 * }
 * @endcode
 *
 * @see se_runtime_try()
 * @see se_runtime_catch()
 * @see se_runtime_exception_catch_stack_prev()
 */
#define se_runtime_try_finalize se_runtime_exception_catch_stack_prev

/**
 * @def se_runtime_try_return
 * @brief Макрос для безопасного возврата из блока обработки исключений.
 *
 * Обеспечивает корректный выход из try-блока с:
 * 1. Восстановлением предыдущего контекста исключений.
 * 2. Освобождением текущего фрейма исключения.
 * 3. Возвратом указанных значений (если есть).
 *
 * @param ... Опциональные возвращаемые значения (аналогично return).
 *
 * @note Должен использоваться вместо обычного return внутри try-блоков.
 * @warning Обязателен для поддержания целостности стека обработчиков.
 * @note Поддерживает все варианты возврата (с значением/без).
 *
 * Пример использования:
 * @code
 * se_runtime_try(frame) {
 *     if (condition) {
 *         se_runtime_try_return(42); // Безопасный возврат значения
 *     }
 *     se_runtime_try_return(); // Безопасный возврат без значения
 * }
 * @endcode
 *
 * @see se_runtime_try()
 * @see se_runtime_try_finalize()
 * @see se_runtime_return()
 */
#define se_runtime_try_return(...)                                                                 \
    se_runtime_try_finalize();                                                                     \
    se_runtime_return(__VA_ARGS__)

#endif // SE_RUNTIME_TRY_H