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
    size_t i;
    unsigned char *a0 = (unsigned char *)a;
    unsigned char *b0 = (unsigned char *)b;

    i = 0;
    if (n == 0) {
        return 0;
    }
    while (i < n) {
        if (a0[i] != b0[i]) {
            return a0[i] - b0[i];
        }
        i++;
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
ft_memset(void *dest, int c, size_t n) {
    unsigned char *tmp;

    tmp = (unsigned char *)dest;
    while (n--) {
        *tmp++ = (unsigned char)c;
    }

    return dest;
}
