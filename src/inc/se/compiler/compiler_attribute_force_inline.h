/**
 * @file compiler_attribute_force_inline.h
 * @brief Заголовочный файл для определения атрибута принудительной инлайнизации функций.
 *
 * Этот файл предоставляет макрос `SE_COMPILER_ATTRIBUTE_FORCE_INLINE`, который определяет
 * атрибут принудительной инлайнизации для различных компиляторов (GCC, Clang, MSVC).
 * Макрос используется для повышения производительности в критически важных участках кода,
 * где важно минимизировать накладные расходы на вызов функций.
 *
 * Поддерживаемые компиляторы:
 * - GCC и Clang: атрибут `__attribute__((always_inline)) inline`
 * - MSVC: атрибут `__forceinline`
 *
 * @note На неподдерживаемых компиляторах макрос
 *       определяется как пустой и выводится предупреждение.
 *
 * Макросы:
 * - `SE_COMPILER_ATTRIBUTE_FORCE_INLINE`:
 *    Принудительная инлайнизация функции.
 */

#ifndef SE_COMPILER_ATTRIBUTE_FORCE_INLINE_H
#define SE_COMPILER_ATTRIBUTE_FORCE_INLINE_H

#include "compiler_type.h"

#if (SE_COMPILER_TYPE == SE_COMPILER_TYPE_GCC) || (SE_COMPILER_TYPE == SE_COMPILER_TYPE_CLANG)
/**
 * @def SE_COMPILER_ATTRIBUTE_FORCE_INLINE
 * @brief Принудительно инлайнирует функцию с помощью GCC/Clang.
 * @details Этот макрос гарантирует, что компилятор попытается инлайнировать функцию,
 *          независимо от уровня оптимизации. Он используется для повышения производительности
 *          в критически важных участках кода, где нужно минимизировать накладные расходы
 *          на вызов функций. Применяется для компиляторов GCC и Clang.
 */
#    define SE_COMPILER_ATTRIBUTE_FORCE_INLINE __attribute__((always_inline)) inline

#elif (SE_COMPILER_TYPE == SE_COMPILER_TYPE_MSVC)
/**
 * @def SE_COMPILER_ATTRIBUTE_FORCE_INLINE
 * @brief Принудительно инлайнирует функцию с помощью MSVC.
 * @details Аналогично GCC/Clang, этот макрос указывает компилятору MSVC инлайнировать
 *          функцию любой ценой, если это возможно. Это полезно для критически важных
 *          по производительности участков кода, где важно минимизировать накладные расходы
 *          на вызов функций. Применяется для компилятора MSVC.
 */
#    define SE_COMPILER_ATTRIBUTE_FORCE_INLINE __forceinline
#else
/**
 * @def SE_COMPILER_ATTRIBUTE_FORCE_INLINE
 * @brief Заглушка для неподдерживаемых компиляторов,
 *        где атрибут 'always_inline' не определен.
 *
 * @details Если компилятор не поддерживает атрибут 'always_inline',
 *          этот макрос будет определен как пустой,
 *          и будет выведено сообщение компилятора,
 *          указывающее на отсутствие поддержки.
 *
 * @warning Использование этого макроса с неподдерживаемым компилятором
 *          не даст желаемого эффекта и вызовет предупреждение компилятора.
 */
#    define SE_COMPILER_ATTRIBUTE_FORCE_INLINE

#    pragma message("Warning: Compiler does not support builtin attribute")
#endif

#endif // SE_COMPILER_ATTRIBUTE_FORCE_INLINE_H
