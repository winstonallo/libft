#ifndef ALLOC_H
#define ALLOC_H

#include "stddef.h"

void *ft_realloc(void *old_buf, size_t bytes_new, size_t bytes_old) __attribute__((warn_unused_result));
void *ft_calloc(size_t nmemb, size_t size) __attribute__((warn_unused_result));
void *ft_memdup(const void *src, const size_t bytes) __attribute__((warn_unused_result));

#endif
