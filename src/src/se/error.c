#include <se/error.h>

#include <se/runtime_check.h>
#include <se/nullptr.h>

se_error_code_t
se_error_get_code(const se_error_t *self)
{
    se_runtime_check(self, SE_RUNTIME_ERROR_NULL_POINTER);
    return self->code;
}

const char *
se_error_get_desc(const se_error_t *self)
{
    se_runtime_check(self, SE_RUNTIME_ERROR_NULL_POINTER);
    return self->desc;
}

void
se_error_set(se_error_t *self, se_error_code_t code, const char *desc)
{
    se_runtime_check(self, SE_RUNTIME_ERROR_NULL_POINTER);
    self->desc = desc;
    self->code = code;
}

void
se_error_set_code(se_error_t *self, se_error_code_t code)
{
    se_error_set(self, code, nullptr);
}

void
se_error_unpack(const se_error_t *self, se_error_code_t *code, const char **desc)
{
    if (code)
    {
        *code = se_error_get_code(self);
    }

    if (desc)
    {
        *desc = se_error_get_desc(self);
    }
}

void
se_error_assign(se_error_t *self, const se_error_t *other)
{
    se_error_code_t code;
    const char     *desc;

    se_error_unpack(other, &code, &desc);
    se_error_set(self, code, desc);
}

void
se_error_clear(se_error_t *self)
{
    const se_error_t _t = {};
    se_error_assign(self, &_t);
}

se_error_code_t
se_error_get_code_and_clear(se_error_t *self)
{
    se_error_code_t code = se_error_get_code(self);
    se_error_clear(self);
    return code;
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

bool
se_error_is_equal(const se_error_t *self, const se_error_t *other)
{
    return se_error_is_code_equal(self, other) && se_error_is_desc_equal(self, other);
}

bool
se_error_is_ok(const se_error_t *self)
{
    return se_error_is_code(self, SE_ERROR_CODE_NONE);
}