#ifndef SE_TYPE_UTIL_H
#define SE_TYPE_UTIL_H

/**
 * @def se_type_size(T)
 * @brief Вычисляет размер типа в байтах.
 *
 * @param T Тип данных, размер которого нужно определить.
 * @return Размер типа T в байтах (результат sizeof).
 *
 * Пример использования:
 * @code
 * int size = se_type_size(int); // Вернёт 4 для 32-битного int
 * @endcode
 */
#define se_type_size(T) (sizeof(T))

/**
 * @def se_type_bits(T)
 * @brief Вычисляет количество битов в типе T.
 *
 * @param T Тип данных, для которого определяется количество битов.
 * @return Количество битов в типе T (sizeof(T) * 8).
 *
 * Пример использования:
 * @code
 * int bits = se_type_bits(int); // Вернёт 32 для 32-битного int
 * @endcode
 */
#define se_type_bits(T) (se_type_size(T) * 8)

#endif // SE_TYPE_UTIL_H
