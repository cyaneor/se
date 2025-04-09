#include <se/runtime/runtime_exception_frame.h>
#include <se/core/nullptr.h>

SE_ATTRIBUTE(THREAD_LOCAL)
se_exception_frame_t *m_runtime_exception_frames[SE_RUNTIME_EXCEPTION_FRAMES_MAX] = {};

SE_ATTRIBUTE(THREAD_LOCAL)
se_exception_frame_t **m_runtime_exception_frame = nullptr;

bool
se_runtime_exception_frame_is_begin(void)
{
    return m_runtime_exception_frame == &m_runtime_exception_frames[0];
}

bool
se_runtime_exception_frame_is_end(void)
{
    return m_runtime_exception_frame ==
           &m_runtime_exception_frames[SE_RUNTIME_EXCEPTION_FRAMES_MAX];
}

se_exception_frame_t *
se_runtime_exception_frame_next(void)
{
    if (!se_runtime_exception_frame_is_end())
    {
        m_runtime_exception_frame++;
    }
    return *m_runtime_exception_frame;
}

se_exception_frame_t *
se_runtime_exception_frame_push(se_exception_frame_t *except)
{
    *m_runtime_exception_frame = except;
    se_runtime_exception_frame_next();
    return except;
}

se_exception_frame_t *
se_runtime_exception_frame_prev(void)
{
    if (!se_runtime_exception_frame_is_begin())
    {
        m_runtime_exception_frame--;
    }
    return *m_runtime_exception_frame;
}

/**
 * @fn se_runtime_exception_frame_init
 * @brief Конструктор для инициализации стека фреймов исключений.
 *
 * Устанавливает указатель `se_runtime_exception_frame`
 * на начало массива `se_runtime_exception_frames`.
 */
se_compiler_constructor(se_runtime_exception_frame_init)
{
    m_runtime_exception_frame = m_runtime_exception_frames;
}

/**
 * @fn se_runtime_exception_frame_deinit
 * @brief Деструктор для очистки стека фреймов исключений.
 *
 * Устанавливает указатель se_runtime_exception_frame в nullptr.
 */
se_compiler_destructor(se_runtime_exception_frame_deinit)
{
    m_runtime_exception_frame = nullptr;
}