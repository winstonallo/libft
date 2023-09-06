/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:37 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/06 15:07:23 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_int_length(int n)
{
	int	length;

	length = 0;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	else
		return (nb * (ft_recursive_power(nb, power - 1)));
}

char	*ft_itoa(int n)
{
	long	ln;
	long	divider;
	int		i;
	char	*res;

	i = 0;
	ln = n;
	res = malloc((ft_get_int_length(n) + 1) * (sizeof(char)));
	if (n < 0)
	{
		res[i] = '-';
		ln = -ln;
		i++;
	}
	divider = ft_recursive_power(10, ft_get_int_length(n) - 1);
	while (divider)
	{
		res[i] = ln / divider + 48;
		i++;
		ln = ln % divider;
		divider = divider / 10;
	}
	res[i] = '\0';
	return (res);
}