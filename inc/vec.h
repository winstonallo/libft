#ifndef VEC_H
#define VEC_H

#include <stddef.h>
#include <stdio.h>

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

// Appends `elem` to `vec`, reallocating if necessary. Returns -1 if reallocation fails.
int vec_push(Vec *const vec, const void *const elem);

// Appends `elems` to `vec`, reallocating if necessary. Returns -1 if reallocation fails.
int vec_push_many(Vec *const vec, const void *const elems, const size_t n_elems);

// Removes the element at `idx` from `vec`, and returns the popped element. Returns `-1`
// if the `idx` is out of range. Negative indices wrap around (-1 is the last element, etc.).
// Attempts to copy the popped element into `out` if it is not `NULL`.
int vec_pop(Vec *const vec, const ssize_t idx, void *const out);

// Removes the elements between `start` and `end` (inclusive) from `vec`, and returns the popped element. Returns `-1`
// if `start` is out of range. If `end` is out of range, removes until `vec->n_elems`.
// Attempts to copy the popped elements into `out` if it is not `NULL`.
int vec_pop_range(Vec *const vec, const size_t start, const size_t end, void *const out);

// Frees the heap-allocated memory in `vec` and resets all fields.
void vec_delete(Vec *vec);

#endif
