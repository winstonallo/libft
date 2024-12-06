#ifndef STR_H
#define STR_H

#include <stddef.h>

size_t ft_strlen(const char *str);
char *ft_substr(char const *str, unsigned int start, size_t len);
char *ft_strtrim(char const *str, char const *set);
char *ft_strjoin(char *a, char *b);
char **ft_split(char const *str, char delimiter);

#endif