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
 * @def se_interval_check_valid_closed
 * @brief Проверяет, является ли интервал с замкнутыми границами валидным.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 *
 * @return Возвращает значение выражения `lower <= upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_check_valid_closed(lower, upper) (lower <= upper)

/**
 * @def se_interval_check_valid_left_open
 * @brief Проверяет, является ли интервал с левой открытой границей валидным.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 *
 * @return Возвращает значение выражения `lower < upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_check_valid_left_open(lower, upper) (lower < upper)

/**
 * @def se_interval_check_valid_right_open
 * @brief Проверяет, является ли интервал с правой открытой границей валидным.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 *
 * @return Возвращает значение выражения `lower <= upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_check_valid_right_open(lower, upper) (lower <= upper)

/**
 * @def se_interval_check_valid_open
 * @brief Проверяет, является ли интервал с обеими открытыми границами валидным.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 *
 * @return Возвращает значение выражения `lower < upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_check_valid_open(lower, upper) (lower < upper)

/**
 * @def se_interval_contains_closed
 * @brief Проверяет, содержится ли значение в замкнутом интервале.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале [lower, upper],
 *         и `false` в противном случае.
 */
#define se_interval_contains_closed(lower, upper, value) ((value) >= (lower) && (value) <= (upper))

/**
 * @def se_interval_contains_left_open
 * @brief Проверяет, содержится ли значение в интервале с левой открытой границей.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале (lower, upper],
 *         и `false` в противном случае.
 */
#define se_interval_contains_left_open(lower, upper, value)                                        \
    ((value) > (lower) && (value) <= (upper))

/**
 * @def se_interval_contains_right_open
 * @brief Проверяет, содержится ли значение в интервале с правой открытой границей.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале [lower, upper),
 *         и `false` в противном случае.
 */
#define se_interval_contains_right_open(lower, upper, value)                                       \
    ((value) >= (lower) && (value) < (upper))

/**
 * @def se_interval_contains_open
 * @brief Проверяет, содержится ли значение в интервале с обеими открытыми границами.
 *
 * @param lower Нижняя граница интервала.
 * @param upper Верхняя граница интервала.
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале (lower, upper),
 *         и `false` в противном случае.
 */
#define se_interval_contains_open(lower, upper, value) ((value) > (lower) && (value) < (upper))

/**
 * @def se_interval_check_valid_closed_reverse
 * @brief Проверяет, является ли обратный интервал с замкнутыми границами валидным.
 *
 * @param lower Нижняя граница интервала (больше верхней).
 * @param upper Верхняя граница интервала (меньше нижней).
 *
 * @return Возвращает значение выражения `lower >= upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_check_valid_closed_reverse(lower, upper) (lower >= upper)

/**
 * @def se_interval_check_valid_left_open_reverse
 * @brief Проверяет, является ли обратный интервал с левой открытой границей валидным.
 *
 * @param lower Нижняя граница интервала (больше верхней).
 * @param upper Верхняя граница интервала (меньше нижней).
 *
 * @return Возвращает значение выражения `lower > upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_check_valid_left_open_reverse(lower, upper) (lower > upper)

/**
 * @def se_interval_check_valid_right_open_reverse
 * @brief Проверяет, является ли обратный интервал с правой открытой границей валидным.
 *
 * @param lower Нижняя граница интервала (больше верхней).
 * @param upper Верхняя граница интервала (меньше нижней).
 *
 * @return Возвращает значение выражения `lower >= upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_check_valid_right_open_reverse(lower, upper) (lower >= upper)

/**
 * @def se_interval_check_valid_open_reverse
 * @brief Проверяет, является ли обратный интервал с обеими открытыми границами валидным.
 *
 * @param lower Нижняя граница интервала (больше верхней).
 * @param upper Верхняя граница интервала (меньше нижней).
 *
 * @return Возвращает значение выражения `lower > upper`,
 *         что истинно, если интервал валиден.
 */
#define se_interval_check_valid_open_reverse(lower, upper) (lower > upper)

/**
 * @def se_interval_contains_closed_reverse
 * @brief Проверяет, содержится ли значение в замкнутом обратном интервале.
 *
 * @param lower Нижняя граница интервала (больше верхней).
 * @param upper Верхняя граница интервала (меньше нижней).
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале [upper, lower],
 *         и `false` в противном случае.
 */
#define se_interval_contains_closed_reverse(lower, upper, value)                                   \
    ((value) >= (upper) && (value) <= (lower))

/**
 * @def se_interval_contains_left_open_reverse
 * @brief Проверяет, содержится ли значение в обратном интервале с левой открытой границей.
 *
 * @param lower Нижняя граница интервала (больше верхней).
 * @param upper Верхняя граница интервала (меньше нижней).
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале (upper, lower],
 *         и `false` в противном случае.
 */
#define se_interval_contains_left_open_reverse(lower, upper, value)                                \
    ((value) > (upper) && (value) <= (lower))

/**
 * @def se_interval_contains_right_open_reverse
 * @brief Проверяет, содержится ли значение в обратном интервале с правой открытой границей.
 *
 * @param lower Нижняя граница интервала (больше верхней).
 * @param upper Верхняя граница интервала (меньше нижней).
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале [upper, lower),
 *         и `false` в противном случае.
 */
#define se_interval_contains_right_open_reverse(lower, upper, value)                               \
    ((value) >= (upper) && (value) < (lower))

/**
 * @def se_interval_contains_open_reverse
 * @brief Проверяет, содержится ли значение в обратном интервале с обеими открытыми границами.
 *
 * @param lower Нижняя граница интервала (больше верхней).
 * @param upper Верхняя граница интервала (меньше нижней).
 * @param value Значение, которое проверяется на принадлежность интервалу.
 *
 * @return Возвращает `true`, если значение `value` лежит в интервале (upper, lower),
 *         и `false` в противном случае.
 */
#define se_interval_contains_open_reverse(lower, upper, value)                                     \
    ((value) > (upper) && (value) < (lower))

#endif // SE_INTERVAL_UTIL_H