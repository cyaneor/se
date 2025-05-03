#include <se/memory_std.h>

#include <se/runtime_return_if.h>
#include <se/runtime_check.h>
#include <se/bit_util.h>
#include <se/ptr_util.h>

#if defined(SE_COMPILE_OPTION_SSE2) || defined(SE_COMPILE_OPTION_AVX2) ||                          \
    defined(SE_COMPILE_OPTION_AVX512)

#    include <immintrin.h> // Для AVX, AVX2, AVX-512 и SSE

#endif

void *
se_memory_std_copy(void *dst, const void *src, se_usize_t n)
{
    se_runtime_check(dst && src, SE_RUNTIME_ERROR_NULL_POINTER);

    se_u8_t       *d = se_ptr_cast(se_u8_t, dst);
    const se_u8_t *s = se_ptr_cast(const se_u8_t, src);

    // Processing of small or unheated blocks
    if (n < 64 || !se_ptr_is_aligned(d, 16) || !se_ptr_is_aligned(s, 16))
    {
        // We use 64-bit copies for blocks> = 8 bytes
        while (n >= 8)
        {
            *(se_u64_t *)d = *(const se_u64_t *)s;
            d += 8;
            s += 8;
            n -= 8;
        }
        // We use 32-bit copies for blocks> = 4 bytes
        while (n >= 4)
        {
            *(se_u32_t *)d = *(const se_u32_t *)s;
            d += 4;
            s += 4;
            n -= 4;
        }
        // The remaining bytes (<4)
        while (n--)
        {
            *d++ = *s++;
        }
        return d;
    }

#ifdef SE_COMPILE_OPTION_AVX512
    // AVX512: 64-byte champs
    while (n >= 64)
    {
        __m512i vec = _mm512_loadu_si512(s);
        _mm512_storeu_si512(d, vec);
        d += 64;
        s += 64;
        n -= 64;
    }
#endif
#ifdef SE_COMPILE_OPTION_AVX2
    // AVX2: 32-byte champs
    while (n >= 32)
    {
        __m256i vec = _mm256_loadu_si256((__m256i const *)s);
        _mm256_storeu_si256((__m256i *)d, vec);
        d += 32;
        s += 32;
        n -= 32;
    }
#endif
#ifdef SE_COMPILE_OPTION_SSE2
    // SSE2: 16-byte champs
    while (n >= 16)
    {
        __m128i vec = _mm_loadu_si128((__m128i const *)s);
        _mm_storeu_si128((__m128i *)d, vec);
        d += 16;
        s += 16;
        n -= 16;
    }
#endif
    // Processing of the remaining bytes
    while (n >= 8)
    {
        *(se_u64_t *)d = *(const se_u64_t *)s;
        d += 8;
        s += 8;
        n -= 8;
    }
    while (n >= 4)
    {
        *(se_u32_t *)d = *(const se_u32_t *)s;
        d += 4;
        s += 4;
        n -= 4;
    }
    // Remaining bytes (<4)
    while (n--)
    {
        *d++ = *s++;
    }
    return d;
}

void *
se_memory_std_copy_reverse(void *dst, const void *src, se_usize_t n)
{
    se_runtime_check(dst && src, SE_RUNTIME_ERROR_NULL_POINTER);

    se_u8_t       *d = se_ptr_shift_unsafe(se_u8_t, dst, n);
    const se_u8_t *s = se_ptr_shift_unsafe(const se_u8_t, src, n);

    // Processing of small or unheated blocks
    if (n < 64 || !se_ptr_is_aligned(d - n, 16) || !se_ptr_is_aligned(s - n, 16))
    {
        // We use 64-bit copies for blocks> = 8 bytes
        while (n >= 8)
        {
            d -= 8;
            s -= 8;
            *(se_u64_t *)d = *(const se_u64_t *)s;
            n -= 8;
        }
        // We use 32-bit copies for blocks> = 4 bytes
        while (n >= 4)
        {
            d -= 4;
            s -= 4;
            *(se_u32_t *)d = *(const se_u32_t *)s;
            n -= 4;
        }
        // Remaining bytes (<4)
        while (n--)
        {
            *(--d) = *(--s);
        }
        return d;
    }

#ifdef SE_COMPILE_OPTION_AVX512
    // AVX512: 64-byte champs
    while (n >= 64)
    {
        d -= 64;
        s -= 64;
        __m512i vec = _mm512_loadu_si512(s);
        _mm512_storeu_si512(d, vec);
        n -= 64;
    }
#endif
#ifdef SE_COMPILE_OPTION_AVX2
    // AVX2: 32-byte champs
    while (n >= 32)
    {
        d -= 32;
        s -= 32;
        __m256i vec = _mm256_loadu_si256((__m256i const *)s);
        _mm256_storeu_si256((__m256i *)d, vec);
        n -= 32;
    }
#endif
#ifdef SE_COMPILE_OPTION_SSE2
    // SSE2: 16-byte champs
    while (n >= 16)
    {
        d -= 16;
        s -= 16;
        __m128i vec = _mm_loadu_si128((__m128i const *)s);
        _mm_storeu_si128((__m128i *)d, vec);
        n -= 16;
    }
#endif
    // Processing of the remaining bytes
    while (n >= 8)
    {
        d -= 8;
        s -= 8;
        *(se_u64_t *)d = *(const se_u64_t *)s;
        n -= 8;
    }
    while (n >= 4)
    {
        d -= 4;
        s -= 4;
        *(se_u32_t *)d = *(const se_u32_t *)s;
        n -= 4;
    }
    // Remaining bytes (<4)
    while (n--)
    {
        *(--d) = *(--s);
    }
    return d;
}

