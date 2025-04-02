/**
 * @file compiler_attribute_thread_local.h
 * @brief Определение атрибута потоковой локальной памяти для различных компиляторов.
 *
 * Этот файл предоставляет макрос `SE_COMPILER_ATTRIBUTE_THREAD_LOCAL` для указания атрибута
 * потоковой локальной памяти. Атрибут позволяет каждой переменной иметь собственное
 * значение для каждого потока выполнения, что полезно в многопоточных приложениях.
 *
 * Поддерживаемые компиляторы:
 * - GCC и Clang: Используется `__thread`.
 * - MSVC: Используется `__declspec(thread)`.
 *
 * @note Для неподдерживаемых компиляторов макрос будет определен как пустой,
 *       и сгенерируется предупреждение.
 *
 * Макрос:
 * - `SE_COMPILER_ATTRIBUTE_THREAD_LOCAL`:
 *    Определяет потоковую локальную область хранения.
 *
 * @warning На неподдерживаемых компиляторах этот макрос
 *          не будет создавать потоковую локальную память.
 */

#ifndef SE_COMPILER_ATTRIBUTE_THREAD_LOCAL_H
#define SE_COMPILER_ATTRIBUTE_THREAD_LOCAL_H

#include "compiler_type.h"

#if (SE_COMPILER_TYPE == SE_COMPILER_TYPE_GCC) || (SE_COMPILER_TYPE == SE_COMPILER_TYPE_CLANG)
/**
 * @def SE_COMPILER_ATTRIBUTE_THREAD_LOCAL
 * @brief Определяет атрибут потоковой локальной памяти для компиляторов GCC и Clang.
 * @details Макрос указывает, что переменная должна иметь потоковую локальную область хранения,
 *          что означает, что у каждого потока будет своя собственная копия переменной.
 *          Это специфично для компиляторов GCC и Clang.
 */
#    define SE_COMPILER_ATTRIBUTE_THREAD_LOCAL __thread

#elif (SE_COMPILER_TYPE == SE_COMPILER_TYPE_MSVC)
/**
 * @def SE_COMPILER_ATTRIBUTE_THREAD_LOCAL
 * @brief Определяет атрибут потоковой локальной памяти для компилятора MSVC.
 * @details Макрос указывает, что переменная должна иметь потоковую локальную область хранения,
 *          что означает, что у каждого потока будет своя собственная копия переменной.
 *          Это специфично для компилятора MSVC.
 */
#    define SE_COMPILER_ATTRIBUTE_THREAD_LOCAL __declspec(thread)

#else
/**
 * @def SE_COMPILER_ATTRIBUTE_THREAD_LOCAL
 * @brief Определяет пустое сообщение об атрибуте
 *        потоковой локальной памяти для неподдерживаемых компиляторов.
 *
 * @details Если компилятор не распознан или не поддерживается,
 *          этот макрос будет определен как пустой,
 *          и будет выдано сообщение компилятора.
 *
 * @warning Использование этого макроса с неподдерживаемым компилятором
 *          не даст желаемого эффекта и приведет к предупреждению компилятора.
 */
#    define SE_COMPILER_ATTRIBUTE_THREAD_LOCAL

#    pragma message("Warning: Compiler does not support thread-local storage attribute")
#endif

#endif // SE_COMPILER_ATTRIBUTE_THREAD_LOCAL_H
