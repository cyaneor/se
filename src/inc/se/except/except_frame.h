/**
 * @file except_frame.h
 * @brief Заголовочный файл, определяющий структуру фрейма исключений.
 *
 * Этот файл содержит определение структуры `se_except_frame_t`,
 * используемой для хранения информации об исключениях
 * и контекста перехода во время выполнения.
 */

#ifndef SE_EXCEPT_FRAME_H
#define SE_EXCEPT_FRAME_H

#include <se/core/error_code.h>
#include "jump_buffer.h"

/**
 * @struct se_except_frame
 * @brief Структура, представляющая фрейм исключений.
 *
 * Содержит код ошибки и буфер перехода
 * для управления обработкой исключений.
 */
typedef struct se_except_frame
{
    /**
     * @var code
     * @brief Код ошибки, связанный с исключением.
     *
     * Хранит значение типа `se_error_code_t`,
     * указывающее тип или причину исключения.
     */
    se_error_code_t code;

    /**
     * @var env
     * @brief Буфер перехода для сохранения контекста выполнения.
     *
     * Хранит состояние стека вызовов (тип `se_jump_buffer_t`),
     * используемое для переходов с помощью `setjmp` и `longjmp`.
     */
    se_jump_buffer_t env;
} se_except_frame_t;

#endif // SE_EXCEPT_FRAME_H
