#ifndef SE_MEMORY_STD_H
#define SE_MEMORY_STD_H

#include "size.h"
#include "attribute.h"

SE_COMPILER(EXTERN_C_BEGIN)

SE_ATTRIBUTE(SYMBOL)
void *
se_memory_std_copy(void *dst, const void *src, se_usize_t n);

SE_ATTRIBUTE(SYMBOL)
void *
se_memory_std_copy_reverse(void *dst, const void *src, se_usize_t n);

SE_ATTRIBUTE(SYMBOL)
void *
se_memory_std_move(void *dst, const void *src, se_usize_t n);

SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_std_compare(const void *lhs, const void *rhs, se_usize_t n);

SE_ATTRIBUTE(SYMBOL)
const void *
se_memory_std_compare_reverse(const void *lhs, const void *rhs, se_usize_t n);

SE_ATTRIBUTE(SYMBOL)
void *
se_memory_std_set(void *dst, se_usize_t len, se_u8_t val);

SE_COMPILER(EXTERN_C_END)

#endif // SE_MEMORY_STD_H
