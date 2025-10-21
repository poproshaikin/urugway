#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static inline void*
emplace_on_heap(const void *obj, size_t size) {
    void* on_heap = malloc(size);
    memcpy(on_heap, obj, size);
    return on_heap;
}

static inline ssize_t
find_in_str(char c, const char* str) {
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (c == str[i]) {
            return i;
        }
    }

    return -1;
}

static inline char*
substr(const char* str, size_t start, size_t end) {
    size_t len = end - start + 1;
    char* new_str = (char*)malloc(len + 1);
    memcpy(new_str, str + start, len);
    new_str[len] = '\0';
    return new_str;
}

#endif