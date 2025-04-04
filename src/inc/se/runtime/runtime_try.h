/**
 * @file runtime_try.h
 * @brief Заголовочный файл
 *        для реализации механизма `try-catch` во время выполнения.
 *
 * Этот файл предоставляет макросы для создания блока `try-catch`,
 * основанного на фреймах исключений, определённых в `runtime_except_frame.h`.
 * Используется для обработки исключений во время выполнения.
 */

#ifndef SE_RUNTIME_TRY_H
#define SE_RUNTIME_TRY_H

#include "runtime_return.h"
#include "runtime_except_frame.h"

/**
 * @def se_runtime_try
 * @brief Начинает блок try для обработки исключений.
 *
 * Создаёт локальный фрейм исключений с указанным именем `e`,
 * сохраняет текущую точку возврата с помощью `se_runtime_except_frame_save` и проверяет,
 * является ли код возврата нулевым (успешное выполнение).
 *
 * @param e Имя переменной типа `se_except_frame_t`,
 *          которая будет использоваться для хранения фрейма исключений.
 */
#define se_runtime_try(e)                                                                          \
    se_except_frame_t e = {};                                                                      \
    if ((e.code = se_runtime_except_frame_save(&e)) == 0)

/**
 * @def se_runtime_try_finalize
 * @brief Завершает блок try, возвращаясь к предыдущему фрейму исключений.
 *
 * Вызывает `se_runtime_except_frame_prev` для перехода к предыдущему фрейму в стеке исключений.
 * Используется для корректного завершения обработки исключений.
 */
#define se_runtime_try_finalize se_runtime_except_frame_prev

/**
 * @def se_runtime_try_return(...)
 * @brief Выполняет возврат из блока `try` с указанным значением.
 *
 * Завершает блок try вызовом `se_runtime_try_finalize`
 * и возвращает управление с переданным значением.
 * @param ... Значение, возвращаемое из блока `try`.
 */
#define se_runtime_try_return(...)                                                                 \
    se_runtime_try_finalize();                                                                     \
    se_runtime_return(__VA_ARGS__)

#endif // SE_RUNTIME_TRY_H
