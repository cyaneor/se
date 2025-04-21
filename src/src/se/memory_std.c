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
    se_runtime_return_ifn(n, dst);

    se_u8_t       *d = se_ptr_cast(se_u8_t, dst);
    const se_u8_t *s = se_ptr_cast(const se_u8_t, src);

    // Handle small copies or misaligned pointers
    if (n < 64 || !se_ptr_is_aligned(d, 16) || !se_ptr_is_aligned(s, 16))
    {
        while (n--)
        {
            *d++ = *s++;
        }
        return d;
    }

#ifdef SE_COMPILE_OPTION_AVX512
    // AVX512: 64-byte chunks
    while (n >= 64)
    {
        __m512i vec = _mm512_loadu_si512(s);
        _mm512_storeu_si512(d, vec);
        s += 64;
        d += 64;
        n -= 64;
    }
#endif // SE_COMPILE_OPTION_AVX512
#ifdef SE_COMPILE_OPTION_AVX2
    // AVX2: 32-byte chunks
    while (n >= 32)
    {
        __m256i vec = _mm256_loadu_si256((__m256i const *)s);
        _mm256_storeu_si256((__m256i *)d, vec);
        s += 32;
        d += 32;
        n -= 32;
    }
#endif // SE_COMPILE_OPTION_AVX2
#ifdef SE_COMPILE_OPTION_SSE2
    // SSE4/SSE2: 16-byte chunks
    while (n >= 16)
    {
        __m128i vec = _mm_loadu_si128((__m128i const *)s);
        _mm_storeu_si128((__m128i *)d, vec);
        s += 16;
        d += 16;
        n -= 16;
    }
#endif // SE_COMPILE_OPTION_SSE2
    // Handle remaining bytes
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
    se_runtime_return_ifn(n, dst);

    se_u8_t       *d = se_ptr_cast(se_u8_t, dst) + n;       // Point to end of dst
    const se_u8_t *s = se_ptr_cast(const se_u8_t, src) + n; // Point to end of src

    // Handle small copies or misaligned pointers
    // Check alignment at the end (d and s) for reverse copying
    if (n < 64 || !se_ptr_is_aligned(d, 16) || !se_ptr_is_aligned(s, 16))
    {
        while (n--)
        {
            *(--d) = *(--s);
        }
        return d;
    }

#ifdef SE_COMPILE_OPTION_AVX512
    // AVX512: 64-byte chunks
    while (n >= 64)
    {
        s -= 64;
        d -= 64;
        __m512i vec = _mm512_loadu_si512(s);
        _mm512_storeu_si512(d, vec);
        n -= 64;
    }
#endif // SE_COMPILE_OPTION_AVX512
#ifdef SE_COMPILE_OPTION_AVX2
    // AVX2: 32-byte chunks
    while (n >= 32)
    {
        s -= 32;
        d -= 32;
        __m256i vec = _mm256_loadu_si256((__m256i const *)s);
        _mm256_storeu_si256((__m256i *)d, vec);
        n -= 32;
    }
#endif // SE_COMPILE_OPTION_AVX2
#ifdef SE_COMPILE_OPTION_SSE2
    // SSE4/SSE2: 16-byte chunks
    while (n >= 16)
    {
        s -= 16;
        d -= 16;
        __m128i vec = _mm_loadu_si128((__m128i const *)s);
        _mm_storeu_si128((__m128i *)d, vec);
        n -= 16;
    }
#endif // SE_COMPILE_OPTION_SSE2
    // Handle remaining bytes
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
    se_runtime_return_ifn(n, nullptr);

    const se_u8_t *l = se_ptr_cast(const se_u8_t, lhs);
    const se_u8_t *r = se_ptr_cast(const se_u8_t, rhs);

    // Handle small sizes or misaligned pointers
    if (n < 64 || !se_ptr_is_aligned(l, 16) || !se_ptr_is_aligned(r, 16))
    {
        for (se_usize_t i = 0; i < n; i++)
        {
            if (l[i] != r[i])
            {
                return &l[i];
            }
        }
        return nullptr;
    }

