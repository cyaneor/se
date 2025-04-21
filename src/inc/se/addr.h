/**
 * @file addr.h
 * @brief Определение типов и лимитов
 *        для адресов в зависимости от размера указателя.
 *
 * Данный код определяет беззнаковые (`se_uaddr_t`) и знаковые (`se_saddr_t`) типы адресов,
 * а также их минимальные, максимальные значения и размер в байтах в зависимости
 * от значения макроса `SE_PTR_SIZE`.
 */

#ifndef SE_ADDR_H
#define SE_ADDR_H

#include "numeric_fixed.h"

#ifdef SE_PTR_SIZE
#    if SE_PTR_SIZE == 8

#        ifndef SE_UADDR_T_MIN
/**
 * @def SE_UADDR_T_MIN
 * @brief Минимальное значение беззнакового типа адреса для 64-битной системы.
 */
#            define SE_UADDR_T_MIN SE_U64_T_MIN
#        endif // SE_UADDR_T_MIN

#        ifndef SE_UADDR_T_MAX
/**
 * @def SE_UADDR_T_MAX
 * @brief Максимальное значение беззнакового типа адреса для 64-битной системы.
 */
#            define SE_UADDR_T_MAX SE_U64_T_MAX
#        endif // SE_UADDR_T_MAX

#        ifndef SE_UADDR_T_SIZE
/**
 * @def SE_UADDR_T_SIZE
 * @brief Размер беззнакового типа адреса в байтах для 64-битной системы.
 */
#            define SE_UADDR_T_SIZE SE_U64_T_SIZE
#        endif // SE_UADDR_T_SIZE

/**
 * @typedef se_uaddr_t
 * @brief Беззнаковый тип адреса для 64-битной системы.
 */
typedef se_u64_t se_uaddr_t;

#        ifndef SE_SADDR_T_MIN
/**
 * @def SE_SADDR_T_MIN
 * @brief Минимальное значение знакового типа адреса для 64-битной системы.
 */
#            define SE_SADDR_T_MIN SE_S64_T_MIN
#        endif // SE_SADDR_T_MIN

#        ifndef SE_SADDR_T_MAX
/**
 * @def SE_SADDR_T_MAX
 * @brief Максимальное значение знакового типа адреса для 64-битной системы.
 */
#            define SE_SADDR_T_MAX SE_S64_T_MAX
#        endif // SE_SADDR_T_MAX

#        ifndef SE_SADDR_T_SIZE
/**
 * @def SE_SADDR_T_SIZE
 * @brief Размер знакового типа адреса в байтах для 64-битной системы.
 */
#            define SE_SADDR_T_SIZE SE_S64_T_SIZE
#        endif // SE_SADDR_T_SIZE

/**
 * @typdef se_saddr_t
 * @brief Знаковый тип адреса для 64-битной системы.
 */
typedef se_s64_t se_saddr_t;

#    elif SE_PTR_SIZE == 4

#        ifndef SE_UADDR_T_MIN
/**
 * @def SE_UADDR_T_MIN
 * @brief Минимальное значение беззнакового типа адреса для 32-битной системы.
 */
#            define SE_UADDR_T_MIN SE_U32_T_MIN
#        endif // SE_UADDR_T_MIN

#        ifndef SE_UADDR_T_MAX
/**
 * @def SE_UADDR_T_MAX
 * @brief Максимальное значение беззнакового типа адреса для 32-битной системы.
 */
#            define SE_UADDR_T_MAX SE_U32_T_MAX
#        endif // SE_UADDR_T_MAX

#        ifndef SE_UADDR_T_SIZE
/**
 * @def SE_UADDR_T_SIZE
 * @brief Размер беззнакового типа адреса в байтах для 32-битной системы.
 */
#            define SE_UADDR_T_SIZE SE_U32_T_SIZE
#        endif // SE_UADDR_T_SIZE

/**
 * @typedef se_uaddr_t
 * @brief Беззнаковый тип адреса для 32-битной системы.
 */
typedef se_u32_t se_uaddr_t;

#        ifndef SE_SADDR_T_MIN
/**
 * @def SE_SADDR_T_MIN
 * @brief Минимальное значение знакового типа адреса для 32-битной системы.
 */
#            define SE_SADDR_T_MIN SE_S32_T_MIN
#        endif // SE_SADDR_T_MIN

#        ifndef SE_SADDR_T_MAX
/**
 * @def SE_SADDR_T_MAX
 * @brief Максимальное значение знакового типа адреса для 32-битной системы.
 */
#            define SE_SADDR_T_MAX SE_S32_T_MAX
#        endif // SE_SADDR_T_MAX

#        ifndef SE_SADDR_T_SIZE
/**
 * @def SE_SADDR_T_SIZE
 * @brief Размер знакового типа адреса в байтах для 32-битной системы.
 */
#            define SE_SADDR_T_SIZE SE_S32_T_SIZE
#        endif // SE_SADDR_T_SIZE

