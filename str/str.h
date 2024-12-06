#ifndef STR_H
#define STR_H

#include <stddef.h>

// Returns the number of bytes between `str` and the next `\0` character.
//
// Safety:
// It is the caller's responsiblity to ensure that `str` is a valid string terminated by a
// `\0` character. Failure to do so will result in invalid memory access.
size_t ft_strlen(const char *str);

// Returns a heap-allocated duplicate of `str[start..start + len]`.
//
// Safety:
// It is the caller's responsiblity to ensure that `str` is a valid string terminated by a
// `\0` character. Failure to do so will result in invalid memory access.
char *ft_substr(char const *str, unsigned int start, size_t len);

// Allocates and returns a new string with characters specified in `set` removed
// from the beginning and end of the input string `str`
//
// Safety:
// It is the caller's responsiblity to ensure that `str` and `set` are valid strings terminated by
// `\0` characters. Failure to do so will result in invalid memory access.
char *ft_strtrim(char const *str, char const *set);

// Allocates and returns a string built by concatenating `a` and `b`.
//
// Safety:
// It is the caller's responsiblity to ensure that `a` and `b` are valid strings terminated by
// `\0` characters. Failure to do so will result in invalid memory access.
char *ft_strjoin(char *a, char *b);

// Allocates and returns an array of strings built by splitting `str` by `delimiter`.
//
// Safety:
// It is the caller's responsiblity to ensure that `str` is a valid string terminated by a
// `\0` character. Failure to do so will result in invalid memory access.
char **ft_split(char const *str, char delimiter);

#endif