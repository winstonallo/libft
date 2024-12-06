#include <stdbool.h>

bool
ft_isascii(int c) {
    return c <= 127 && c >= 0;
}

bool
ft_isprint(int c) {
    return c > 31 && c < 127;
}

bool
ft_isdigit(int c) {
    return c >= '0' && c <= '9';
}

bool
ft_isalpha(int c) {
    return (c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A');
}

bool
ft_isalnum(int c) {
    return ft_isalpha(c) || ft_isdigit(c);
}
