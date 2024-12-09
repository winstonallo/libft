#include "alloc.h"
#include "mem.h"
#include "stdlib.h"
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

size_t
ft_strlen(const char *str) {
    const char *char_ptr;

    // Process `str` byte-by-byte until `char_ptr` is aligned to a word boundary.
    //
    // Why does the pointer need to be aligned?
    // - CPUs fetch memory in chunks (32 or 64 bits) rather than byte-by-byte.
    // - Starting at an unaligned address may cause additional overhead or slower fetches, because
    //   the CPU could have to fetch twice for the same word.
    //
    // We iterate over the input string one byte at a time until `char_ptr` points
    // to a memory address that is a multiple of `OPTSIZ` (the word size). Once we know it is aligned,
    // we can process the string more efficiently.
    for (char_ptr = str; ((op_t)char_ptr % OPTSIZ) != 0; ++char_ptr) {

        // If we find a null byte before aligment (aka the string length is less than `OPTSIZ - 1`),
        // we return the length.
        if (*char_ptr == '\0') {
            return char_ptr - str;
        }
    }

    const op_t *op_t_ptr = (op_t *)char_ptr;

    // All MSB set.
    op_t himagic = 0x80808080L;
    // All LSB set.
    op_t lomagic = 0x01010101L;

    if (OPTSIZ > 4) {
        // 64-bit architecture, extend magic numbers.
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }

    for (;;) {
        op_t lw = *op_t_ptr++;

        // This condition is the magic behind the optimization. It detects NULL bytes in 32/64-bit
        // words (depending on the CPU architecture). Instead of checking each byte individually, this
        // approach allows scanning multiple bytes (word-sized chunks) at once, significantly
        // reducing the number of checks needed.
        //
        // A written explanation can only do so much - if you still do not understand what is going on here,
        // take a pen and paper and calculate it by hand a few times, with numbers that do/do not contain null bytes.
        // It will help you see the pattern.
        //
        // Step-by-step explanation:
        // 1. `(lw - lomagic)`
        //    - `lomagic` is `0x01010101...`, where each byte is `0x01`.
        //    - Subtracting `lomagic` from `lw` decreases each byte in `lw` by 1.
        //    - If a byte in `lw` was `0x00`, it underflows to `0xFF`.
        //
        // 2. `~lw`
        //    - Bitwise NOT of `lw`. Bytes with `0x00` in `lw` become `0xFF`.
        //
        // 3. `& ~lw & himagic`
        //    - `himagic` is `0x80808080...`, where the most significant bit (MSB) of each byte
        //      is set.
        //    - This step isolates bytes in `lw` where:
        //      a. Subtraction resulted in `0xFF` (from the null byte in `lw`).
        //      b. The MSB is set due to the underflow.
        //    - When a match is found, the condition evaluates to true.
        //
        // If this condition evaluates to true, we know a null byte exists in the current word. To find
        // its exact position, we iterate over it until we find the null byte.
        if (((lw - lomagic) & ~lw & himagic) != 0) {
            const char *char_block_ptr = (const char *)(op_t_ptr - 1);

            if (char_block_ptr[0] == '\0') {
                return char_block_ptr - str;
            } else if (char_block_ptr[1] == '\0') {
                return char_block_ptr + 1 - str;
            } else if (char_block_ptr[2] == '\0') {
                return char_block_ptr + 2 - str;
            } else if (char_block_ptr[3] == '\0') {
                return char_block_ptr + 3 - str;
            }

#if __SIZEOF_POINTER == 8
            if (char_block_ptr[4] == '\0') {
                return char_block_ptr + 4 - str;
            } else if (char_block_ptr[5] == '\0') {
                return char_block_ptr + 5 - str;
            } else if (char_block_ptr[6] == '\0') {
                return char_block_ptr + 6 - str;
            } else if (char_block_ptr[7] == '\0') {
                return char_block_ptr + 7 - str;
            }
#endif
        }
    }
}

