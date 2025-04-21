/**
 * @file numeric_fixed_limits.h
 * @brief Заголовочный файл, определяющий минимальные
 *        и максимальные значения для различных целочисленных типов данных.
 *
 * @details Этот файл содержит макросы, которые определяют минимальные и максимальные значения
 *          для знаковых и беззнаковых целочисленных типов с фиксированной разрядностью,
 *          включая 8, 16, 32, 64 и 128 бит.
 */

#ifndef SE_NUMERIC_FIXED_LIMITS_H
#define SE_NUMERIC_FIXED_LIMITS_H

#include "numeric_limits.h"

#ifndef SE_S8_T_MIN
/**
 * @def SE_S8_T_MIN
 * @brief Минимальное значение для знакового 8-битного целочисленного типа (se_s8_t).
 * @details Определяется как минимальный предел знакового целого числа для se_s8_t.
 */
#    define SE_S8_T_MIN SE_SCHAR_T_MIN
#endif

#ifndef SE_S8_T_MAX
/**
 * @def SE_S8_T_MAX
 * @brief Максимальное значение для знакового 8-битного целочисленного типа (se_s8_t).
 * @details Определяется как максимальный предел знакового целого числа для se_s8_t.
 */
#    define SE_S8_T_MAX SE_SCHAR_T_MAX
#endif

#ifndef SE_S8_T_SIZE
/**
 * @def SE_S8_T_SIZE
 * @brief Размер в байтах для знакового 8-битного целочисленного типа (se_s8_t).
 * @details Определяется как SE_CHAR_T_SIZE, обычно равен 1 байту (8 бит).
 */
#    define SE_S8_T_SIZE SE_CHAR_T_SIZE
#endif

#ifndef SE_U8_T_MIN
/**
 * @def SE_U8_T_MIN
 * @brief Минимальное значение для беззнакового 8-битного целочисленного типа (se_u8_t).
 * @details Определяется как минимальный предел беззнакового целого числа для se_u8_t.
 */
#    define SE_U8_T_MIN SE_UCHAR_T_MIN
#endif

#ifndef SE_U8_T_MAX
/**
 * @def SE_U8_T_MAX
 * @brief Максимальное значение для беззнакового 8-битного целочисленного типа (se_u8_t).
 * @details Определяется как максимальный предел беззнакового целого числа для se_u8_t.
 */
#    define SE_U8_T_MAX SE_UCHAR_T_MAX
#endif

#ifndef SE_U8_T_SIZE
/**
 * @def SE_U8_T_SIZE
 * @brief Размер в байтах для беззнакового 8-битного целочисленного типа (se_u8_t).
 * @details Определяется как SE_CHAR_T_SIZE, обычно равен 1 байту (8 бит).
 */
#    define SE_U8_T_SIZE SE_CHAR_T_SIZE
#endif

#ifndef SE_S16_T_MIN
/**
 * @def SE_S16_T_MIN
 * @brief Минимальное значение для знакового 16-битного целочисленного типа (se_s16_t).
 * @details Определяется как минимальный предел знакового целого числа для se_s16_t.
 */
#    define SE_S16_T_MIN SE_SSHORT_T_MIN
#endif

#ifndef SE_S16_T_MAX
/**
 * @def SE_S16_T_MAX
 * @brief Максимальное значение для знакового 16-битного целочисленного типа (se_s16_t).
 * @details Определяется как максимальный предел знакового целого числа для se_s16_t.
 */
#    define SE_S16_T_MAX SE_SSHORT_T_MAX
#endif

#ifndef SE_S16_T_SIZE
/**
 * @def SE_S16_T_SIZE
 * @brief Размер в байтах для знакового 16-битного целочисленного типа (se_s16_t).
 * @details Определяется как SE_SHORT_T_SIZE, обычно равен 2 байтам (16 бит).
 */
#    define SE_S16_T_SIZE SE_SHORT_T_SIZE
#endif

