#ifndef MEM_H
#define MEM_H

#include <stddef.h>

void *ft_memchr(const void *s, int c, size_t n);
short ft_memcmp(const void *s1, const void *s2, size_t n);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memset(void *s, int x, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);

#endif
