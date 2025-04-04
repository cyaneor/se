/**
 * @file offset.h
 * @brief Заголовочный файл для определения типов смещений в памяти.
 *
 * Этот файл содержит определения типов
 * для знаковых и беззнаковых смещений в памяти:
 *
 * - @c se_soffset_t для знаковых смещений.
 * - @c se_uoffset_t для беззнаковых смещений.
 *
 * Эти типы используются при работе с адресами и индексами в памяти,
 * например, при манипуляциях с буферами или массивами.
 * - Тип @c se_soffset_t поддерживает как положительные, так и отрицательные значения,
 *   что полезно при вычислении смещений, которые могут быть как в положительную,
 *   так и в отрицательную сторону.
 * - Тип @c se_uoffset_t поддерживает только положительные значения и используется
 *   для операций с индексами, где отрицательные значения недопустимы.
 *
 * Этот файл также включает заголовочный файл @c "size.h" для использования базовых типов
 * @c se_ssize_t и @c se_usize_t, которые являются исходными типами для определения
 * @c se_soffset_t и @c se_uoffset_t.
 */

#ifndef SE_OFFSET_H
#define SE_OFFSET_H

#include "size.h"

/**
 * @typedef se_soffset_t
 * @brief Тип для представления знаковых смещений в памяти.
 *
 * Этот тип используется для хранения смещений в памяти, которые могут быть отрицательными,
 * например, при выполнении операций с отрицательными адресами в массиве или буфере.
 * Он является псевдонимом для типа @c se_ssize_t.
 */
typedef se_ssize_t se_soffset_t;

/**
 * @typedef se_uoffset_t
 * @brief Тип для представления беззнаковых смещений в памяти.
 *
 * Этот тип используется для хранения смещений в памяти, которые всегда должны быть
 * положительными (или нулевыми), например, при манипуляциях с положительными индексами массивов.
 * Он является псевдонимом для типа @c se_usize_t.
 */
typedef se_usize_t se_uoffset_t;

#endif // SE_OFFSET_H