#ifndef SE_U16_T_MIN
/**
 * @def SE_U16_T_MIN
 * @brief Минимальное значение для беззнакового 16-битного целочисленного типа (se_u16_t).
 * @details Определяется как минимальный предел беззнакового целого числа для se_u16_t.
 */
#    define SE_U16_T_MIN SE_USHORT_T_MIN
#endif

#ifndef SE_U16_T_MAX
/**
 * @def SE_U16_T_MAX
 * @brief Максимальное значение для беззнакового 16-битного целочисленного типа (se_u16_t).
 * @details Определяется как максимальный предел беззнакового целого числа для se_u16_t.
 */
#    define SE_U16_T_MAX SE_USHORT_T_MAX
#endif

#ifndef SE_U16_T_SIZE
/**
 * @def SE_U16_T_SIZE
 * @brief Размер в байтах для беззнакового 16-битного целочисленного типа (se_u16_t).
 * @details Определяется как SE_SHORT_T_SIZE, обычно равен 2 байтам (16 бит).
 */
#    define SE_U16_T_SIZE SE_SHORT_T_SIZE
#endif

#ifndef SE_S32_T_MIN
/**
 * @def SE_S32_T_MIN
 * @brief Минимальное значение для знакового 32-битного целочисленного типа (se_s32_t).
 * @details Определяется как минимальный предел знакового целого числа для se_s32_t.
 */
#    define SE_S32_T_MIN SE_SINT_T_MIN
#endif

#ifndef SE_S32_T_MAX
/**
 * @def SE_S32_T_MAX
 * @brief Максимальное значение для знакового 32-битного целочисленного типа (se_s32_t).
 * @details Определяется как максимальный предел знакового целого числа для se_s32_t.
 */
#    define SE_S32_T_MAX SE_SINT_T_MAX
#endif

#ifndef SE_S32_T_SIZE
/**
 * @def SE_S32_T_SIZE
 * @brief Размер в байтах для знакового 32-битного целочисленного типа (se_s32_t).
 * @details Определяется как SE_INT_T_SIZE, обычно равен 4 байтам (32 бита).
 */
#    define SE_S32_T_SIZE SE_INT_T_SIZE
#endif

#ifndef SE_U32_T_MIN
/**
 * @def SE_U32_T_MIN
 * @brief Минимальное значение для беззнакового 32-битного целочисленного типа (se_u32_t).
 * @details Определяется как минимальный предел беззнакового целого числа для se_u32_t.
 */
#    define SE_U32_T_MIN SE_UINT_T_MIN
#endif

#ifndef SE_U32_T_MAX
/**
 * @def SE_U32_T_MAX
 * @brief Максимальное значение для беззнакового 32-битного целочисленного типа (se_u32_t).
 * @details Определяется как максимальный предел беззнакового целого числа для se_u32_t.
 */
#    define SE_U32_T_MAX SE_UINT_T_MAX
#endif

#ifndef SE_U32_T_SIZE
/**
 * @def SE_U32_T_SIZE
 * @brief Размер в байтах для беззнакового 32-битного целочисленного типа (se_u32_t).
 * @details Определяется как SE_INT_T_SIZE, обычно равен 4 байтам (32 бита).
 */
#    define SE_U32_T_SIZE SE_INT_T_SIZE
#endif

#ifndef SE_S64_T_MIN
/**
 * @def SE_S64_T_MIN
 * @brief Минимальное значение для знакового 64-битного целочисленного типа (se_s64_t).
 * @details Определяется как минимальный предел знакового целого числа для se_s64_t.
 */
#    define SE_S64_T_MIN SE_SLLONG_T_MIN
#endif

#ifndef SE_S64_T_MAX
/**
 * @def SE_S64_T_MAX
 * @brief Максимальное значение для знакового 64-битного целочисленного типа (se_s64_t).
 * @details Определяется как максимальный предел знакового целого числа для se_s64_t.
 */
