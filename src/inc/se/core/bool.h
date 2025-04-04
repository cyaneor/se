/**
 * @file bool.h
 * @brief Определение типа `bool` для представления булевых значений в языке C.
 *
 * Этот файл предоставляет определение типа `bool` как перечисления для представления
 * булевых значений `true` и `false` в коде на языке C. Файл реализует совместимость
 * с проектами, использующими стандарты C ниже C23, в которых встроенный булевый
 * тип отсутствует.
 *
 * Особенности:
 * - Тип `bool` доступен только в C, если стандарт C ниже C23.
 * - Поддерживает кросс-компиляцию, предотвращая дублирование типов в C++
 *   или при использовании стандартного заголовка `<stdbool.h>`.
 *
 * @note Полезен для обеспечения логических выражений
 *       и совместимости кода в стандартах C до C23.
 */

#ifndef SE_BOOL_H
#define SE_BOOL_H

#include <se/compiler/compiler.h>

#if !defined(__cplusplus) && !defined(__STDBOOL_H)
#    if (SE_COMPILER_STD_VERSION_C < SE_COMPILER_STD_VERSION_C23)

/**
 * @enum bool
 * @brief Перечисление для представления булевых значений.
 *
 * Перечисление `bool` используется для представления булевых значений
 * `true` и `false` в коде на языке C. Оно позволяет создать простой и
 * понятный способ работы с логическими выражениями, учитывая отсутствие
 * встроенного булевого типа в стандартном языке C.
 *
 * Значения:
 * - `false`: Представляет булевое значение "ложь".
 * - `true`: Представляет булевое значение "истина".
 */
typedef enum
{
    false, /**< Представляет булевое значение "ложь". */
    true   /**< Представляет булевое значение "истина". */
} bool;

#    endif // SE_STD_C_VERSION < SE_STD_VERSION_C23
#endif     // !defined(__cplusplus) && !defined(__STDBOOL_H)

#endif // SE_BOOL_H
