#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stdint.h>

#define VEC_DEFAULT_CAPACITY 4

typedef struct Vec {
    void *data;
    uint64_t size;
    uint64_t capacity;
    uint64_t elem_size;
} Vec;

// Initializes a Vec object.
void *vec_init(Vec *vec, uint64_t elem_size);

// Destroys the Vec, freeing any allocated memory.
void vec_destroy(Vec *vec);

// Appends `elem` to the Vec.
int vec_push(Vec *vec, const void *elem);

// Retrieves the element at `index`. Returns NULL and sets errno to `EINVAL` if
// the index is out of bounds.
void *vec_get(Vec *vec, uint64_t index);

#endif
