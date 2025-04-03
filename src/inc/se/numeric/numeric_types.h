/**
 * @file numeric_types.h
 * @brief Заголовочный файл, определяющий пользовательские числовые типы с префиксом se_.
 *
 * Этот файл предоставляет набор псевдонимов типов для стандартных целочисленных типов C,
 * разделенных на беззнаковые (unsigned) и знаковые (signed) варианты с явными префиксами
 * 'se_u' и 'se_s' соответственно.
 */

#ifndef SE_NUMERIC_TYPES_H
#define SE_NUMERIC_TYPES_H

/**
 * @typedef se_uchar_t
 * @brief Псевдоним для беззнакового символа (8 бит).
 */
typedef unsigned char se_uchar_t;

/**
 * @typedef se_ushort_t
 * @brief Псевдоним для беззнакового короткого целого (обычно 16 бит).
 */
typedef unsigned short se_ushort_t;

/**
 * @typedef se_uint_t
 * @brief Псевдоним для беззнакового целого (обычно 32 бита).
 */
typedef unsigned int se_uint_t;

/**
 * @typedef se_ulong_t
 * @brief Псевдоним для беззнакового длинного целого
 *        (обычно 32 или 64 бита в зависимости от платформы).
 */
typedef unsigned long se_ulong_t;

/**
 * @typedef se_ullong_t
 * @brief Псевдоним для беззнакового очень длинного целого (обычно 64 бита).
 */
typedef unsigned long long se_ullong_t;

/**
 * @typedef se_schar_t
 * @brief Псевдоним для знакового символа (8 бит).
 */
typedef char se_schar_t;

/**
 * @typedef se_sshort_t
 * @brief Псевдоним для знакового короткого целого (обычно 16 бит).
 */
typedef short se_sshort_t;

/**
 * @typedef se_sint_t
 * @brief Псевдоним для знакового целого (обычно 32 бита).
 */
typedef int se_sint_t;

/**
 * @typedef se_slong_t
 * @brief Псевдоним для знакового длинного целого
 *        (обычно 32 или 64 бита в зависимости от платформы).
 */
typedef long se_slong_t;

/**
 * @typedef se_sllong_t
 * @brief Псевдоним для знакового очень длинного целого (обычно 64 бита).
 */
typedef long long se_sllong_t;

#ifdef SE_INT128_T_SIZE

/**
 * @typedef se_sint128_t
 * @brief Псевдоним для знакового 128-битного целого.
 */
typedef __int128 se_sint128_t;

/**
 * @typedef se_uint128_t
 * @brief Псевдоним для беззнакового 128-битного целого.
 */
typedef unsigned __int128 se_uint128_t;

#endif // SE_INT128_T_SIZE

#endif /* SE_NUMERIC_TYPES_H */