#pragma once

#include "cutils_heap.h"

struct cutils_heap {
    size_t elem_size;
    size_t capacity;
    size_t size;
    void* data;
    cutils_cmp_t cmp;
};
