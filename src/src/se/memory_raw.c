#include <se/memory_raw.h>

#include <se/runtime_check.h>
#include <se/runtime_try.h>
#include <se/ptr_util.h>
#include <se/nullptr.h>
#include <se/memory.h>
#include <se/size.h>

void *
se_memory_raw_copy(void *dst, const void *dst_end, const void *src, const void *src_end)
{
    se_usize_t dst_size = se_ptr_to_addr_diff(dst_end, dst);
    se_usize_t src_size = se_ptr_to_addr_diff(src_end, src);
    return se_memory_copy(dst, dst_size, src, src_size);
}

void *
se_memory_raw_copy_rev(void *dst, const void *dst_end, const void *src, const void *src_end)
{
    se_usize_t dst_size = se_ptr_to_addr_diff(dst_end, dst);
    se_usize_t src_size = se_ptr_to_addr_diff(src_end, src);
    return se_memory_copy_rev(dst, dst_size, src, src_size);
}

void *
se_memory_raw_move(void *dst, const void *dst_end, const void *src, const void *src_end)
{
    se_usize_t dst_size = se_ptr_to_addr_diff(dst_end, dst);
    se_usize_t src_size = se_ptr_to_addr_diff(src_end, src);
    return se_memory_move(dst, dst_size, src, src_size);
}

const void *
se_memory_raw_compare(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end)
{
    se_usize_t lhs_size = se_ptr_to_addr_diff(lhs_end, lhs);
    se_usize_t rhs_size = se_ptr_to_addr_diff(rhs_end, rhs);
    return se_memory_compare(lhs, lhs_size, rhs, rhs_size);
}

const void *
se_memory_raw_compare_rev(const void *lhs,
                          const void *lhs_end,
                          const void *rhs,
                          const void *rhs_end)
{
    se_usize_t lhs_size = se_ptr_to_addr_diff(lhs_end, lhs);
    se_usize_t rhs_size = se_ptr_to_addr_diff(rhs_end, rhs);
    return se_memory_compare_rev(lhs, lhs_size, rhs, rhs_size);
}

const void *
se_memory_raw_find(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end)
{
    se_runtime_check(lhs && rhs, SE_RUNTIME_ERROR_NULL_POINTER);

    const se_u8_t *_lhs_end = se_ptr_cast(se_u8_t, lhs_end);
    for (const se_u8_t *_lhs = lhs; _lhs < _lhs_end; ++_lhs)
    {
        if (!se_memory_raw_compare(_lhs, lhs_end, rhs, rhs_end))
        {
            return _lhs;
        }
    }
    return nullptr;
}

const void *
se_memory_raw_find_rev(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end)
{
    se_runtime_check(lhs && rhs, SE_RUNTIME_ERROR_NULL_POINTER);

    const se_u8_t *_lhs = se_ptr_cast(se_u8_t, lhs);
    for (const se_u8_t *_lhs_end = lhs_end; _lhs_end > _lhs; --_lhs_end)
    {
        if (!se_memory_raw_compare_rev(lhs, _lhs_end, rhs, rhs_end))
        {
            return se_ptr_subtract_unsafe(void, _lhs_end, se_ptr_to_addr_diff(rhs_end, rhs));
        }
    }
    return nullptr;
}

void *
se_memory_raw_set(void *dst, const void *dst_end, se_u8_t val)
{
    se_usize_t dst_size = se_ptr_to_addr_diff(dst_end, dst);
    return se_memory_set(dst, dst_size, val);
}

void *
se_memory_raw_repeat(void *dst, const void *dst_end, const void *src, const void *src_end)
{
    se_u8_t       *_dst     = se_ptr_cast(se_u8_t, dst);
    const se_u8_t *_dst_end = se_ptr_cast(const se_u8_t, dst_end);
    do
    {
        _dst = se_memory_raw_move(_dst, dst_end, src, src_end);
    } while (_dst < _dst_end && src < src_end);
    return _dst;
}