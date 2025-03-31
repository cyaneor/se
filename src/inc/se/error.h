/**
 * @file error.h
 * @brief Заголовочный файл, содержащий структуру для обработки ошибок.
 *
 * Этот файл определяет структуру `se_error_t`, которая используется
 * для хранения информации об ошибке, возникшей в процессе выполнения программы.
 *
 * Структура включает код ошибки и текстовое описание,
 * что позволяет эффективно диагностировать и обрабатывать исключения.
 */

#ifndef SE_ERROR_H
#define SE_ERROR_H

#include "attribute.h"
#include "bool.h"
#include "error_code.h"

/**
 * @typedef se_error_t
 * @brief Структура для хранения информации об ошибке.
 *
 * Эта структура используется для представления ошибки, возникающей во время выполнения.
 * Она содержит код ошибки и текстовое описание, которые могут быть использованы для
 * диагностики и обработки исключений.
 */
typedef struct se_error
{
    se_error_code_t code; /**< Код ошибки, идентифицирующий тип или причину ошибки. */
    const char *desc; /**< Указатель на строку с текстовым описанием ошибки. */
} se_error_t;

SE_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Получает код ошибки из объекта se_error_t.
 * @param[in] self Указатель на объект se_error_t.
 * @return Код ошибки или 0, если self равен nullptr.
 */
SE_ATTRIBUTE(SYMBOL)
se_error_code_t
se_error_get_code(const se_error_t *self);

/**
 * @brief Получает код ошибки и очищает объект se_error_t.
 * @param[in,out] self Указатель на объект se_error_t.
 * @return Код ошибки, который был в объекте до очистки.
 */
SE_ATTRIBUTE(SYMBOL)
se_error_code_t
se_error_get_code_and_clear(se_error_t *self);

/**
 * @brief Получает описание ошибки из объекта se_error_t.
 * @param[in] self Указатель на объект se_error_t.
 * @return Указатель на строку с описанием ошибки или nullptr,
 *         если self равен nullptr.
 */
SE_ATTRIBUTE(SYMBOL)
const char *
se_error_get_desc(const se_error_t *self);

/**
 * @brief Устанавливает код ошибки и описание в объекте se_error_t.
 * @param[in,out] self Указатель на объект se_error_t.
 * @param[in] code Код ошибки для установки.
 * @param[in] desc Указатель на строку с описанием ошибки.
 */
SE_ATTRIBUTE(SYMBOL)
void
se_error_set(se_error_t *self, se_error_code_t code, const char *desc);

/**
 * @brief Устанавливает только код ошибки в объекте se_error_t.
 * @param[in,out] self Указатель на объект se_error_t.
 * @param[in] code Код ошибки для установки.
 */
SE_ATTRIBUTE(SYMBOL)
void
se_error_set_code(se_error_t *self, se_error_code_t code);

/**
 * @brief Извлекает код ошибки и описание из объекта se_error_t.
 * @param[in] self Указатель на объект se_error_t.
 * @param[out] code Указатель для сохранения кода ошибки (может быть nullptr).
 * @param[out] desc Указатель для сохранения описания ошибки (может быть nullptr).
 */
SE_ATTRIBUTE(SYMBOL)
void
se_error_unpack(const se_error_t *self, se_error_code_t *code, const char **desc);

/**
 * @brief Копирует содержимое одного объекта se_error_t в другой.
 * @param[in,out] self Указатель на целевой объект se_error_t.
 * @param[in] other Указатель на исходный объект se_error_t.
 */
SE_ATTRIBUTE(SYMBOL)
void
se_error_assign(se_error_t *self, const se_error_t *other);

/**
 * @brief Очищает объект se_error_t, сбрасывая его в состояние по умолчанию.
 * @param[in,out] self Указатель на объект se_error_t.
 */
SE_ATTRIBUTE(SYMBOL)
void
se_error_clear(se_error_t *self);

/**
 * @brief Проверяет, имеет ли объект se_error_t указанный код ошибки.
 * @param[in] self Указатель на объект se_error_t.
 * @param[in] code Код ошибки для проверки.
 * @return true, если код ошибки совпадает с указанным; иначе false.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_error_is_code(const se_error_t *self, se_error_code_t code);

/**
 * @brief Сравнивает код ошибки текущего объекта с кодом ошибки другого объекта.
 * @param[in] self Указатель на текущий объект se_error_t.
 * @param[in] other Указатель на другой объект se_error_t для сравнения.
 * @return true, если коды ошибок совпадают; иначе false.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_error_is_code_equal(const se_error_t *self, const se_error_t *other);

/**
 * @brief Проверяет, имеет ли объект se_error_t указанное текстовое описание ошибки.
 * @param[in] self Указатель на объект se_error_t.
 * @param[in] desc Текстовое описание для проверки.
 * @return true, если описание совпадает с указанным; иначе false.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_error_is_desc(const se_error_t *self, const char *desc);

/**
 * @brief Сравнивает текстовое описание ошибки текущего объекта с описанием другого объекта.
 * @param[in] self Указатель на текущий объект se_error_t.
 * @param[in] other Указатель на другой объект se_error_t для сравнения.
 * @return true, если описания совпадают; иначе false.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_error_is_desc_equal(const se_error_t *self, const se_error_t *other);

/**
 * @brief Проверяет, равны ли два объекта se_error_t.
 * @param[in] self Указатель на текущий объект se_error_t.
 * @param[in] other Указатель на другой объект se_error_t для сравнения.
 * @return true, если объекты равны (по коду и описанию, если включена опция описания); иначе false.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_error_is_equal(const se_error_t *self, const se_error_t *other);

/**
 * @brief Проверяет, является ли объект se_error_t "нет ошибки".
 * @param[in] self Указатель на объект se_error_t.
 * @return true, если код ошибки равен SE_ERROR_CODE_NONE; иначе false.
 */
SE_ATTRIBUTE(SYMBOL)
bool
se_error_is_ok(const se_error_t *self);

SE_COMPILER(EXTERN_C_END)

#endif // SE_ERROR_H
