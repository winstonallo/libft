#ifndef VEC_H
#define VEC_H

#include <stddef.h>

typedef struct Vec {
    void *data;
    size_t n_elems;
    // Size of the type stored.
    size_t elem_size;
    // Allocated elements.
    size_t capacity;
} Vec;

// Allocates a new `Vec`, copying `n_elems * elem_size` bytes from `data` into
// a heap-allocated buffer.
// Preallocates `capacity * elem_size` bytes if it is set to a positive value.
// Note that capacity must be larger than or equal to `n_elems`.
int vec_new(Vec *vec, const void *const data, const size_t n_elems, const size_t elem_size, const size_t capacity);

// Appends `elem` to `vec`, reallocating if necessary.
int vec_push(Vec *const vec, const void *const elem);

int vec_push_many(Vec *const vec, const void *const elems, const size_t n_elems);

void vec_delete(Vec *vec);

#endif
