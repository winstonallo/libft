#ifndef ALLOC_H
#define  ALLOC_H

#include "stddef.h"

void *ft_realloc(void *old_buf, size_t bytes_new, size_t bytes_old);
void *ft_calloc(size_t nmemb, size_t size);
char *ft_strdup(const char *src);

#endif
