#include <se/runtime_terminate.h>

/**
 * @var m_runtime_terminate
 * @brief Указатель на текущую функцию аварийного завершения.
 *
 * Инициализируется в зависимости от опции `SE_LIBRARY_OPTION_TERMINATE_INIT_STDLIB`:
 * - Если `ON`: устанавливается в `abort()` (стандартное завершение из stdlib).
 * - Если `OFF`: устанавливается в `nullptr` (требует явной настройки).
 *
 * @note Потокобезопасна (THREAD_LOCAL), каждый поток может иметь свой обработчик.
 * @see se_runtime_terminate_set()
 */
#ifdef SE_LIBRARY_OPTION_TERMINATE_INIT_STDLIB
#    include <stdlib.h>
SE_ATTRIBUTE(THREAD_LOCAL)
se_runtime_terminate_fn *m_runtime_terminate = abort;
#else
#    include <se/core/nullptr.h>
SE_ATTRIBUTE(THREAD_LOCAL)
se_runtime_terminate_fn *m_runtime_terminate = nullptr;
#endif

void
se_runtime_terminate(void)
{
    m_runtime_terminate();
    se_compiler_unreachable();
}

se_runtime_terminate_fn *
se_runtime_terminate_set(se_runtime_terminate_fn *fn)
{
    se_runtime_terminate_fn *prev = m_runtime_terminate;
    m_runtime_terminate           = fn;
    return prev;
}