#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>

struct cutils_heap;
typedef struct cutils_heap cutils_heap_t;

typedef int (*cutils_cmp_t)(void const*, void const*);

cutils_heap_t* cutils_heap_create(size_t elem_size, cutils_cmp_t);
void cutils_heap_free(cutils_heap_t* heap);

size_t cutils_heap_size(cutils_heap_t const* heap);
static inline bool cutils_heap_is_empty(cutils_heap_t const* heap) {
    return cutils_heap_size(heap) == 0;
}

void cutils_heap_push(cutils_heap_t* heap, void* elem);
void const* cutils_heap_pop(cutils_heap_t* heap);
void const* cutils_heap_peek(cutils_heap_t* heap);

#ifdef __cplusplus
}
#endif