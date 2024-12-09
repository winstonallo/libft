#include "mem.h"
#include <stddef.h>
#include <stdint.h>

void *
ft_memsrch(const void *haystack, int needle, uint64_t n) {
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
ft_memcmp(const void *a, const void *b, uint64_t n) {
    uint64_t idx = 0;
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
ft_memcpy(void *dest, const void *src, uint64_t n) {
    if (!dest && !src) {
        return NULL;
    }

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__)
    __asm__ __volatile__("rep movsb" : : "S"(src), "D"(dest), "c"(n) : "memory");
#else
    uint64_t i = 0;

    while (i < n) {
        ((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
        i++;
    }
#endif

    return dest;
}

void *
ft_memset(void *dest, int c, uint64_t len) {
    long dst = (long)dest;

    if (len >= 8) {

        // Create a "fat character" of size OPTSIZ bits, and set all of its bytes to `c`.
        op_t C = (uint8_t)c;
        C |= C << 8;
        C |= C << 16;
        if (OPTSIZ == 8) {
            C |= (C << 16) << 16;
        }

        // Align the destination pointer to the word size (OPTSIZ).
        while (dst % OPTSIZ != 0) {
            ((uint8_t *)dst)[0] = c;
            ++dst;
            --len;
        }

        // Now that the pointer is aligned, we can bring out the big guns -
        // spam `c` as fat characters, 8 at a time.
        // Writing in blocks reduces loop iterations and takes advantage of
        // memory bandwidth.
        uint64_t n_blocks = len / (OPTSIZ * 8);
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

        uint64_t n_remaining_u64 = len / OPTSIZ;
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
