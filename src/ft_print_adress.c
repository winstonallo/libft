/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:13:48 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/08 16:40:23 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*ft_fill_string(unsigned long n, int *strlen)
{
	int				i;
	unsigned long	temp;
	char			*str;

	i = 0;
	temp = n;
	while (temp != 0)
	{
		temp = temp / 16;
		i++;
	}
	str = ft_calloc(i + 1, sizeof(char));
	*strlen = i - 1;
	return (str);
}

int	ft_print_adress(unsigned long n, int font)
{
	unsigned long	temp;
	char			*res;
	int				i;
	int				*iptr;

	iptr = &i;
	temp = n;
	res = ft_fill_string(n, iptr);
	if (!res)
		return (0);
	while (temp != 0 && i-- >= 0)
	{
		if ((temp % 16) < 10)
			res[i + 1] = (temp % 16) + '0';
		else
			res[i + 1] = (temp % 16) + font;
		temp = temp / 16;
	}
	i = ft_strlen(res);
	i += ft_putstr_int("0x");
	ft_putstr_fd(res, 1);
	free(res);
	if (n == 0)
		i += ft_putchar_int('0');
	return (i);
}
