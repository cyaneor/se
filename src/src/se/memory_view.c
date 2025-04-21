#include <se/memory_view.h>

#include <se/ptr_util.h>
#include <se/runtime_check.h>
#include <se/runtime_error_code.h>

const void *
se_memory_view_get_begin(const se_memory_view_t *self)
{
    se_runtime_check(self, SE_RUNTIME_ERROR_NULL_POINTER);
    return self->begin;
}

const void *
se_memory_view_get_end(const se_memory_view_t *self)
{
    se_runtime_check(self, SE_RUNTIME_ERROR_NULL_POINTER);
    return self->end;
}

void
se_memory_view_unpack(const se_memory_view_t *self, const void **begin, const void **end)
{
    if (begin)
        *begin = se_memory_view_get_begin(self);

    if (end)
        *end = se_memory_view_get_end(self);
}

bool
se_memory_view_is_empty(const se_memory_view_t *self)
{
    const void *end = se_memory_view_get_end(self);
    return se_memory_view_is_begin_equal(self, end);
}

bool
se_memory_view_is_valid(const se_memory_view_t *self)
{
    const void *begin, *end;
    se_memory_view_unpack(self, &begin, &end);
    return se_ptr_range_is_valid(begin, end);
}

bool
se_memory_view_contains_pointer(const se_memory_view_t *self, const void *ptr)
{
    se_runtime_check(se_memory_view_is_valid(self), SE_RUNTIME_ERROR_INVALID_MEMORY_RANGE);

    const void *begin, *end;
    se_memory_view_unpack(self, &begin, &end);
    return se_ptr_within_range(begin, end, ptr);
}

bool
se_memory_view_contains(const se_memory_view_t *self, const se_memory_view_t *other)
{
    const void *begin, *end;
    se_memory_view_unpack(other, &begin, &end);
    return se_memory_view_is_valid(other) && se_memory_view_contains_pointer(self, begin) &&
           se_memory_view_contains_pointer(self, end);
}

bool
se_memory_view_contains_range(const se_memory_view_t *self, const void *begin, const void *end)
{
    const se_memory_view_t _t = {begin, end};
    return se_memory_view_contains(self, &_t);
}

se_usize_t
se_memory_view_get_size(const se_memory_view_t *self)
{
    se_runtime_check(se_memory_view_is_valid(self), SE_RUNTIME_ERROR_INVALID_MEMORY_RANGE);
    return (se_usize_t)se_ptr_diff(self->end, self->begin);
}

bool
se_memory_view_is_multiple_of(const se_memory_view_t *self, se_usize_t element_size)
{
    se_runtime_check(element_size, SE_RUNTIME_ERROR_INVALID_ARGUMENT);
    const se_usize_t size = se_memory_view_get_size(self);
    return se_numeric_no_remainder(size, element_size);
}

bool
se_memory_view_is_aligned(const se_memory_view_t *self, se_usize_t alignment_size)
{
    se_runtime_check(alignment_size, SE_RUNTIME_ERROR_INVALID_ARGUMENT);

    const void *begin, *end;
    se_memory_view_unpack(self, &begin, &end);
    return se_ptr_pair_is_aligned(begin, end, alignment_size);
}

bool
se_memory_view_is_valid_offset(const se_memory_view_t *self, se_uoffset_t offset)
{
    return offset < se_memory_view_get_size(self);
}

const void *
se_memory_view_at_begin(const se_memory_view_t *self, se_uoffset_t offset)
{
    se_runtime_check(se_memory_view_is_valid_offset(self, offset), SE_RUNTIME_ERROR_OUT_OF_RANGE);

    const void *begin = se_memory_view_get_begin(self);
    return se_ptr_shift(const void, begin, offset);
}

const void *
se_memory_view_at_end(const se_memory_view_t *self, se_uoffset_t offset)
{
    const se_usize_t size = se_memory_view_get_size(self);
    return se_memory_view_at_begin(self, size - (offset + 1));
}

const void *
se_memory_view_at(const se_memory_view_t *self, se_uoffset_t offset, bool reversed)
{
    return reversed ? se_memory_view_at_end(self, offset) : se_memory_view_at_begin(self, offset);
}

const void *
se_memory_view_get_first(const void *self)
{
    return se_memory_view_at(self, 0, false);
}

const void *
se_memory_view_get_last(const void *self)
{
    return se_memory_view_at(self, 0, true);
}

bool
se_memory_view_is_begin_equal(const se_memory_view_t *self, const void *ptr)
{
    return se_memory_view_get_begin(self) == ptr;
}

bool
se_memory_view_is_end_equal(const se_memory_view_t *self, const void *ptr)
{
    return se_memory_view_get_end(self) == ptr;
}

bool
se_memory_view_is_begin_equal_to(const se_memory_view_t *self, const se_memory_view_t *other)
{
    return se_memory_view_is_begin_equal(self, se_memory_view_get_begin(other));
}

bool
se_memory_view_is_end_equal_to(const se_memory_view_t *self, const se_memory_view_t *other)
{
    return se_memory_view_is_end_equal(self, se_memory_view_get_end(other));
}

bool
se_memory_view_is_equal(const se_memory_view_t *self, const se_memory_view_t *other)
{
    return se_memory_view_is_begin_equal_to(self, other) &&
           se_memory_view_is_end_equal_to(self, other);
}