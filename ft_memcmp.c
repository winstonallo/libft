/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:15:18 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/05 12:19:23 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*s11;
	unsigned char		*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	while ((s11[i] != '\0' || s22[i] != '\0') && i <= n)
	{
		if (s11[i] != s22[i])
		{
			if (s11[i] - s22[i] > 0)
				return (1);
			else if (s11[i] - s22[i] < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}