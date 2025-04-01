#ifndef SE_RUNTIME_ERROR_H
#define SE_RUNTIME_ERROR_H

#include <se/error/error_code.h>
#include <se/attribute/attribute.h>

SE_COMPILER_EXTERN
SE_ATTRIBUTE(THREAD_LOCAL)
se_error_code_t se_runtime_error;

#endif // SE_RUNTIME_ERROR_H
