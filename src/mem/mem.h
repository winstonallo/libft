#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <stdint.h>

#if __SIZEOF_POINTER__ == 8
// `uint<CPU-architecture>_t`
typedef uint64_t op_t;
#else
// `uint<CPU-architecture>_t`
typedef uint32_t op_t;
#endif

#define OPTSIZ sizeof(op_t)

// Returns a pointer to the first occurence of `needle` in the first `n_bytes` of `haystack`.
// If nothing is found, returns a NULL pointer.
void *ft_memsrch(const void *haystack, int needle, uint64_t n_bytes);

// Compares the first `n_bytes` bytes `a` to `b`. Returns `0` if they are equal,
// or a non-zero u8 if not.
//
// Safety:
// If `a` and `b` are equal and both point to allocated regions shorter than `n_bytes`,
// this function will access invalid memory.
short ft_memcmp(const void *a, const void *b, uint64_t n_bytes);

// Copies the first `n_bytes` of `src` into `dest`.
//
// Safety:
// If `n_bytes` is bigger than `src` or `dest`, this might result in invalid
// memory access.
void *ft_memcpy(void *dest, const void *src, uint64_t n_bytes);

// Sets the first `n_bytes` of `src` to `c`.
//
// Safety:
// If `n_bytes` is bigger than the allocated region `src` is pointing to, this will
// result in invalid memory access.
void *ft_memset(void *src, int c, uint64_t n_bytes);

#endif
