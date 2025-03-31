/**
 * @file runtime_throw_with_desc.h
 * @brief Заголовочный файл для макроса `se_runtime_throw_with_desc`.
 *
 * Этот файл содержит определение макроса `se_runtime_throw_with_desc`,
 * который предоставляет удобный способ выбрасывания исключений
 * в `runtime` с фиксированным кодом прерывания и описанием ошибки.
 *
 * Макрос предназначен для использования в ситуациях,
 * когда необходимо указать только текстовое описание ошибки,
 * позволяя разработчикам избежать необходимости явного указания кода ошибки.
 * Доступность макроса зависит от определения опции `SE_LIBRARY_OPTION_ERROR_DESC`.
 *
 * @note При использовании данного макроса важно следить за правильной
 *       инициализацией фреймов исключений, так как он зависит от
 *       корректной работы функции `se_runtime_throw`.
 *
 * @warning Если опция `SE_LIBRARY_OPTION_ERROR_DESC` не определена,
 *          макрос `se_runtime_throw_with_desc` будет недоступен.
 *
 * @see se_runtime_throw
 * @see se_runtime_except_frame_is_begin
 * @see se_except_frame_t
 * @see se_error_t
 * @see SE_RUNTIME_ERROR_INTERRUPT
 */

#ifndef SE_RUNTIME_THROW_DESC_H
#define SE_RUNTIME_THROW_DESC_H

#include "runtime_throw.h"
#include "runtime_error_code.h"

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
/**
 * @def se_runtime_throw_with_desc(desc, ...)
 * @brief Выбрасывает исключение в `runtime`
 *        с описанием ошибки и фиксированным кодом прерывания.
 *
 * Этот макрос является оберткой над `se_runtime_throw`, предназначенной для случаев,
 * когда требуется указать только описание ошибки без явного задания кода ошибки.
 *
 * Он доступен только при включенной опции `SE_LIBRARY_OPTION_ERROR_DESC`
 * и использует фиксированный код ошибки `SE_RUNTIME_ERROR_INTERRUPT`.
 *
 * Макрос передает управление предыдущему фрейму исключений через `longjmp`,
 * если текущий фрейм не является начальным (`se_runtime_except_frame_is_begin() == false`).
 *
 * @param desc Описание ошибки (строка), передаваемое в `se_runtime_throw`.
 * @param ... Значения, возвращаемые при прерывании выполнения (например, значение по умолчанию).
 *
 * @note Макрос доступен только если определена опция `SE_LIBRARY_OPTION_ERROR_DESC`.
 *       Код ошибки фиксирован как `SE_RUNTIME_ERROR_INTERRUPT`,
 *       что делает его подходящим для общих прерываний
 *       с информативным описанием.
 *
 * @see se_runtime_throw
 * @see se_runtime_except_frame_is_begin
 * @see se_except_frame_t
 * @see se_error_t
 * @see SE_RUNTIME_ERROR_INTERRUPT
 */
#    define se_runtime_throw_with_desc(desc, ...)                                                  \
        se_runtime_throw(SE_RUNTIME_ERROR_INTERRUPT, desc, __VA_ARGS__)
#else
#    error                                                                                         \
        "You must enable SE_LIBRARY_OPTION_ERROR_DESC option in CMake to use error description macros."
#endif // SE_LIBRARY_OPTION_ERROR_DESC

#endif // SE_RUNTIME_THROW_DESC_H
