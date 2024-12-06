#ifndef MEM_H
#define MEM_H

#include <stddef.h>

void *ft_memsrch(const void *haystack, int needle, size_t n);
short ft_memcmp(const void *a, const void *b, size_t n);
void *ft_memcpy(void *dest, const void *src, size_t n);
void *ft_memset(void *s, int x, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);

#endif
