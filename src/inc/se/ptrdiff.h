/**
 * @file ptrdiff.h
 * @brief Определения для типа разности указателей.
 *
 * Этот файл содержит макросы и типы, необходимые для работы с разностью указателей.
 * Основной тип `se_ptrdiff_t` используется для представления результатов вычитания
 * указателей и вычисления расстояний между адресами памяти. Все определения зависят
 * от типов и макросов, предоставленных в `intptr.h`, что обеспечивает согласованность
 * с платформо-зависимыми характеристиками указателей.
 *
 * Основные компоненты:
 * - Макросы для размера, минимального и максимального значений типа `se_ptrdiff_t`.
 * - Тип `se_ptrdiff_t`, синоним для `se_sintptr_t`, предназначенный для арифметики указателей.
 *
 * @note Этот файл зависит от `intptr.h`, который определяет базовые типы и макросы
 *       для работы с указателями.
 */

#ifndef SE_PTRDIFF_H
#define SE_PTRDIFF_H

#include "intptr.h"

/**
 * @def SE_PTRDIFF_T_SIZE
 * @brief Размер типа `ptrdiff_t` в байтах.
 *
 * Определяет размер типа `se_ptrdiff_t`, который эквивалентен размеру `se_sintptr_t`.
 * Значение берется из макроса `SE_SINTPTR_T_SIZE`, обеспечивая совместимость с платформой.
 */
#define SE_PTRDIFF_T_SIZE SE_SINTPTR_T_SIZE

/**
 * @def SE_PTRDIFF_T_MIN
 * @brief Минимальное значение типа `ptrdiff_t`.
 *
 * Определяет минимальное значение для типа `se_ptrdiff_t`, равное минимальному значению
 * `se_sintptr_t`. Значение берется из макроса `SE_SINTPTR_T_MIN`.
 */
#define SE_PTRDIFF_T_MIN SE_SINTPTR_T_MIN

/**
 * @def SE_PTRDIFF_T_MAX
 * @brief Максимальное значение типа `ptrdiff_t`.
 *
 * Определяет максимальное значение для типа `se_ptrdiff_t`, равное максимальному значению
 * `se_sintptr_t`. Значение берется из макроса `SE_SINTPTR_T_MAX`.
 */
#define SE_PTRDIFF_T_MAX SE_SINTPTR_T_MAX

/**
 * @typedef se_ptrdiff_t
 * @brief Тип для хранения разности указателей.
 *
 * Определяет `se_ptrdiff_t` как синоним `se_sintptr_t`. Используется для вычисления
 * расстояния между двумя указателями в байтах или для хранения результатов арифметики
 * указателей. Этот тип является знаковым и платформо-зависимым, что позволяет корректно
 * обрабатывать как положительные, так и отрицательные смещения.
 *
 * @note Тип зависит от разрядности системы, так как наследует характеристики `se_sintptr_t`.
 */
typedef se_sintptr_t se_ptrdiff_t;

#endif // SE_PTRDIFF_H