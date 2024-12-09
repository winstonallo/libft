#ifndef ALLOC_H
#define ALLOC_H

#include "stddef.h"
#include <stdint.h>

// Allocates a buffer of size `bytes_new` and copies `old_buf` into it.
// Returns NULL on malloc failure, or if `bytes_old` is larger than
// `bytes_new`.
void *ft_realloc(void *old_buf, uint64_t bytes_new, uint64_t bytes_old) __attribute__((warn_unused_result));

// Allocates a buffer of size `nmemb * size`, 0-initialized bytes.
// Returns NULL on malloc failure, or if `nmemb * size` would
// result in a `uint64_t` overflow.
void *ft_calloc(uint64_t nmemb, uint64_t size) __attribute__((warn_unused_result));

// Returns a heap-allocated duplicate of `src`.
// Returns NULL on malloc failure.
void *ft_memdup(const void *src, const uint64_t bytes) __attribute__((warn_unused_result));

#endif