void *
se_memory_std_move(void *dst, const void *src, se_usize_t n)
{
    const void *_src_end = se_ptr_add(const void *, src, n);
    if (se_ptr_ranges_is_overlap(dst, src, _src_end))
    {
        void *_dst = se_memory_std_copy_reverse(dst, src, n);
        return se_ptr_add(void *, _dst, n);
    }
    return se_memory_std_copy(dst, src, n);
}

const void *
se_memory_std_compare(const void *lhs, const void *rhs, se_usize_t n)
{
    se_runtime_check(lhs && rhs, SE_RUNTIME_ERROR_NULL_POINTER);

    const se_u8_t *l = se_ptr_cast(const se_u8_t, lhs);
    const se_u8_t *r = se_ptr_cast(const se_u8_t, rhs);

    // Обработка маленьких или невыровненных блоков
    if (n < 64 || !se_ptr_is_aligned(l, 16) || !se_ptr_is_aligned(r, 16))
    {
        // We use 64-bit comparisons for blocks> = 8 bytes
        while (n >= 8)
        {
            se_u64_t l_val = *(const se_u64_t *)l;
            se_u64_t r_val = *(const se_u64_t *)r;
            if (l_val != r_val)
            {
                se_u64_t   diff = l_val ^ r_val;
                se_ulong_t index;
                se_bit_scan_forward64(&index, diff);
                return &l[index / 8];
            }
            l += 8;
            r += 8;
            n -= 8;
        }
        // We use 32-bit comparisons for blocks> = 4 bytes
        while (n >= 4)
        {
            se_u32_t l_val = *(const se_u32_t *)l;
            se_u32_t r_val = *(const se_u32_t *)r;
            if (l_val != r_val)
            {
                se_u32_t   diff = l_val ^ r_val;
                se_ulong_t index;
                se_bit_scan_forward32(&index, diff);
                return &l[index / 8];
            }
            l += 4;
            r += 4;
            n -= 4;
        }
        // Remaining bytes (<4)
        while (n--)
        {
            if (*l != *r)
            {
                return l;
            }
            l++;
            r++;
        }
        return nullptr;
    }

#ifdef SE_COMPILE_OPTION_AVX512
    // AVX512: 64-byte champs
    while (n >= 64)
    {
        __m512i  l_vec = _mm512_loadu_si512(l);
        __m512i  r_vec = _mm512_loadu_si512(r);
        se_u64_t mask  = _mm512_cmpeq_epi8_mask(l_vec, r_vec);
        if (mask != 0xFFFFFFFFFFFFFFFFULL)
        {
            se_ulong_t index;
            se_bit_scan_forward64(&index, ~mask);
            return &l[index];
        }
        l += 64;
        r += 64;
        n -= 64;
    }
#endif
#ifdef SE_COMPILE_OPTION_AVX2
    // AVX2: 32-byte champs
    while (n >= 32)
    {
        __m256i   l_vec = _mm256_loadu_si256((__m256i const *)l);
        __m256i   r_vec = _mm256_loadu_si256((__m256i const *)r);
        __m256i   cmp   = _mm256_cmpeq_epi8(l_vec, r_vec);
        se_sint_t mask  = _mm256_movemask_epi8(cmp);
        if (mask != 0xFFFFFFFF)
        {
            se_ulong_t index;
            se_bit_scan_forward32(&index, ~mask);
            return &l[index];
        }
        l += 32;
        r += 32;
        n -= 32;
    }
#endif
#ifdef SE_COMPILE_OPTION_SSE2
    // SSE2: 16-byte champs
    while (n >= 16)
    {
        __m128i   l_vec = _mm_loadu_si128((__m128i const *)l);
        __m128i   r_vec = _mm_loadu_si128((__m128i const *)r);
        __m128i   cmp   = _mm_cmpeq_epi8(l_vec, r_vec);
        se_sint_t mask  = _mm_movemask_epi8(cmp);
        if (mask != 0xFFFF)
        {
            se_ulong_t index;
            se_bit_scan_forward32(&index, ~mask);
            return &l[index];
        }
        l += 16;
        r += 16;
        n -= 16;
    }
#endif
    // Processing of the remaining bytes (similarly)
    while (n >= 8)
    {
        se_u64_t l_val = *(const se_u64_t *)l;
        se_u64_t r_val = *(const se_u64_t *)r;
        if (l_val != r_val)
        {
            se_u64_t   diff = l_val ^ r_val;
            se_ulong_t index;
            se_bit_scan_forward64(&index, diff);
            return &l[index / 8];
        }
        l += 8;
        r += 8;
        n -= 8;
    }
    while (n >= 4)
    {
        se_u32_t l_val = *(const se_u32_t *)l;
        se_u32_t r_val = *(const se_u32_t *)r;
        if (l_val != r_val)
        {
            se_u32_t   diff = l_val ^ r_val;
            se_ulong_t index;
            se_bit_scan_forward32(&index, diff);
            return &l[index / 8];
        }
        l += 4;
        r += 4;
        n -= 4;
    }
    // Remaining bytes (<4)
    while (n--)
    {
        if (*l != *r)
        {
            return l;
        }
        l++;
        r++;
    }

    return nullptr;
}

