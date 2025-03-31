#include <se/error/error.h>

#include <se/runtime/runtime_check.h>
#include <se/runtime/runtime_error_code.h>

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
#    include <se/core/nullptr.h>
#endif // SE_LIBRARY_OPTION_ERROR_DESC

se_error_code_t
se_error_get_code(const se_error_t *self)
{
    se_runtime_check(self, SE_RUNTIME_ERROR_NULL_POINTER, 0);
    return self->code;
}

se_error_code_t
se_error_get_code_and_clear(se_error_t *self)
{
    se_error_code_t code = se_error_get_code(self);
    se_error_clear(self);
    return code;
}

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
const char *
se_error_get_desc(const se_error_t *self)
{
    se_runtime_check(self, SE_RUNTIME_ERROR_NULL_POINTER, 0);
    return self->desc;
}
#endif // SE_LIBRARY_OPTION_ERROR_DESC

void
#ifdef SE_LIBRARY_OPTION_ERROR_DESC
se_error_set(se_error_t *self, se_error_code_t code, const char *desc)
{
    se_runtime_check(self, SE_RUNTIME_ERROR_NULL_POINTER);
    self->desc = desc;
#else
se_error_set(se_error_t *self, se_error_code_t code)
{
    se_runtime_check(self, SE_RUNTIME_ERROR_NULL_POINTER);
#endif // SE_LIBRARY_OPTION_ERROR_DESC
    self->code = code;
}

void
se_error_set_code(se_error_t *self, se_error_code_t code)
{
#ifdef SE_LIBRARY_OPTION_ERROR_DESC
    se_error_set(self, code, nullptr);
#else
    se_error_set(self, code);
#endif // SE_LIBRARY_OPTION_ERROR_DESC
}

void
#ifdef SE_LIBRARY_OPTION_ERROR_DESC
se_error_unpack(const se_error_t *self, se_error_code_t *code, const char **desc)
{
    if (desc)
        *desc = se_error_get_desc(self);
#else
se_error_unpack(const se_error_t *self, se_error_code_t *code)
{
#endif // SE_LIBRARY_OPTION_ERROR_DESC
    if (code)
        *code = se_error_get_code(self);
}

void
se_error_assign(se_error_t *self, const se_error_t *other)
{
    se_error_code_t code;
#ifdef SE_LIBRARY_OPTION_ERROR_DESC
    const char *desc;
    se_error_unpack(other, &code, &desc);
    se_error_set(self, code, desc);
#else
    se_error_unpack(other, &code);
    se_error_set(self, code);
#endif // SE_LIBRARY_OPTION_ERROR_DESC
}

void
se_error_clear(se_error_t *self)
{
    const se_error_t _t = {};
    se_error_assign(self, &_t);
}

bool
se_error_is_code(const se_error_t *self, se_error_code_t code)
{
    return se_error_get_code(self) == code;
}

bool
se_error_is_code_equal(const se_error_t *self, const se_error_t *other)
{
    const se_error_code_t code = se_error_get_code(other);
    return se_error_is_code(self, code);
}

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
bool
se_error_is_desc(const se_error_t *self, const char *desc)
{
    return se_error_get_desc(self) == desc;
}

bool
se_error_is_desc_equal(const se_error_t *self, const se_error_t *other)
{
    const char *desc = se_error_get_desc(other);
    return se_error_is_desc(self, desc);
}
#endif // SE_LIBRARY_OPTION_ERROR_DESC

bool
se_error_is_equal(const se_error_t *self, const se_error_t *other)
{
#ifdef SE_LIBRARY_OPTION_ERROR_DESC
    return se_error_is_code_equal(self, other) && se_error_is_desc_equal(self, other);
#else
    return se_error_is_code_equal(self, other);
#endif // SE_LIBRARY_OPTION_ERROR_DESC
}

bool
se_error_is_ok(const se_error_t *self)
{
    return se_error_is_code(self, SE_ERROR_CODE_NONE);
}