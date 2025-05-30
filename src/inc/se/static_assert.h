/**
 * @file static_assert.h
 * @brief Определение макроса для выполнения компилируемых проверок условий.
 *
 * Этот файл предоставляет макрос `se_static_assert`,
 * позволяющий выполнять статические проверки условий на этапе компиляции.
 *
 * Макрос используется для генерации ошибок компиляции,
 * если заданное логическое выражение `expr` оказывается ложным,
 * что позволяет выявлять потенциальные ошибки на ранних этапах разработки.
 *
 * @note Файл полезен при создании кода, требующего строгих проверок предположений
 *       о размерах данных, совместимости типов или других компилируемых условий.
 */

#ifndef SE_STATIC_ASSERT_H
#define SE_STATIC_ASSERT_H

#ifdef __cplusplus
/**
 * @def se_static_assert(expr, msg)
 * @brief Выполняет статическую проверку условия на этапе компиляции.
 *
 * Этот макрос предоставляет механизм
 * для проверки логического выражения `expr` во время компиляции.
 *
 * Если выражение `expr` оказывается ложным,
 * компилятор генерирует ошибку с указанным сообщением `msg`.
 *
 * Макрос реализован с использованием `static_assert` в C++ и `_Static_assert` в C,
 * что обеспечивает совместимость с обоими языками.
 *
 * @param expr Логическое выражение, которое должно быть истинным для успешной компиляции.
 * @param msg Строка сообщения, отображаемая компилятором в случае ошибки, если `expr` ложно.
 *
 * @note Использование этого макроса помогает выявлять ошибки в предположениях о коде,
 *       таких как размеры типов данных или совместимость, на этапе компиляции,
 *       предотвращая потенциальные проблемы во время выполнения.
 *
 * Пример использования:
 * @code
 * #define MY_TYPE_SIZE 4
 * se_static_assert(sizeof(int) == MY_TYPE_SIZE, "Размер int должен быть равен MY_TYPE_SIZE");
 * @endcode
 */
#    define se_static_assert(expr, msg) static_assert(expr, msg)
#else

/**
 * @def se_static_assert
 * @brief Компилируемая проверка условия во время компиляции.
 *
 * Этот макрос реализует статическое утверждение,
 * проверяя условие `expr` во время компиляции.
 *
 * Если выражение `expr` ложно,
 * компилятор выдаёт сообщение об ошибке,
 * используя текст `msg` для описания причины.
 *
 * @param expr Логическое выражение, которое должно быть истинным.
 * @param msg Сообщение об ошибке, выводимое компилятором, если `expr` ложно.
 *
 * @note Макрос полезен для выявления ошибок на этапе компиляции,
 *       предотвращая выполнение кода с потенциально неверными допущениями.
 *
 * Пример использования:
 * @code
 * se_static_assert(sizeof(int) == 4, "Размер типа int должен быть 4 байта");
 * @endcode
 */
#    define se_static_assert(expr, msg) _Static_assert(expr, msg)
#endif // __cplusplus

#endif // SE_STATIC_ASSERT_H
