/**
 * @file error.h
 * @brief Заголовочный файл для управления ошибками в библиотеке.
 *
 * Этот файл содержит определения и функции для работы с ошибками,
 * включая установку и получение кодов ошибок, а также их описания.
 *
 * Структура `se_error_t` используется для хранения информации об ошибках,
 * а предоставляемые функции позволяют управлять этими ошибками.
 *
 * В зависимости от конфигурации сборки, могут быть доступны
 * дополнительные функции для работы с текстовыми описаниями ошибок.
 *
 * @note Для включения текстовых описаний ошибок необходимо определить
 *       опцию сборки `SE_LIBRARY_OPTION_ERROR_DESC`.
 */

#ifndef SE_ERROR_H
#define SE_ERROR_H

#include "error_code.h"
#include <se/core/bool.h>
#include <se/attribute/attribute.h>

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
/**
 * @def se_error_set(self, code, desc)
 * @brief Устанавливает код ошибки и текстовое описание для объекта ошибки.
 *
 * Этот макрос используется для установки кода ошибки
 * и текстового описания в объекте типа `se_error_t`.
 *
 * Он доступен, когда опция сборки `SE_LIBRARY_OPTION_ERROR_DESC` определена.
 * Макрос последовательно вызывает функции `se_error_set_code` для установки
 * кода ошибки и `se_error_set_desc` для установки текстового описания.
 *
 * @param[in] self Указатель на объект ошибки типа `se_error_t`,
 *                 в котором устанавливаются значения.
 * @param[in] code Код ошибки типа `se_error_code_t`, который будет установлен.
 * @param[in] desc Указатель на null-terminated строку с текстовым описанием
 *                 ошибки, которое будет установлено.
 *
 * @throw AE_RUNTIME_ERROR_NULL_POINTER
 *        Если указатель `self` равен `nullptr`.
 *
 * @see se_error_set_code
 * @see se_error_set_desc
 */
#    define se_error_set(self, code, desc)                                                         \
        se_error_set_code(self, code);                                                             \
        se_error_set_desc(self, desc)
#else
/**
 * @def se_error_set(self, code, ...)
 * @brief Устанавливает код ошибки для объекта ошибки,
 *        игнорируя дополнительные аргументы.
 *
 * Этот макрос используется для установки только кода ошибки в объекте типа `se_error_t`.
 * Он доступен, когда опция сборки `SE_LIBRARY_OPTION_ERROR_DESC` не определена.
 *
 * Макрос вызывает функцию `se_error_set_code` для установки кода ошибки,
 * а любые дополнительные аргументы (например, описание ошибки) игнорируются.
 *
 * @param[in] self Указатель на объект ошибки типа `se_error_t`,
 *                 в котором устанавливается значение.
 * @param[in] code Код ошибки типа `se_error_code_t`, который будет установлен.
 * @param[in] ... Дополнительные аргументы, которые игнорируются в этой конфигурации.
 *
 * @note Этот вариант макроса не поддерживает установку текстового описания ошибки,
 *       так как опция `SE_LIBRARY_OPTION_ERROR_DESC` не активирована.
 *
 * @throw AE_RUNTIME_ERROR_NULL_POINTER
 *        Если указатель `self` равен `nullptr`.
 *
 * @see se_error_set_code
 */
#    define se_error_set(self, code, ...) se_error_set_code(self, code)
#endif // SE_LIBRARY_OPTION_ERROR_DESC

/**
 * @typedef se_error_t
 * @brief Структура для хранения информации об ошибках в системе
 *
 * Эта структура используется для представления ошибок,
 * возникающих в процессе работы библиотеки.
 *
 * Она включает обязательный код ошибки и опциональное текстовое описание,
 * которое становится доступным, если при сборке библиотеки
 * была активирована опция `SE_LIBRARY_OPTION_ERROR_DESC`.
 */
typedef struct se_error
{
    /** Код ошибки, уникальный идентификатор типа ошибки. */
    se_error_code_t code;
#ifdef SE_LIBRARY_OPTION_ERROR_DESC
    /** Указатель на null-terminated строку с текстовым описанием ошибки. */
    const char *desc;
#endif // SE_LIBRARY_OPTION_ERROR_DESC
} se_error_t;

SE_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Получает код ошибки из структуры `se_error_t`.
 *
 * Эта функция извлекает код ошибки
 * из переданной структуры типа `se_error_t`.
 *
 * Если указатель на структуру равен `nullptr`,
 * будет вызван макрос `AE_RUNTIME_ASSERT` для обработки ошибки.
 *
 * @param self Указатель на структуру `se_error_t`,
 *             из которой необходимо получить код ошибки.
 *
 * @return Код ошибки типа `ae_error_code_t`,
 *         содержащийся в структуре `se_error_t`.
 *
 * @throw AE_RUNTIME_ERROR_NULL_POINTER
 *        Если указатель `self` равен `nullptr`.
 */
SE_ATTRIBUTE(SYMBOL)
se_error_code_t
se_error_get_code(const void *self);

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
/**
 * @brief Получает сообщение об ошибке из структуры `se_error_t`.
 *
 * Эта функция извлекает сообщение об ошибке
 * из переданной структуры типа `se_error_t`.
 *
 * @param self Указатель на структуру `se_error_t`,
 *             из которой необходимо получить сообщение об ошибке.
 *
 * @return Сообщение об ошибке типа `ae_error_desc_t`,
 *         содержащееся в структуре `se_error_t`.
 *
 * @throw AE_RUNTIME_ERROR_NULL_POINTER
 *        Если указатель `self` равен `nullptr`.
 */
SE_ATTRIBUTE(SYMBOL)
const char *
se_error_get_desc(const void *self);
#endif // SE_LIBRARY_OPTION_ERROR_DESC

/**
 * @brief Устанавливает код ошибки для объекта ошибки.
 *
 * Эта функция устанавливает код ошибки в объект ошибки,
 * представленный указателем `self`.
 *
 * @param[in] self Указатель на объект ошибки.
 * @param[in] code Код ошибки, который должен быть установлен.
 *
 * @throw AE_RUNTIME_ERROR_NULL_POINTER
 *        Если указатель `self` равен `nullptr`.
 */
SE_ATTRIBUTE(SYMBOL)
void
se_error_set_code(void *self, se_error_code_t code);

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
/**
 * @brief Устанавливает описание ошибки для объекта ошибки.
 *
 * Эта функция устанавливает описание ошибки в объект ошибки,
 * представленный указателем `self`.
 *
 * @param[in] self Указатель на объект ошибки.
 * @param[in] desc Описание ошибки, которое должно быть установлено.
 *
 * @throw AE_RUNTIME_ERROR_NULL_POINTER
 *        Если указатель `self` равен `nullptr`.
 */
SE_ATTRIBUTE(SYMBOL)
void
se_error_set_desc(void *self, const char *desc);
#endif // SE_LIBRARY_OPTION_ERROR_DESC

SE_COMPILER(EXTERN_C_END)

#endif // SE_ERROR_H
