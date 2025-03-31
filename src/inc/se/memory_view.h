#ifndef SE_MEMORY_VIEW_H
#define SE_MEMORY_VIEW_H

#include "attribute.h"
#include "bool.h"
#include "offset.h"

/**
 * @struct se_memory_view
 * @brief Представление области памяти.
 *
 * Эта структура используется для описания диапазона памяти,
 * определяемого указателями на начало и конец.
 *
 * Она может быть полезна для работы с буферами,
 * массивами или любыми другими областями памяти,
 * где необходимо указать диапазон.
 */
typedef struct se_memory_view
{
    /**
     * @var se_memory_view::begin
     * @brief Указатель на начало области памяти.
     *
     * Этот указатель указывает на первый байт в области памяти,
     * которую представляет данная структура. Он должен быть
     * инициализирован перед использованием.
     */
    const void *begin;

    /**
     * @var se_memory_view::end
     * @brief Указатель на конец области памяти.
     *
     * Этот указатель указывает на байт, следующий за последним
     * байтом в области памяти. Это позволяет определить размер
     * области, а также избежать выхода за пределы при работе с ней.
     */
    const void *end;
} se_memory_view_t;

SE_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Возвращает указатель на начало области памяти из `se_memory_view_t`.
 * @param[in] self Указатель на se_memory_view_t.
 * @return self->begin или nullptr при ошибке.
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_view_get_begin(const se_memory_view_t *self);

/**
 * @brief Возвращает указатель на конец области памяти из se_memory_view_t.
 * @param[in] self Указатель на se_memory_view_t.
 * @return self->end или nullptr при ошибке.
 * @note Проверяет self на nullptr.
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_view_get_end(const se_memory_view_t *self);

/**
 * @brief Распаковывает указатели begin и end из se_memory_view_t.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[out] begin Указатель для записи начала (если не nullptr).
 * @param[out] end Указатель для записи конца (если не nullptr).
 */
SE_ATTRIBUTE(SYMBOL)
void
se_memory_view_unpack(const se_memory_view_t *self, const void **begin, const void **end);

/**
 * @brief Проверяет, пуста ли область памяти.
 * @param[in] self Указатель на se_memory_view_t.
 * @return true, если begin равен end.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_is_empty(const se_memory_view_t *self);

/**
 * @brief Проверяет валидность диапазона памяти.
 * @param[in] self Указатель на se_memory_view_t.
 * @return true, если диапазон корректен.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_is_valid(const se_memory_view_t *self);

/**
 * @brief Проверяет, содержит ли область указатель.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] ptr Указатель для проверки.
 * @return true, если ptr в пределах self.
 * @note Требует валидности self.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_contains_pointer(const se_memory_view_t *self, const void *ptr);

/**
 * @brief Проверяет, содержит ли одна область другую.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] other Указатель на другую se_memory_view_t.
 * @return true, если other целиком в self.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_contains(const se_memory_view_t *self, const se_memory_view_t *other);

/**
 * @brief Проверяет, содержит ли область заданный диапазон.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] begin Начало диапазона.
 * @param[in] end Конец диапазона.
 * @return true, если диапазон в self.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_contains_range(const se_memory_view_t *self, const void *begin, const void *end);

/**
 * @brief Возвращает размер области памяти.
 * @param[in] self Указатель на se_memory_view_t.
 * @return Размер в байтах.
 * @note Требует валидности self.
 */
SE_ATTRIBUTE(SYMBOL)
se_usize_t
se_memory_view_get_size(const se_memory_view_t *self);

/**
 * @brief Проверяет, кратен ли размер области заданному размеру элемента.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] element_size Размер элемента.
 * @return true, если размер кратен element_size.
 * @note Проверяет element_size на ноль.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_is_multiple_of(const se_memory_view_t *self, se_usize_t element_size);

/**
 * @brief Проверяет выравнивание указателей begin и end.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] alignment_size Размер выравнивания.
 * @return true, если оба указателя выровнены.
 * @note Проверяет alignment_size на ноль.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_is_aligned(const se_memory_view_t *self, se_usize_t alignment_size);

/**
 * @brief Проверяет, валиден ли смещение в области.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] offset Смещение в байтах.
 * @return true, если offset < размера области.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_is_valid_offset(const se_memory_view_t *self, se_uoffset_t offset);

/**
 * @brief Возвращает указатель на начало со смещением.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] offset Смещение в байтах.
 * @return Сдвинутый begin или nullptr при ошибке.
 * @note Проверяет валидность offset.
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_view_at_begin(const se_memory_view_t *self, se_uoffset_t offset);

/**
 * @brief Возвращает указатель на конец с обратным смещением.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] offset Смещение в байтах.
 * @return Сдвинутый end или nullptr при ошибке.
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_view_at_end(const se_memory_view_t *self, se_uoffset_t offset);

/**
 * @brief Возвращает указатель с учетом направления.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] offset Смещение.
 * @param[in] reversed true для конца, false для начала.
 * @return Сдвинутый указатель.
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_view_at(const se_memory_view_t *self, se_uoffset_t offset, bool reversed);

/**
 * @brief Возвращает первый элемент области.
 * @param[in] self Указатель на se_memory_view_t.
 * @return Указатель на begin.
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_view_get_first(const void *self);

/**
 * @brief Возвращает последний элемент области.
 * @param[in] self Указатель на se_memory_view_t.
 * @return Указатель на end - 1.
 */
SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_view_get_last(const void *self);

/**
 * @brief Сравнивает begin с указателем.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] ptr Указатель для сравнения.
 * @return true, если begin равен ptr.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_is_begin_equal(const se_memory_view_t *self, const void *ptr);

/**
 * @brief Сравнивает end с указателем.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] ptr Указатель для сравнения.
 * @return true, если end равен ptr.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_is_end_equal(const se_memory_view_t *self, const void *ptr);

/**
 * @brief Сравнивает begin двух областей.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] other Указатель на другую se_memory_view_t.
 * @return true, если begin совпадают.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_is_begin_equal_to(const se_memory_view_t *self, const se_memory_view_t *other);

/**
 * @brief Сравнивает end двух областей.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] other Указатель на другую se_memory_view_t.
 * @return true, если end совпадают.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_is_end_equal_to(const se_memory_view_t *self, const se_memory_view_t *other);

/**
 * @brief Сравнивает две области полностью.
 * @param[in] self Указатель на se_memory_view_t.
 * @param[in] other Указатель на другую se_memory_view_t.
 * @return true, если begin и end совпадают.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_memory_view_is_equal(const se_memory_view_t *self, const se_memory_view_t *other);

SE_COMPILER(EXTERN_C_END)

#endif // SE_MEMORY_VIEW_H
