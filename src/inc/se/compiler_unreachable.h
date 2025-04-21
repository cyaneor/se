/**
 * @file compiler_unreachable.h
 * @brief Определение макроса `se_compiler_unreachable` для различных компиляторов.
 *
 * Этот файл содержит определение макроса `se_compiler_unreachable`,
 * который позволяет указать компилятору, что определённая точка кода недостижима.
 *
 * Макрос адаптирован для работы с компиляторами GCC, Clang и MSVC,
 * а также предоставляет пустое определение для неподдерживаемых компиляторов.
 *
 * @details
 * - Для компиляторов GCC и Clang используется встроенная функция `__builtin_unreachable()`,
 *   которая сообщает компилятору о недостижимости кода для оптимизации.
 * - Для компилятора MSVC используется директива `__assume(0)`,
 *   выполняющая аналогичную функцию.
 * - Если компилятор не поддерживается, макрос будет определён как пустой,
 *   и будет выдано предупреждение компилятора.
 *
 * @warning Использование макроса `se_compiler_unreachable` с неподдерживаемым компилятором
 *          не даст желаемого эффекта оптимизации и может привести к предупреждениям компилятора.
 *
 * @pre Данный файл должен быть включен в проект
 *      для использования макроса `se_compiler_unreachable`.
 */

#ifndef SE_COMPILER_UNREACHABLE_H
#define SE_COMPILER_UNREACHABLE_H

#include "compiler_type.h"

#if (SE_COMPILER_TYPE == SE_COMPILER_TYPE_GCC) || (SE_COMPILER_TYPE == SE_COMPILER_TYPE_CLANG)
/**
 * @def se_compiler_unreachable
 * @brief Определяет встроенную функцию недостижимого кода для GCC/Clang.
 * @details Использует `__builtin_unreachable()` для указания компилятору,
 *          что текущая точка кода недостижима, что позволяет улучшить оптимизацию.
 */
#    define se_compiler_unreachable() __builtin_unreachable()

#elif (SE_COMPILER_TYPE == SE_COMPILER_TYPE_MSVC)
/**
 * @def se_compiler_unreachable
 * @brief Определяет директиву недостижимого кода для MSVC.
 * @details Использует `__assume(0)` для указания компилятору,
 *          что текущая точка кода недостижима, что позволяет улучшить оптимизацию.
 */
#    define se_compiler_unreachable() __assume(0)

#else
/**
 * @def se_compiler_unreachable
 * @brief Пустое определение для неподдерживаемых компиляторов.
 * @details Если компилятор не распознан или не поддерживается,
 *          этот макрос будет определён как пустой и будет выдано сообщение компилятора.
 *
 * @warning Использование этого макроса с неподдерживаемым компилятором
 *          не даст эффекта оптимизации и приведёт к предупреждению компилятора.
 */
#    define se_compiler_unreachable()

#    pragma message("Warning: Compiler does not support unreachable hint functionality")
#endif

#endif // SE_COMPILER_UNREACHABLE_H