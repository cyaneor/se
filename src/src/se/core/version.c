#include <se/core/str_util.h>
#include <se/core/version.h>

const char *
se_version()
{
    return se_str_from_args(SE_VERSION_MAJOR.SE_VERSION_MINOR.SE_VERSION_PATCH);
}

se_return_t
se_version_major()
{
    return SE_VERSION_MAJOR;
}

se_return_t
se_version_minor()
{
    return SE_VERSION_MINOR;
}

se_return_t
se_version_patch()
{
    return SE_VERSION_PATCH;
}