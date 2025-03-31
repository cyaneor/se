#include <se/memory_raw.h>

#include <se/nullptr.h>
#include <se/ptr_util.h>
#include <se/runtime_check.h>
#include <se/runtime_return_if.h>
#include <se/runtime_try.h>
#include <se/size.h>

#if defined(SE_COMPILE_OPTION_AVX) || defined(SE_COMPILE_OPTION_AVX2)
#    include <immintrin.h> // Для AVX
#endif                     // SE_COMPILE_OPTION_AVX

#ifdef SE_COMPILE_OPTION_SSE
#    include <xmmintrin.h> // Для SSE
#endif                     // SE_COMPILE_OPTION_SSE

#ifdef SE_COMPILE_OPTION_SSE2
#    include <emmintrin.h> // Для SSE2
#endif                     // SE_COMPILE_OPTION_SSE2

#ifdef SE_COMPILE_OPTION_SSE3
#    include <pmmintrin.h> // Для SSE3
#endif                     // SE_COMPILE_OPTION_SSE3

#ifdef SE_COMPILE_OPTION_SSE41
#    include <smmintrin.h> // Для SSE4.1
#endif                     // SE_COMPILE_OPTION_SSE41
                           // SE_COMPILE_OPTION_SSE41

void *
se_memory_raw_copy(void *dst, const void *dst_end, const void *src, const void *src_end)
{
    se_runtime_check(dst && src, SE_RUNTIME_ERROR_NULL_POINTER);

    se_u8_t       *_dst     = se_ptr_cast(se_u8_t, dst);
    const se_u8_t *_dst_end = se_ptr_cast(const se_u8_t, dst_end);
    const se_u8_t *_src     = se_ptr_cast(const se_u8_t, src);
    const se_u8_t *_src_end = se_ptr_cast(const se_u8_t, src_end);

    while (_dst < _dst_end && _src < _src_end)
    {
        const se_usize_t dst_len = se_ptr_diff(_dst_end, _dst);
        const se_usize_t src_len = se_ptr_diff(_src_end, _src);

#if defined(SE_COMPILE_OPTION_AVX512)
        if (dst_len >= 64 && src_len >= 64)
        {
            __m512i zmm0 = _mm512_loadu_si512(se_ptr_cast(const __m512i, _src));
            _mm512_storeu_si512(se_ptr_cast(__m512i, _dst), zmm0);
            _dst += 64;
            _src += 64;
            continue;
        }
#endif

#if defined(SE_COMPILE_OPTION_AVX) || defined(SE_COMPILE_OPTION_AVX2)
        if (dst_len >= 32 && src_len >= 32)
        {
            __m256i ymm0 = _mm256_loadu_si256(se_ptr_cast(const __m256i, _src));
            _mm256_storeu_si256(se_ptr_cast(__m256i, _dst), ymm0);
            _dst += 32;
            _src += 32;
            continue;
        }
#endif

#ifdef SE_COMPILE_OPTION_SSE
        if (dst_len >= 16 && src_len >= 16)
        {
            __m128i xmm0 = _mm_loadu_si128(se_ptr_cast(const __m128i, _src));
            _mm_storeu_si128(se_ptr_cast(__m128i, _dst), xmm0);
            _dst += 16;
            _src += 16;
            continue;
        }
#endif

        *_dst++ = *_src++;
    }
    return _dst;
}

