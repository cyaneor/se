/**
 * @file compiler_attribute.h
 * @brief Общие определения атрибутов компилятора
 *        для кроссплатформенной разработки.
 *
 * Этот файл объединяет различные определения атрибутов, обеспечивая единый интерфейс
 * для атрибутов компилятора, таких как встроенные функции, символы, неиспользуемые
 * переменные и функции, а также атрибуты для потоковой локальности.
 *
 * Включаемые файлы:
 * - `compiler_attribute_force_inline.h`:
 *    Определения встроенных функций компилятора.
 * - `compiler_attribute_symbol.h`:
 *    Атрибуты для управления экспортом и импортом символов.
 * - `compiler_attribute_unused.h`:
 *    Атрибуты для пометки неиспользуемых переменных и функций.
 * - `compiler_attribute_thread.h`:
 *    Атрибуты для поддержки потоковой локальности.
 *
 * @note Этот заголовок упрощает управление атрибутами компилятора,
 *       делая код более переносимым и единообразным
 *       при использовании различных компиляторов и платформ.
 */

#ifndef SE_COMPILER_ATTRIBUTE_H
#define SE_COMPILER_ATTRIBUTE_H

#include "compiler_attribute_force_inline.h"
#include "compiler_attribute_symbol.h"
#include "compiler_attribute_target.h"
#include "compiler_attribute_thread_local.h"
#include "compiler_attribute_unused.h"

#endif // SE_COMPILER_ATTRIBUTE_H
