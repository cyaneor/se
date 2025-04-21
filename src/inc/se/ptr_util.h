/**
 * @file ptr_util.h
 * @brief Утилиты для операций с указателями и их арифметикой.
 *
 * Этот файл предоставляет макросы для манипуляций с указателями:
 * преобразование типов, вычисление разниц, смещение, выравнивание.
 * Поддерживаются как безопасные (с проверкой NULL), так и небезопасные операции.
 */

#ifndef SE_PTR_UTIL_H
#define SE_PTR_UTIL_H

#include "addr_util.h"
#include "interval_util.h"
#include "nullptr.h"
#include "ptrdiff.h"
#include "static_cast.h"

/**
 * @def se_ptr_cast
 * @brief Приводит указатель к заданному типу.
 *
 * Преобразует указатель `ptr` к типу `T *`
 * с использованием безопасного приведения типов.
 *
 * @param T Целевой тип указателя.
 * @param ptr Указатель для преобразования.
 * @return Указатель типа `T *`, соответствующий `ptr`.
 */
#define se_ptr_cast(T, ptr) se_static_cast(T *, ptr)

/**
 * @def se_ptr_to_addr
 * @brief Преобразует указатель в числовой адрес.
 *
 * Преобразует указатель `ptr` в адрес типа `se_uaddr_t`.
 *
 * @param ptr Указатель для преобразования.
 * @return Адрес в виде `se_uaddr_t`.
 */
#define se_ptr_to_addr(ptr) se_addr_from_ptr(ptr)

/**
 * @def se_ptr_to_diff
 * @brief Преобразует указатель в тип разницы указателей.
 *
 * Преобразует указатель `ptr` в тип `se_ptrdiff_t`
 * для вычисления разницы адресов.
 *
 * @param ptr Указатель для преобразования.
 * @return Значение типа `se_ptrdiff_t`.
 */
#define se_ptr_to_diff(ptr) se_static_cast(se_ptrdiff_t, ptr)

/**
 * @def se_ptr_diff
 * @brief Вычисляет разницу между двумя указателями в байтах.
 *
 * Вычисляет разницу между адресами `ptr1` и `ptr2`
 * в виде целого числа.
 *
 * @param ptr1 Первый указатель.
 * @param ptr2 Второй указатель.
 * @return Разница в байтах между `ptr1` и `ptr2`.
 */
#define se_ptr_diff(ptr1, ptr2) (se_ptr_to_diff(ptr1) - se_ptr_to_diff(ptr2))

/**
 * @def se_ptr_to_addr_diff
 * @brief Вычисляет разницу адресов двух указателей.
 *
 * Преобразует указатели в адреса
 * и вычисляет их разницу в виде `se_uaddr_t`.
 *
 * @param ptr1 Первый указатель.
 * @param ptr2 Второй указатель.
 * @return Разница адресов в виде `se_uaddr_t`.
 */
#define se_ptr_to_addr_diff(ptr1, ptr2) se_addr_diff(se_ptr_to_addr(ptr1), se_ptr_to_addr(ptr2))

/**
 * @def se_ptr_shift_unsafe
 * @brief Смещает указатель
 *        на заданное количество байтов без проверки NULL.
 *
 * Прибавляет смещение `offset`
 * к указателю `ptr` типа `T` без проверки на NULL.
 *
 * @param T Тип указателя.
 * @param ptr Указатель для смещения.
 * @param offset Смещение в байтах.
 * @return Новый указатель после смещения.
 */
#define se_ptr_shift_unsafe(T, ptr, offset) se_addr_to_ptr(T, (se_ptr_to_addr(ptr) + offset))

/**
 * @def se_ptr_add_unsafe
 * @brief Добавляет адрес второго указателя к первому без проверки NULL.
 *
 * Прибавляет адрес `ptr2`
 * к `ptr1` типа `T` без проверки на NULL.
 *
 * @param T Тип указателя `ptr1`.
 * @param ptr1 Указатель для смещения.
 * @param ptr2 Указатель, преобразуемый в смещение.
 * @return Новый указатель после смещения.
 */
#define se_ptr_add_unsafe(T, ptr1, ptr2) se_ptr_shift_unsafe(T, ptr1, se_ptr_to_addr(ptr2))

/**
 * @def se_ptr_shift
 * @brief Смещает указатель на заданное количество байтов с проверкой NULL.
 *
 * Прибавляет смещение `offset` к указателю `ptr` типа `T`,
 * возвращает NULL, если `ptr` нулевой.
 *
 * @param T Тип указателя.
 * @param ptr Указатель для смещения.
 * @param offset Смещение в байтах.
 * @return Новый указатель или NULL, если `ptr` нулевой.
 */
#define se_ptr_shift(T, ptr, offset) (ptr == nullptr ? ptr : se_ptr_shift_unsafe(T, ptr, offset))

