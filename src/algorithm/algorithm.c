#include "algorithm.h"

#include <string.h>
#include <stdio.h>

static void* midpoint(void* first, void* last, size_t elem_size) {
    size_t i = ((char*)last - (char*)first) / elem_size;
    i /= 2;
    return (char*)first + (i * elem_size);
}

void* cutils_lower_bound(void* buf, size_t len, size_t elem_size, cutils_cmp_t cmp, void const* value) {
    char* first = buf;
    char* last = first + len * elem_size;
    while (first != last) {
        char* mid = midpoint(first, last, elem_size);
        if (cmp(mid, value) < 0) {
            first = mid + elem_size;
        } else {
            last = mid;
        }
    }

    return first;
}

void* cutils_upper_bound(void* buf, size_t len, size_t elem_size, cutils_cmp_t cmp, void const* value) {
    char* first = buf;
    char* last = first + len * elem_size;
    while (first != last) {
        char* mid = midpoint(first, last, elem_size);
        if (cmp(value, mid) < 0) {
            last = mid;
        } else {
            first = mid + elem_size;
        }
    }

    return first;
}

void cutils_swap(void* lhs, void* rhs, size_t elem_size) {
    void* tmp = alloca(elem_size);
    memcpy(tmp, lhs, elem_size);
    memcpy(lhs, rhs, elem_size);
    memcpy(rhs, tmp, elem_size);
}

static inline void* last_element(void* buf, size_t len, size_t elem_size) {
    return (char*)buf + ((len) ? len - 1 : 0) * elem_size;
}

void cutils_reverse(void* buf, size_t len, size_t elem_size) {
    char* first = buf;
    char* last = last_element(buf, len, elem_size);
    while (first < last) {
        cutils_swap(first, last, elem_size);
        first += elem_size;
        last -= elem_size;
    }
}

void* cutils_next_permutation(void* buf, size_t len, size_t elem_size, cutils_cmp_t cmp) {
    char* first = buf;
    char* last = last_element(buf, len, elem_size);
    char* r_last = first - elem_size;

    // find the find the first element that is not in reverse sorted order
    char* left = last - elem_size;
    while (left != r_last && cmp(left, left + elem_size) >= 0) {
        left -= elem_size;
    }

    if (left != r_last) {
        // find the first element that is greater than the element found above
        char* right = last;
        while (cmp(left, right) > 0) {
            right -= elem_size;
        }

        cutils_swap(left, right, elem_size);
    }

    cutils_reverse(left + elem_size, (last - left) / elem_size, elem_size);

    return (left == r_last) ? NULL : buf;
}