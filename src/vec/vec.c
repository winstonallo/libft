
#include "vec.h"
#include "alloc.h"
#include "mem.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

__attribute__((always_inline)) static inline bool
size_t_product_overflows(const size_t a, const size_t b) {
    return b != 0 && a > SIZE_MAX / b;
}

int
vec_new(Vec *const vec, const void *const data, const size_t n_elems, const size_t elem_size, const size_t capacity) {
    assert(vec != NULL);
    assert(elem_size != 0);
    assert(!size_t_product_overflows(n_elems, elem_size));
    assert(!size_t_product_overflows(capacity, elem_size));
    assert(capacity == 0 || capacity >= n_elems);

    const size_t actual_capacity = capacity > 0 ? capacity : n_elems;
    const size_t input_bytes = n_elems * elem_size;
    const size_t capacity_bytes = actual_capacity * elem_size;

    if ((vec->data = malloc(capacity_bytes)) == NULL) {
        return -1;
    }

    if (data != NULL && n_elems > 0) {
        ft_memcpy(vec->data, data, input_bytes);
    }

    vec->capacity = capacity > 0 ? capacity : n_elems;
    vec->elem_size = elem_size;
    vec->n_elems = n_elems;
    return 0;
}

int
vec_push(Vec *const vec, const void *const elem) {
    assert(vec != NULL);
    assert(elem != NULL);

    if (vec->capacity < (vec->n_elems + 1)) {
        const size_t new_capacity = vec->capacity * 2;
        void *new_data = ft_realloc(vec->data, new_capacity * vec->elem_size, vec->capacity * vec->elem_size);
        if (new_data == NULL) {
            return -1;
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }

    ft_memcpy(vec->data + (vec->n_elems * vec->elem_size), elem, vec->elem_size);
    vec->n_elems += 1;
    return 0;
}

int
vec_push_many(Vec *const vec, const void *const elems, const size_t n_elems) {
    assert(vec != NULL);
    assert(elems != NULL);

    if (vec->capacity < (vec->n_elems + n_elems)) {
        size_t new_capacity = vec->capacity;
        while (new_capacity < vec->n_elems + n_elems) {
            new_capacity *= 2;
        }
        void *new_data = ft_realloc(vec->data, new_capacity * vec->elem_size, vec->capacity * vec->elem_size);
        if (new_data == NULL) {
            return -1;
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }

    ft_memcpy(vec->data + (vec->n_elems * vec->elem_size), elems, vec->elem_size * n_elems);
    vec->n_elems += n_elems;
    return 0;
}

int
vec_pop(Vec *const vec, const ssize_t idx, void *const out) {
    assert(vec != NULL);

    const size_t actual_idx = idx >= 0 ? idx : (ssize_t)vec->n_elems + idx;
    if (actual_idx >= vec->n_elems) {
        return -1;
    }

    if (out != NULL) {
        ft_memcpy(out, vec->data + (actual_idx * vec->elem_size), vec->elem_size);
    }

    if (idx == -1 || actual_idx == vec->n_elems - 1) {
        vec->n_elems--;
        return 0;
    }

    const size_t remaining = vec->n_elems - idx - 1;
    vec->n_elems--;

    ft_memcpy(vec->data + (actual_idx * vec->elem_size), vec->data + ((actual_idx + 1) * vec->elem_size), remaining * vec->elem_size);

    return 0;
}

int
vec_pop_range(Vec *const vec, const size_t start, size_t end, void *const out) {
    assert(vec != NULL);
    assert(end >= start);
    assert(start < vec->n_elems);

    if (end >= vec->n_elems) {
        end = vec->n_elems - 1;
    }

    size_t n_elems = end - start + 1;

    if (out != NULL) {
        ft_memcpy(out, vec->data + (start * vec->elem_size), vec->elem_size * n_elems);
    }

    if (end == vec->n_elems - 1) {
        vec->n_elems -= n_elems;
        return 0;
    }

    const size_t remaining = vec->n_elems - start - n_elems;
    vec->n_elems -= n_elems;

    ft_memcpy(vec->data + (start * vec->elem_size), vec->data + ((end + 1) * vec->elem_size), remaining * vec->elem_size);

    return 0;
}

void
vec_delete(Vec *vec) {
    free(vec->data);
    *vec = (Vec){0};
}