/**
 * @typedef se_saddr_t
 * @brief Знаковый тип адреса для 32-битной системы.
 */
typedef se_s32_t se_saddr_t;

#    elif SE_PTR_SIZE == 2

#        ifndef SE_UADDR_T_MIN
/**
 * @def SE_UADDR_T_MIN
 * @brief Минимальное значение беззнакового типа адреса для 16-битной системы.
 */
#            define SE_UADDR_T_MIN SE_U16_T_MIN
#        endif // SE_UADDR_T_MIN

#        ifndef SE_UADDR_T_MAX
/**
 * @def SE_UADDR_T_MAX
 * @brief Максимальное значение беззнакового типа адреса для 16-битной системы.
 */
#            define SE_UADDR_T_MAX SE_U16_T_MAX
#        endif // SE_UADDR_T_MAX

#        ifndef SE_UADDR_T_SIZE
/**
 * @def SE_UADDR_T_SIZE
 * @brief Размер беззнакового типа адреса в байтах для 16-битной системы.
 */
#            define SE_UADDR_T_SIZE SE_U16_T_SIZE
#        endif // SE_UADDR_T_SIZE

/**
 * @typedef se_uaddr_t
 * @brief Беззнаковый тип адреса для 16-битной системы.
 */
typedef se_u16_t se_uaddr_t;

#        ifndef SE_SADDR_T_MIN
/**
 * @def SE_SADDR_T_MIN
 * @brief Минимальное значение знакового типа адреса для 16-битной системы.
 */
#            define SE_SADDR_T_MIN SE_S16_T_MIN
#        endif // SE_SADDR_T_MIN

#        ifndef SE_SADDR_T_MAX
/**
 * @def SE_SADDR_T_MAX
 * @brief Максимальное значение знакового типа адреса для 16-битной системы.
 */
#            define SE_SADDR_T_MAX SE_S16_T_MAX
#        endif // SE_SADDR_T_MAX

#        ifndef SE_SADDR_T_SIZE
/**
 * @def SE_SADDR_T_SIZE
 * @brief Размер знакового типа адреса в байтах для 16-битной системы.
 */
#            define SE_SADDR_T_SIZE SE_S16_T_SIZE
#        endif // SE_SADDR_T_SIZE

/**
 * @typedef se_saddr_t
 * @brief Знаковый тип адреса для 16-битной системы.
 */
typedef se_s16_t se_saddr_t;

#    elif SE_PTR_SIZE == 1

#        ifndef SE_UADDR_T_MIN
/**
 * @def SE_UADDR_T_MIN
 * @brief Минимальное значение беззнакового типа адреса для 8-битной системы.
 */
#            define SE_UADDR_T_MIN SE_U8_T_MIN
#        endif // SE_UADDR_T_MIN

#        ifndef SE_UADDR_T_MAX
/**
 * @def SE_UADDR_T_MAX
 * @brief Максимальное значение беззнакового типа адреса для 8-битной системы.
 */
#            define SE_UADDR_T_MAX SE_U8_T_MAX
#        endif // SE_UADDR_T_MAX

#        ifndef SE_UADDR_T_SIZE
/**
 * @define SE_UADDR_T_SIZE
 * @brief Размер беззнакового типа адреса в байтах для 8-битной системы.
 */
#            define SE_UADDR_T_SIZE SE_U8_T_SIZE
#        endif // SE_UADDR_T_SIZE

/**
 * @typedef se_uaddr_t
 * @brief Беззнаковый тип адреса для 8-битной системы.
 */
typedef se_u8_t se_uaddr_t;

#        ifndef SE_SADDR_T_MIN
/**
 * @def SE_SADDR_T_MIN
 * @brief Минимальное значение знакового типа адреса для 8-битной системы.
 */
#            define SE_SADDR_T_MIN SE_S8_T_MIN
#        endif // SE_SADDR_T_MIN

#        ifndef SE_SADDR_T_MAX
/**
 * @def SE_SADDR_T_MAX
 * @brief Максимальное значение знакового типа адреса для 8-битной системы.
 */
#            define SE_SADDR_T_MAX SE_S8_T_MAX
#        endif // SE_SADDR_T_MAX

#        ifndef SE_SADDR_T_SIZE
/**
 * @def SE_SADDR_T_SIZE
 * @brief Размер знакового типа адреса в байтах для 8-битной системы.
 */
#            define SE_SADDR_T_SIZE SE_S8_T_SIZE
#        endif // SE_SADDR_T_SIZE

/**
 * @typedef se_saddr_t
 * @brief Знаковый тип адреса для 8-битной системы.
 */
typedef se_s8_t se_saddr_t;

#    else
#        error "Unsupported pointer size SE_PTR_SIZE"
#    endif
#else
#    error "SE_PTR_SIZE is not defined"
#endif

#endif /* SE_ADDR_H */