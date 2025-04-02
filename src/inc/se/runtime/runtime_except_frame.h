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
#define se_runtime_except_frame_save(x) setjmp(*se_runtime_except_frame_push(x))

/**
 * @def se_runtime_except_frame_load(x)
 * @brief Выполняет возврат к предыдущему фрейму исключений.
 * @param x Значение, возвращаемое при переходе.
 */
#define se_runtime_except_frame_load(x) longjmp(se_runtime_except_frame_prev()->env, x)

/**
 * @var se_runtime_except_frames
 * @brief Массив указателей на фреймы исключений
 *        с максимальным размером `SE_RUNTIME_EXCEPTION_FRAMES_MAX`.
 *
 * Этот массив хранит стек фреймов исключений для текущего потока выполнения.
 * @note Переменная является `thread-local`.
 */
SE_COMPILER(EXTERN)
SE_ATTRIBUTE(THREAD_LOCAL)
se_except_frame_t *se_runtime_except_frames[SE_RUNTIME_EXCEPTION_FRAMES_MAX];

/**
 * @var se_runtime_except_frame
 * @brief Указатель на текущий фрейм исключений в стеке.
 *
 * Указывает на текущую позицию в массиве `se_runtime_except_frames`.
 * @note Переменная является `thread-local`.
 */
SE_COMPILER(EXTERN)
SE_ATTRIBUTE(THREAD_LOCAL)
se_except_frame_t **se_runtime_except_frame;

/**
 * @fn bool se_runtime_except_frame_is_begin(void)
 * @brief Проверяет, находится ли текущий фрейм в начале стека.
 * @return `true`, если текущий фрейм является первым в массиве, иначе `false`.
 */
SE_COMPILER_ATTRIBUTE_FORCE_INLINE
bool
se_runtime_except_frame_is_begin(void)
{
    return se_runtime_except_frame == &se_runtime_except_frames[0];
}

/**
 * @fn bool se_runtime_except_frame_is_end(void)
 * @brief Проверяет, находится ли текущий фрейм в конце стека.
 * @return `true`, если текущий фрейм является последним в массиве, иначе `false`.
 */
SE_COMPILER_ATTRIBUTE_FORCE_INLINE
bool
se_runtime_except_frame_is_end(void)
{
    return se_runtime_except_frame == &se_runtime_except_frames[SE_RUNTIME_EXCEPTION_FRAMES_MAX];
}

/**
 * @fn se_except_frame_t* se_runtime_except_frame_next(void)
 * @brief Переходит к следующему фрейму исключений в стеке.
 */
SE_COMPILER_ATTRIBUTE_FORCE_INLINE
void
se_runtime_except_frame_next(void)
{
    if (!se_runtime_except_frame_is_end())
    {
        se_runtime_except_frame++;
    }
}

/**
 * @fn se_jump_buffer_t* se_runtime_except_frame_push(se_except_frame_t *except)
 * @brief Добавляет новый фрейм исключений в стек.
 * @param except Указатель на фрейм исключений для добавления.
 * @return Указатель на буфер перехода (jmp_buf) нового фрейма.
 */
SE_COMPILER_ATTRIBUTE_FORCE_INLINE
se_jump_buffer_t *
se_runtime_except_frame_push(se_except_frame_t *except)
{
    *se_runtime_except_frame = except;
    se_runtime_except_frame_next();
    return &except->env;
}

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
SE_COMPILER_ATTRIBUTE_FORCE_INLINE
se_except_frame_t *
se_runtime_except_frame_prev(void)
{
    if (!se_runtime_except_frame_is_begin())
    {
        se_runtime_except_frame--;
    }
    return *se_runtime_except_frame;
}

#endif // SE_RUNTIME_EXCEPT_FRAMES_H