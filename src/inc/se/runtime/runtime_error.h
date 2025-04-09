/**
 * @file runtime_error.h
 * @brief Заголовочный файл для работы
 *        с глобальной переменной ошибки времени выполнения.
 *
 * Этот файл содержит объявление функции `se_runtime_error()`, которая предоставляет доступ
 * к глобальной переменной ошибки времени выполнения `m_runtime_error`. Используется для
 * обработки ошибок и диагностики во время выполнения в рамках SE.
 */

#ifndef SE_RUNTIME_ERROR_H
#define SE_RUNTIME_ERROR_H

#include <se/error/error.h>

SE_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Возвращает указатель на глобальную переменную ошибки времени выполнения.
 * @return Указатель на m_runtime_error.
 */
SE_ATTRIBUTE(SYMBOL)
se_error_t *
se_runtime_error();

SE_COMPILER(EXTERN_C_END)

#endif // SE_RUNTIME_ERROR_H
