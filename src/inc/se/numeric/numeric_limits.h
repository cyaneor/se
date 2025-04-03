/**
 * @file numeric_limits.h
 * @brief Заголовочный файл, который определяет макросы
 *        для установления размеров и предельных значений различных числовых типов.
 *
 * Этот файл содержит макросы, определяющие размеры (в битах)
 * и минимальные/максимальные значения для различных числовых типов,
 * таких как `char`, `short`, `int`, `long`, `long long`, а также их
 * беззнаковые аналоги.
 */

#ifndef SE_NUMERIC_LIMITS_H
#define SE_NUMERIC_LIMITS_H

#include "numeric_limit.h"
#include "numeric_types.h"

#ifndef SE_CHAR_T_SIZE
#    define SE_CHAR_T_SIZE (sizeof(se_schar_t))
#endif // SE_CHAR_T_SIZE

#ifndef SE_SHORT_T_SIZE
#    define SE_SHORT_T_SIZE (sizeof(se_sshort_t))
#endif // SE_SHORT_T_SIZE

#ifndef SE_INT_T_SIZE
#    define SE_INT_T_SIZE (sizeof(se_sint_t))
#endif // SE_INT_T_SIZE

#ifndef SE_LONG_T_SIZE
#    define SE_LONG_T_SIZE (sizeof(se_slong_t))
#endif // SE_LONG_T_SIZE

#ifndef SE_LLONG_T_SIZE
#    define SE_LLONG_T_SIZE (sizeof(se_sllong_t))
#endif // SE_LLONG_T_SIZE

#ifndef SE_UCHAR_T_MIN
/**
 * @def SE_UCHAR_T_MIN
 * @brief Минимальное значение для типа unsigned char.
 *
 * Этот макрос возвращает минимальное значение для типа `unsigned char`,
 * используя функцию `se_numeric_limit_uint_min` с типом `se_uchar_t`.
 */
#    define SE_UCHAR_T_MIN se_numeric_limit_uint_min(se_uchar_t)
#endif // SE_UCHAR_T_MIN

#ifndef SE_UCHAR_T_MAX
/**
 * @def SE_UCHAR_T_MAX
 * @brief Максимальное значение для типа unsigned char.
 *
 * Этот макрос возвращает максимальное значение для типа `unsigned char`,
 * используя функцию `se_numeric_limit_uint_max` с типом `se_uchar_t`.
 */
#    define SE_UCHAR_T_MAX se_numeric_limit_uint_max(se_uchar_t)
#endif // SE_UCHAR_T_MAX

#ifndef SE_USHORT_T_MIN
/**
 * @def SE_USHORT_T_MIN
 * @brief Минимальное значение для типа unsigned short.
 *
 * Этот макрос возвращает минимальное значение для типа `unsigned short`,
 * используя функцию `se_numeric_limit_uint_min` с типом `se_ushort_t`.
 */
#    define SE_USHORT_T_MIN se_numeric_limit_uint_min(se_ushort_t)
#endif // SE_USHORT_T_MIN

#ifndef SE_USHORT_T_MAX
/**
 * @def SE_USHORT_T_MAX
 * @brief Максимальное значение для типа unsigned short.
 *
 * Этот макрос возвращает максимальное значение для типа `unsigned short`,
 * используя функцию `se_numeric_limit_uint_max` с типом `se_ushort_t`.
 */
#    define SE_USHORT_T_MAX se_numeric_limit_uint_max(se_ushort_t)
#endif // SE_USHORT_T_MAX

#ifndef SE_UINT_T_MIN
/**
 * @def SE_UINT_T_MIN
 * @brief Минимальное значение для типа unsigned int.
 *
 * Этот макрос возвращает минимальное значение для типа `unsigned int`,
 * используя функцию `se_numeric_limit_uint_min` с типом `se_uint_t`.
 */
#    define SE_UINT_T_MIN se_numeric_limit_uint_min(se_uint_t)
#endif // SE_UINT_T_MIN

#ifndef SE_UINT_T_MAX
/**
 * @def SE_UINT_T_MAX
 * @brief Максимальное значение для типа unsigned int.
 *
 * Этот макрос возвращает максимальное значение для типа `unsigned int`,
 * используя функцию `se_numeric_limit_uint_max` с типом `se_uint_t`.
 */
#    define SE_UINT_T_MAX se_numeric_limit_uint_max(se_uint_t)
#endif // SE_UINT_T_MAX

