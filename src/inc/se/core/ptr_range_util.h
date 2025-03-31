/**
 * @file ptr_range_util.h
 * @brief Утилиты для работы с диапазонами указателей.
 *
 * Этот файл содержит макросы для работы с диапазонами указателей,
 * включая проверку их принадлежности, выравнивания, пересечения и размера.
 *
 * Макросы предоставляют функциональность для:
 * - проверки принадлежности указателя диапазону;
 * - проверки выравнивания указателей и диапазонов;
 * - определения пересечения двух диапазонов;
 * - проверки валидности диапазонов;
 * - вычисления размера диапазона в количестве элементов.
 */

#ifndef SE_PTR_RANGE_UTIL_H
#define SE_PTR_RANGE_UTIL_H

#include "interval_util.h"
#include "ptr_util.h"

/**
 * @def se_ptr_range_contains
 * @brief Проверяет, находится ли указатель в пределах заданного диапазона.
 *
 * Проверяет, лежит ли указатель `ptr` в диапазоне от `begin` до `end` (включительно).
 * Использует `se_interval_has_closed` для проверки принадлежности с замкнутыми границами.
 *
 * @param begin Начало диапазона.
 * @param end Конец диапазона.
 * @param ptr Указатель для проверки.
 * @return `true`, если `ptr` находится в диапазоне [begin, end], иначе `false`.
 *
 * @see se_interval_has_closed
 */
#define se_ptr_range_contains(begin, end, ptr) se_interval_has_closed(begin, end, ptr)

/**
 * @def se_ptr_range_check_alignment
 * @brief Проверяет выравнивание двух указателей по заданному значению.
 *
 * Проверяет, выровнены ли адреса указателей `ptr1` и `ptr2` по заданному `align`.
 *
 * @param ptr1 Первый указатель.
 * @param ptr2 Второй указатель.
 * @param align Значение выравнивания.
 * @return `true`, если оба указателя выровнены по `align`, иначе `false`.
 *
 * @note Выравнивание `align` не должно быть нулевым.
 */
#define se_ptr_range_check_alignment(ptr1, ptr2, align)                                            \
    (se_ptr_check_alignment(ptr1, align) && se_ptr_check_alignment(ptr2, align))

/**
 * @def se_ptr_range_check_both_aligned
 * @brief Проверяет выравнивание двух диапазонов указателей.
 *
 * Проверяет, выровнены ли оба диапазона (`lhs`..`lhs_end` и `rhs`..`rhs_end`) по `align`.
 *
 * @param lhs Начало первого диапазона.
 * @param lhs_end Конец первого диапазона.
 * @param rhs Начало второго диапазона.
 * @param rhs_end Конец второго диапазона.
 * @param align Значение выравнивания.
 * @return `true`, если оба диапазона выровнены, иначе `false`.
 *
 * @note Выравнивание `align` не должно быть нулевым.
 */
#define se_ptr_range_check_both_aligned(lhs, lhs_end, rhs, rhs_end, align)                         \
    (se_ptr_range_check_alignment(lhs, lhs_end, align) &&                                          \
     se_ptr_range_check_alignment(rhs, rhs_end, align))

/**
 * @def se_ptr_range_no_overlap
 * @brief Проверяет, не пересекаются ли два диапазона.
 *
 * Определяет, не перекрываются ли диапазоны `lhs_begin` и `rhs_begin`..`rhs_end`.
 *
 * @param lhs_begin Начало первого диапазона.
 * @param rhs_begin Начало второго диапазона.
 * @param rhs_end Конец второго диапазона.
 * @return `true`, если диапазоны не пересекаются, иначе `false`.
 */
#define se_ptr_range_no_overlap(lhs_begin, rhs_begin, rhs_end)                                     \
    ((lhs_begin <= rhs_begin) || (rhs_end <= lhs_begin))

/**
 * @def se_ptr_range_overlaps
 * @brief Проверяет, пересекаются ли два диапазона.
 *
 * Определяет, перекрываются ли диапазоны `lhs_begin` и `rhs_begin`..`rhs_end`.
 *
 * @param lhs_begin Начало первого диапазона.
 * @param rhs_begin Начало второго диапазона.
 * @param rhs_end Конец второго диапазона.
 * @return `true`, если диапазоны пересекаются, иначе `false`.
 */
#define se_ptr_range_overlaps(lhs_begin, rhs_begin, rhs_end)                                       \
    (!se_ptr_range_no_overlap(lhs_begin, rhs_begin, rhs_end))

/**
 * @def se_ptr_range_element_count
 * @brief Вычисляет количество элементов заданного типа в диапазоне.
 *
 * Рассчитывает, сколько элементов размера `type_size` помещается между `begin` и `end`.
 *
 * @param begin Начало диапазона.
 * @param end Конец диапазона.
 * @param type_size Размер типа данных в байтах (например, sizeof(int)).
 * @return Количество элементов типа `type_size` в диапазоне.
 *
 * @note Указатели должны быть выровнены и в одном блоке памяти.
 *
 * Пример использования:
 * @code
 * int arr[] = {1, 2, 3, 4};
 * size_t count = se_ptr_range_element_count(arr, arr + 4, sizeof(int)); // вернёт 4
 * @endcode
 */
#define se_ptr_range_element_count(begin, end, type_size)                                          \
    (se_ptr_addr_diff(end, begin) / (type_size))

/**
 * @def se_ptr_range_validate
 * @brief Проверяет валидность диапазона указателей.
 *
 * Проверяет, что `begin` не NULL и диапазон `begin`..`end` валиден (замкнут).
 *
 * @param begin Начало диапазона.
 * @param end Конец диапазона.
 * @return `true`, если диапазон валиден, иначе `false`.
 *
 * @see se_interval_is_valid_closed
 */
#define se_ptr_range_validate(begin, end) (begin && se_interval_is_valid_closed(begin, end))

/**
 * @def se_ptr_range_validate_both
 * @brief Проверяет валидность двух диапазонов указателей.
 *
 * Проверяет, что оба диапазона (`r1_begin`..`r1_end` и `r2_begin`..`r2_end`) валидны.
 *
 * @param r1_begin Начало первого диапазона.
 * @param r1_end Конец первого диапазона.
 * @param r2_begin Начало второго диапазона.
 * @param r2_end Конец второго диапазона.
 * @return `true`, если оба диапазона валидны, иначе `false`.
 */
#define se_ptr_range_validate_both(r1_begin, r1_end, r2_begin, r2_end)                             \
    (se_ptr_range_validate(r1_begin, r1_end) && se_ptr_range_validate(r2_begin, r2_end))

#endif // SE_PTR_RANGE_UTIL_H