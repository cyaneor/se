#include <se/runtime/runtime_error.h>

SE_ATTRIBUTE(THREAD_LOCAL)
se_error_t m_runtime_error = {};

se_error_t *
se_runtime_error(void)
{
    return &m_runtime_error;
}