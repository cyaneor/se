#include <se/version.h>
#include <se/str_util.h>

const char *
se_version(void)
{
    return se_str_from_args(SE_VERSION_MAJOR.SE_VERSION_MINOR.SE_VERSION_PATCH);
}

se_return_t
se_version_major(void)
{
    return SE_VERSION_MAJOR;
}

se_return_t
se_version_minor(void)
{
    return SE_VERSION_MINOR;
}

se_return_t
se_version_patch(void)
{
    return SE_VERSION_PATCH;
}