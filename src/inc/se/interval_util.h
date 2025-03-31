/**
 * @file interval_util.h
 * @brief Набор макросов для работы с интервалами.
 *
 * Этот файл содержит макросы для проверки валидности интервалов с различными типами границ
 * (замкнутые, открытые, левые и правые открытые границы) и для проверки, находится ли
 * значение внутри интервала с указанными типами границ.
 *
 * Макросы позволяют легко проверять, является ли интервал валидным
 * и содержится ли значение в интервале с учетом типа границ.
 */

#ifndef SE_INTERVAL_UTIL_H
#define SE_INTERVAL_UTIL_H

/**
 * @def se_interval_valid_closed
 * @brief Проверяет, является ли интервал с замкнутыми границами валидным.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 *
 * @return Возвращает значение выражения `lower <= upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_valid_closed(lower, upper) (lower <= upper)

/**
 * @def se_interval_valid_lopen
 * @brief Проверяет, является ли интервал с левой открытой границей валидным.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 *
 * @return Возвращает значение выражения `lower < upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_valid_lopen(lower, upper) (lower < upper)

/**
 * @def se_interval_valid_ropen
 * @brief Проверяет, является ли интервал с правой открытой границей валидным.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 *
 * @return Возвращает значение выражения `lower <= upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_valid_ropen(lower, upper) (lower <= upper)

/**
 * @def se_interval_valid_open
 * @brief Проверяет, является ли интервал с обеими открытыми границами валидным.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 *
 * @return Возвращает значение выражения `lower < upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_valid_open(lower, upper) (lower < upper)

/**
 * @def se_interval_within_closed
 * @brief Проверяет, содержится ли значение в замкнутом интервале.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале [lower, upper],
 *         и `false` в противном случае.
 */
#define se_interval_within_closed(lower, upper, value) ((value) >= (lower) && (value) <= (upper))

/**
 * @def se_interval_within_lopen
 * @brief Проверяет, содержится ли значение в интервале с левой открытой границей.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале (lower, upper],
 *         и `false` в противном случае.
 */
#define se_interval_within_lopen(lower, upper, value) ((value) > (lower) && (value) <= (upper))

/**
 * @def se_interval_within_ropen
 * @brief Проверяет, содержится ли значение в интервале с правой открытой границей.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале [lower, upper),
 *         и `false` в противном случае.
 */
#define se_interval_within_ropen(lower, upper, value) ((value) >= (lower) && (value) < (upper))

/**
 * @def se_interval_within_open
 * @brief Проверяет, содержится ли значение в интервале с обеими открытыми границами.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале (lower, upper),
 *         и `false` в противном случае.
 */
#define se_interval_within_open(lower, upper, value) ((value) > (lower) && (value) < (upper))

/**
 * @def se_interval_contains_closed
 * @brief Проверяет, содержится ли второй замкнутый интервал в первом замкнутом интервале.
 */
#define se_interval_contains_closed(outer_lower, outer_upper, inner_lower, inner_upper)            \
    (se_interval_within_closed((outer_lower), (outer_upper), (inner_lower)) &&                     \
     se_interval_within_closed((outer_lower), (outer_upper), (inner_upper)))

/**
 * @def se_interval_contains_open
 * @brief Проверяет, содержится ли второй открытый интервал в первом открытом интервале.
 */
#define se_interval_contains_open(outer_lower, outer_upper, inner_lower, inner_upper)              \
    (se_interval_within_open((outer_lower), (outer_upper), (inner_lower)) &&                       \
     se_interval_within_open((outer_lower), (outer_upper), (inner_upper)))

/**
 * @def se_interval_contains_lopen
 * @brief Проверяет, содержится ли второй левый-открытый интервал в первом интервале.
 */
#define se_interval_contains_lopen(outer_lower, outer_upper, inner_lower, inner_upper)             \
    (se_interval_within_lopen((outer_lower), (outer_upper), (inner_lower)) &&                      \
     se_interval_within_lopen((outer_lower), (outer_upper), (inner_upper)))

/**
 * @def se_interval_contains_ropen
 * @brief Проверяет, содержится ли второй правый-открытый интервал в первом интервале.
 */
#define se_interval_contains_ropen(outer_lower, outer_upper, inner_lower, inner_upper)             \
    (se_interval_within_ropen((outer_lower), (outer_upper), (inner_lower)) &&                      \
     se_interval_within_ropen((outer_lower), (outer_upper), (inner_upper)))

#endif // SE_INTERVAL_UTIL_H