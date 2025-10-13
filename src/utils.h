#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

inline void*
emplace_on_heap(void *obj, size_t size) {
    void* on_heap = malloc(size);
    memcpy(on_heap, obj, size);
    return on_heap;
}

#endif