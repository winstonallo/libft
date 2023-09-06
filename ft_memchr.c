/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:27:55 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/06 12:44:49 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*asd;

	asd = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (asd[i] == c)
			return ((void *)s + (i * sizeof(unsigned char)));
		i++;
	}
	return (0);
}
