#include <se/runtime_exception_catch_stack.h>

#include <se/static_assert.h>
#include <se/nullptr.h>

se_static_assert(SE_RUNTIME_EXCEPTION_CATCH_STACK_MAX,
                 "SE_RUNTIME_EXCEPTION_CATCH_STACK_MAX must be greater than 0. "
                 "Zero stack depth makes exception handling impossible. "
                 "Please define a positive stack size in compile_definitions.cmake");

/**
 * @var se_exception_catch_t *m_runtime_exceptions
 * @brief Массив фреймов исключений для обработки runtime-исключений
 *
 * Данный массив хранит указатели на фреймы исключений, используемые механизмом обработки
 * исключений. Каждый поток имеет свою собственную копию массива благодаря THREAD_LOCAL атрибуту.
 *
 * Размер массива определяется значением SE_RUNTIME_EXCEPTION_CATCH_STACK_MAX,
 * которое задается как compile definition в CMake (файл compile_definitions.cmake).
 *
 * Это значение определяет максимальное количество
 * одновременно обрабатываемых исключений в одном потоке.
 *
 * @note Инициализируется нулевыми указателями при создании
 * @see compile_definitions.cmake - файл конфигурации CMake, где задается значение
 */
SE_ATTRIBUTE(THREAD_LOCAL)
se_exception_catch_t *m_runtime_exceptions[SE_RUNTIME_EXCEPTION_CATCH_STACK_MAX] = {};

/**
 * @var se_exception_catch_t **m_runtime_exception
 * @brief Указатель на текущий активный фрейм исключения
 *
 * Используется для отслеживания текущего контекста исключения в потоке.
 * Имеет THREAD_LOCAL атрибут, что обеспечивает потокобезопасность.
 *
 * @note Инициализируется нулевым указателем (nullptr)
 */
SE_ATTRIBUTE(THREAD_LOCAL)
se_exception_catch_t **m_runtime_exception = nullptr;

se_exception_catch_t *
se_runtime_exception_catch_stack_get_current(void)
{
    return *m_runtime_exception;
}

bool
se_runtime_exception_catch_stack_is_begin(void)
{
    return m_runtime_exception == m_runtime_exceptions;
}

bool
se_runtime_exception_catch_stack_is_end(void)
{
    return m_runtime_exception == &m_runtime_exceptions[SE_RUNTIME_EXCEPTION_CATCH_STACK_MAX];
}

se_exception_catch_t *
se_runtime_exception_catch_stack_next(void)
{
    if (!se_runtime_exception_catch_stack_is_end())
    {
        m_runtime_exception++;
        return *m_runtime_exception;
    }
    return nullptr;
}

se_exception_catch_t *
se_runtime_exception_catch_stack_prev(void)
{
    if (!se_runtime_exception_catch_stack_is_begin())
    {
        m_runtime_exception--;
        return *m_runtime_exception;
    }
    return nullptr;
}

se_exception_catch_t *
se_runtime_exception_catch_stack_push(se_exception_catch_t *e)
{
    if (!se_runtime_exception_catch_stack_is_end())
    {
        *m_runtime_exception = e;
        se_runtime_exception_catch_stack_next();
        return e;
    }
    return nullptr;
}

se_compiler_constructor(se_runtime_exception_catch_stack_init)
{
    m_runtime_exception = m_runtime_exceptions;
}

se_compiler_destructor(se_runtime_exception_catch_stack_deinit)
{
    m_runtime_exception = nullptr;
}