/**
 * @def se_ptr_add
 * @brief Добавляет адрес второго указателя к первому с проверкой NULL.
 *
 * Прибавляет адрес `ptr2` к `ptr1` типа `T`,
 * возвращает NULL, если `ptr1` нулевой.
 *
 * @param T Тип указателя `ptr1`.
 * @param ptr1 Указатель для смещения.
 * @param ptr2 Указатель, преобразуемый в смещение.
 * @return Новый указатель или NULL, если `ptr1` нулевой.
 */
#define se_ptr_add(T, ptr1, ptr2) se_ptr_shift(T, ptr1, se_ptr_to_addr(ptr2))

/**
 * @def se_ptr_subtract_unsafe
 * @brief Вычитает смещение из указателя без проверки NULL.
 *
 * Вычитает смещение `offset`
 * из указателя `ptr` типа `T` без проверки на NULL.
 *
 * @param T Тип указателя.
 * @param ptr Указатель для смещения.
 * @param offset Смещение в байтах.
 * @return Новый указатель после вычитания.
 */
#define se_ptr_subtract_unsafe(T, ptr, offset) se_addr_to_ptr(T, (se_ptr_to_addr(ptr) - offset))

/**
 * @def se_ptr_sub_unsafe
 * @brief Вычитает адрес второго указателя из первого без проверки NULL.
 *
 * Вычитает адрес `ptr2`
 * из `ptr1` типа `T` без проверки на NULL.
 *
 * @param T Тип указателя `ptr1`.
 * @param ptr1 Указатель для смещения.
 * @param ptr2 Указатель, преобразуемый в смещение.
 * @return Новый указатель после вычитания.
 */
#define se_ptr_sub_unsafe(T, ptr1, ptr2) se_ptr_subtract_unsafe(T, ptr1, se_ptr_to_addr(ptr2))

/**
 * @def se_ptr_subtract
 * @brief Вычитает смещение из указателя с проверкой NULL.
 *
 * Вычитает смещение `offset` из указателя `ptr` типа `T`,
 * возвращает NULL, если `ptr` нулевой.
 *
 * @param T Тип указателя.
 * @param ptr Указатель для смещения.
 * @param offset Смещение в байтах.
 * @return Новый указатель или NULL, если `ptr` нулевой.
 */
#define se_ptr_subtract(T, ptr, offset)                                                            \
    (ptr == nullptr ? ptr : se_ptr_subtract_unsafe(T, ptr, offset))

/**
 * @def se_ptr_sub
 * @brief Вычитает адрес второго указателя из первого с проверкой NULL.
 *
 * Вычитает адрес `ptr2` из `ptr1` типа `T`,
 * возвращает NULL, если `ptr1` нулевой.
 *
 * @param T Тип указателя `ptr1`.
 * @param ptr1 Указатель для смещения.
 * @param ptr2 Указатель, преобразуемый в смещение.
 * @return Новый указатель или NULL, если `ptr1` нулевой.
 */
#define se_ptr_sub(T, ptr1, ptr2) se_ptr_subtract(T, ptr1, se_ptr_to_addr(ptr2))

/**
 * @def se_ptr_is_aligned
 * @brief Проверяет выравнивание указателя.
 *
 * Проверяет,
 * выровнен ли адрес указателя `ptr` по значению `align`.
 *
 * @param ptr Указатель для проверки.
 * @param align Значение выравнивания.
 * @return `true`, если указатель выровнен, иначе `false`.
 * @note `align` не должно быть нулевым.
 */
#define se_ptr_is_aligned(ptr, align) se_addr_is_aligned(se_ptr_to_addr(ptr), align)

/**
 * @def se_ptr_align_up
 * @brief Выравнивает указатель вверх по заданному размеру.
 *
 * Выравнивает `ptr` вверх
 * до кратного `type_size` относительно `begin`.
 *
 * @param T Тип указателя.
 * @param ptr Указатель для выравнивания.
 * @param begin Базовый указатель для вычисления смещения.
 * @param type_size Размер для выравнивания.
 * @return Выровненный указатель.
 */
#define se_ptr_align_up(T, ptr, begin, type_size)                                                  \
    se_ptr_shift(T, ptr, (type_size - (se_ptr_diff(ptr, begin) % type_size)) % type_size)

/**
 * @def se_ptr_align_down
 * @brief Выравнивает указатель вниз по заданному размеру.
 *
 * Выравнивает `ptr` вниз
 * до кратного `type_size` относительно `begin`.
 *
 * @param T Тип указателя.
 * @param ptr Указатель для выравнивания.
 * @param begin Базовый указатель для вычисления смещения.
 * @param type_size Размер для выравнивания.
 * @return Выровненный указатель.
 */
#define se_ptr_align_down(T, ptr, begin, type_size)                                                \
    se_ptr_subtract(T, ptr, (se_ptr_diff(ptr, begin) % type_size))

/**
 * @def se_ptr_within_range
 * @brief Проверяет, находится ли указатель в пределах заданного диапазона.
 *
 * Проверяет, лежит ли указатель `ptr` в диапазоне от `begin` до `end` (включительно).
 * Использует `se_interval_within_closed` для проверки принадлежности с замкнутыми границами.
 *
 * @param begin Начало диапазона.
 * @param end Конец диапазона.
 * @param ptr Указатель для проверки.
 * @return `true`, если `ptr` находится в диапазоне [begin, end], иначе `false`.
 *
 * @see se_interval_within_closed
 */
