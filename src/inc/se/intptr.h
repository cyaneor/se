/**
 * @file intptr.h
 * @brief Определения и типы для работы с указателями.
 *
 * Этот файл содержит определения макросов и типов, которые используются
 * для работы с указателями как для знаковых, так и для беззнаковых типов.
 * Типы и макросы зависят от разрядности системы.
 *
 * Основные компоненты:
 * - Макросы для минимальных, максимальных значений и размера типов.
 * - Типы `se_uintptr_t` и `se_sintptr_t`, которые являются синонимами
 *   для типов `se_uaddr_t` и `se_saddr_t` соответственно.
 */

#ifndef SE_INTPTR_H
#define SE_INTPTR_H

#include "addr.h"

/**
 * @def SE_UINTPTR_T_MIN
 * @brief Минимальное значение для типа `se_uintptr_t`.
 *
 * Этот макрос определяет минимальное значение для типа `se_uintptr_t`,
 * эквивалентного `se_uaddr_t`. Значение берется из макроса `SE_UADDR_T_MIN`.
 */
#define SE_UINTPTR_T_MIN SE_UADDR_T_MIN

/**
 * @def SE_UINTPTR_T_MAX
 * @brief Максимальное значение для типа `se_uintptr_t`.
 *
 * Этот макрос определяет максимальное значение для типа `se_uintptr_t`,
 * эквивалентного `se_uaddr_t`. Значение берется из макроса `SE_UADDR_T_MAX`.
 */
#define SE_UINTPTR_T_MAX SE_UADDR_T_MAX

/**
 * @def SE_UINTPTR_T_SIZE
 * @brief Размер типа `se_uintptr_t` в байтах.
 *
 * Этот макрос определяет размер типа `se_uintptr_t`,
 * эквивалентного `se_uaddr_t`, с использованием макроса `SE_UADDR_T_SIZE`.
 */
#define SE_UINTPTR_T_SIZE SE_UADDR_T_SIZE

/**
 * @typedef se_uintptr_t
 * @brief Тип для представления беззнаковых указателей.
 *
 * Этот тип является синонимом для типа `se_uaddr_t` и используется для работы
 * с беззнаковыми указателями. Размер типа определяется разрядностью системы.
 */
typedef se_uaddr_t se_uintptr_t;

/**
 * @def SE_SINTPTR_T_MIN
 * @brief Минимальное значение для типа `se_sintptr_t`.
 *
 * Этот макрос определяет минимальное значение для типа `se_sintptr_t`,
 * эквивалентного `se_saddr_t`. Значение берется из макроса `SE_SADDR_T_MIN`.
 */
#define SE_SINTPTR_T_MIN SE_SADDR_T_MIN

/**
 * @def SE_SINTPTR_T_MAX
 * @brief Максимальное значение для типа `se_sintptr_t`.
 *
 * Этот макрос определяет максимальное значение для типа `se_sintptr_t`,
 * эквивалентного `se_saddr_t`. Значение берется из макроса `SE_SADDR_T_MAX`.
 */
#define SE_SINTPTR_T_MAX SE_SADDR_T_MAX

/**
 * @def SE_SINTPTR_T_SIZE
 * @brief Размер типа `se_sintptr_t` в байтах.
 *
 * Этот макрос определяет размер типа `se_sintptr_t`,
 * эквивалентного `se_saddr_t`, с использованием макроса `SE_SADDR_T_SIZE`.
 */
#define SE_SINTPTR_T_SIZE SE_SADDR_T_SIZE

/**
 * @typedef se_sintptr_t
 * @brief Тип для представления знаковых указателей.
 *
 * Этот тип является синонимом для типа `se_saddr_t` и используется для работы
 * с знаковыми указателями. Размер типа определяется разрядностью системы.
 */
typedef se_saddr_t se_sintptr_t;

#endif // SE_INTPTR_H
