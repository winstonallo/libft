#include "libft.h"
#include <errno.h>
#include <stdlib.h>

// Allocates a buffer of size `bytes_new` and copies `old_buf` into it.
// Returns NULL on malloc failure, or if `bytes_old` is larger than
// `bytes_new`.
void *
ft_realloc(void *old_buf, size_t bytes_new, size_t bytes_old) {
    if (bytes_new < bytes_old) {
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

// Allocates a buffer of size `nmemb * size`, 0-initialized bytes.
// Returns NULL on malloc failure, or if the `nmemb * size` would
// result in an overflow.
void *
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

    ft_bzero(dest, size * nmemb);
    return dest;
}

char *
ft_strdup(const char *src) {
    char *dest;
    int size;

    size = ft_strlen(src) + 1;

    dest = (char *)malloc(sizeof(char) * (size));
    if (!dest) {
        return NULL;
    }

    ft_memcpy(dest, src, size);
    return (char *)dest;
}
