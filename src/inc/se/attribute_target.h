/**
 * @file attribute_target.h
 * @brief Заголовочный файл, который содержит макрос `SE_ATTRIBUTE_TARGET(x)`,
 *        оборачивающий поведение макроса `SE_COMPILER_ATTRIBUTE_TARGET(x)`
 *        для задания целевой архитектуры или платформы в зависимости от типа компилятора.
 *
 * Этот файл предоставляет макрос `SE_ATTRIBUTE_TARGET(x)`, который является оберткой
 * для макроса `SE_COMPILER_ATTRIBUTE_TARGET(x)`. Он используется для задания целевой
 * архитектуры или платформы, и его поведение зависит от компилятора.
 *
 * Для компиляторов GCC и Clang макрос определяет атрибут `__attribute__((target(x)))`,
 * для MSVC макрос не определяет атрибут, а для других компиляторов выводит
 * предупреждающее сообщение.
 *
 * Пример использования:
 * @code
 * SE_ATTRIBUTE_TARGET("x86_64");
 * @endcode
 *
 * @see SE_COMPILER_ATTRIBUTE_TARGET
 * @note Макрос `SE_ATTRIBUTE_TARGET` является оберткой для макроса `SE_COMPILER_ATTRIBUTE_TARGET`,
 *       и его поведение зависит от реализации этого макроса.
 */

#ifndef SE_ATTRIBUTE_TARGET_H
#define SE_ATTRIBUTE_TARGET_H

#include "compiler.h"

/**
 * @def SE_ATTRIBUTE_TARGET(x)
 * @brief Обертка для макроса `SE_COMPILER_ATTRIBUTE_TARGET(x)`,
 *        который определяет атрибут компилятора для указания целевой архитектуры или платформы.
 *
 * Этот макрос является оберткой для макроса
 * и используется для задания целевой архитектуры или платформы.
 *
 * Он перенаправляет на оригинальный макрос,
 * который работает в зависимости от типа компилятора.
 *
 * Для GCC и Clang он определяет атрибут, для MSVC не определяет атрибут,
 * а для других компиляторов выводит предупреждающее сообщение.
 *
 * Пример использования:
 * @code
 * SE_ATTRIBUTE_TARGET("x86_64");
 * @endcode
 *
 * @param x Целевая архитектура или платформа,
 *          на которой должен быть выполнен код.
 *
 * @see SE_COMPILER_ATTRIBUTE_TARGET
 * @note Макрос `SE_ATTRIBUTE_TARGET` является оберткой,
 *       и его поведение зависит от реализации макроса `SE_COMPILER_ATTRIBUTE_TARGET`.
 */
#define SE_ATTRIBUTE_TARGET(x) SE_COMPILER_ATTRIBUTE_TARGET(x)

#endif // SE_ATTRIBUTE_TARGET_H
