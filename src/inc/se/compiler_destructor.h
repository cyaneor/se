/**
 * @file compiler_destructor.h
 * @brief Заголовочный файл для определения атрибута деструктора.
 *
 * Этот файл содержит макрос `se_compiler_destructor`,
 * который позволяет определять функции деструкторов
 * для различных компиляторов, таких как GCC, Clang и MSVC.
 *
 * Деструкторы — это функции, которые автоматически вызываются после выхода из функции `main()`,
 * что позволяет выполнять завершающие операции, такие как освобождение ресурсов.
 *
 *
 * @details В зависимости от типа компилятора,
 *          макрос `se_compiler_destructor` будет определен различным образом:
 *          - Для компиляторов GCC и Clang используется атрибут `__attribute__((destructor))`,
 *            который указывает, что функция должна быть вызвана при завершении программы.
 *          - Для компилятора MSVC используется специальная секция `.CRT$XTU`,
 *            в которую помещаются функции деструкторов для последующего вызова.
 *          - Если компилятор не распознан или не поддерживается,
 *            макрос будет определен как пустой и выведет предупреждение на этапе компиляции.
 *
 * Основные функции:
 * - `se_compiler_destructor(f)`
 *    - определяет функцию деструктора для соответствующего компилятора.
 *
 * @warning Если компилятор не поддерживает деструкторы,
 *          будет выдано предупреждение на этапе компиляции.
 */

#ifndef SE_COMPILER_DESTRUCTOR_H
#define SE_COMPILER_DESTRUCTOR_H

#include "compiler_type.h"

#if (SE_COMPILER_TYPE == SE_COMPILER_TYPE_GCC) || (SE_COMPILER_TYPE == SE_COMPILER_TYPE_CLANG)
/**
 * @def se_compiler_destructor(f)
 * @brief Определяет атрибут деструктора для компиляторов GCC и Clang.
 * @details Атрибут определяет функцию деструктора,
 *          которая будет выполнена после выхода из функции main().
 *          Это характерно для компиляторов GCC и Clang.
 */
#    define se_compiler_destructor(f) __attribute__((destructor)) static void f(void)

#elif (SE_COMPILER_TYPE == SE_COMPILER_TYPE_MSVC)
/**
 * @def se_compiler_destructor(f)
 * @brief Определяет атрибут деструктора для компилятора MSVC.
 * @details Атрибут определяет функцию деструктора,
 *          которая будет выполнена после выхода из функции main().
 *          Это специфично для компилятора MSVC.
 */
#    define se_compiler_destructor(f)                                                              \
        __pragma(section(".CRT$XTU", read)) static void __cdecl f(void);                           \
        __declspec(allocate(".CRT$XTU")) void(__cdecl * f##_)(void) = f;                           \
        __pragma(comment(linker, "/include:" #f "_"));                                             \
        static void __cdecl f(void)
#else
/**
 * @def se_compiler_destructor
 * @brief Определяет пустой деструктор
 *        для неподдерживаемых компиляторов.
 *
 * @details Если компилятор не распознан или не поддерживается,
 *          этот макрос будет определен как пустой и будет выдано сообщение компилятора.
 */
#    define se_compiler_destructor

#    pragma message("Warning: Compiler does not support destructor function")
#endif

#endif // SE_COMPILER_DESTRUCTOR_H