#ifdef SE_COMPILE_OPTION_AVX512
    // AVX512: 64-byte chunks
    while (n >= 64)
    {
        __m512i  l_vec = _mm512_loadu_si512(l);
        __m512i  r_vec = _mm512_loadu_si512(r);
        se_u64_t mask  = _mm512_cmpeq_epi8_mask(l_vec, r_vec);
        if (mask != 0xFFFFFFFFFFFFFFFFULL)
        {
            // Find first differing byte
            se_ulong_t index;
            se_bit_scan_forward64(&index, ~mask);
            return &l[index];
        }
        l += 64;
        r += 64;
        n -= 64;
    }
#endif // SE_COMPILE_OPTION_AVX512
#ifdef SE_COMPILE_OPTION_AVX2
    // AVX2: 32-byte chunks
    while (n >= 32)
    {
        __m256i   l_vec = _mm256_loadu_si256((__m256i const *)l);
        __m256i   r_vec = _mm256_loadu_si256((__m256i const *)r);
        __m256i   cmp   = _mm256_cmpeq_epi8(l_vec, r_vec);
        se_sint_t mask  = _mm256_movemask_epi8(cmp);
        if (mask != 0xFFFFFFFF)
        {
            // Find first differing byte
            se_ulong_t index;
            se_bit_scan_forward32(&index, ~mask);
            return &l[index];
        }
        l += 32;
        r += 32;
        n -= 32;
    }
#endif // SE_COMPILE_OPTION_AVX2
#ifdef SE_COMPILE_OPTION_SSE2
    // SSE2: 16-byte chunks
    while (n >= 16)
    {
        __m128i   l_vec = _mm_loadu_si128((__m128i const *)l);
        __m128i   r_vec = _mm_loadu_si128((__m128i const *)r);
        __m128i   cmp   = _mm_cmpeq_epi8(l_vec, r_vec);
        se_sint_t mask  = _mm_movemask_epi8(cmp);
        if (mask != 0xFFFF)
        {
            // Find first differing byte
            se_ulong_t index;
            se_bit_scan_forward32(&index, ~mask);
            return &l[index];
        }
        l += 16;
        r += 16;
        n -= 16;
    }
#endif // SE_COMPILE_OPTION_SSE2
    // Handle remaining bytes
    for (se_usize_t i = 0; i < n; i++)
    {
        if (l[i] != r[i])
        {
            return &l[i];
        }
    }

    return nullptr;
}

const void *
se_memory_std_compare_reverse(const void *lhs, const void *rhs, se_usize_t n)
{
    se_runtime_check(lhs && rhs, SE_RUNTIME_ERROR_NULL_POINTER);
    se_runtime_return_ifn(n, nullptr);

    const se_u8_t *l = se_ptr_cast(const se_u8_t, lhs) + n; // Point to end of lhs
    const se_u8_t *r = se_ptr_cast(const se_u8_t, rhs) + n; // Point to end of rhs

    // Handle small sizes or misaligned pointers
    if (n < 64 || !se_ptr_is_aligned(l, 16) || !se_ptr_is_aligned(r, 16))
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
    // AVX512: 64-byte chunks
    while (n >= 64)
    {
        l -= 64;
        r -= 64;
        __m512i  l_vec = _mm512_loadu_si512(l);
        __m512i  r_vec = _mm512_loadu_si512(r);
        se_u64_t mask  = _mm512_cmpeq_epi8_mask(l_vec, r_vec);
        if (mask != 0xFFFFFFFFFFFFFFFFULL)
        {
            // Find last differing byte
            se_ulong_t index;
            se_bit_scan_reverse64(&index, ~mask);
            return &l[index];
        }
        n -= 64;
    }
#endif // SE_COMPILE_OPTION_AVX512
#ifdef SE_COMPILE_OPTION_AVX2
    // AVX2: 32-byte chunks
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
            // Find last differing byte
            se_ulong_t index;
            se_bit_scan_reverse32(&index, ~mask);
            return &l[index];
        }
        n -= 32;
    }
#endif // SE_COMPILE_OPTION_AVX2
#ifdef SE_COMPILE_OPTION_SSE2
    // SSE2: 16-byte chunks
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
            // Find last differing byte
            se_ulong_t index;
            se_bit_scan_reverse32(&index, ~mask);
            return &l[index];
        }
        n -= 16;
    }