const void *
se_memory_std_compare_reverse(const void *lhs, const void *rhs, se_usize_t n)
{
    se_runtime_check(lhs && rhs, SE_RUNTIME_ERROR_NULL_POINTER);
    se_runtime_return_ifn(n, nullptr);

    const se_u8_t *l = se_ptr_shift_unsafe(const se_u8_t, lhs, n);
    const se_u8_t *r = se_ptr_shift_unsafe(const se_u8_t, rhs, n);

    // Processing of small or unheated blocks
    if (n < 64 || !se_ptr_is_aligned((const se_u8_t *)lhs, 16) ||
        !se_ptr_is_aligned((const se_u8_t *)rhs, 16))
    {
        while (n--)
        {
            l--;
            r--;
            if (*l != *r)
            {
                return l;
            }
        }
        return nullptr;
    }

#ifdef SE_COMPILE_OPTION_AVX512
    // AVX512: 64-byte champs
    while (n >= 64)
    {
        l -= 64;
        r -= 64;
        __m512i  l_vec = _mm512_loadu_si512(l);
        __m512i  r_vec = _mm512_loadu_si512(r);
        se_u64_t mask  = _mm512_cmpeq_epi8_mask(l_vec, r_vec);
        if (mask != 0xFFFFFFFFFFFFFFFFULL)
        {
            se_ulong_t index;
            se_bit_scan_reverse64(&index, ~mask);
            return &l[index];
        }
        n -= 64;
    }
#endif
#ifdef SE_COMPILE_OPTION_AVX2
    // AVX2: 32-byte champs
    while (n >= 32)
    {
        l -= 32;
        r -= 32;
        __m256i   l_vec = _mm256_loadu_si256((__m256i const *)l);
        __m256i   r_vec = _mm256_loadu_si256((__m256i const *)r);
        __m256i   cmp   = _mm256_cmpeq_epi8(l_vec, r_vec);
        se_sint_t mask  = _mm256_movemask_epi8(cmp);
        if (mask != 0xFFFFFFFF)
        {
            se_ulong_t index;
            se_bit_scan_reverse32(&index, ~mask);
            return &l[index];
        }
        n -= 32;
    }
#endif
#ifdef SE_COMPILE_OPTION_SSE2
    // SSE2: 16-byte champs
    while (n >= 16)
    {
        l -= 16;
        r -= 16;
        __m128i   l_vec = _mm_loadu_si128((__m128i const *)l);
        __m128i   r_vec = _mm_loadu_si128((__m128i const *)r);
        __m128i   cmp   = _mm_cmpeq_epi8(l_vec, r_vec);
        se_sint_t mask  = _mm_movemask_epi8(cmp);
        if (mask != 0xFFFF)
        {
            se_ulong_t index;
            se_bit_scan_reverse32(&index, ~mask);
            return &l[index];
        }
        n -= 16;
    }
#endif
    // Processing of the remaining bytes
    while (n >= 8)
    {
        l -= 8;
        r -= 8;
        se_u64_t l_val = *(const se_u64_t *)l;
        se_u64_t r_val = *(const se_u64_t *)r;
        if (l_val != r_val)
        {
            se_u64_t   diff = l_val ^ r_val;
            se_ulong_t index;
            se_bit_scan_reverse64(&index, diff);
            return &l[index / 8];
        }
        n -= 8;
    }
    while (n >= 4)
    {
        l -= 4;
        r -= 4;
        se_u32_t l_val = *(const se_u32_t *)l;
        se_u32_t r_val = *(const se_u32_t *)r;
        if (l_val != r_val)
        {
            se_u32_t   diff = l_val ^ r_val;
            se_ulong_t index;
            se_bit_scan_reverse32(&index, diff);
            return &l[index / 8];
        }
        n -= 4;
    }
    // Handle remaining bytes
    while (n--)
    {
        l--;
        r--;
        if (*l != *r)
        {
            return l;
        }
    }

    return nullptr;
}

