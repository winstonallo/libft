
#include <errno.h>
#include <mem.h>
#include <stdint.h>
#include <stdlib.h>

__attribute__((warn_unused_result)) void *
ft_realloc(void *old_buf, uint64_t bytes_new, uint64_t bytes_old) {
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
ft_calloc(uint64_t nmemb, uint64_t size) {
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
ft_calloc_aligned(uint64_t nmemb, uint64_t size, uint8_t alignment) {

    if (nmemb == 0 || size == 0) {
        return malloc(0);
    }

    if ((size * nmemb) / nmemb != size) {
        errno = ERANGE;
        return NULL;
    }

    uint64_t total_size = nmemb * size + alignment + sizeof(void *);

    void *raw_ptr = malloc(total_size);

    raw_ptr = malloc(total_size);
    if (!raw_ptr) {
        return NULL;
    }

    uintptr_t address = (uintptr_t)raw_ptr + sizeof(void *);
    void *aligned_ptr = (void *)((address + alignment - 1) & ~(alignment - 1));

    ((void **)aligned_ptr)[-1] = raw_ptr;

    ft_memset(aligned_ptr, 0, nmemb * size);
    return aligned_ptr;
}

void
ft_free_aligned(void *ptr) {
    if (ptr) {
        void *raw_ptr = ((void **)ptr)[-1];
        free(raw_ptr);
    }
}

__attribute__((warn_unused_result)) void *
ft_memdup(const void *src, const uint64_t bytes) {
    char *dest;

    dest = (char *)malloc(bytes);
    if (!dest) {
        return NULL;
    }

    ft_memcpy(dest, src, bytes);
    return (char *)dest;
}
