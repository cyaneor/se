#include "se/numeric/numeric_fixed_types.h"
#include "se/static/static_assert.h"

se_static_assert(sizeof(se_s8_t) == 1, "Size of type se_u8_t must be 1 byte.");
se_static_assert(sizeof(se_s16_t) == 2, "Size of type se_u16_t must be 2 bytes.");
se_static_assert(sizeof(se_s32_t) == 4, "Size of type se_u32_t must be 4 bytes.");
se_static_assert(sizeof(se_s64_t) == 8, "Size of type se_u64_t must be 8 bytes.");