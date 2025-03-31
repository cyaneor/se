/**
 * @file compiler_attribute_noreturn.h
 * @brief Определение макроса для пометки функций, которые не возвращают управление.
 *
 * Этот файл предоставляет макрос `SE_COMPILER_ATTRIBUTE_NORETURN`,
 * который используется для указания компилятору, что функция не возвращает управление
 * (например, функции, завершающие программу или входящие в бесконечный цикл).
 *
 * Макрос поддерживает разные реализации в зависимости от компилятора:
 * - GCC и Clang: атрибут `__attribute__((noreturn))`
 * - MSVC: спецификатор `__declspec(noreturn)`
 *
 * Если тип компилятора не определен, используется пустой атрибут,
 * и при компиляции выводится сообщение о возможном отсутствии поддержки.
 *
 * @note Использование этого атрибута позволяет компилятору оптимизировать код
 *       и генерировать более точные предупреждения.
 */

#ifndef SE_COMPILER_ATTRIBUTE_NORETURN_H
#define SE_COMPILER_ATTRIBUTE_NORETURN_H

#include "compiler_type.h"

#if (SE_COMPILER_TYPE == SE_COMPILER_TYPE_GCC) || (SE_COMPILER_TYPE == SE_COMPILER_TYPE_CLANG)
/**
 * @def SE_COMPILER_ATTRIBUTE_NORETURN
 * @brief Указывает компилятору GCC/Clang, что функция не возвращает управление.
 *
 * @details Этот атрибут сообщает компилятору, что функция не завершается нормально
 *          (например, вызывает abort(), exit() или входит в бесконечный цикл).
 *          Это позволяет компилятору выполнять дополнительные оптимизации
 *          и избегать предупреждений о недостижимом коде.
 *
 * @warning Любой код после вызова функции с этим атрибутом считается недостижимым.
 */
#    define SE_COMPILER_ATTRIBUTE_NORETURN __attribute__((noreturn))

#elif (SE_COMPILER_TYPE == SE_COMPILER_TYPE_MSVC)
/**
 * @def SE_COMPILER_ATTRIBUTE_NORETURN
 * @brief Указывает компилятору MSVC, что функция не возвращает управление.
 *
 * @details Этот спецификатор сообщает компилятору MSVC, что функция не завершается
 *          нормально. Это позволяет компилятору оптимизировать код и избегать
 *          предупреждений о недостижимом коде.
 *
 * @note В отличие от GCC/Clang,
 *       в MSVC этот спецификатор применяется к объявлению функции.
 */
#    define SE_COMPILER_ATTRIBUTE_NORETURN __declspec(noreturn)

#else
/**
 * @def SE_COMPILER_ATTRIBUTE_NORETURN
 * @brief Заглушка для компиляторов, не поддерживающих атрибут 'noreturn'.
 *
 * @details Если компилятор не поддерживает атрибут 'noreturn',
 *          этот макрос будет определен как пустой, и будет выведено
 *          сообщение компилятора, указывающее на отсутствие поддержки.
 *
 * @warning Использование этого макроса с неподдерживаемым компилятором
 *          не даст желаемого эффекта оптимизации и может привести к
 *          отсутствию предупреждений о недостижимом коде.
 */
#    define SE_COMPILER_ATTRIBUTE_NORETURN
#    pragma message("Warning: Compiler does not support no return attribute")
#endif

#endif // SE_COMPILER_ATTRIBUTE_NORETURN_H