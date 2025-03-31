/**
 * @file attribute_noreturn.h
 * @brief Файл-адаптер для макроса,
 *        помечающего функции как не возвращающие управление.
 *
 * Этот файл предоставляет упрощенный интерфейс `SE_ATTRIBUTE_NORETURN`
 * для макроса `SE_COMPILER_ATTRIBUTE_NORETURN`,
 * который помечает функции как не возвращающие управление
 * (например, функции завершения программы или бесконечных циклов).
 *
 * @see SE_COMPILER_ATTRIBUTE_NORETURN
 */

#ifndef SE_ATTRIBUTE_NORETURN_H
#define SE_ATTRIBUTE_NORETURN_H

#include "compiler.h"

/**
 * @def SE_ATTRIBUTE_NORETURN
 * @brief Алиас для SE_COMPILER_ATTRIBUTE_NORETURN,
 *        помечающего функции как не возвращающие управление.
 *
 * @details Этот макрос является упрощенным интерфейсом для `SE_COMPILER_ATTRIBUTE_NORETURN`.
 *          Он наследует все особенности и поведение базового макроса,
 *          включая поддержку разных компиляторов:
 *              - GCC/Clang: `__attribute__((noreturn))`
 *              - MSVC: `__declspec(noreturn)`
 *              - Другие компиляторы: пустая реализация с предупреждением
 *
 * @note Используйте этот макрос для пометки функций,
 *       которые никогда не возвращают управление,
 *       что позволяет компилятору выполнять дополнительные оптимизации.
 *
 * @warning Код после вызова функции
 *          с этим атрибутом считается недостижимым.
 *
 * Пример использования:
 * @code
 * SE_ATTRIBUTE_NORETURN void fatal_error(const char* message) {
 *     printf("Fatal error: %s\n", message);
 *     exit(1);
 * }
 * @endcode
 */
#define SE_ATTRIBUTE_NORETURN SE_COMPILER_ATTRIBUTE_NORETURN

#endif // SE_ATTRIBUTE_NORETURN_H