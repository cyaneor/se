/**
 * @file runtime_error.h
 * @brief Содержит объявление переменной кода ошибки времени выполнения
 *        с локальным хранением для потоков.
 *
 * Этот заголовочный файл предоставляет объявление переменной
 * с локальным хранением для потоков, используемой
 * для хранения кодов ошибок времени выполнения.
 */

#ifndef SE_RUNTIME_ERROR_CODE_H
#define SE_RUNTIME_ERROR_CODE_H

#include <se/error/error_code.h>
#include <se/attribute/attribute.h>

/**
 * @var se_error_code_t se_runtime_error_code
 * @brief Переменная с локальным хранением для потоков,
 *        содержащая текущий код ошибки времени выполнения.
 */
SE_COMPILER_EXTERN
SE_ATTRIBUTE(THREAD_LOCAL)
se_error_code_t se_runtime_error_code;

#endif // SE_RUNTIME_ERROR_CODE_H