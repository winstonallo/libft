#include "alloc.h"
#include "mem.h"
#include "stdlib.h"
#include <stdbool.h>

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
ft_substr(char const *str, unsigned int start, size_t len) {
    char *dest;

    if (start >= ft_strlen(str)) {
        return (ft_calloc(1, sizeof(char)));
    }

    if (ft_strlen(str + start) < len) {
        len = ft_strlen(str + start);
    }

    dest = malloc((len + 1) * sizeof(char));
    if (!dest) {
        return NULL;
    }

    ft_memcpy(dest, str + start, len + 1);

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

short
ft_strncmp(const char *a, const char *b, size_t n) {
    return ft_memcmp(a, b, n);
}

void
ft_strncpy(char *dst, const char *src, size_t size) {
    ft_memcpy(dst, src, size);
}

char *
ft_strjoin(char *a, char *b) {

    if (!a) {

        a = malloc(1 * sizeof(char));
        if (!a) {
            return (NULL);
        }

        a[0] = '\0';
    }

    size_t a_len = ft_strlen(a);
    size_t b_len = ft_strlen(b);

    char *dest = malloc((a_len + b_len + 1) * sizeof(char));
    if (!dest) {
        return (free(a), NULL);
    }

    ft_memcpy(dest, a, a_len);
    ft_memcpy(dest + a_len, b, b_len);
    dest[a_len + b_len] = '\0';

    return dest;
}

__attribute__((always_inline)) static inline char **
free_array(char **arr) {

    for (size_t i = 0; arr[i]; ++i) {
        free(arr[i]);
    }

    free(arr);
    return (NULL);
}

__attribute__((always_inline)) static inline size_t
count_words(const char *str, char delimiter) {
    size_t words = 0;
    bool in_word = 0;

    while (*str) {
        if (*str == delimiter) {
            in_word = false;
        } else if (!in_word) {
            words++;
            in_word = true;
        }
        str++;
    }
    return words;
}

char **
ft_split(char const *str, char delimiter) {
    if (!str || !str[0]) {
        return NULL;
    }

    size_t word_count = count_words(str, delimiter);

    char **res = malloc(sizeof(char *) * (word_count + 1));
    if (!res) {
        return NULL;
    }

    size_t idx = 0;
    while (*str) {
        while (*str == delimiter) {
            str++;
        }

        if (!*str) {
            break;
        }

        const char *word_start = str;
        size_t word_len = 0;
        while (*str && *str != delimiter) {
            word_len++;
            str++;
        }

        res[idx] = malloc(word_len + 1);
        if (!res[idx]) {
            return free_array(res);
        }

        ft_memcpy(res[idx], word_start, word_len + 1);
        idx++;
    }

    res[idx] = NULL;
    return res;
}