void *
se_memory_std_set(void *dst, se_usize_t len, se_u8_t val)
{
    se_runtime_check(dst, SE_RUNTIME_ERROR_NULL_POINTER);

    se_u8_t *d = (se_u8_t *)dst;

    // Precompute values once
    const se_u64_t val64 = ((se_u64_t)val) * 0x0101010101010101ULL;
    const se_u32_t val32 = (se_u32_t)(val * 0x01010101U);

    // Handle small or unaligned blocks
    if (len < 64 || !se_ptr_is_aligned(d, 16))
    {
        while (len >= 8)
        {
            *(se_u64_t *)d = val64;
            d += 8;
            len -= 8;
        }
        while (len >= 4)
        {
            *(se_u32_t *)d = val32;
            d += 4;
            len -= 4;
        }
        while (len--)
        {
            *d++ = val;
        }
        return d;
    }

    // Process large aligned blocks using SIMD
#ifdef SE_COMPILE_OPTION_AVX512
    if (len >= 64)
    {
        __m512i vec = _mm512_set1_epi8(val);
        // Align to 64 bytes if possible
        se_uintptr_t misalign = (se_uintptr_t)d % 64;
        if (misalign)
        {
            se_usize_t adjust = 64 - misalign;
            se_usize_t chunk  = (len >= adjust) ? adjust : len;
            len -= chunk;
            while (chunk >= 8)
            {
                *(se_u64_t *)d = val64;
                d += 8;
                chunk -= 8;
            }
            while (chunk--)
                *d++ = val;
        }
        // Use non-temporal for large blocks
        if (len >= (1 << 20))
        {
            while (len >= 64)
            {
                _mm512_stream_si512((__m512i *)d, vec);
                d += 64;
                len -= 64;
            }
            _mm_sfence();
        }
        else
        {
            while (len >= 64)
            {
                _mm512_store_si512((__m512i *)d, vec);
                d += 64;
                len -= 64;
            }
        }
    }
#endif

#ifdef SE_COMPILE_OPTION_AVX2
    if (len >= 32)
    {
        __m256i vec = _mm256_set1_epi8(val);
        // Align to 32 bytes if possible
        se_uintptr_t misalign = (se_uintptr_t)d % 32;
        if (misalign)
        {
            se_usize_t adjust = 32 - misalign;
            se_usize_t chunk  = (len >= adjust) ? adjust : len;
            len -= chunk;
            while (chunk >= 8)
            {
                *(se_u64_t *)d = val64;
                d += 8;
                chunk -= 8;
            }
            while (chunk--)
                *d++ = val;
        }
        while (len >= 32)
        {
            _mm256_store_si256((__m256i *)d, vec);
            d += 32;
            len -= 32;
        }
    }
#endif

#ifdef SE_COMPILE_OPTION_SSE2
    if (len >= 16)
    {
        __m128i vec = _mm_set1_epi8(val);
        // Align to 16 bytes if possible
        se_uintptr_t misalign = (se_uintptr_t)d % 16;
        if (misalign)
        {
            se_usize_t adjust = 16 - misalign;
            se_usize_t chunk  = (len >= adjust) ? adjust : len;
            len -= chunk;
            while (chunk >= 8)
            {
                *(se_u64_t *)d = val64;
                d += 8;
                chunk -= 8;
            }
            while (chunk--)
                *d++ = val;
        }
        while (len >= 16)
        {
            _mm_store_si128((__m128i *)d, vec);
            d += 16;
            len -= 16;
        }
    }
#endif
    // Handle remaining bytes
    while (len >= 8)
    {
        *(se_u64_t *)d = val64;
        d += 8;
        len -= 8;
    }
    while (len >= 4)
    {
        *(se_u32_t *)d = val32;
        d += 4;
        len -= 4;
    }
    while (len--)
    {
        *d++ = val;
    }
    return d;
}