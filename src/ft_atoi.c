/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:48:41 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/08 16:38:22 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

long	ft_atoi(const char *nptr)
{
	long	sign;
	long	base;
	long	i;

	sign = 1;
	base = 0;
	i = 0;
	while (nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		sign = 1 - 2 * (nptr[i++] == '-');
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (base > 2147483647 / 10
			|| (base == 2147483647 / 10 && nptr[i] - '0' > 7))
		{
			if (sign == 1)
				return (2147483648);
		}
		base = 10 * base + (nptr[i++] - '0');
		if (base < -2147483648)
			return (-2147483649);
	}
	return (base * sign);
}
