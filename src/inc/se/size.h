/**
 * @file size.h
 * @brief Заголовочный файл, определяющий знаковые
 *        и беззнаковые типы размеров (se_ssize_t и se_usize_t).
 *
 * Этот файл предоставляет определения типов `se_ssize_t` и `se_usize_t`,
 * а также их минимальные и максимальные значения в зависимости от размера,
 * заданного макросом `SE_SIZE_T_SIZE`.
 */

#ifndef SE_SIZE_H
#define SE_SIZE_H

#include "numeric_fixed.h"

#ifdef SE_SIZE_T_SIZE
#    if SE_SIZE_T_SIZE == 8
#        ifndef SE_SSIZE_T_MIN
/**
 * @def SE_SSIZE_T_MIN
 * @brief Минимальное значение для знакового типа размера (64-бит).
 */
#            define SE_SSIZE_T_MIN SE_S64_T_MIN
#        endif

#        ifndef SE_SSIZE_T_MAX
/**
 * @def SE_SSIZE_T_MAX
 * @brief Максимальное значение для знакового типа размера (64-бит).
 */
#            define SE_SSIZE_T_MAX SE_S64_T_MAX
#        endif

/**
 * @typedef se_ssize_t
 * @brief Знаковый 64-битный целочисленный тип для представления размеров или счетчиков.
 */
typedef se_s64_t se_ssize_t;

#        ifndef SE_USIZE_T_MIN
/**
 * @def SE_USIZE_T_MIN
 * @brief Минимальное значение для беззнакового типа размера (64-бит).
 */
#            define SE_USIZE_T_MIN SE_U64_T_MIN
#        endif

#        ifndef SE_USIZE_T_MAX
/**
 * @def SE_USIZE_T_MAX
 * @brief Максимальное значение для беззнакового типа размера (64-бит).
 */
#            define SE_USIZE_T_MAX SE_U64_T_MAX
#        endif

/**
 * @typedef se_usize_t
 * @brief Беззнаковый 64-битный целочисленный тип для представления размеров или счетчиков.
 */
typedef se_u64_t se_usize_t;

#    elif SE_SIZE_T_SIZE == 4
#        ifndef SE_SSIZE_T_MIN
/**
 * @def SE_SSIZE_T_MIN
 * @brief Минимальное значение для знакового типа размера (32-бит).
 */
#            define SE_SSIZE_T_MIN SE_S32_T_MIN
#        endif

#        ifndef SE_SSIZE_T_MAX
/**
 * @def SE_SSIZE_T_MAX
 * @brief Максимальное значение для знакового типа размера (32-бит).
 */
#            define SE_SSIZE_T_MAX SE_S32_T_MAX
#        endif

/**
 * @typedef se_ssize_t
 * @brief Знаковый 32-битный целочисленный тип для представления размеров или счетчиков.
 *  Псевдоним для s32_t.
 */
typedef se_s32_t se_ssize_t;

#        ifndef SE_USIZE_T_MIN
/**
 * @def SE_USIZE_T_MIN
 * @brief Минимальное значение для беззнакового типа размера (32-бит).
 */
#            define SE_USIZE_T_MIN SE_U32_T_MIN
#        endif

#        ifndef SE_USIZE_T_MAX
/**
 * @def SE_USIZE_T_MAX
 * @brief Максимальное значение для беззнакового типа размера (32-бит).
 */
#            define SE_USIZE_T_MAX SE_U32_T_MAX
#        endif

/**
 * @typedef se_usize_t
 * @brief Беззнаковый 32-битный целочисленный тип для представления размеров или счетчиков.
 *  Псевдоним для u32_t.
 */
typedef se_u32_t se_usize_t;

#    elif SE_SIZE_T_SIZE == 2
#        ifndef SE_SSIZE_T_MIN
/**
 * @def SE_SSIZE_T_MIN
 * @brief Минимальное значение для знакового типа размера (16-бит).
 */
#            define SE_SSIZE_T_MIN SE_S16_T_MIN
#        endif

#        ifndef SE_SSIZE_T_MAX
/**
 * @def SE_SSIZE_T_MAX
 * @brief Максимальное значение для знакового типа размера (16-бит).
 */
#            define SE_SSIZE_T_MAX SE_S16_T_MAX
#        endif

/**
 * @typedef se_ssize_t
 * @brief Знаковый 16-битный целочисленный тип для представления размеров или счетчиков.
 */
typedef se_s16_t se_ssize_t;

#        ifndef SE_USIZE_T_MIN
/**
 * @def SE_USIZE_T_MIN
 * @brief Минимальное значение для беззнакового типа размера (16-бит).
 */
#            define SE_USIZE_T_MIN SE_U16_T_MIN
#        endif

#        ifndef SE_USIZE_T_MAX
/**
 * @def SE_USIZE_T_MAX
 * @brief Максимальное значение для беззнакового типа размера (16-бит).
 */
#            define SE_USIZE_T_MAX SE_U16_T_MAX
#        endif

/**
 * @typedef se_usize_t
 * @brief Беззнаковый 16-битный целочисленный тип для представления размеров или счетчиков.
 */
typedef se_u16_t se_usize_t;

#    elif SE_SIZE_T_SIZE == 1
#        ifndef SE_SSIZE_T_MIN
/**
 * @def SE_SSIZE_T_MIN
 * @brief Минимальное значение для знакового типа размера (8-бит).
 */
#            define SE_SSIZE_T_MIN SE_S8_T_MIN
#        endif

#        ifndef SE_SSIZE_T_MAX
/**
 * @def SE_SSIZE_T_MAX
 * @brief Максимальное значение для знакового типа размера (8-бит).
 */
#            define SE_SSIZE_T_MAX SE_S8_T_MAX
#        endif

/**
 * @typedef se_ssize_t
 * @brief Знаковый 8-битный целочисленный тип для представления размеров или счетчиков.
 */
typedef se_s8_t se_ssize_t;

#        ifndef SE_USIZE_T_MIN
/**
 * @def SE_USIZE_T_MIN
 * @brief Минимальное значение для беззнакового типа размера (8-бит).
 */
#            define SE_USIZE_T_MIN SE_U8_T_MIN
#        endif

#        ifndef SE_USIZE_T_MAX
/**
 * @def SE_USIZE_T_MAX
 * @brief Максимальное значение для беззнакового типа размера (8-бит).
 */
#            define SE_USIZE_T_MAX SE_U8_T_MAX
#        endif

/**
 * @typedef se_usize_t
 * @brief Беззнаковый 8-битный целочисленный тип для представления размеров или счетчиков.
 */
typedef se_u8_t se_usize_t;
#    endif
#endif // SE_SIZE_T_SIZE

#endif // SE_SIZE_H