void *
se_memory_raw_copy_from_end(const void *dst, void *dst_end, const void *src, const void *src_end)
{
    se_runtime_check(dst && src, SE_RUNTIME_ERROR_NULL_POINTER);

    se_u8_t       *_dst     = se_ptr_cast(se_u8_t, dst_end);
    const se_u8_t *_src     = se_ptr_cast(const se_u8_t, src_end);
    const se_u8_t *_dst_end = se_ptr_cast(const se_u8_t, dst);
    const se_u8_t *_src_end = se_ptr_cast(const se_u8_t, src);

    while (_dst > _dst_end && _src > _src_end)
    {
        const se_usize_t dst_len = se_ptr_diff(_dst, _dst_end);
        const se_usize_t src_len = se_ptr_diff(_src, _src_end);

#if defined(SE_COMPILE_OPTION_AVX512)
        if (dst_len >= 64 && src_len >= 64)
        {
            __m512i zmm0 = _mm512_loadu_si512(se_ptr_cast(const __m512i, _src - 1));
            _mm512_storeu_si512(se_ptr_cast(__m512i, _dst - 1), zmm0);
            _dst -= 64;
            _src -= 64;
            continue;
        }
#endif

#if defined(SE_COMPILE_OPTION_AVX) || defined(SE_COMPILE_OPTION_AVX2)
        if (dst_len >= 32 && src_len >= 32)
        {
            __m256i ymm0 = _mm256_loadu_si256(se_ptr_cast(const __m256i, _src - 1));
            _mm256_storeu_si256(se_ptr_cast(__m256i, _dst - 1), ymm0);
            _dst -= 32;
            _src -= 32;
            continue;
        }
#endif

#ifdef SE_COMPILE_OPTION_SSE
        if (dst_len >= 16 && src_len >= 16)
        {
            __m128i xmm0 = _mm_loadu_si128(se_ptr_cast(const __m128i, _src - 1));
            _mm_storeu_si128(se_ptr_cast(__m128i, _dst - 1), xmm0);
            _dst -= 16;
            _src -= 16;
            continue;
        }
#endif

        *--_dst = *--_src;
    }
    return _dst;
}

void *
se_memory_raw_move(void *dst, const void *dst_end, const void *src, const void *src_end)
{
    se_runtime_check(dst && src, SE_RUNTIME_ERROR_NULL_POINTER);

    if (se_ptr_ranges_overlap(dst, src, src_end))
    {
        void *_dst_end = se_ptr_cast(void, dst_end);
        void *_ptr     = se_memory_raw_copy_from_end(dst, _dst_end, src, src_end);
        return se_ptr_sub(void, _dst_end, se_ptr_to_addr_diff(_ptr, dst));
    }
    return se_memory_raw_copy(dst, dst_end, src, src_end);
}