#    define SE_S64_T_MAX SE_SLLONG_T_MAX
#endif

#ifndef SE_S64_T_SIZE
/**
 * @def SE_S64_T_SIZE
 * @brief Размер в байтах для знакового 64-битного целочисленного типа (se_s64_t).
 * @details Определяется как SE_LLONG_T_SIZE, обычно равен 8 байтам (64 бита).
 */
#    define SE_S64_T_SIZE SE_LLONG_T_SIZE
#endif

#ifndef SE_U64_T_MIN
/**
 * @def SE_U64_T_MIN
 * @brief Минимальное значение для беззнакового 64-битного целочисленного типа (se_u64_t).
 * @details Определяется как минимальный предел беззнакового целого числа для se_u64_t.
 */
#    define SE_U64_T_MIN SE_ULLONG_T_MIN
#endif

#ifndef SE_U64_T_MAX
/**
 * @def SE_U64_T_MAX
 * @brief Максимальное значение для беззнакового 64-битного целочисленного типа (se_u64_t).
 * @details Определяется как максимальный предел беззнакового целого числа для se_u64_t.
 */
#    define SE_U64_T_MAX SE_ULLONG_T_MAX
#endif

#ifndef SE_U64_T_SIZE
/**
 * @def SE_U64_T_SIZE
 * @brief Размер в байтах для беззнакового 64-битного целочисленного типа (se_u64_t).
 * @details Определяется как SE_LLONG_T_SIZE, обычно равен 8 байтам (64 бита).
 */
#    define SE_U64_T_SIZE SE_LLONG_T_SIZE
#endif

#if defined(SE_INT128_T_SIZE) && SE_INT128_T_SIZE == 16
#    ifndef SE_S128_T_MIN
/**
 * @def SE_S128_T_MIN
 * @brief Минимальное значение для знакового 128-битного целочисленного типа (se_s128_t).
 * @details Определяется как минимальный предел знакового целого числа для se_s128_t.
 */
#        define SE_S128_T_MIN SE_SINT128_T_MIN
#    endif

#    ifndef SE_S128_T_MAX
/**
 * @def SE_S128_T_MAX
 * @brief Максимальное значение для знакового 128-битного целочисленного типа (se_s128_t).
 * @details Определяется как максимальный предел знакового целого числа для se_s128_t.
 */
#        define SE_S128_T_MAX SE_SINT128_T_MAX
#    endif

#    ifndef SE_S128_T_SIZE
/**
 * @def SE_S128_T_SIZE
 * @brief Размер в байтах для знакового 128-битного целочисленного типа (se_s128_t).
 * @details Определяется как sizeof(se_s128_t), обычно равен 16 байтам (128 бит).
 */
#        define SE_S128_T_SIZE SE_INT128_T_SIZE
#    endif

#    ifndef SE_U128_T_MIN
/**
 * @def SE_U128_T_MIN
 * @brief Минимальное значение для беззнакового 128-битного целочисленного типа (se_u128_t).
 * @details Определяется как минимальный предел беззнакового целого числа для se_u128_t.
 */
#        define SE_U128_T_MIN SE_UINT128_T_MIN
#    endif

#    ifndef SE_U128_T_MAX
/**
 * @def SE_U128_T_MAX
 * @brief Максимальное значение для беззнакового 128-битного целочисленного типа (se_u128_t).
 * @details Определяется как максимальный предел беззнакового целого числа для se_u128_t.
 */
#        define SE_U128_T_MAX SE_UINT128_T_MAX
#    endif

#    ifndef SE_U128_T_SIZE
/**
 * @def SE_U128_T_SIZE
 * @brief Размер в байтах для беззнакового 128-битного целочисленного типа (se_u128_t).
 * @details Определяется как sizeof(se_u128_t), обычно равен 16 байтам (128 бит).
 */
#        define SE_U128_T_SIZE SE_INT128_T_SIZE
#    endif
#endif

#endif // SE_NUMERIC_FIXED_LIMITS_H