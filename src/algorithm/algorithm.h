#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef int (*cutils_cmp_t)(void const*, void const*);

void* cutils_lower_bound(void* buf, size_t len, size_t elem_size, cutils_cmp_t, void const* value);
void* cutils_upper_bound(void* buf, size_t len, size_t elem_size, cutils_cmp_t, void const* value);

void cutils_swap(void* lhs, void* rhs, size_t elem_size);
void cutils_reverse(void* buf, size_t len, size_t elem_size);
void* cutils_next_permutation(void* buf, size_t len, size_t elem_size, cutils_cmp_t);

typedef struct {
    void* begin;
    void* end;
} cutils_range_t;

static inline cutils_range_t cutils_equal_range(
    void* buf,
    size_t len,
    size_t elem_size,
    cutils_cmp_t cmp,
    void const* value
) {
    cutils_range_t range;
    range.begin = cutils_lower_bound(buf, len, elem_size, cmp, value);
    range.end = cutils_upper_bound(buf, len, elem_size, cmp, value);
    return range;
}

#ifdef __cplusplus
}
#endif