#ifndef SE_ULONG_T_MIN
/**
 * @def SE_ULONG_T_MIN
 * @brief Минимальное значение для типа unsigned long.
 *
 * Этот макрос возвращает минимальное значение для типа `unsigned long`,
 * используя функцию `se_numeric_limit_uint_min` с типом `se_ulong_t`.
 */
#    define SE_ULONG_T_MIN se_numeric_limit_uint_min(se_ulong_t)
#endif // SE_ULONG_T_MIN

#ifndef SE_ULONG_T_MAX
/**
 * @def SE_ULONG_T_MAX
 * @brief Максимальное значение для типа unsigned long.
 *
 * Этот макрос возвращает максимальное значение для типа `unsigned long`,
 * используя функцию `se_numeric_limit_uint_max` с типом `se_ulong_t`.
 */
#    define SE_ULONG_T_MAX se_numeric_limit_uint_max(se_ulong_t)
#endif // SE_ULONG_T_MAX

#ifndef SE_ULLONG_T_MIN
/**
 * @def SE_ULLONG_T_MIN
 * @brief Минимальное значение для типа unsigned long long.
 *
 * Этот макрос возвращает минимальное значение для типа `unsigned long long`,
 * используя функцию `se_numeric_limit_uint_min` с типом `se_ullong_t`.
 */
#    define SE_ULLONG_T_MIN se_numeric_limit_uint_min(se_ullong_t)
#endif // SE_ULLONG_T_MIN

#ifndef SE_ULLONG_T_MAX
/**
 * @def SE_ULLONG_T_MAX
 * @brief Максимальное значение для типа unsigned long long.
 *
 * Этот макрос возвращает максимальное значение для типа `unsigned long long`,
 * используя функцию `se_numeric_limit_uint_max` с типом `se_ullong_t`.
 */
#    define SE_ULLONG_T_MAX se_numeric_limit_uint_max(se_ullong_t)
#endif // SE_ULLONG_T_MAX

#ifndef SE_SCHAR_T_MIN
/**
 * @def SE_SCHAR_T_MIN
 * @brief Минимальное значение для типа signed char.
 *
 * Этот макрос возвращает минимальное значение для типа `signed char`,
 * используя функцию `se_numeric_limit_sint_min` с типом `se_schar_t`.
 */
#    define SE_SCHAR_T_MIN se_numeric_limit_sint_min(se_schar_t)
#endif // SE_SCHAR_T_MIN

#ifndef SE_SCHAR_T_MAX
/**
 * @def SE_SCHAR_T_MAX
 * @brief Максимальное значение для типа signed char.
 *
 * Этот макрос возвращает максимальное значение для типа `signed char`,
 * используя функцию `se_numeric_limit_sint_max` с типом `se_schar_t`.
 */
#    define SE_SCHAR_T_MAX se_numeric_limit_sint_max(se_schar_t)
#endif // SE_SCHAR_T_MAX

#ifndef SE_SSHORT_T_MIN
/**
 * @def SE_SSHORT_T_MIN
 * @brief Минимальное значение для типа signed short.
 *
 * Этот макрос возвращает минимальное значение для типа `signed short`,
 * используя функцию `se_numeric_limit_sint_min` с типом `se_sshort_t`.
 */
#    define SE_SSHORT_T_MIN se_numeric_limit_sint_min(se_sshort_t)
#endif // SE_SSHORT_T_MIN

#ifndef SE_SSHORT_T_MAX
/**
 * @def SE_SSHORT_T_MAX
 * @brief Максимальное значение для типа signed short.
 *
 * Этот макрос возвращает максимальное значение для типа `signed short`,
 * используя функцию `se_numeric_limit_sint_max` с типом `se_sshort_t`.
 */
#    define SE_SSHORT_T_MAX se_numeric_limit_sint_max(se_sshort_t)
#endif // SE_SSHORT_T_MAX

#ifndef SE_SINT_T_MIN
/**
 * @def SE_SINT_T_MIN
 * @brief Минимальное значение для типа signed int.
 *
 * Этот макрос возвращает минимальное значение для типа `signed int`,
 * используя функцию `se_numeric_limit_sint_min` с типом `se_sint_t`.
 */
#    define SE_SINT_T_MIN se_numeric_limit_sint_min(se_sint_t)
#endif // SE_SINT_T_MIN

