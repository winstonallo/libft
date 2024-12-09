#include "mem.h"
#include <stddef.h>
#include <stdint.h>

void *
ft_memsrch(const void *haystack, int needle, size_t n) {
    while (n != 0) {
        if (*(unsigned char *)haystack == (unsigned char)needle) {
            return (void *)haystack;
        }
        n--;
        haystack++;
    }
    return NULL;
}

short
ft_memcmp(const void *a, const void *b, size_t n) {
    size_t idx = 0;
    unsigned char *a0 = (unsigned char *)a;
    unsigned char *b0 = (unsigned char *)b;

    if (n == 0) {
        return 0;
    }
    while (idx < n) {
        if (a0[idx] != b0[idx]) {
            return a0[idx] - b0[idx];
        }
        idx++;
    }
    return 0;
}

void *
ft_memcpy(void *dest, const void *src, size_t n) {
    if (!dest && !src) {
        return NULL;
    }

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__)
    __asm__ __volatile__("rep movsb" : : "S"(src), "D"(dest), "c"(n) : "memory");
#else
    size_t i = 0;

    while (i < n) {
        ((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
        i++;
    }
#endif

    return dest;
}

void *
ft_memset(void *dest, int c, size_t len) {
    long dst = (long)dest;

    if (len >= 8) {

        // Create a "fat character" of size <CPU architecture> bits, 
        // and set all of its bytes to `c`. This allows for faster writes 
        // than writing byte by byte.
        op_t C;

        C = (unsigned char)c;
        C |= C << 8;
        C |= C << 16;
        if (OPTSIZ == 8) {
            C |= (C << 16) << 16;
        }

        // Write single bytes until the destination pointer is aligned.
        while (dst % OPTSIZ != 0) {
            ((uint8_t *)dst)[0] = c;
            ++dst;
            --len;
        }

        size_t n_blocks = len / (OPTSIZ * 8);
        while (n_blocks > 0) {
            ((op_t *)dst)[0] = C;
            ((op_t *)dst)[1] = C;
            ((op_t *)dst)[2] = C;
            ((op_t *)dst)[3] = C;
            ((op_t *)dst)[4] = C;
            ((op_t *)dst)[5] = C;
            ((op_t *)dst)[6] = C;
            ((op_t *)dst)[7] = C;

            dst += OPTSIZ * 8;
            --n_blocks;
        }

        len %= OPTSIZ * 8;

        size_t n_remaining_u64 = len / OPTSIZ;
        while (n_remaining_u64 > 0) {
            ((op_t *)dst)[0] = C;
            dst += OPTSIZ;
            --n_remaining_u64;
        }

        len %= OPTSIZ;
    }

    while (len > 0) {
        ((uint8_t *)dst)[0] = c;
        ++dst;
        --len;
    }

    return dest;
}
