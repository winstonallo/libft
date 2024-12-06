#include "mem.h"
#include "str.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define FT_PRINTF_BUFSIZ 256

static ssize_t
distribute_args(int fd, const char *s, void *arg) {
    char buf[32];
    ssize_t result = 0;

    if (*s == 's') {
        char *str = (char *)arg;
        result = write(fd, str, ft_strlen(str));
    } else if (*s == 'c') {
        char c = *(char *)arg;
        result = write(fd, &c, 1);
    } else if (*s == 'p') {
        void *ptr = (void *)&arg;
        uint64_t addr = (uint64_t)ptr;
        if (addr) {
            ft_memcpy(buf, "0x", 2);
            ft_btoa((void *)&addr, 16, 64, buf + 2, 32, false, false);
            result = write(fd, buf, ft_strlen(buf));
        } else {
            result = write(fd, "(nil)", 5);
        }
    } else if (*s == 'd' || *s == 'i') {
        int32_t *value = (int *)&arg;
        ft_btoa(value, 10, 32, buf, 32, true, false);
        result = write(fd, buf, ft_strlen(buf));
    } else if (*s == 'u') {
        uint32_t *value = (uint32_t *)&arg;
        ft_btoa(value, 10, 32, buf, 32, false, false);
        result = write(fd, buf, ft_strlen(buf));
    } else if (*s == 'x') {
        uint32_t *value = (uint32_t *)&arg;
        ft_btoa(value, 16, 32, buf, 32, false, false);
        result = write(fd, buf, ft_strlen(buf));
    } else if (*s == 'X') {
        uint32_t *value = (uint32_t *)&arg;
        ft_btoa(value, 16, 32, buf, 32, false, true);
        result = write(fd, buf, ft_strlen(buf));
    }

    return result;
}

ssize_t
ft_printf(int fd, const char *s, ...) {
    ssize_t bytes_written = 0;

    if (!s) {
        return (-1);
    }

    va_list args;
    va_start(args, s);

    char buf[FT_PRINTF_BUFSIZ];
    uint16_t buf_idx = 0;

    while (*s) {
        if (*s == '%') {
            s++;

            if (ft_memsrch("cspdiuxX", *s, 8)) {
                bytes_written += write(fd, buf, buf_idx);
                buf_idx = 0;
                bytes_written += distribute_args(fd, s, va_arg(args, void *));
            } else if (*s == '%') {
                buf[buf_idx++] = '%';
                if (buf_idx >= FT_PRINTF_BUFSIZ - 1) {
                    bytes_written += write(fd, buf, buf_idx);
                    buf_idx = 0;
                }
            }

        } else {
            buf[buf_idx++] = *s;
            if (buf_idx >= FT_PRINTF_BUFSIZ - 1) {
                bytes_written += write(fd, buf, buf_idx);
                buf_idx = 0;
            }
        }
        s++;
    }
    va_end(args);

    if (buf_idx > 0) {
        bytes_written += write(fd, buf, buf_idx);
    }

    return bytes_written;
}
