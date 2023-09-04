/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:21:27 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/04 17:46:25 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, unsigned long long n)
{
	const unsigned char	*s;
	unsigned char		*d;
	unsigned long long	i;

	s = src;
	i = 0;
	d = dest;

	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

