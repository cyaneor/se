#ifndef SE_STR_UTIL_H
#define SE_STR_UTIL_H

#include "char_util.h"

/**
 * @def se_str_from_args
 * @brief Создаёт строковый литерал из переданных аргументов.
 *
 * Этот макрос оборачивает se_char_to_string, позволяя передавать переменное число аргументов.
 * Используется для удобного преобразования аргументов в строку.
 *
 * @param ... Переменное число аргументов, которые будут преобразованы в строку.
 * @return Строковый литерал, представляющий переданные аргументы.
 *
 * Пример использования:
 * @code
 * ```c
 * printf("%s\n", se_str_from_args(123));       // Вывод: "123"
 * printf("%s\n", se_str_from_args(x + y));     // Вывод: "x + y"
 * ```
 * @endcode
 */
#define se_str_from_args(...) se_char_to_string(__VA_ARGS__)

#endif // SE_STR_UTIL_H
