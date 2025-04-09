/**
 * @file runtime_return_with_error.h
 * @brief Определение макроса для обработки ошибок и возврата из функций.
 *
 * Этот файл содержит определение макроса se_runtime_return_with_error, который упрощает
 * установку кода ошибки и возврат значения из функции в одной операции. Поведение макроса
 * зависит от наличия препроцессорного символа SE_LIBRARY_OPTION_ERROR_DESC:
 * - Если символ определён, макрос принимает код ошибки и её описание.
 * - Если символ не определён, макрос принимает только код ошибки.
 *
 * Макрос предназначен для использования в ситуациях, где требуется обработка ошибок
 * с немедленным выходом из функции, обеспечивая единообразие и читаемость кода.
 *
 * @note Файл зависит от заголовочного файла runtime_error.h из библиотеки se/runtime,
 *       который предоставляет функции se_error_set() и se_runtime_error().
 *
 * @see se_error_set(), se_runtime_error()
 */

#ifndef SE_RUNTIME_RETURN_WITH_ERROR_H
#define SE_RUNTIME_RETURN_WITH_ERROR_H

#include <se/runtime/runtime_error.h>

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
/**
 * @def se_runtime_return_with_error(code, desc, ...)
 * @brief Устанавливает код ошибки с описанием
 *        и возвращает указанное значение из функции.
 *
 * Этот макрос используется для установки кода ошибки и её описания через se_error_set(),
 * после чего немедленно возвращает указанное значение из функции. Данная версия макроса
 * доступна, когда определён препроцессорный символ `SE_LIBRARY_OPTION_ERROR_DESC`.
 *
 * @param code Код ошибки, который будет установлен через se_error_set().
 * @param desc Описание ошибки, передаваемое в se_error_set() для дополнительной информации.
 * @param ... Значение, которое будет возвращено из функции.
 *
 * @return Возвращает значение, указанное в __VA_ARGS__.
 *
 * @note Макрос вызывает se_error_set() с объектом ошибки,
 *       полученным из se_runtime_error().
 *
 * @see se_error_set(),
 *      se_runtime_error()
 */
#    define se_runtime_return_with_error(code, desc, ...)                                          \
        se_error_set(se_runtime_error(), code, desc);                                              \
        return __VA_ARGS__;
#else
/**
 * @def se_runtime_return_with_error(code, ...)
 * @brief Устанавливает код ошибки и возвращает указанное значение из функции.
 *
 * Этот макрос используется для установки кода ошибки через se_error_set(),
 * после чего немедленно возвращает указанное значение из функции. Данная версия макроса
 * используется, когда препроцессорный символ SE_LIBRARY_OPTION_ERROR_DESC не определён,
 * и описание ошибки не передаётся.
 *
 * @param code Код ошибки, который будет установлен через se_error_set().
 * @param ... Значение, которое будет возвращено из функции.
 *
 * @return Возвращает значение, указанное в __VA_ARGS__.
 *
 * @note Макрос вызывает se_error_set() с объектом ошибки,
 *        полученным из se_runtime_error().
 *
 * @see se_error_set(),
 *      se_runtime_error()
 */
#    define se_runtime_return_with_error(code, ...)                                                \
        se_error_set(se_runtime_error(), code);                                                    \
        return __VA_ARGS__;
#endif // SE_LIBRARY_OPTION_ERROR_DESC

#endif // SE_RUNTIME_RETURN_WITH_ERROR_H