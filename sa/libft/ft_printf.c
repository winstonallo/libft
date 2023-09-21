/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:28:51 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/21 14:59:21 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_distribute_args(const char *s, void *arg)
{
	int				i;
	unsigned long	ptr;

	i = 0;
	if (*s == 's')
		i += ft_putstr_int((char *) arg);
	if (*s == 'c')
		i += ft_putchar_int(*(char *) &arg);
	else if (*s == 'p')
	{
		ptr = (unsigned long) arg;
		if (ptr)
			i += ft_print_adress((unsigned long) arg, 87);
		else
			i += (ft_putstr_int("(nil)"));
	}
	else if (*s == 'd' || *s == 'i')
		i += ft_putnbr_int(*(int *) &arg);
	else if (*s == 'u')
		i += ft_putnbr_unsigned_int(*(int *) &arg);
	else if (*s == 'x')
		i += ft_puthex_int(*(int *) &arg, 87);
	else if (*s == 'X')
		i += ft_puthex_int(*(int *) &arg, 55);
	return (i);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;

	if (s == NULL)
		return (-1);
	i = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (ft_strchr("cspdiuxX", *s))
				i += ft_distribute_args(s, va_arg(args, void *));
			else if (*s == '%')
				i += ft_putchar_int('%');
		}
		else
			i += ft_putchar_int(*s);
		s++;
	}
	va_end(args);
	return (i);
}