#ifndef SE_SINT_T_MAX
/**
 * @def SE_SINT_T_MAX
 * @brief Максимальное значение для типа signed int.
 *
 * Этот макрос возвращает максимальное значение для типа `signed int`,
 * используя функцию `se_numeric_limit_sint_max` с типом `se_sint_t`.
 */
#    define SE_SINT_T_MAX se_numeric_limit_sint_max(se_sint_t)
#endif // SE_SINT_T_MAX

#ifndef SE_SLONG_T_MIN
/**
 * @def SE_SLONG_T_MIN
 * @brief Минимальное значение для типа signed long.
 *
 * Этот макрос возвращает минимальное значение для типа `signed long`,
 * используя функцию `se_numeric_limit_sint_min` с типом `se_slong_t`.
 */
#    define SE_SLONG_T_MIN se_numeric_limit_sint_min(se_slong_t)
#endif // SE_SLONG_T_MIN

#ifndef SE_SLONG_T_MAX
/**
 * @def SE_SLONG_T_MAX
 * @brief Максимальное значение для типа signed long.
 *
 * Этот макрос возвращает максимальное значение для типа `signed long`,
 * используя функцию `se_numeric_limit_sint_max` с типом `se_slong_t`.
 */
#    define SE_SLONG_T_MAX se_numeric_limit_sint_max(se_slong_t)
#endif // SE_SLONG_T_MAX

#ifndef SE_SLLONG_T_MIN
/**
 * @def SE_SLLONG_T_MIN
 * @brief Минимальное значение для типа signed long long.
 *
 * Этот макрос возвращает минимальное значение для типа `signed long long`,
 * используя функцию `se_numeric_limit_sint_min` с типом `se_sllong_t`.
 */
#    define SE_SLLONG_T_MIN se_numeric_limit_sint_min(se_sllong_t)
#endif // SE_SLLONG_T_MIN

#ifndef SE_SLLONG_T_MAX
/**
 * @def SE_SLLONG_T_MAX
 * @brief Максимальное значение для типа signed long long.
 *
 * Этот макрос возвращает максимальное значение для типа `signed long long`,
 * используя функцию `se_numeric_limit_sint_max` с типом `se_sllong_t`.
 */
#    define SE_SLLONG_T_MAX se_numeric_limit_sint_max(se_sllong_t)
#endif // SE_SLLONG_T_MAX

#ifdef SE_INT128_T_SIZE

#    ifndef SE_SINT128_T_MIN
/**
 * @def SE_SINT128_T_MIN
 * @brief Минимальное значение для типа 128-битного числа с знаком.
 *
 * Этот макрос возвращает минимальное значение для типа `se_sint128_t`,
 * используя функцию `se_numeric_limit_sint_min`.
 */
#        define SE_SINT128_T_MIN se_numeric_limit_sint_min(se_sint128_t)
#    endif // SE_SINT128_T_MIN

#    ifndef SE_SINT128_T_MAX
/**
 * @def SE_SINT128_T_MAX
 * @brief Максимальное значение для типа 128-битного числа с знаком.
 *
 * Этот макрос возвращает максимальное значение для типа `se_sint128_t`,
 * используя функцию `se_numeric_limit_sint_max`.
 */
#        define SE_SINT128_T_MAX se_numeric_limit_sint_max(se_sint128_t)
#    endif // SE_SINT128_T_MAX

#    ifndef SE_UINT128_T_MIN
/**
 * @def SE_UINT128_T_MIN
 * @brief Минимальное значение для типа 128-битного числа без знака.
 *
 * Этот макрос возвращает минимальное значение для типа `se_uint128_t`,
 * используя функцию `se_numeric_limit_uint_min`.
 */
#        define SE_UINT128_T_MIN se_numeric_limit_uint_min(se_uint128_t)
#    endif // SE_UINT128_T_MIN

#    ifndef SE_UINT128_T_MAX
/**
 * @def SE_UINT128_T_MAX
 * @brief Максимальное значение для типа 128-битного числа без знака.
 *
 * Этот макрос возвращает максимальное значение для типа `se_uint128_t`,
 * используя функцию `se_numeric_limit_uint_max`.
 */
#        define SE_UINT128_T_MAX se_numeric_limit_uint_max(se_uint128_t)
#    endif // SE_UINT128_T_MAX

#endif // SE_INT128_T_SIZE

#endif // SE_NUMERIC_LIMITS_H
