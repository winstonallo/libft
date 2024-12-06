#include <stddef.h>
#include <stdint.h>

void *
ft_memchr(const void *s, int c, size_t n) {
    while (n != 0) {
        if (*(unsigned char *)s == (unsigned char)c) {
            return (void *)s;
        }
        n--;
        s++;
    }
    return 0;
}

short
ft_memcmp(const void *s1, const void *s2, size_t n) {
    size_t i;
    unsigned char *s11;
    unsigned char *s22;

    s11 = (unsigned char *)s1;
    s22 = (unsigned char *)s2;
    i = 0;
    if (n == 0) {
        return 0;
    }
    while (i < n) {
        if (s11[i] != s22[i]) {
            return s11[i] - s22[i];
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
ft_memset(void *s, int x, size_t n) {
    unsigned char *p;

    p = (unsigned char *)s;
    while (n--) {
        *p++ = (unsigned char)x;
    }
    return s;
}

void *
ft_memmove(void *dest, const void *src, size_t n) {
    const char *csrc;
    char *cdst;

    cdst = dest;
    csrc = src;
    if (!dest && !src)
        return NULL;
    if (dest < src)
        ft_memcpy(dest, src, n);
    else {
        while (n != 0) {
            n--;
            cdst[n] = csrc[n];
        }
    }
    return dest;
}
