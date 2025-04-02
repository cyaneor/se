#include <se/runtime/runtime_except_frame.h>
#include <se/core/nullptr.h>

SE_ATTRIBUTE(THREAD_LOCAL)
se_except_frame_t *se_runtime_except_frames[SE_RUNTIME_EXCEPTION_FRAMES_MAX] = {};

SE_ATTRIBUTE(THREAD_LOCAL)
se_except_frame_t **se_runtime_except_frame = nullptr;

/**
 * @fn se_runtime_except_frame_init
 * @brief Конструктор для инициализации стека фреймов исключений.
 *
 * Устанавливает указатель `se_runtime_except_frame`
 * на начало массива `se_runtime_except_frames`.
 */
se_compiler_constructor(se_runtime_except_frame_init)
{
    se_runtime_except_frame = se_runtime_except_frames;
}

/**
 * @fn se_runtime_except_frame_deinit
 * @brief Деструктор для очистки стека фреймов исключений.
 *
 * Устанавливает указатель se_runtime_except_frame в nullptr.
 */
se_compiler_destructor(se_runtime_except_frame_deinit)
{
    se_runtime_except_frame = nullptr;
}