const void *
se_memory_raw_compare(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end)
{
    se_runtime_check(lhs && rhs, SE_RUNTIME_ERROR_NULL_POINTER);
    se_runtime_return_if(lhs == rhs, nullptr);

    const se_u8_t *_lhs     = se_ptr_cast(const se_u8_t, lhs);
    const se_u8_t *_lhs_end = se_ptr_cast(const se_u8_t, lhs_end);
    const se_u8_t *_rhs     = se_ptr_cast(const se_u8_t, rhs);
    const se_u8_t *_rhs_end = se_ptr_cast(const se_u8_t, rhs_end);

    while (_lhs < _lhs_end && _rhs < _rhs_end)
    {
        const se_usize_t lhs_len = se_ptr_diff(_lhs_end, _lhs);
        const se_usize_t rhs_len = se_ptr_diff(_rhs_end, _rhs);

#if defined(SE_COMPILE_OPTION_AVX512)
        if (lhs_len >= 64 && rhs_len >= 64)
        {
            __m512i   zmm_lhs = _mm512_loadu_si512(se_ptr_cast(const __m512i, _lhs));
            __m512i   zmm_rhs = _mm512_loadu_si512(se_ptr_cast(const __m512i, _rhs));
            __mmask64 mask    = _mm512_cmpeq_epi8_mask(zmm_lhs, zmm_rhs);
            if (mask != 0xFFFFFFFFFFFFFFFF)
            {
                se_sint_t index = _tzcnt_u64(~mask);
                return _lhs + index;
            }
            _lhs += 64;
            _rhs += 64;
            continue;
        }
#endif

#ifdef SE_COMPILE_OPTION_AVX2
        if (lhs_len >= 32 && rhs_len >= 32)
        {
            __m256i   ymm_lhs       = _mm256_loadu_si256(se_ptr_cast(const __m256i, _lhs));
            __m256i   ymm_rhs       = _mm256_loadu_si256(se_ptr_cast(const __m256i, _rhs));
            __m256i   cmp           = _mm256_cmpeq_epi8(ymm_lhs, ymm_rhs);
            se_sint_t mask          = _mm256_movemask_epi8(cmp);
            se_uint_t inverted_mask = ~mask;

            if (inverted_mask != 0)
            {
#    if (SE_COMPILER_TYPE == SE_COMPILER_TYPE_GCC || SE_COMPILER_TYPE == SE_COMPILER_TYPE_CLANG)
                se_sint_t index = __builtin_ctz(inverted_mask);
#    elif SE_COMPILER_TYPE == SE_COMPILER_TYPE_MSVC
                se_ulong_t index;
                _BitScanForward(&index, inverted_mask);
#    endif
                return _lhs + index;
            }
            _lhs += 32;
            _rhs += 32;
            continue;
        }
#elif defined(SE_COMPILE_OPTION_AVX) || defined(SE_COMPILE_OPTION_SSE)
        if (lhs_len >= 16 && rhs_len >= 16)
        {
            __m128i   xmm_lhs       = _mm_loadu_si128(se_ptr_cast(const __m128i, _lhs));
            __m128i   xmm_rhs       = _mm_loadu_si128(se_ptr_cast(const __m128i, _rhs));
            __m128i   cmp           = _mm_cmpeq_epi8(xmm_lhs, xmm_rhs);
            se_sint_t mask          = _mm_movemask_epi8(cmp);
            se_uint_t inverted_mask = ~mask & 0xFFFF;

            if (inverted_mask != 0)
            {
#    if (SE_COMPILER_TYPE == SE_COMPILER_TYPE_GCC || SE_COMPILER_TYPE == SE_COMPILER_TYPE_CLANG)
                se_sint_t index = __builtin_ctz(inverted_mask);
#    elif SE_COMPILER_TYPE == SE_COMPILER_TYPE_MSVC
                se_ulong_t index;
                _BitScanForward(&index, inverted_mask);
#    else
#        error "Unsupported compiler for memory raw function compare"
#    endif
                return _lhs + index;
            }
            _lhs += 16;
            _rhs += 16;
            continue;
        }
#endif
        if (*_lhs != *_rhs)
        {
            return _lhs;
        }
        _lhs++;
        _rhs++;
    }

    return nullptr;
}