#endif // SE_COMPILE_OPTION_SSE2
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
    se_runtime_return_ifn(len, dst);

    se_u8_t       *d       = (se_u8_t *)dst;
    const se_u64_t pattern = val * 0x0101010101010101ULL;

    // 1. Точечная обработка 16, 64, 256 байт
    switch (len)
    {
    case 16: // SSE2/AVX оптимизация
#ifdef SE_COMPILE_OPTION_AVX2
        _mm_store_si128((__m128i *)d, _mm256_castsi256_si128(_mm256_set1_epi8(val)));
#elif defined(SE_COMPILE_OPTION_SSE2)
        _mm_storeu_si128((__m128i *)d, _mm_set1_epi8(val));
#else
        *(se_u64_t *)d       = pattern;
        *(se_u64_t *)(d + 8) = pattern;
#endif
        return dst;

    case 64: // AVX2/SSE2 оптимизация
#ifdef SE_COMPILE_OPTION_AVX2
        _mm256_storeu_si256((__m256i *)d, _mm256_set1_epi8(val));
        _mm256_storeu_si256((__m256i *)(d + 32), _mm256_set1_epi8(val));
#elif defined(SE_COMPILE_OPTION_SSE2)
        _mm_storeu_si128((__m128i *)d, _mm_set1_epi8(val));
        _mm_storeu_si128((__m128i *)(d + 16), _mm_set1_epi8(val));
        _mm_storeu_si128((__m128i *)(d + 32), _mm_set1_epi8(val));
        _mm_storeu_si128((__m128i *)(d + 48), _mm_set1_epi8(val));
#else
        for (se_sint_t i = 0; i < 8; ++i)
        {
            *(se_u64_t *)(d + i * 8) = pattern;
        }
#endif
        return dst;

    case 256: // AVX-512/AVX2 оптимизация
#ifdef SE_COMPILE_OPTION_AVX512
        _mm512_storeu_si512((__m512i *)d, _mm512_set1_epi8(val));
        _mm512_storeu_si512((__m512i *)(d + 64), _mm512_set1_epi8(val));
        _mm512_storeu_si512((__m512i *)(d + 128), _mm512_set1_epi8(val));
        _mm512_storeu_si512((__m512i *)(d + 192), _mm512_set1_epi8(val));
#elif defined(SE_COMPILE_OPTION_AVX2)
        for (se_sint_t i = 0; i < 8; ++i)
        {
            _mm256_storeu_si256((__m256i *)(d + i * 32), _mm256_set1_epi8(val));
        }
#else
        for (se_sint_t i = 0; i < 32; ++i)
        {
            *(se_u64_t *)(d + i * 8) = pattern;
        }
#endif
        return dst;

    default:
        break;
    }

    // 2. Ручное выравнивание указателя
    if (!se_ptr_is_aligned(d, 64))
    {
        const size_t align = 64 - ((se_uintptr_t)d % 64);
        size_t       i     = 0;
        // 8-байтные операции для быстрого заполнения
        while (i + 8 <= align)
        {
            *(se_u64_t *)(d + i) = pattern;
            i += 8;
        }
        // Оставшиеся байты
        while (i < align)
        {
            d[i++] = val;
        }
        d += align;
        len -= align;
    }

    // 3. AVX-512 с Non-Temporal Stores
#ifdef SE_COMPILE_OPTION_AVX512
    __m512i avx512_val = _mm512_set1_epi8(val);
    while (len >= 64)
    {
        _mm512_stream_si512((__m512i *)d, avx512_val);
        d += 64;
        len -= 64;
    }
    _mm_sfence();
#endif

    // 4. AVX2 для средних блоков
#ifdef SE_COMPILE_OPTION_AVX2
    __m256i avx2_val = _mm256_set1_epi8(val);
    while (len >= 32)
    {
        _mm256_store_si256((__m256i *)d, avx2_val);
        d += 32;
        len -= 32;
    }
#endif

    // 5. SSE2 для остатков
#ifdef SE_COMPILE_OPTION_SSE2
    __m128i sse_val = _mm_set1_epi8(val);
    while (len >= 16)
    {
        _mm_store_si128((__m128i *)d, sse_val);
        d += 16;
        len -= 16;
    }
#endif

    // 6. Финальные остатки
    if (len >= 8)
    {
        *(se_u64_t *)d = pattern;
        d += 8;
        len -= 8;
    }
    if (len >= 4)
    {
        *(se_u32_t *)d = (se_u32_t)pattern;
        d += 4;
        len -= 4;
    }
    while (len--)
        *d++ = val;

    return dst;
}