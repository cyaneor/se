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
 * @def se_ptr_get_addr
 * @brief Преобразует указатель в числовой адрес.
 *
 * Преобразует указатель `ptr` в адрес типа `se_uaddr_t`.
 *
 * @param ptr Указатель для преобразования.
 * @return Адрес в виде `se_uaddr_t`.
 * @see se_addr_from_ptr
 */
#define se_ptr_get_addr(ptr) se_addr_from_ptr(ptr)

/**
 * @def se_ptr_to_diff
 * @brief Преобразует указатель в тип разницы указателей.
 *
 * Преобразует указатель `ptr` в тип `se_ptrdiff_t` для вычисления разницы адресов.
 *
 * @param ptr Указатель для преобразования.
 * @return Значение типа `se_ptrdiff_t`.
 */
#define se_ptr_to_diff(ptr) se_static_cast(se_ptrdiff_t, ptr)

/**
 * @def se_ptr_diff
 * @brief Вычисляет разницу между двумя указателями в байтах.
 *
 * Вычисляет разницу между адресами `ptr1` и `ptr2` в виде целого числа.
 *
 * @param ptr1 Первый указатель.
 * @param ptr2 Второй указатель.
 * @return Разница в байтах между `ptr1` и `ptr2`.
 */
#define se_ptr_diff(ptr1, ptr2) (se_ptr_to_diff(ptr1) - se_ptr_to_diff(ptr2))

/**
 * @def se_ptr_addr_diff
 * @brief Вычисляет разницу адресов двух указателей.
 *
 * Преобразует указатели в адреса и вычисляет их разницу в виде `se_uaddr_t`.
 *
 * @param ptr1 Первый указатель.
 * @param ptr2 Второй указатель.
 * @return Разница адресов в виде `se_uaddr_t`.
 * @see se_ptr_get_addr
 */
#define se_ptr_addr_diff(ptr1, ptr2) se_addr_diff(se_ptr_get_addr(ptr1), se_ptr_get_addr(ptr2))

/**
 * @def se_ptr_shift_unsafe
 * @brief Смещает указатель на заданное количество байтов без проверки NULL.
 *
 * Прибавляет смещение `offset` к указателю `ptr` типа `T` без проверки на NULL.
 *
 * @param T Тип указателя.
 * @param ptr Указатель для смещения.
 * @param offset Смещение в байтах.
 * @return Новый указатель после смещения.
 */
#define se_ptr_shift_unsafe(T, ptr, offset) se_addr_to_ptr(T, (se_ptr_get_addr(ptr) + offset))

/**
 * @def se_ptr_add_ptr_unsafe
 * @brief Добавляет адрес второго указателя к первому без проверки NULL.
 *
 * Прибавляет адрес `ptr2` к `ptr1` типа `T` без проверки на NULL.
 *
 * @param T Тип указателя `ptr1`.
 * @param ptr1 Указатель для смещения.
 * @param ptr2 Указатель, преобразуемый в смещение.
 * @return Новый указатель после смещения.
 */
#define se_ptr_add_ptr_unsafe(T, ptr1, ptr2) se_ptr_shift_unsafe(T, ptr1, se_ptr_get_addr(ptr2))

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
 * @def se_ptr_add_ptr
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
#define se_ptr_add_ptr(T, ptr1, ptr2) se_ptr_shift(T, ptr1, se_ptr_get_addr(ptr2))

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
#define se_ptr_subtract_unsafe(T, ptr, offset) se_addr_to_ptr(T, (se_ptr_get_addr(ptr) - offset))

/**
 * @def se_ptr_sub_ptr_unsafe
 * @brief Вычитает адрес второго указателя из первого без проверки NULL.
 *
 * Вычитает адрес `ptr2` из `ptr1` типа `T` без проверки на NULL.
 *
 * @param T Тип указателя `ptr1`.
 * @param ptr1 Указатель для смещения.
 * @param ptr2 Указатель, преобразуемый в смещение.
 * @return Новый указатель после вычитания.
 */
#define se_ptr_sub_ptr_unsafe(T, ptr1, ptr2) se_ptr_subtract_unsafe(T, ptr1, se_ptr_get_addr(ptr2))

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
 * @def se_ptr_sub_ptr
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
#define se_ptr_sub_ptr(T, ptr1, ptr2) se_ptr_subtract(T, ptr1, se_ptr_get_addr(ptr2))

/**
 * @def se_ptr_check_alignment
 * @brief Проверяет выравнивание указателя.
 *
 * Проверяет, выровнен ли адрес указателя `ptr` по значению `align`.
 *
 * @param ptr Указатель для проверки.
 * @param align Значение выравнивания.
 * @return `true`, если указатель выровнен, иначе `false`.
 * @note `align` не должно быть нулевым.
 */
#define se_ptr_check_alignment(ptr, align) se_addr_is_aligned(se_ptr_get_addr(ptr), align)

/**
 * @def se_ptr_align_upward
 * @brief Выравнивает указатель вверх по заданному размеру.
 *
 * Выравнивает `ptr` вверх до кратного `type_size` относительно `begin`.
 *
 * @param T Тип указателя.
 * @param ptr Указатель для выравнивания.
 * @param begin Базовый указатель для вычисления смещения.
 * @param type_size Размер для выравнивания.
 * @return Выровненный указатель.
 */
#define se_ptr_align_upward(T, ptr, begin, type_size)                                              \
    se_ptr_shift(T, ptr, (type_size - (se_ptr_diff(ptr, begin) % type_size)) % type_size)

/**
 * @def se_ptr_align_downward
 * @brief Выравнивает указатель вниз по заданному размеру.
 *
 * Выравнивает `ptr` вниз до кратного `type_size` относительно `begin`.
 *
 * @param T Тип указателя.
 * @param ptr Указатель для выравнивания.
 * @param begin Базовый указатель для вычисления смещения.
 * @param type_size Размер для выравнивания.
 * @return Выровненный указатель.
 */
#define se_ptr_align_downward(T, ptr, begin, type_size)                                            \
    se_ptr_subtract(T, ptr, (se_ptr_diff(ptr, begin) % type_size))

#endif // SE_PTR_UTIL_H