/**
 * @file compiler_attribute.h
 * @brief Общие определения атрибутов компилятора
 *        для кроссплатформенной разработки.
 *
 * Этот файл объединяет различные определения атрибутов, обеспечивая единый интерфейс
 * для атрибутов компилятора, таких как встроенные функции, символы, неиспользуемые
 * переменные и функции, атрибуты для потоковой локальности, целевых атрибутов и
 * функций, которые не возвращают управление.
 *
 * Включаемые файлы:
 * - `compiler_attribute_force_inline.h`:
 *    Определения встроенных функций компилятора.
 * - `compiler_attribute_symbol.h`:
 *    Атрибуты для управления экспортом и импортом символов.
 * - `compiler_attribute_unused.h`:
 *    Атрибуты для пометки неиспользуемых переменных и функций.
 * - `compiler_attribute_thread_local.h`:
 *    Атрибуты для поддержки потоковой локальности.
 * - `compiler_attribute_target.h`:
 *    Атрибуты для специфичных оптимизаций под определенные архитектуры.
 * - `compiler_attribute_no_return.h`:
 *    Атрибуты для пометки функций, которые не возвращают управление.
 *
 * @note Этот заголовок упрощает управление атрибутами компилятора,
 *       делая код более переносимым и единообразным
 *       при использовании различных компиляторов и платформ.
 * @note Все атрибуты собраны в одном месте для удобства использования
 *       и обеспечения согласованности в проекте.
 */

#ifndef SE_COMPILER_ATTRIBUTE_H
#define SE_COMPILER_ATTRIBUTE_H

#include "compiler_attribute_force_inline.h"
#include "compiler_attribute_noreturn.h"
#include "compiler_attribute_symbol.h"
#include "compiler_attribute_target.h"
#include "compiler_attribute_thread_local.h"
#include "compiler_attribute_unused.h"

#endif // SE_COMPILER_ATTRIBUTE_H