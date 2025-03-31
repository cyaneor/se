/**
 * @file attribute_unused.h
 * @brief Заголовочный файл для алиаса атрибута неиспользуемых элементов.
 *
 * Файл предоставляет удобный сокращенный макрос `SE_ATTRIBUTE_UNUSED`
 * для пометки неиспользуемых переменных, функций и параметров с целью
 * подавления предупреждений компилятора.
 *
 * Основные возможности:
 * - Упрощенный синтаксис по сравнению с базовым макросом.
 * - Кросс-компиляторная поддержка (GCC, Clang, MSVC).
 * - Подавление предупреждений о неиспользуемых элементах.
 * - Поддержка условно компилируемого кода.
 *
 * @note Для работы требует подключения <se/compiler/compiler.h>
 * @warning В случае неподдерживаемого компилятора атрибут может не работать.
 *
 * Пример использования:
 * @code
 * // Для переменных
 * SE_ATTRIBUTE_UNUSED int debug_counter;
 *
 * // Для функций
 * SE_ATTRIBUTE_UNUSED void deprecated_function() {}
 *
 * // Для параметров функций
 * void callback(int param1, SE_ATTRIBUTE_UNUSED int param2) {}
 * @endcode
 *
 * @see SE_COMPILER_ATTRIBUTE_UNUSED
 */

#ifndef SE_ATTRIBUTE_UNUSED_H
#define SE_ATTRIBUTE_UNUSED_H

#include "compiler.h"

/**
 * @def SE_ATTRIBUTE_UNUSED
 * @brief Удобный алиас для пометки неиспользуемых элементов кода
 * @details Этот макрос является сокращенным вариантом SE_COMPILER_ATTRIBUTE_UNUSED,
 *          предназначенным для подавления предупреждений компилятора о неиспользуемых
 *          переменных, функциях или параметрах.
 *
 *          Поведение зависит от компилятора:
 *          - В GCC/Clang использует __attribute__((unused))
 *          - В MSVC применяет (void) приведение
 *          - Для других компиляторов может быть пустым
 *
 * @note Особенно полезен при условной компиляции,
 *       когда некоторые элементы могут не использоваться в определенных конфигурациях.
 *
 * Пример использования:
 * @code
 * SE_ATTRIBUTE_UNUSED int unused_var;  // Не будет вызывать предупреждение
 * SE_ATTRIBUTE_UNUSED void unused_function() {}  // Аналогично для функций
 * @endcode
 *
 * @see SE_COMPILER_ATTRIBUTE_UNUSED
 */
#define SE_ATTRIBUTE_UNUSED SE_COMPILER_ATTRIBUTE_UNUSED

#endif // SE_ATTRIBUTE_UNUSED_H
