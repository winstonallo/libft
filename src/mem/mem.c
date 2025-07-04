#include <mem.h>
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

// Performs block copy with `movsb` on x86-84, falls back to naive memcpy
// on other architectures.
//
// `dst` and `src` MAY overlap.
void *
ft_memcpy(void *dest, const void *src, size_t n) {
    if (dest == src) {
        return dest;
    }

#ifdef __x86_64__
    __asm__ volatile("mov %0, %%rsi;"
                     "mov %1, %%rdi;"
                     "cld;"
                     "rep movsb"
                     : "+a"(src), "+d"(dest)
                     : "c"(n)
                     : "memory", "flags", "rsi", "rdi");
#else
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if (!dest || !src || n == 0) {
        return dest;
    }

    if (d < s || d >= s + n) {
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else {
        for (size_t i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }

#endif
    return (dest);
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