char *
ft_substr(char const *str, unsigned int start, size_t len) {
    char *dest;
    size_t str_len = ft_strlen(str);

    if (start >= str_len) {
        return (ft_calloc(1, sizeof(char)));
    }

    if (str_len + start < len) {
        len = str_len + start;
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

char *
ft_strnstr(const char *haystack, const char *needle, size_t n_bytes) {
    size_t h_idx = 0;
    size_t n_idx = 0;

    if (needle[0] == '\0') {
        return (char *)haystack;
    }

    while (h_idx < n_bytes && haystack[h_idx]) {

        if (haystack[h_idx] == needle[n_idx]) {
            if (needle[n_idx + 1] == '\0') {
                return ((char *)haystack + h_idx - n_idx);
            }
            n_idx++;
        } else {
            h_idx -= n_idx;
            n_idx = 0;
        }

        h_idx++;
    }
    return NULL;
}

char *
ft_tolower(char *str) {
    for (size_t idx = 0; str[idx]; ++idx) {
        str[idx] = (str[idx] <= 'Z' && str[idx] >= 'A') ? str[idx] + 32 : str[idx];
    }
    return str;
}

char *
ft_toupper(char *str) {
    for (size_t idx = 0; str[idx]; ++idx) {
        str[idx] = (str[idx] <= 'z' && str[idx] >= 'a') ? str[idx] - 32 : str[idx];
    }
    return str;
}

typedef bool (*ConversionFunc)(const char *nptr, int base, void *out_value, bool negative);

__attribute__((always_inline)) static inline bool
convert_unsigned(const char *nptr, int base, void *out_value, bool negative) {
    if (negative) {
        errno = EINVAL;
        return false;
    }

    uintmax_t result = 0;

    while (*nptr) {
        int digit;
        if (*nptr >= '0' && *nptr <= '9') {
            digit = *nptr - '0';
        } else if (*nptr >= 'a' && *nptr <= 'f') {
            digit = *nptr - 'a' + 10;
        } else if (*nptr >= 'A' && *nptr <= 'F') {
            digit = *nptr - 'A' + 10;
        } else {
            break;
        }

        if (digit >= base) {
            break;
        }

        result = result * base + digit;
        nptr++;
    }

    if (result <= UINT8_MAX) {
        *(uint8_t *)out_value = (uint8_t)result;
    } else if (result <= UINT16_MAX) {
        *(uint16_t *)out_value = (uint16_t)result;
    } else if (result <= UINT32_MAX) {
        *(uint32_t *)out_value = (uint32_t)result;
    } else if (result <= UINT64_MAX) {
        *(uint64_t *)out_value = (uint64_t)result;
    } else {
        errno = ERANGE;
        return false;
    }

    return true;
}

__attribute__((always_inline)) static inline bool
convert_signed(const char *nptr, int base, void *out_value, bool negative) {
    intmax_t result = 0;
    while (*nptr) {
        int digit;
        if (*nptr >= '0' && *nptr <= '9') {
            digit = *nptr - '0';
        } else if (*nptr >= 'a' && *nptr <= 'f') {
            digit = *nptr - 'a' + 10;
        } else if (*nptr >= 'A' && *nptr <= 'F') {
            digit = *nptr - 'A' + 10;
        } else {
            break;
        }

        if (digit >= base) {
            break;
        }

        result = result * base + digit;
        nptr++;
    }

    if (negative) {
        result = -result;
    }

    if (result >= INT8_MIN && result <= INT8_MAX) {
        *(int8_t *)out_value = (int8_t)result;
    } else if (result >= INT16_MIN && result <= INT16_MAX) {
        *(int16_t *)out_value = (int16_t)result;
    } else if (result >= INT32_MIN && result <= INT32_MAX) {
        *(int32_t *)out_value = (int32_t)result;
    } else if (result >= INT64_MIN && result <= INT64_MAX) {
        *(int64_t *)out_value = (int64_t)result;
    } else {
        errno = ERANGE;
        return false;
    }

    return true;
}

bool
ft_atob(const char *nptr, int base, int bits, void *out_value, bool is_signed) {
    if (!nptr || base < 2 || base > 16 || (bits != 8 && bits != 16 && bits != 32 && bits != 64)) {
        errno = EINVAL;
        return false;
    }

    while (*nptr == ' ' || *nptr == '\t') {
        nptr++;
    }

    bool negative = *nptr == '-';
    if (*nptr == '+' || *nptr == '-') {
        nptr++;
    }

    if (base == 0) {
        if (*nptr == '0') {
            nptr++;
            base = (*nptr == 'x' || *nptr == 'X') ? 16 : 8;
            if (base == 16 && *nptr == 'x') {
                nptr++;
            }
        } else {
            base = 10;
        }
    }

    ConversionFunc convert = is_signed ? convert_signed : convert_unsigned;

    return convert(nptr, base, out_value, negative);
}

__attribute__((always_inline)) static inline bool
convert_unsigned_to_str(uintmax_t value, int base, char *buffer, size_t buffer_size, bool uppercase) {
    if (base < 2 || base > 16 || !buffer || buffer_size == 0) {
        errno = EINVAL;
        return false;
    }

    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

    char tmp[65];
    size_t idx = 0;

    do {
        if (idx >= sizeof(tmp) - 1) {
            errno = ERANGE;
            return false;
        }
        tmp[idx++] = digits[value % base];
        value /= base;
    } while (value > 0);

    if (idx >= buffer_size) {
        errno = ERANGE;
        return false;
    }

    for (size_t i = 0; i < idx; ++i) {
        buffer[i] = tmp[idx - i - 1];
    }
    buffer[idx] = '\0';
    return true;
}

__attribute__((always_inline)) static inline bool
convert_signed_to_str(intmax_t value, int base, char *buffer, size_t buffer_size, bool uppercase) {
    if (base < 2 || base > 16 || !buffer || buffer_size == 0) {
        errno = EINVAL;
        return false;
    }

    bool negative = value < 0;
    uintmax_t abs_value = negative ? -(uintmax_t)value : (uintmax_t)value;

    if (!convert_unsigned_to_str(abs_value, base, buffer, buffer_size, uppercase)) {
        return false;
    }

    if (negative) {
        size_t len = ft_strlen(buffer);
        if (len + 1 >= buffer_size) {
            errno = ERANGE;
            return false;
        }
        ft_memcpy(buffer + 1, buffer, len + 1);
        buffer[0] = '-';
    }

    return true;
}

bool
ft_btoa(void *value, int base, int bits, char *buffer, size_t buffer_size, bool is_signed, bool uppercase) {
    if (!value || !buffer || buffer_size == 0 || base < 2 || base > 16 || (bits != 8 && bits != 16 && bits != 32 && bits != 64)) {
        errno = EINVAL;
        return false;
    }

    if (is_signed) {
        switch (bits) {
        case 8:
            return convert_signed_to_str(*(int8_t *)value, base, buffer, buffer_size, uppercase);
        case 16:
            return convert_signed_to_str(*(int16_t *)value, base, buffer, buffer_size, uppercase);
        case 32:
            return convert_signed_to_str(*(int32_t *)value, base, buffer, buffer_size, uppercase);
        case 64:
            return convert_signed_to_str(*(int64_t *)value, base, buffer, buffer_size, uppercase);
        }
    } else {
        switch (bits) {
        case 8:
            return convert_unsigned_to_str(*(uint8_t *)value, base, buffer, buffer_size, uppercase);
        case 16:
            return convert_unsigned_to_str(*(uint16_t *)value, base, buffer, buffer_size, uppercase);
        case 32:
            return convert_unsigned_to_str(*(uint32_t *)value, base, buffer, buffer_size, uppercase);
        case 64:
            return convert_unsigned_to_str(*(uint64_t *)value, base, buffer, buffer_size, uppercase);
        }
    }

    errno = EINVAL;
    return false;
}