#define se_ptr_within_range(begin, end, ptr) se_interval_within_closed(begin, end, ptr)

/**
 * @def se_ptr_pair_is_aligned
 * @brief Проверяет выравнивание двух указателей по заданному значению.
 *
 * @param ptr1 Первый указатель.
 * @param ptr2 Второй указатель.
 * @param align Значение выравнивания.
 * @return `true`, если оба указателя выровнены по `align`, иначе `false`.
 *
 * @note Выравнивание `align` не должно быть нулевым.
 */
#define se_ptr_pair_is_aligned(ptr1, ptr2, align)                                                  \
    (se_ptr_is_aligned(ptr1, align) && se_ptr_is_aligned(ptr2, align))

/**
 * @def se_ptr_ranges_is_aligned
 * @brief Проверяет выравнивание двух диапазонов указателей.
 *
 * @param r1_begin Начало первого диапазона.
 * @param r1_end Конец первого диапазона.
 * @param r2_begin Начало второго диапазона.
 * @param r2_end Конец второго диапазона.
 * @param align Значение выравнивания.
 * @return `true`, если оба диапазона выровнены, иначе `false`.
 *
 * @note Выравнивание `align` не должно быть нулевым.
 */
#define se_ptr_ranges_is_aligned(r1_begin, r1_end, r2_begin, r2_end, align)                        \
    (se_ptr_pair_is_aligned(r1_begin, r1_end, align) &&                                            \
     se_ptr_pair_is_aligned(r2_begin, r2_end, align))

/**
 * @def se_ptr_ranges_no_overlap
 * @brief Проверяет, не пересекаются ли два диапазона.
 *
 * @param r1_begin Начало первого диапазона.
 * @param r2_begin Начало второго диапазона.
 * @param r2_end Конец второго диапазона.
 * @return `true`, если диапазоны не пересекаются, иначе `false`.
 */
#define se_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end)                                       \
    ((r1_begin <= r2_begin) || (r2_end <= r1_begin))

/**
 * @def se_ptr_ranges_is_overlap
 * @brief Проверяет, пересекаются ли два диапазона.
 *
 * @param r1_begin Начало первого диапазона.
 * @param r2_begin Начало второго диапазона.
 * @param r2_end Конец второго диапазона.
 * @return `true`, если диапазоны пересекаются, иначе `false`.
 */
#define se_ptr_ranges_is_overlap(r1_begin, r2_begin, r2_end)                                       \
    (!se_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end))

/**
 * @def se_ptr_range_get_size
 * @brief Вычисляет количество элементов заданного типа в диапазоне.
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
#define se_ptr_range_get_size(begin, end, type_size) (se_ptr_to_addr_diff(end, begin) / (type_size))

/**
 * @def se_ptr_range_is_valid
 * @brief Проверяет валидность диапазона указателей.
 *
 * @param begin Начало диапазона.
 * @param end Конец диапазона.
 * @return `true`, если диапазон валиден, иначе `false`.
 *
 * @see se_interval_check_valid_closed
 */
#define se_ptr_range_is_valid(begin, end) (begin && se_interval_valid_closed(begin, end))

/**
 * @def se_ptr_range_within
 * @brief Проверяет, содержится ли один замкнутый интервал указателей
 *        в другом замкнутом интервале указателей.
 *
 * Данный макрос использует `se_interval_contains_closed` для проверки,
 * находится ли интервал, определяемый указателями `r2_begin` и `r2_end`,
 * полностью внутри интервала, определяемого указателями `r1_begin` и `r1_end`.
 *
 * @param r1_begin Начало первого интервала (внешнего).
 * @param r1_end Конец первого интервала (внешнего).
 * @param r2_begin Начало второго интервала (внутреннего).
 * @param r2_end Конец второго интервала (внутреннего).
 *
 * @return Возвращает `true`, если интервал [r2_begin, r2_end]
 *         содержится в интервале [r1_begin, r1_end], и `false` в противном случае.
 */
#define se_ptr_range_within(r1_begin, r1_end, r2_begin, r2_end)                                    \
    se_interval_contains_closed(r1_begin, r1_end, r2_begin, r2_end)

/**
 * @def se_ptr_ranges_is_valid
 * @brief Проверяет валидность двух диапазонов указателей.
 *
 * @param r1_begin Начало первого диапазона.
 * @param r1_end Конец первого диапазона.
 * @param r2_begin Начало второго диапазона.
 * @param r2_end Конец второго диапазона.
 * @return `true`, если оба диапазона валидны, иначе `false`.
 */
#define se_ptr_ranges_is_valid(r1_begin, r1_end, r2_begin, r2_end)                                 \
    (se_ptr_range_is_valid(r1_begin, r1_end) && se_ptr_range_is_valid(r2_begin, r2_end))

#endif // SE_PTR_UTIL_H