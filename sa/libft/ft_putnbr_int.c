/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:15:08 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/21 12:50:28 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_int_length(int n)
{
	int	length;

	if (n == 0)
		return (1);
	length = 0;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

static char	*ft_allocate_room(int i)
{
	char	*s;

	s = malloc((i + 1) * (sizeof(char)));
	if (s == NULL)
		return (0);
	return (s);
}

int	ft_putnbr_int(int n)
{
	long	ln;
	size_t	i;
	char	*res;
	int		len;

	i = ft_get_int_length(n);
	ln = n;
	if (n < 0)
	{
		ln = -ln;
		i++;
	}
	len = i;
	res = ft_allocate_room(i);
	*(res + i) = 0;
	while (i--)
	{
		*(res + i) = ln % 10 + 48;
		ln = ln / 10;
	}
	if (n < 0)
		*(res + 0) = '-';
	ft_putstr_fd(res, 1);
	free(res);
	return (len);
}
