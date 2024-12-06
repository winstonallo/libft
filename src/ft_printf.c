/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:28:51 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/08 16:40:26 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int
ft_distribute_args(int fd, const char *s, void *arg) {
    int i;
    unsigned long ptr;

    i = 0;
    if (*s == 's')
        i += ft_putstr_int(fd, (char *)arg);
    if (*s == 'c')
        i += ft_putchar_int(fd, *(char *)&arg);
    else if (*s == 'p') {
        ptr = (unsigned long)arg;
        if (ptr)
            i += ft_print_adress(fd, (unsigned long)arg, 87);
        else
            i += (ft_putstr_int(fd, "(nil)"));
    } else if (*s == 'd' || *s == 'i')
        i += ft_putnbr_int(fd, *(int *)&arg);
    else if (*s == 'u')
        i += ft_putnbr_unsigned_int(fd, *(int *)&arg);
    else if (*s == 'x')
        i += ft_puthex_int(fd, *(int *)&arg, 87);
    else if (*s == 'X')
        i += ft_puthex_int(fd, *(int *)&arg, 55);
    return (i);
}

int
ft_printf(int fd, const char *s, ...) {
    va_list args;
    int i;

    if (s == NULL)
        return (-1);
    i = 0;
    va_start(args, s);
    while (*s) {
        if (*s == '%') {
            s++;
            if (ft_strchr("cspdiuxX", *s)) {
                i += ft_distribute_args(fd, s, va_arg(args, void *));
            } else if (*s == '%') {
                i += ft_putchar_int(fd, '%');
            }
        } else {
            i += ft_putchar_int(fd, *s);
        }
        s++;
    }
    va_end(args);
    return (i);
}
