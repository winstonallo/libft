/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/07 18:52:50 by abied-ch         ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	long	ln;
	size_t	i;
	char	*res;

	i = ft_get_int_length(n);
	ln = n;
	if (n < 0)
	{
		ln = -ln;
		i++;
	}
	res = malloc((i + 1) * (sizeof(char)));
	if (res == NULL)
		return (NULL);
	*(res + i) = 0;
	while (i--)
	{
		*(res + i) = ln % 10 + 48;
		ln = ln / 10;
	}
	if (n < 0)
		*(res + 0) = '-';
	return (res);
}
