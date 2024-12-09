#include "mem.h"
#include "str.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// File system block size.
// Set in the Makefile at compile time with `-DFS_BLOCK_SIZE=$(stat -fc %s .)`.
#ifndef FS_BLOCK_SIZE
#define FS_BLOCK_SIZE 4096
#endif

static void
flush_if_full(const char *const buf, uint16_t *idx, size_t len_to_write, ssize_t *result, int fd) {
    if (*idx + len_to_write >= FS_BLOCK_SIZE) {
        *result = write(fd, buf, *idx);
        *idx = 0;
    }
}

static void
write_to_buf(char *const buf, const char *const src, size_t len, uint16_t *idx, int fd) {
    ssize_t result = 0;
    flush_if_full(buf, idx, len, &result, fd);

    ft_memcpy(buf + *idx, src, len);
    *idx += (result + len);
}

static ssize_t
distribute_args(int fd, const char *s, void *arg, char *buf, uint16_t *idx) {
    ssize_t result = 0;

    if (*s == 's') {

        char *str = (char *)arg;
        write_to_buf(buf, str, ft_strlen(str), idx, fd);

    } else if (*s == 'c') {

        char c = *(char *)arg;
        write_to_buf(buf, &c, 1, idx, fd);

    } else if (*s == 'p') {

        void *ptr = (void *)&arg;
        uint64_t addr = (uint64_t)ptr;
        char address_buf[19];

        if (addr) {
            ft_memcpy(address_buf, "0x", 2);
            ft_btoa((void *)&addr, 16, 64, address_buf + 2, 32, false, false);
        } else {
            ft_memcpy(address_buf + *idx, "(nil)\0", 6);
        }

        write_to_buf(buf, address_buf, ft_strlen(address_buf), idx, fd);

    } else if (*s == 'd' || *s == 'i') {

        int32_t *value = (int32_t *)&arg;
        char num_buf[32];
        ft_btoa(value, 10, 32, num_buf, 32, true, false);

        write_to_buf(buf, num_buf, ft_strlen(num_buf), idx, fd);

    } else if (*s == 'u') {

        char num_buf[32];
        uint32_t *value = (uint32_t *)&arg;
        ft_btoa(value, 10, 32, num_buf, 32, false, false);
        write_to_buf(buf, num_buf, ft_strlen(num_buf), idx, fd);

    } else if (*s == 'x' || *s == 'X') {

        char num_buf[32];
        uint32_t *value = (uint32_t *)&arg;
        ft_btoa(value, 16, 32, num_buf, 32, false, false);
        write_to_buf(buf, num_buf, ft_strlen(num_buf), idx, fd);
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

    char buf[FS_BLOCK_SIZE];
    uint16_t buf_idx = 0;

    while (*s) {
        if (*s == '%') {
            s++;

            if (ft_memsrch("cspdiuxX", *s, 8)) {
                bytes_written += distribute_args(fd, s, va_arg(args, void *), buf, &buf_idx);
            } else if (*s == '%') {
                buf[buf_idx++] = '%';
                if (buf_idx >= FS_BLOCK_SIZE - 1) {
                    bytes_written += write(fd, buf, buf_idx);
                    buf_idx = 0;
                }
                flush_if_full(buf, &buf_idx, 0, &bytes_written, fd);
            }

        } else {
            buf[buf_idx++] = *s;
            flush_if_full(buf, &buf_idx, 0, &bytes_written, fd);
        }
        s++;
    }
    va_end(args);

    if (buf_idx > 0) {
        bytes_written += write(fd, buf, buf_idx);
    }

    return bytes_written;
}
