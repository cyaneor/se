/**
 * @file numeric_fixed_types.h
 * @brief Заголовочный файл,
 *        определяющий псевдонимы для фиксированных типов целых чисел.
 *
 * В этом файле определены псевдонимы для различных типов целых чисел
 * с фиксированным размером (8, 16, 32, 64 и 128 бит), как для знаковых,
 * так и для беззнаковых типов.
 */

#ifndef SE_NUMERIC_FIXED_TYPES_H
#define SE_NUMERIC_FIXED_TYPES_H

#include "numeric_types.h"

/**
 * @typedef se_u8_t
 * @brief Псевдоним для беззнакового 8-битного целого.
 *
 * Этот тип соответствует типу `se_uchar_t` и используется
 * для представления беззнаковых целых чисел размером 8 бит.
 */
typedef se_uchar_t se_u8_t;

/**
 * @typedef se_u16_t
 * @brief Псевдоним для беззнакового 16-битного целого.
 *
 * Этот тип соответствует типу `se_ushort_t` и используется
 * для представления беззнаковых целых чисел размером 16 бит.
 */
typedef se_ushort_t se_u16_t;

/**
 * @typedef se_u32_t
 * @brief Псевдоним для беззнакового 32-битного целого.
 *
 * Этот тип соответствует типу `se_uint_t` и используется
 * для представления беззнаковых целых чисел размером 32 бита.
 */
typedef se_uint_t se_u32_t;

/**
 * @typedef se_u64_t
 * @brief Псевдоним для беззнакового 64-битного целого.
 *
 * Этот тип соответствует типу `se_ullong_t` и используется
 * для представления беззнаковых целых чисел размером 64 бита.
 */
typedef se_ullong_t se_u64_t;

/**
 * @typedef se_s8_t
 * @brief Псевдоним для знакового 8-битного целого.
 *
 * Этот тип соответствует типу `se_schar_t` и используется
 * для представления знаковых целых чисел размером 8 бит.
 */
typedef se_schar_t se_s8_t;

/**
 * @typedef se_s16_t
 * @brief Псевдоним для знакового 16-битного целого.
 *
 * Этот тип соответствует типу `se_sshort_t` и используется
 * для представления знаковых целых чисел размером 16 бит.
 */
typedef se_sshort_t se_s16_t;

/**
 * @typedef se_s32_t
 * @brief Псевдоним для знакового 32-битного целого.
 *
 * Этот тип соответствует типу `se_sint_t` и используется
 * для представления знаковых целых чисел размером 32 бита.
 */
typedef se_sint_t se_s32_t;

/**
 * @typedef se_s64_t
 * @brief Псевдоним для знакового 64-битного целого.
 *
 * Этот тип соответствует типу `se_sllong_t` и используется
 * для представления знаковых целых чисел размером 64 бита.
 */
typedef se_sllong_t se_s64_t;

#if defined(SE_INT128_T_SIZE) && SE_INT128_T_SIZE == 16
/**
 * @typedef se_s128_t
 * @brief Псевдоним для знакового 128-битного целого.
 *
 * Этот тип соответствует типу `se_sint128_t` и используется для представления
 * знаковых целых чисел размером 128 бит. Этот тип доступен только в случае,
 * если размер 128-битных целых чисел поддерживается платформой.
 */
typedef se_sint128_t se_s128_t;

/**
 * @typedef se_u128_t
 * @brief Псевдоним для беззнакового 128-битного целого.
 *
 * Этот тип соответствует типу `se_uint128_t` и используется для представления
 * беззнаковых целых чисел размером 128 бит. Этот тип доступен только в случае,
 * если размер 128-битных целых чисел поддерживается платформой.
 */
typedef se_uint128_t se_u128_t;
#endif

#endif // SE_NUMERIC_FIXED_TYPES_H
