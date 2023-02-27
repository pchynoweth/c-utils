#include "cutils_heap_private.h"

#include <string.h>

static void* element(cutils_heap_t* heap, size_t i) {
    return (char*)heap->data + (i * heap->elem_size);
}

static inline bool has_parent(size_t i) {
    return i != 0;
}

static inline size_t parent_index(size_t i) {
    return (i-1)/2;
}

static inline size_t left_child_index(size_t i) {
    return (i*2) + 1;
}

static inline size_t right_child_index(size_t i) {
    return (i*2) + 2;
}

static void* parent(cutils_heap_t* heap, size_t i) {
    if (i == 0) return NULL;
    return element(heap, parent_index(i));
}

static void* left_child(cutils_heap_t* heap, size_t i) {
    return element(heap, left_child_index(i));
}

static void* right_child(cutils_heap_t* heap, size_t i) {
    return element(heap, right_child_index(i));
}

size_t get_index(cutils_heap_t const* heap, void const* elem) {
    size_t difference = (char const*)elem - (char const*)heap->data;
    return difference / heap->elem_size;
}

static void swap(void* lhs, void* rhs, size_t size) {
    void* tmp = alloca(size);
    memcpy(tmp, lhs, size);
    memcpy(lhs, rhs, size);
    memcpy(rhs, tmp, size);
}

cutils_heap_t* cutils_heap_create(size_t elem_size, cutils_cmp_t cmp) {
    cutils_heap_t* ret = calloc(1, sizeof(cutils_heap_t));
    ret->elem_size = elem_size;
    ret->cmp = cmp;
    return ret;
}

void cutils_heap_free(cutils_heap_t* heap) {
    free(heap->data);
    free(heap);
}

size_t cutils_heap_size(cutils_heap_t const* heap) {
    if (heap == NULL) return 0;
    return heap->size;
}

void cutils_heap_push(cutils_heap_t* heap, void* elem) {
    if (heap->capacity == heap->size) {
        heap->capacity = (heap->capacity) ? heap->capacity * 2 : 8;
        void* data = realloc(heap->data, heap->elem_size * heap->capacity);
        if (!data) abort();
        heap->data = data;
    }

    memcpy(
        element(heap, heap->size),
        elem,
        heap->elem_size
    );

    size_t i = heap->size;
    while (has_parent(i) && heap->cmp(element(heap, i), parent(heap, i)) < 0) {
        swap(parent(heap, i), element(heap, i), heap->elem_size);
        i = parent_index(i);       
    }
    ++heap->size;
}

void const* cutils_heap_pop(cutils_heap_t* heap) {
    if (!heap || heap->size == 0) return NULL;
    
    --heap->size;
    swap(element(heap, 0), element(heap, heap->size), heap->elem_size);
    
    size_t i = 0;
    while (left_child_index(i) < heap->size) {
        void* smallest_child = left_child(heap, i);
        if (right_child_index(i) < heap->size && heap->cmp(right_child(heap, i), smallest_child) < 0) {
            smallest_child = right_child(heap, i);
        }
        
        if (heap->cmp(smallest_child, element(heap, i)) >= 0) {
            break;
        }

        swap(smallest_child, element(heap, i), heap->elem_size);
        i = get_index(heap, smallest_child);
    }
    
    return element(heap, heap->size);
}

void const* cutils_heap_peek(cutils_heap_t* heap) {
    if (!heap || heap->size == 0) return NULL;
    return heap->data;
}