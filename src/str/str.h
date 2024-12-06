#ifndef STR_H
#define STR_H

#include <stddef.h>
#include <stdbool.h>

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

// Returns a pointer to the first occurrence of `needle` in the first `n_bytes` of
// `haystack`. Returns a NULL pointer if nothing is found.
//
// Safety:
// It is the caller's responsiblity to ensure that `needle` and `haystack` are valid strings terminated by
// `\0` characters. Failure to do so will result in invalid memory access.
char *ft_strnstr(const char *haystack, const char *needle, size_t n_bytes);

// Converts all characters in `str` to lowercase.
//
// Safety:
// It is the caller's responsiblity to ensure that `str` is a valid string terminated by a
// `\0` character. Failure to do so will result in invalid memory access.
char *ft_tolower(char *str);

// Converts all characters in `str` to uppercase.
//
// Safety:
// It is the caller's responsiblity to ensure that `str` is a valid string terminated by a
// `\0` character. Failure to do so will result in invalid memory access.
char *ft_toupper(char *str);

// Converts a byte array `nptr` of base `base` into a `bits` bits `is_signed` integer, and stores the
// result into `out_value`.
//
// Parameters:
// - `nptr`: Pointer to the null-terminated input string representing the number to be converted.
// - `base`: The numeric base to interpret the input string (2–16).
// - `bits`: The target bit size of the output value (8, 16, 32, or 64).
// - `out_value`: Pointer to the output memory where the converted value will be stored.
// - `is_signed`: Indicates whether the output value should be treated as signed (true) or unsigned (false).
//
// Returns:
// - `true` if the conversion was successful, and `out_value` contains the result.
// - `false` if an error occurred, setting `errno` appropriately.
//
// Errors:
// - `EINVAL`: Invalid input parameters (e.g., invalid base or bits).
// - `ERANGE`: Overflow or underflow occurred during the conversion.
//
// Safety:
// It is the caller's responsibility to ensure that all values passed are correct. Failure
// to do so may result in undefined behavior.
bool ft_atob(const char *nptr, int base, int bits, void *out_value, bool is_signed);

// Converts a numeric value stored in `value` into a string representation in the specified `base`,
// and stores the result into the `buffer`.
//
// Parameters:
// - `value`: Pointer to the numeric value to convert. Must point to an integer of `bits` bits.
// - `base`: The numeric base for the output string (2–16).
// - `bits`: The bit size of the input value (8, 16, 32, or 64).
// - `buffer`: Pointer to a character buffer where the resulting string will be stored.
// - `buffer_size`: The size of the `buffer`. Must be large enough to store the result plus the null terminator.
// - `is_signed`: Indicates whether the input value should be treated as signed (true) or unsigned (false).
// - `uppercase`: Indicated whether letters in base > 10 values should be printed in uppercase format (true) or lowercase format (false).
//
// Returns:
// - `true` if the conversion was successful, and `buffer` contains the result as a null-terminated string.
// - `false` if an error occurred, setting `errno` appropriately.
//
// Errors:
// - `EINVAL`: Invalid input parameters (e.g., invalid base, bits, or null pointers).
// - `ERANGE`: The result string did not fit into `buffer_size`.
//
// Notes:
// - The caller must ensure that the `buffer` is large enough to hold the result. For example, a base 2
//   representation of a 64-bit integer requires up to 65 characters (64 digits + null terminator).
//
// Safety:
// The caller must ensure that the `buffer` is large enough to hold the result. For example, a base 2
// representation of a 64-bit integer requires up to 65 characters (64 digits + null terminator).
bool ft_btoa(void *value, int base, int bits, char *buffer, size_t buffer_size, bool is_signed, bool uppercase);

#endif