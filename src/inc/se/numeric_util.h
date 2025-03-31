#ifndef SE_NUMERIC_UTIL_H
#define SE_NUMERIC_UTIL_H

/**
 * @def se_numeric_is_nonzero
 * @brief Проверяет, является ли значение ненулевым.
 *
 * Этот макрос выполняет простую проверку, сравнивая входное значение с нулём.
 * Используется в ситуациях, где требуется убедиться, что значение не равно нулю,
 * например, для валидации входных данных или условий.
 *
 * @param x Входное значение (может быть любого числового типа).
 * @return 1 (true), если x не равно 0, иначе 0 (false).
 *
 * Пример использования:
 * @code
 * int value = 5;
 * if (se_numeric_is_nonzero(value)) {
 *     printf("Value is non-zero: %d\n", value); // Вывод: "Value is non-zero: 5"
 * }
 * @endcode
 */
#define se_numeric_is_nonzero(x) ((x) != 0)

/**
 * @def se_numeric_subtract_one
 * @brief Уменьшает входное значение на 1.
 *
 * Этот макрос вычитает единицу из переданного значения. Может использоваться
 * в арифметических операциях, циклах или для подготовки данных к дальнейшим
 * вычислениям, например, в побитовых операциях.
 *
 * @param x Входное значение (может быть любого числового типа).
 * @return Значение x, уменьшенное на 1.
 *
 * Пример использования:
 * @code
 * int value = 10;
 * int result = se_numeric_subtract_one(value);
 * printf("Value minus one: %d\n", result); // Вывод: "Value minus one: 9"
 * @endcode
 */
#define se_numeric_subtract_one(x) ((x)-1)

/**
 * @def se_numeric_no_remainder
 * @brief Проверяет, является ли число кратным заданному делителю.
 *
 * Этот макрос принимает значение и делитель, и возвращает
 * логическое значение, указывающее, является ли `value`
 * кратным `divisor`.
 *
 * @param value Число, которое необходимо проверить.
 * @param divisor Делитель, на который проверяется кратность.
 *
 * @return `true`, если `value` кратно `divisor`;
 *         `false` в противном случае.
 *
 * @note Делитель не должен быть равен нулю,
 *       так как это приведет к неопределенному поведению.
 */
#define se_numeric_no_remainder(value, divisor) ((value % divisor) == 0)

#endif // SE_NUMERIC_UTIL_H
