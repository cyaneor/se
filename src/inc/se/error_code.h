/**
 * @file error_code.h
 * @brief Заголовочный файл для определения типа `se_error_code_t`
 *        и связанных с ним макросов.
 *
 * Этот файл предоставляет определение типа `se_error_code_t`,
 * используемого для представления кодов ошибок, возвращаемых функциями,
 * а также макросов, связанных с его диапазоном и размером.
 *
 * Файл служит основой для унифицированной обработки кодов ошибок,
 * позволяя разработчикам использовать стандартизированные значения
 * для обозначения ошибок и успешных состояний.
 */

#ifndef SE_ERROR_CODE_H
#define SE_ERROR_CODE_H

#include "return.h"

/**
 * @def SE_ERROR_CODE_T_SIZE
 * @brief Размер типа `se_error_code_t` в байтах.
 *
 * Макрос `SE_ERROR_CODE_T_SIZE` определяет размер (в байтах) типа `se_error_code_t`,
 * используя значение, установленное для `SE_RETURN_T_SIZE`.
 */
#define SE_ERROR_CODE_T_SIZE SE_RETURN_T_SIZE

/**
 * @def SE_ERROR_CODE_T_MIN
 * @brief Минимальное значение, которое может принимать `se_error_code_t`.
 *
 * Макрос `SE_ERROR_CODE_T_MIN` определяет минимально возможное значение
 * для типа `se_error_code_t`, используя значение `SE_RETURN_T_MIN`.
 */
#define SE_ERROR_CODE_T_MIN SE_RETURN_T_MIN

/**
 * @def SE_ERROR_CODE_T_MAX
 * @brief Максимальное значение, которое может принимать `se_error_code_t`.
 *
 * Макрос `SE_ERROR_CODE_T_MAX` определяет максимально возможное значение
 * для типа `se_error_code_t`, используя значение `SE_RETURN_T_MAX`.
 */
#define SE_ERROR_CODE_T_MAX SE_RETURN_T_MAX

/**
 * @def SE_ERROR_CODE_NONE
 * @brief Код, указывающий на отсутствие ошибки.
 *
 * Макрос `SE_ERROR_CODE_NONE` представляет собой значение 0,
 * указывающее на успешное выполнение или отсутствие ошибки.
 *
 * Используется в функциях, возвращающих `se_error_code_t`,
 * чтобы обозначить отсутствие ошибок.
 */
#define SE_ERROR_CODE_NONE 0

/**
 * @typedef se_error_code_t
 * @brief Определяет тип кода ошибки для функций.
 *
 * Тип `se_error_code_t` представляет собой псевдоним для `se_return_t` и используется
 * для обозначения кодов ошибок, возвращаемых функциями. Коды ошибок позволяют
 * легко определять и обрабатывать ситуации, когда выполнение функции
 * завершилось с ошибкой.
 *
 * Положительные значения `se_error_code_t` могут указывать на успешное выполнение
 * функции или различные состояния успешного завершения, в то время как
 * отрицательные значения служат для обозначения специфических ошибок.
 */
typedef se_return_t se_error_code_t;

#endif // SE_ERROR_CODE_H
