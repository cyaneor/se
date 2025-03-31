#include <se/error/error.h>
#include <se/core/ptr_util.h>

se_error_code_t
se_error_get_code(const void *self)
{
    return se_ptr_cast(const se_error_t, self)->code;
}

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
const char *
se_error_get_desc(const void *self)
{
    return se_ptr_cast(const se_error_t, self)->desc;
}
#endif // SE_LIBRARY_OPTION_ERROR_DESC

void
se_error_set_code(void *self, se_error_code_t code)
{
    se_ptr_cast(se_error_t, self)->code = code;
#ifdef SE_LIBRARY_OPTION_ERROR_DESC
    se_error_set_desc(self, nullptr);
#endif
}

#ifdef SE_LIBRARY_OPTION_ERROR_DESC
void
se_error_set_desc(void *self, const char *desc)
{
    se_ptr_cast(se_error_t, self)->desc = desc;
}
#endif // SE_LIBRARY_OPTION_ERROR_DESC