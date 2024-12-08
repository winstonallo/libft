#include "mem.h"
#include <errno.h>
#include <stdlib.h>

__attribute__((warn_unused_result)) void *
ft_realloc(void *old_buf, size_t bytes_new, size_t bytes_old) {
    if (bytes_new < bytes_old) {
        errno = EINVAL;
        return NULL;
    }

    void *new_buf = malloc(bytes_new);
    if (!new_buf) {
        return NULL;
    }

    ft_memcpy(new_buf, old_buf, bytes_old);

    free(old_buf);

    return new_buf;
}

__attribute__((warn_unused_result)) void *
ft_calloc(size_t nmemb, size_t size) {
    void *dest;

    dest = NULL;
    if (nmemb == 0 || size == 0) {
        return malloc(0);
    }

    if ((size * nmemb) / nmemb != size) {
        errno = ERANGE;
        return NULL;
    }

    dest = malloc(nmemb * size);
    if (!dest) {
        return NULL;
    }

    ft_memset(dest, 0, size * nmemb);
    return dest;
}

__attribute__((warn_unused_result)) void *
ft_memdup(const void *src, const size_t bytes) {
    char *dest;

    dest = (char *)malloc(bytes);
    if (!dest) {
        return NULL;
    }

    ft_memcpy(dest, src, bytes);
    return (char *)dest;
}
