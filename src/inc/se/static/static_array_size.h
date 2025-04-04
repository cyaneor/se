/**
 * @file static_array_size.h
 * @brief Заголовочный файл для макроса вычисления количества элементов в массиве.
 *
 * Этот файл содержит определение макроса `se_static_array_size`,
 * который позволяет вычислить количество элементов в статическом массиве.
 *
 * Макрос основан на использовании оператора `sizeof`
 * для получения размера массива и его первого элемента.
 */

#ifndef SE_STATIC_ARRAY_SIZE_H
#define SE_STATIC_ARRAY_SIZE_H

#ifdef __cplusplus
#    include "size.h"
/**
 * @brief Функция для получения размера массива.
 *
 * Эта функция возвращает количество элементов в статическом массиве.
 * Она использует размер массива, переданный как параметр,
 * и возвращает его как константное выражение.
 *
 * @tparam T Тип элементов массива.
 * @tparam N Размер массива.
 * @param arr Массив, размер которого нужно получить.
 * @return Размер массива.
 *
 * Пример использования:
 * @code
 * int arr[5];
 * constexpr auto size = se_static_array_size(arr); // size == 5
 * @endcode
 */
template <typename T, se_usize_t N>
inline constexpr auto
se_static_array_size(const T (&)[N])
{
    return N;
}
#else
/**
 * @def se_static_array_size
 * @brief Вычисляет количество элементов в массиве.
 *
 * Этот макрос позволяет получить количество элементов в статическом массиве
 * путем деления общего размера массива на размер его первого элемента.
 *
 * @param x Массив, для которого нужно вычислить размер.
 * @return Количество элементов в массиве.
 *
 * @note Используйте этот макрос только с статическими массивами.
 *       Не применяйте его к указателям, так как это приведет
 *       к некорректному вычислению размера.
 */
#    define se_static_array_size(x) (sizeof(x) / sizeof(x[0]))
#endif // __cplusplus

#endif // SE_STATIC_ARRAY_SIZE_H
