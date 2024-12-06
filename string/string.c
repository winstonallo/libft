#include "alloc.h"
#include "mem.h"
#include "stdlib.h"

size_t
ft_strlen(const char *str) {
    size_t len;

    len = 0;
    while (*str) {
        str++;
        len++;
    }

    return len;
}

char *
ft_substr(char const *s, unsigned int start, size_t len) {
    char *dest;

    if (start >= ft_strlen(s)) {
        return (ft_calloc(1, sizeof(char)));
    }

    if (ft_strlen(s + start) < len) {
        len = ft_strlen(s + start);
    }

    dest = malloc((len + 1) * sizeof(char));
    if (!dest) {
        return NULL;
    }

    ft_memcpy(dest, s + start, len + 1);

    return dest;
}

char *
ft_strtrim(char const *str, char const *set) {
    if (!str) {
        return NULL;
    }

    size_t len = ft_strlen(str);

    if (!set || set[0] == '\0') {
        return ft_memdup(str, len + 1);
    }

    char *start = (char *)str;
    char *end = (char *)str + len - 1;

    while (*start && ft_memsrch(set, *start, ft_strlen(set))) {
        start++;
    }

    while (end >= start && ft_memsrch(set, *end, ft_strlen(set))) {
        end--;
    }

    size_t new_len = end >= start ? (end - start + 1) : 0;

    char *res = malloc(new_len + 1);
    if (!res) {
        return NULL;
    }

    ft_memcpy(res, start, new_len);
    res[new_len] = '\0';

    return res;
}
