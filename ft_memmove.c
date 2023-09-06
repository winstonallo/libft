/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:01:20 by abied-ch          #+#    #+#             */
/*   Updated: 2023/09/06 16:56:50 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*csrc;
	char		*cdst;

	cdst = dest;
	csrc = src;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		while (n != 0)
		{
			cdst[n] = csrc[n];
			n--;
		}
	}
	return (dest);
}
