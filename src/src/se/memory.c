#include <se/memory.h>

#include <se/memory_std.h>
#include <se/memory_raw.h>
#include <se/ptr_util.h>

void *
se_memory_copy(void *dst, se_usize_t dst_size, const void *src, se_usize_t src_size)
{
    const se_usize_t n = se_numeric_min(dst_size, src_size);
    return se_memory_std_copy(dst, src, n);
}

void *
se_memory_copy_reverse(void *dst, se_usize_t dst_size, const void *src, se_usize_t src_size)
{
    const se_usize_t n = se_numeric_min(dst_size, src_size);
    return se_memory_std_copy_reverse(dst, src, n);
}

void *
se_memory_move(void *dst, se_usize_t dst_size, const void *src, se_usize_t src_size)
{
    const se_usize_t n = se_numeric_min(dst_size, src_size);
    return se_memory_std_move(dst, src, n);
}

const void *
se_memory_compare(const void *lhs, se_usize_t lhs_size, const void *rhs, se_usize_t rhs_size)
{
    const se_usize_t n = se_numeric_min(lhs_size, rhs_size);
    return se_memory_std_compare(lhs, rhs, n);
}

const void *
se_memory_compare_reverse(const void *lhs,
                          se_usize_t  lhs_size,
                          const void *rhs,
                          se_usize_t  rhs_size)
{
    se_usize_t compare_size = se_numeric_min(lhs_size, rhs_size);

    // Adjust pointers to align shorter region to the end
    const se_u8_t *l = se_ptr_add(const void, lhs, lhs_size - compare_size);
    const se_u8_t *r = se_ptr_add(const void, rhs, rhs_size - compare_size);

    return se_memory_std_compare_reverse(l, r, compare_size);
}

const void *
se_memory_find(const void *lhs, se_usize_t lhs_size, const void *rhs, se_usize_t rhs_size)
{
    const void *lhs_end = se_ptr_add(const void *, lhs, lhs_size);
    const void *rhs_end = se_ptr_add(const void *, rhs, rhs_size);
    return se_memory_raw_find(lhs, lhs_end, rhs, rhs_end);
}

const void *
se_memory_find_from_end(const void *lhs, se_usize_t lhs_size, const void *rhs, se_usize_t rhs_size)
{
    const void *lhs_end = se_ptr_add(const void *, lhs, lhs_size);
    const void *rhs_end = se_ptr_add(const void *, rhs, rhs_size);
    return se_memory_raw_find_from_end(lhs, lhs_end, rhs, rhs_end);
}

void *
se_memory_set(void *dst, se_usize_t dst_size, const void *src, se_usize_t src_size)
{
    const void *dst_end = se_ptr_add(void *, dst, dst_size);
    const void *src_end = se_ptr_add(const void *, src, src_size);
    return se_memory_raw_set(dst, dst_end, src, src_end);
}