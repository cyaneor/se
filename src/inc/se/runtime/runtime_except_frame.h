/**
 * @file runtime_except_frame.h
 * @brief Заголовочный файл
 *        для управления фреймами исключений во время выполнения.
 *
 * Этот файл предоставляет макросы, переменные и функции для работы со стеком фреймов исключений,
 * используемых для обработки исключений во время выполнения программы.
 */

#ifndef SE_RUNTIME_EXCEPT_FRAMES_H
#define SE_RUNTIME_EXCEPT_FRAMES_H

#include <se/core/bool.h>
#include <se/except/except_frame.h>
#include <se/attribute/attribute.h>

/**
 * @def se_runtime_except_frame_save(x)
 * @brief Сохраняет текущую точку возврата для фрейма исключений.
 * @param x Указатель на se_except_frame_t для сохранения точки возврата.
 * @return Результат выполнения setjmp.
 */
#define se_runtime_except_frame_save(x) setjmp(se_runtime_except_frame_push(x)->env)

/**
 * @def se_runtime_except_frame_load(x)
 * @brief Выполняет возврат к предыдущему фрейму исключений.
 * @param x Значение, возвращаемое при переходе.
 */
#define se_runtime_except_frame_load(x) longjmp(se_runtime_except_frame_prev()->env, x)

/**
 * @fn bool se_runtime_except_frame_is_begin(void)
 * @brief Проверяет, находится ли текущий фрейм в начале стека.
 * @return `true`, если текущий фрейм является первым в массиве, иначе `false`.
 */
SE_ATTRIBUTE(HIDDEN)
bool
se_runtime_except_frame_is_begin(void);

/**
 * @fn bool se_runtime_except_frame_is_end(void)
 * @brief Проверяет, находится ли текущий фрейм в конце стека.
 * @return `true`, если текущий фрейм является последним в массиве, иначе `false`.
 */
SE_ATTRIBUTE(HIDDEN)
bool
se_runtime_except_frame_is_end(void);

/**
 * @fn se_except_frame_t* se_runtime_except_frame_next(void)
 * @brief Переходит к следующему фрейму исключений в стеке.
 * @return Указатель на добавленный фрейм исключений.
 */
SE_ATTRIBUTE(HIDDEN)
se_except_frame_t *
se_runtime_except_frame_next(void);

/**
 * @fn se_except_frame_t* se_runtime_except_frame_push(se_except_frame_t *except)
 * @brief Добавляет новый фрейм исключений в стек.
 * @param except Указатель на фрейм исключений для добавления.
 * @return Указатель на добавленный фрейм исключений.
 */
SE_ATTRIBUTE(HIDDEN)
se_except_frame_t *
se_runtime_except_frame_push(se_except_frame_t *except);

/**
 * @fn se_except_frame_t* se_runtime_except_frame_prev(void)
 * @brief Переходит к предыдущему фрейму исключений в стеке и возвращает его.
 *
 * Уменьшает указатель `se_runtime_except_frame` на один,
 * если текущий фрейм не является начальным,
 * и возвращает указатель на предыдущий фрейм исключений.
 *
 * @return Указатель на предыдущий фрейм исключений или текущий,
 *         если достигнуто начало стека.
 */
SE_ATTRIBUTE(HIDDEN)
se_except_frame_t *
se_runtime_except_frame_prev(void);

#endif // SE_RUNTIME_EXCEPT_FRAMES_H