/**
 * @file memory.h
 * @brief Заголовочный файл для безопасной работы с памятью с проверкой размеров.
 *
 * Данный файл содержит объявления функций для операций с памятью,
 * которые принимают явные размеры буферов для предотвращения переполнений.
 * Все функции проверяют размеры буферов перед выполнением операций.
 *
 * Основные функции включают:
 * - Безопасное копирование данных между буферами
 * - Перемещение данных между перекрывающимися областями
 * - Сравнение блоков памяти с проверкой размеров
 * - Поиск подблоков в памяти с контролем границ
 * - Заполнение памяти с учетом размера буфера
 *
 * @see se_memory_copy
 * @see se_memory_move
 * @see se_memory_compare
 * @see se_memory_find
 * @see se_memory_set
 */

#ifndef SE_MEMORY_H
#define SE_MEMORY_H

#include "size.h"
#include "attribute.h"

SE_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Копирует данные из исходного буфера в целевой с проверкой размеров.
 *
 * Функция копирует данные из `src` в `dst`, проверяя что `dst_size >= src_size`.
 * Копирование выполняется от начала к концу с использованием оптимальных
 * методов копирования (SIMD инструкции при наличии).
 *
 * @param dst Указатель на целевой буфер
 * @param dst_size Размер целевого буфера в байтах
 * @param src Указатель на исходный буфер
 * @param src_size Размер копируемых данных в байтах
 * @return Указатель на `dst` в случае успеха, `NULL` если размеры недопустимы
 */
SE_ATTRIBUTE(SYMBOL)
void *
se_memory_copy(void *dst, se_usize_t dst_size, const void *src, se_usize_t src_size);

/**
 * @brief Копирует данные из исходного буфера в целевой с конца.
 *
 * Аналогична `se_memory_copy`, но копирование выполняется от конца к началу,
 * что полезно для перекрывающихся буферов когда `dst > src`.
 *
 * @param dst Указатель на целевой буфер
 * @param dst_size Размер целевого буфера в байтах
 * @param src Указатель на исходный буфер
 * @param src_size Размер копируемых данных в байтах
 * @return Указатель на dst в случае успеха, NULL если размеры недопустимы
 */
SE_ATTRIBUTE(SYMBOL)
void *
se_memory_copy_rev(void *dst, se_usize_t dst_size, const void *src, se_usize_t src_size);

/**
 * @brief Перемещает данные между буферами с проверкой размеров.
 *
 * Автоматически определяет направление копирования (вперед или назад)
 * для корректной работы с перекрывающимися областями памяти.
 * Проверяет что `dst_size >= src_size`.
 *
 * @param dst Указатель на целевой буфер
 * @param dst_size Размер целевого буфера в байтах
 * @param src Указатель на исходный буфер
 * @param src_size Размер перемещаемых данных в байтах
 * @return Указатель на `dst` в случае успеха, `NULL` если размеры недопустимы
 */
SE_ATTRIBUTE(SYMBOL)
void *
se_memory_move(void *dst, se_usize_t dst_size, const void *src, se_usize_t src_size);

/**
 * @brief Сравнивает два блока памяти с проверкой размеров.
 *
 * Сравнивает блоки памяти `lhs` и `rhs` побайтово, проверяя что `lhs_size == rhs_size`.
 * Использует оптимизированные методы сравнения (SIMD при наличии).
 *
 * @param lhs Указатель на первый блок памяти
 * @param lhs_size Размер первого блока
 * @param rhs Указатель на второй блок памяти
 * @param rhs_size Размер второго блока
 * @return Указатель на первое несовпадение или NULL если блоки идентичны
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_compare(const void *lhs, se_usize_t lhs_size, const void *rhs, se_usize_t rhs_size);

/**
 * @brief Сравнивает два блока памяти с конца с проверкой размеров.
 *
 * Аналогична `se_memory_compare`,
 * но сравнение выполняется от конца к началу.
 *
 * @param lhs Указатель на первый блок памяти
 * @param lhs_size Размер первого блока
 * @param rhs Указатель на второй блок памяти
 * @param rhs_size Размер второго блока
 * @return Указатель на первое несовпадение или `NULL` если блоки идентичны
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_compare_rev(const void *lhs, se_usize_t lhs_size, const void *rhs, se_usize_t rhs_size);

/**
 * @brief Ищет подблок в памяти с проверкой размеров.
 *
 * Ищет блок `rhs` в блоке `lhs`, проверяя что `rhs_size <= lhs_size`.
 * Поиск выполняется от начала к концу.
 *
 * @param lhs Указатель на блок памяти для поиска
 * @param lhs_size Размер блока для поиска
 * @param rhs Указатель на искомый блок
 * @param rhs_size Размер искомого блока
 * @return Указатель на первое вхождение или `NULL` если не найдено
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_find(const void *lhs, se_usize_t lhs_size, const void *rhs, se_usize_t rhs_size);

/**
 * @brief Ищет подблок в памяти
 *        с конца с проверкой размеров.
 *
 * Аналогична `se_memory_find`,
 * но поиск выполняется от конца к началу.
 *
 * @param lhs Указатель на блок памяти для поиска
 * @param lhs_size Размер блока для поиска
 * @param rhs Указатель на искомый блок
 * @param rhs_size Размер искомого блока
 * @return Указатель на первое вхождение или `NULL` если не найдено
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_find_rev(const void *lhs, se_usize_t lhs_size, const void *rhs, se_usize_t rhs_size);

/**
 * @brief Повторяет блок памяти
 *        в целевом блоке с проверкой размеров.
 *
 * Аналогична `se_memory_raw_repeat`,
 * но принимает размеры блоков вместо конечных указателей.
 *
 * @param dst Указатель на целевой блок памяти
 * @param dst_size Размер целевого блока
 * @param src Указатель на блок-источник для повторения
 * @param src_size Размер блока-источника
 * @return Указатель на целевой блок памяти
 */
SE_ATTRIBUTE(SYMBOL)
void *
se_memory_repeat(void *dst, se_usize_t dst_size, const void *src, se_usize_t src_size);

/**
 * @brief Заполняет блок памяти указанным значением.
 *
 * Аналогична `se_memory_std_set`,
 * выполняет заполнение памяти заданным байтовым значением.
 *
 * @param dst Указатель на целевой блок памяти
 * @param len Размер блока памяти в байтах
 * @param val Значение для заполнения (байт)
 * @return Указатель на целевой блок памяти
 */
SE_ATTRIBUTE(SYMBOL)
void *
se_memory_set(void *dst, se_usize_t len, se_u8_t val);

SE_COMPILER(EXTERN_C_END)

#endif // SE_MEMORY_H