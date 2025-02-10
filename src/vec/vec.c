#include "vec/vec.h"
#include "alloc/alloc.h"
#include "mem/mem.h"
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

void *
vec_init(Vec *vec, uint64_t elem_size) {
    vec->data = ft_calloc(VEC_DEFAULT_CAPACITY, elem_size);
    if (!vec->data) {
        return NULL;
    }

    vec->capacity = VEC_DEFAULT_CAPACITY;
    vec->size = 0;
    vec->elem_size = elem_size;

    return vec;
}

void
vec_destroy(Vec *vec) {
    free(vec->data);
}

int
vec_push(Vec *vec, const void *elem) {
    if (vec->size == vec->capacity) {
        void *data = ft_realloc(vec->data, (vec->capacity * vec->elem_size) * 2, (vec->capacity * vec->elem_size));
        if (!data) {
            vec_destroy(vec);
            return -1;
        }
        vec->data = data;
        vec->capacity *= 2;
    }

    ft_memcpy((uint8_t *)vec->data + (vec->size * vec->elem_size), elem, vec->elem_size);
    vec->size++;
    return 0;
}

void *
vec_get(Vec *vec, uint64_t index) {
    if (index >= vec->size) {
        errno = EINVAL;
        return NULL;
    }

    return (uint8_t *)vec->data + (index * vec->elem_size);
}