const void *
se_memory_raw_compare_from_end(const void *lhs,
                               const void *lhs_end,
                               const void *rhs,
                               const void *rhs_end)
{
    se_runtime_check(lhs && rhs, SE_RUNTIME_ERROR_NULL_POINTER);

    const se_u8_t *_lhs = se_ptr_cast(const se_u8_t, lhs_end - 1);
    const se_u8_t *_rhs = se_ptr_cast(const se_u8_t, rhs_end - 1);

    se_usize_t lhs_len = se_ptr_diff(lhs_end, lhs);
    se_usize_t rhs_len = se_ptr_diff(rhs_end, rhs);
    se_usize_t min_len = (lhs_len < rhs_len) ? lhs_len : rhs_len;

#if defined(SE_COMPILE_OPTION_AVX512)
    while (min_len >= 64)
    {
        const se_u8_t *_lhs_chunk_start = _lhs - 63;
        const se_u8_t *_rhs_chunk_start = _rhs - 63;

        __m512i   zmm_lhs = _mm512_loadu_si512(se_ptr_cast(const __m512i, _lhs_chunk_start));
        __m512i   zmm_rhs = _mm512_loadu_si512(se_ptr_cast(const __m512i, _rhs_chunk_start));
        __mmask64 mask    = _mm512_cmpeq_epi8_mask(zmm_lhs, zmm_rhs);
        if (mask != 0xFFFFFFFFFFFFFFFF)
        {
            se_sint_t index = 63 - _lzcnt_u64(~mask);
            return _lhs_chunk_start + index;
        }
        _lhs = _lhs_chunk_start - 1;
        _rhs = _rhs_chunk_start - 1;
        min_len -= 64;
    }
#endif

#ifdef SE_COMPILE_OPTION_AVX2
    while (min_len >= 32)
    {
        const se_u8_t *_lhs_chunk_start = _lhs - 31;
        const se_u8_t *_rhs_chunk_start = _rhs - 31;

        __m256i   ymm_lhs       = _mm256_loadu_si256((const __m256i *)_lhs_chunk_start);
        __m256i   ymm_rhs       = _mm256_loadu_si256((const __m256i *)_rhs_chunk_start);
        __m256i   cmp           = _mm256_cmpeq_epi8(ymm_lhs, ymm_rhs);
        se_sint_t mask          = _mm256_movemask_epi8(cmp);
        se_uint_t inverted_mask = ~mask;

        if (inverted_mask != 0)
        {
#    if (SE_COMPILER_TYPE == SE_COMPILER_TYPE_GCC || SE_COMPILER_TYPE == SE_COMPILER_TYPE_CLANG)
            se_sint_t index = 31 - __builtin_clz(inverted_mask);
#    elif SE_COMPILER_TYPE == SE_COMPILER_TYPE_MSVC
            se_ulong_t index;
            _BitScanReverse(&index, inverted_mask);
#    endif
            return _lhs_chunk_start + index;
        }
        _lhs = _lhs_chunk_start - 1;
        _rhs = _rhs_chunk_start - 1;
        min_len -= 32;
    }
#endif

#if defined(SE_COMPILE_OPTION_AVX) || defined(SE_COMPILE_OPTION_SSE)
    while (min_len >= 16)
    {
        const se_u8_t *_lhs_chunk_start = _lhs - 15;
        const se_u8_t *_rhs_chunk_start = _rhs - 15;

        __m128i   xmm_lhs       = _mm_loadu_si128(se_ptr_cast(const __m128i, _lhs_chunk_start));
        __m128i   xmm_rhs       = _mm_loadu_si128(se_ptr_cast(const __m128i, _rhs_chunk_start));
        __m128i   cmp           = _mm_cmpeq_epi8(xmm_lhs, xmm_rhs);
        se_sint_t mask          = _mm_movemask_epi8(cmp);
        se_uint_t inverted_mask = ~mask & 0xFFFF;

        if (inverted_mask != 0)
        {
#    if (SE_COMPILER_TYPE == SE_COMPILER_TYPE_GCC || SE_COMPILER_TYPE == SE_COMPILER_TYPE_CLANG)
            se_sint_t index = 15 - __builtin_clz(inverted_mask);
#    elif SE_COMPILER_TYPE == SE_COMPILER_TYPE_MSVC
            se_ulong_t index;
            _BitScanReverse(&index, inverted_mask);
#    else
#        error "Unsupported compiler for memory raw function compare from end"
#    endif
            return _lhs_chunk_start + index;
        }
        _lhs = _lhs_chunk_start - 1;
        _rhs = _rhs_chunk_start - 1;
        min_len -= 16;
    }
#endif

    for (se_usize_t i = 0; i < min_len; ++i)
    {
        if (*_lhs != *_rhs)
        {
            return _lhs;
        }
        --_lhs;
        --_rhs;
    }

    return nullptr;
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
se_memory_raw_find_from_end(const void *lhs,
                            const void *lhs_end,
                            const void *rhs,
                            const void *rhs_end)
{
    se_runtime_check(lhs && rhs, SE_RUNTIME_ERROR_NULL_POINTER);

    const se_u8_t *_lhs = se_ptr_cast(se_u8_t, lhs);
    for (const se_u8_t *_lhs_end = lhs_end; _lhs_end > _lhs; --_lhs_end)
    {
        if (!se_memory_raw_compare_from_end(lhs, _lhs_end, rhs, rhs_end))
        {
            return se_ptr_subtract_unsafe(void, _lhs_end, se_ptr_to_addr_diff(rhs_end, rhs));
        }
    }
    return nullptr;
}

void *
se_memory_raw_set(void *dst, const void *dst_end, const void *src, const void *src_end)
{
    se_runtime_try(e)
    {
        do
        {
            dst = se_memory_raw_move(dst, dst_end, src, src_end);
        } while (dst < dst_end);
        se_runtime_try_return(dst);
    }
    se_runtime_rethrow();
}